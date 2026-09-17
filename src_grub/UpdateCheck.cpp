//---------------------------------------------------------------------------

#pragma hdrstop

#include "UpdateCheck.h"

#include <memory>
#include <System.JSON.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.HttpClientComponent.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Classes.hpp>

#include "GitVersion.h"
#include "UpdateSecrets.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace System::Net::Httpclient;
using namespace System::Net::Urlclient;

// GitHub API - той самий приватний репозиторій, з якого зібрана ця програма.
//
// ПРИМІТКА (2026-09-16): спочатку тут була ручна реалізація на "сирому"
// WinHTTP - технічно робоча (перевірено окремим тестом на цій же машині),
// але у польових умовах на кількох різних Windows-машинах (з різними
// антивірусами/HTTPS-фільтрами) WinHttpSendRequest стабільно проходив, а
// WinHttpReceiveResponse падав з ERROR_WINHTTP_INVALID_SERVER_RESPONSE
// (12152) - тобто TCP+TLS з'єднання з реальним IP GitHub встановлювалось
// (підтверджено діагностикою WINHTTP_OPTION_CONNECTION_INFO), але суворий
// парсер відповідей WinHTTP відмовлявся розбирати те, що повертав
// локальний HTTPS-перехоплювач. System.Net.HttpClient (THTTPClient) -
// той самий стек, яким користується сучасний RAD Studio код за замовчуванням -
// значно толерантніший до таких відповідей (аналогічно до того, чому
// PowerShell Invoke-WebRequest на тих самих машинах працював без проблем).
static const UnicodeString GH_OWNER_REPO = L"Segmalion/GRUBer2";
static const UnicodeString GH_API_HOST   = L"api.github.com";
static const int MAX_REDIRECT_HOPS = 5;
//---------------------------------------------------------------------------
static TNetHeaders makeHeaders(std::vector<std::pair<UnicodeString, UnicodeString>> pairs)
{
	TNetHeaders h;
	h.Length = (int)pairs.size();
	for (size_t i = 0; i < pairs.size(); i++)
		h[(int)i] = TNameValuePair(pairs[i].first, pairs[i].second);
	return h;
}
static TNetHeaders githubApiHeaders(UnicodeString accept)
{
	std::vector<std::pair<UnicodeString, UnicodeString>> pairs = {
		{L"Authorization", L"Bearer " + UnicodeString(GITHUB_UPDATE_TOKEN)},
		{L"Accept", accept},
		{L"X-GitHub-Api-Version", L"2022-11-28"}
	};
	return makeHeaders(pairs);
}
static UnicodeString findResponseHeader(const _di_IHTTPResponse &resp, UnicodeString name)
{
	TNetHeaders hdrs = resp->Headers;
	for (int i = 0; i < hdrs.Length; i++) {
		if (hdrs[i].Name.LowerCase() == name.LowerCase()) return hdrs[i].Value;
	}
	return UnicodeString();
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

	try {
		std::unique_ptr<TNetHTTPClient> client(new TNetHTTPClient(NULL));
		client->ConnectionTimeout = 15000;
		client->ResponseTimeout = 15000;
		client->HandleRedirects = true; // цей ендпоінт на сторонній хост не редиректить

		_di_IHTTPResponse resp = client->Get(url, NULL, githubApiHeaders(L"application/vnd.github+json"));
		int status = resp->StatusCode;

		if (status == 404) return false; // релізів ще немає - не помилка
		if (status == 401 || status == 403) {
			errMsg = L""; // токен протух/недійсний - тихий лог, без діалогу (див. Th_UpdateCheck)
			return false;
		}
		if (status != 200) { errMsg = L"Помилка сервера GitHub: " + UnicodeString(status); return false; }

		UnicodeString jsonText = resp->ContentAsString(TEncoding::UTF8);
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
	catch (Exception &e) {
		errMsg = L"Помилка мережі: " + e.Message;
		return false;
	}
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

	try {
		std::unique_ptr<TNetHTTPClient> client(new TNetHTTPClient(NULL));
		client->ConnectionTimeout = 15000;
		client->ResponseTimeout = 60000;
		// приватний ассет GitHub редиректить на підписаний blob-URL (Azure/S3) -
		// керуємо редиректом вручну, щоб НЕ передати туди GitHub-заголовок
		// Authorization (і взагалі жодних GitHub-специфічних заголовків)
		client->HandleRedirects = false;

		if (progressCb) progressCb(0, L"Завантаження оновлення...");

		TNetHeaders hdrs = githubApiHeaders(L"application/octet-stream");
		UnicodeString curUrl = url;
		_di_IHTTPResponse resp;
		int status = 0;
		int hop = 0;
		for (; hop < MAX_REDIRECT_HOPS; hop++) {
			resp = client->Get(curUrl, NULL, hdrs);
			status = resp->StatusCode;
			if (status == 301 || status == 302 || status == 303 || status == 307 || status == 308) {
				UnicodeString location = findResponseHeader(resp, L"Location");
				if (location.IsEmpty()) { errMsg = L"Редирект ассету без Location."; return false; }
				curUrl = location;
				hdrs = TNetHeaders(); // подальші хопи (не api.github.com) - без жодних заголовків
				continue;
			}
			break;
		}
		if (hop >= MAX_REDIRECT_HOPS) { errMsg = L"Забагато редиректів при завантаженні ассету."; return false; }
		if (status != 200) { errMsg = L"Помилка сервера при завантаженні ассету: " + UnicodeString(status); return false; }

		std::error_code ec;
		fs::create_directories(destPath.parent_path(), ec);
		{
			std::unique_ptr<TFileStream> outFile(new TFileStream(UnicodeString(destPath.c_str()), fmCreate));
			resp->ContentStream->Position = 0;
			outFile->CopyFrom(resp->ContentStream, 0);
		}

		if (progressCb) progressCb(100, L"Завантаження оновлення завершено (100%)");
		return true;
	}
	catch (Exception &e) {
		errMsg = L"Помилка мережі: " + e.Message;
		return false;
	}
}
//---------------------------------------------------------------------------
