//---------------------------------------------------------------------------

#pragma hdrstop

#include "UpdateCheck.h"

#include <winhttp.h>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <System.JSON.hpp>

#include "GitVersion.h"
#include "UpdateSecrets.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment(lib, "winhttp.lib")

// GitHub API - той самий приватний репозиторій, з якого зібрана ця програма
static const UnicodeString GH_OWNER_REPO = L"Segmalion/GRUBer2";
static const UnicodeString GH_API_HOST   = L"api.github.com";
static const int MAX_REDIRECT_HOPS = 5;
static const DWORD MAX_RESPONSE_BYTES = 4 * 1024 * 1024; // метаданих релізу вистачить з запасом

typedef std::vector<std::pair<UnicodeString, UnicodeString>> HttpHeaders;
//---------------------------------------------------------------------------
static UnicodeString formatBytes(uintmax_t bytes) {
	if (bytes < 1024) return UnicodeString((int)bytes) + " B";
	if (bytes < 1024 * 1024) return FloatToStrF(bytes / 1024.0, ffFixed, 4, 1) + " KB";
	if (bytes < 1024ull * 1024 * 1024) return FloatToStrF(bytes / 1048576.0, ffFixed, 4, 1) + " MB";
	return FloatToStrF(bytes / 1073741824.0, ffFixed, 4, 1) + " GB";
}
//---------------------------------------------------------------------------
// Один HTTP GET без автоматичного слідування за редиректом (WinHTTP
// налаштований на WINHTTP_OPTION_REDIRECT_POLICY_NEVER) - виклик сам вирішує,
// повторювати запит на outLocation, чи ні, і з якими заголовками (для
// приватних ассетів GitHub заголовок Authorization НЕ можна передавати на
// адресу редиректу - див. Update_DownloadAsset).
// streamToFile=false -> тіло відповіді збирається у outBody (обмежено
// MAX_RESPONSE_BYTES); streamToFile=true -> тіло пишеться одразу у destPath
// з прогресом через progressCb (для великих файлів-ассетів).
// peekOnly=true - лише статус+Location, тіло відповіді НЕ читається (навіть
// при статусі 200) - для проміжного "чи це редирект?" запиту на приватний
// ассет GitHub, щоб не тягнути вміст файлу в пам'ять лише заради перевірки.
static bool httpRequestOnce(const UnicodeString &url, const HttpHeaders &headers,
	int sendRecvTimeoutMs, DWORD &outStatus, UnicodeString &outLocation,
	bool streamToFile, const fs::path &destPath, short updateMs,
	std::atomic<bool> &cancelFlag, EsetDlProgressCb progressCb,
	std::string &outBody, UnicodeString &errMsg, bool peekOnly = false)
{
	outStatus = 0;
	outLocation = L"";

	::URL_COMPONENTS urlComp = {0};
	urlComp.dwStructSize = sizeof(urlComp);
	wchar_t hostName[256] = {0};
	wchar_t urlPath[2048] = {0};
	urlComp.lpszHostName = hostName;
	urlComp.dwHostNameLength = _countof(hostName);
	urlComp.lpszUrlPath = urlPath;
	urlComp.dwUrlPathLength = _countof(urlPath);

	if (!WinHttpCrackUrl(url.c_str(), url.Length(), 0, &urlComp)) {
		errMsg = L"Некоректний URL оновлення.";
		return false;
	}

	HINTERNET hSession = WinHttpOpen(L"GRUBer-Updater/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (!hSession) { errMsg = L"Не вдалось ініціалізувати WinHTTP."; return false; }
	WinHttpSetTimeouts(hSession, 5000, 5000, sendRecvTimeoutMs, sendRecvTimeoutMs);

	HINTERNET hConnect = WinHttpConnect(hSession, hostName, urlComp.nPort, 0);
	if (!hConnect) {
		errMsg = L"Не вдалось підключитись до сервера оновлень.";
		WinHttpCloseHandle(hSession);
		return false;
	}

	DWORD requestFlags = (urlComp.nScheme == INTERNET_SCHEME_HTTPS) ? WINHTTP_FLAG_SECURE : 0;
	HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", urlPath, NULL, WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES, requestFlags);
	if (!hRequest) {
		errMsg = L"Не вдалось створити HTTP-запит оновлення.";
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return false;
	}

	DWORD redirectPolicy = WINHTTP_OPTION_REDIRECT_POLICY_NEVER;
	WinHttpSetOption(hRequest, WINHTTP_OPTION_REDIRECT_POLICY, &redirectPolicy, sizeof(redirectPolicy));

	for (auto &h : headers) {
		UnicodeString line = h.first + L": " + h.second;
		WinHttpAddRequestHeaders(hRequest, line.c_str(), (DWORD)-1L, WINHTTP_ADDREQ_FLAG_ADD);
	}

	bool ok = false;
	if (WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) &&
		WinHttpReceiveResponse(hRequest, NULL))
	{
		DWORD dwSize = sizeof(outStatus);
		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
			WINHTTP_HEADER_NAME_BY_INDEX, &outStatus, &dwSize, WINHTTP_NO_HEADER_INDEX);

		if (outStatus == 301 || outStatus == 302 || outStatus == 303 ||
			outStatus == 307 || outStatus == 308)
		{
			wchar_t locBuf[2048] = {0};
			DWORD locSize = sizeof(locBuf);
			if (WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_LOCATION, WINHTTP_HEADER_NAME_BY_INDEX,
				locBuf, &locSize, WINHTTP_NO_HEADER_INDEX)) {
				outLocation = locBuf;
			}
			ok = true; // редирект - це не помилка транспорту, вирішує викликач
		}
		else if (peekOnly) {
			ok = true; // статус/заголовки вже отримано, тіло свідомо не читаємо
		}
		else if (!streamToFile) {
			std::vector<char> buffer(8192);
			DWORD bytesRead = 0;
			while (outBody.size() < MAX_RESPONSE_BYTES &&
				WinHttpReadData(hRequest, buffer.data(), (DWORD)buffer.size(), &bytesRead) && bytesRead > 0) {
				outBody.append(buffer.data(), bytesRead);
			}
			ok = true;
		}
		else {
			DWORD contentLength = 0;
			dwSize = sizeof(contentLength);
			WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER,
				WINHTTP_HEADER_NAME_BY_INDEX, &contentLength, &dwSize, WINHTTP_NO_HEADER_INDEX);

			if (outStatus == 200) {
				std::error_code ec;
				fs::create_directories(destPath.parent_path(), ec);
				std::ofstream outFile(destPath, std::ios::binary);
				if (outFile.is_open()) {
					std::vector<char> buffer(8192);
					DWORD bytesRead = 0;
					uintmax_t totalBytesRead = 0;
					bool cancelled = false;
					while (WinHttpReadData(hRequest, buffer.data(), (DWORD)buffer.size(), &bytesRead) && bytesRead > 0) {
						if (cancelFlag) { cancelled = true; break; }
						outFile.write(buffer.data(), bytesRead);
						totalBytesRead += bytesRead;
						if (progressCb) {
							int percent = (contentLength > 0) ? (int)((totalBytesRead * 100) / contentLength) : 0;
							UnicodeString phase = L"Завантаження оновлення: " + formatBytes(totalBytesRead) + " / "
								+ (contentLength > 0 ? formatBytes(contentLength) : UnicodeString(L"? MB"))
								+ L" (" + UnicodeString(percent) + L"%)";
							progressCb(percent, phase);
						}
					}
					outFile.close();
					if (cancelled) {
						errMsg = L"Ручна зупинка завантаження оновлення.";
						fs::remove(destPath, ec);
						ok = false;
					} else {
						if (progressCb) progressCb(100, L"Завантаження оновлення: " + formatBytes(totalBytesRead) + L" (100%)");
						ok = true;
					}
				} else {
					errMsg = L"Не вдалось створити файл " + UnicodeString(destPath.c_str());
				}
			} else {
				ok = true; // не 200 - тіло не тягнемо, статус розбере викликач
			}
		}
	} else {
		errMsg = L"Помилка мережі: " + UnicodeString((int)GetLastError());
	}

	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hSession);
	return ok;
}
//---------------------------------------------------------------------------
static HttpHeaders githubApiHeaders(UnicodeString accept)
{
	HttpHeaders h;
	h.push_back({L"Authorization", L"Bearer " + UnicodeString(GITHUB_UPDATE_TOKEN)});
	h.push_back({L"Accept", accept});
	h.push_back({L"X-GitHub-Api-Version", L"2022-11-28"});
	return h;
}
//---------------------------------------------------------------------------
bool Update_FetchLatestRelease(UpdateRelease &out, UnicodeString &errMsg)
{
	out = UpdateRelease();
	errMsg = L"";

	if (UnicodeString(GITHUB_UPDATE_TOKEN).IsEmpty()) {
		// перевірка оновлень тихо вимкнена - немає токена (UpdateSecrets.h з
		// шаблону/незаповнений) - НЕ помилка, errMsg лишається порожнім
		return false;
	}

	UnicodeString url = L"https://" + GH_API_HOST + L"/repos/" + GH_OWNER_REPO + L"/releases/latest";
	HttpHeaders headers = githubApiHeaders(L"application/vnd.github+json");

	DWORD status = 0; UnicodeString location; std::string body;
	std::atomic<bool> noCancel{false};
	int hop = 0;
	for (; hop < MAX_REDIRECT_HOPS; hop++) {
		body.clear();
		if (!httpRequestOnce(url, headers, 15000, status, location, false, fs::path(), 0,
			noCancel, nullptr, body, errMsg)) {
			return false; // errMsg вже заповнено - справжня мережева помилка
		}
		if (status == 301 || status == 302 || status == 303 || status == 307 || status == 308) {
			if (location.IsEmpty()) { errMsg = L"Редирект без Location."; return false; }
			url = location;
			continue;
		}
		break;
	}
	if (hop >= MAX_REDIRECT_HOPS) { errMsg = L"Забагато редиректів."; return false; }

	if (status == 404) return false; // релізів ще немає - не помилка
	if (status == 401 || status == 403) {
		errMsg = L""; // токен протух/недійсний - тихий лог, без діалогу (див. Th_UpdateCheck)
		return false;
	}
	if (status != 200) { errMsg = L"Помилка сервера GitHub: " + UnicodeString((int)status); return false; }

	UTF8String rawUtf8(body.c_str(), (int)body.size());
	UnicodeString jsonText = rawUtf8;
	std::unique_ptr<TJSONObject> root(dynamic_cast<TJSONObject*>(TJSONObject::ParseJSONValue(jsonText)));
	if (!root) { errMsg = L"Некоректна відповідь GitHub (JSON)."; return false; }

	auto getStr = [&root](UnicodeString key) -> UnicodeString {
		return root->Values[key] ? root->Values[key]->Value() : UnicodeString();
	};
	out.tagName = getStr(L"tag_name");
	out.name = getStr(L"name");
	out.body = getStr(L"body");
	out.publishedAt = getStr(L"published_at");

	TJSONArray *assetsArr = dynamic_cast<TJSONArray*>(root->Values[L"assets"]);
	if (assetsArr) {
		for (int i = 0; i < assetsArr->Count; i++) {
			TJSONObject *a = dynamic_cast<TJSONObject*>(assetsArr->Items[i]);
			if (!a) continue;
			UpdateAsset asset;
			asset.name = a->Values[L"name"] ? a->Values[L"name"]->Value() : UnicodeString();
			asset.id = a->Values[L"id"] ? StrToInt64Def(a->Values[L"id"]->Value(), 0) : 0;
			asset.size = a->Values[L"size"] ? StrToInt64Def(a->Values[L"size"]->Value(), 0) : 0;
			if (!asset.name.IsEmpty() && asset.id != 0) out.assets.push_back(asset);
		}
	}

	out.valid = !out.tagName.IsEmpty();
	return out.valid;
}
//---------------------------------------------------------------------------
bool Update_IsNewer(const UpdateRelease &rel, UnicodeString skipTag)
{
	if (!rel.valid) return false;
	if (rel.tagName == UnicodeString(GIT_COMMIT_HASH)) return false;
	if (!skipTag.IsEmpty() && rel.tagName == skipTag) return false;
	return true;
}
//---------------------------------------------------------------------------
bool Update_FindAsset(const UpdateRelease &rel, UnicodeString assetName, UpdateAsset &out)
{
	for (auto &a : rel.assets) {
		if (a.name == assetName) { out = a; return true; }
	}
	return false;
}
//---------------------------------------------------------------------------
bool Update_DownloadAsset(const UpdateAsset &asset, const fs::path &destPath, short updateMs,
	std::atomic<bool> &cancelFlag, EsetDlProgressCb progressCb, UnicodeString &errMsg)
{
	if (UnicodeString(GITHUB_UPDATE_TOKEN).IsEmpty()) { errMsg = L""; return false; }

	UnicodeString url = L"https://" + GH_API_HOST + L"/repos/" + GH_OWNER_REPO +
		L"/releases/assets/" + IntToStr(asset.id);
	HttpHeaders ghHeaders = githubApiHeaders(L"application/octet-stream");
	HttpHeaders noAuthHeaders; // на редирект-хост (Azure/S3) НЕ передаємо Authorization/GitHub-заголовки

	bool first = true;
	std::string dummyBody;
	for (int hop = 0; hop < MAX_REDIRECT_HOPS; hop++) {
		DWORD status = 0; UnicodeString location;
		const HttpHeaders &hdrs = first ? ghHeaders : noAuthHeaders;
		// peekOnly=true - лише щоб дізнатись статус/Location, без витрати
		// трафіку на тіло відповіді (файл може бути кілька десятків МБ)
		bool ok = httpRequestOnce(url, hdrs, 60000, status, location,
			false, fs::path(), 0, cancelFlag, nullptr, dummyBody, errMsg, /*peekOnly*/ true);
		if (!ok) return false;

		if (status == 301 || status == 302 || status == 303 || status == 307 || status == 308) {
			if (location.IsEmpty()) { errMsg = L"Редирект ассету без Location."; return false; }
			url = location;
			first = false; // усі наступні хопи - вже НЕ api.github.com
			continue;
		}
		if (status != 200) { errMsg = L"Помилка сервера при завантаженні ассету: " + UnicodeString((int)status); return false; }

		// статус 200 підтверджено (тіло ще не читалось) - повторюємо запит
		// тим самим URL з streamToFile=true, щоб записати тіло у файл із
		// живим прогресом
		DWORD status2 = 0; UnicodeString loc2;
		return httpRequestOnce(url, hdrs, 60000, status2, loc2,
			true, destPath, updateMs, cancelFlag, progressCb, dummyBody, errMsg);
	}
	errMsg = L"Забагато редиректів при завантаженні ассету.";
	return false;
}
//---------------------------------------------------------------------------
