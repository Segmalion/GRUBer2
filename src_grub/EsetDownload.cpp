//---------------------------------------------------------------------------

#pragma hdrstop

#include "EsetDownload.h"

#include <winhttp.h>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <chrono>
#include <memory>

#include "RunApp.h"
#include "Dir.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment(lib, "winhttp.lib")

extern Dir curDir;

//---------------------------------------------------------------------------
static UnicodeString formatBytes(uintmax_t bytes) {
	if (bytes < 1024) return UnicodeString((int)bytes) + " B";
	if (bytes < 1024 * 1024) return FloatToStrF(bytes / 1024.0, ffFixed, 4, 1) + " KB";
	if (bytes < 1024ull * 1024 * 1024) return FloatToStrF(bytes / 1048576.0, ffFixed, 4, 1) + " MB";
	return FloatToStrF(bytes / 1073741824.0, ffFixed, 4, 1) + " GB";
}
//---------------------------------------------------------------------------
bool EsetDownload_DownloadFile(UnicodeString url, const fs::path &destPath,
	UnicodeString user, UnicodeString pass, short updateMs,
	std::atomic<bool> &cancelFlag, EsetDlProgressCb progressCb, UnicodeString &errMsg)
{
	::URL_COMPONENTS urlComp = {0};
	urlComp.dwStructSize = sizeof(urlComp);
	wchar_t hostName[256] = {0};
	wchar_t urlPath[2048] = {0};
	urlComp.lpszHostName = hostName;
	urlComp.dwHostNameLength = _countof(hostName);
	urlComp.lpszUrlPath = urlPath;
	urlComp.dwUrlPathLength = _countof(urlPath);

	if (!WinHttpCrackUrl(url.c_str(), url.Length(), 0, &urlComp)) {
		errMsg = L"Некоректний URL завантаження бази ESET.";
		return false;
	}

	std::error_code ec;
	fs::create_directories(destPath.parent_path(), ec);

	bool success = false;
	HINTERNET hSession = WinHttpOpen(L"GRUBer ESET Downloader/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (!hSession) { errMsg = L"Не вдалось ініціалізувати WinHTTP."; return false; }

	HINTERNET hConnect = WinHttpConnect(hSession, hostName, urlComp.nPort, 0);
	if (!hConnect) {
		errMsg = L"Не вдалось підключитись до сервера.";
		WinHttpCloseHandle(hSession);
		return false;
	}

	DWORD requestFlags = (urlComp.nScheme == INTERNET_SCHEME_HTTPS) ? WINHTTP_FLAG_SECURE : 0;
	HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", urlPath, NULL, WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES, requestFlags);
	if (!hRequest) {
		errMsg = L"Не вдалось створити HTTP-запит.";
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return false;
	}

	if (!user.IsEmpty() && !pass.IsEmpty())
		WinHttpSetCredentials(hRequest, WINHTTP_AUTH_TARGET_SERVER, WINHTTP_AUTH_SCHEME_BASIC,
			user.c_str(), pass.c_str(), NULL);

	if (WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) &&
		WinHttpReceiveResponse(hRequest, NULL)) {

		DWORD statusCode = 0, dwSize = sizeof(statusCode);
		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
			WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &dwSize, WINHTTP_NO_HEADER_INDEX);

		if (statusCode == 200) {
			DWORD contentLength = 0;
			dwSize = sizeof(contentLength);
			WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER,
				WINHTTP_HEADER_NAME_BY_INDEX, &contentLength, &dwSize, WINHTTP_NO_HEADER_INDEX);

			// файл вже повністю завантажено раніше - докачка не потрібна
			if (contentLength > 0 && fs::exists(destPath, ec) && fs::file_size(destPath, ec) == contentLength) {
				if (progressCb) progressCb(100, L"Завантаження: " + formatBytes(contentLength) + " / "
					+ formatBytes(contentLength) + " (100%)");
				success = true;
			} else {
				std::ofstream outFile(destPath, std::ios::binary);
				if (outFile.is_open()) {
					std::vector<char> buffer(8192);
					DWORD bytesRead = 0;
					uintmax_t totalBytesRead = 0;
					auto lastUpdate = std::chrono::steady_clock::now();
					uintmax_t bytesSinceLastUpdate = 0;
					std::deque<double> speedHistory;
					const size_t speedWindow = 7;
					bool cancelled = false;

					while (WinHttpReadData(hRequest, buffer.data(), (DWORD)buffer.size(), &bytesRead) && bytesRead > 0) {
						if (cancelFlag) { cancelled = true; break; }
						outFile.write(buffer.data(), bytesRead);
						totalBytesRead += bytesRead;
						bytesSinceLastUpdate += bytesRead;

						auto now = std::chrono::steady_clock::now();
						auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();
						if (elapsedMs >= updateMs || totalBytesRead == contentLength) {
							if (elapsedMs > 0) {
								double speedBps = (double)bytesSinceLastUpdate / elapsedMs * 1000.0;
								speedHistory.push_back(speedBps);
								if (speedHistory.size() > speedWindow) speedHistory.pop_front();
							}
							// медіана останніх вимірів згладжує стрибки швидкості між чанками
							double medianSpeed = 0.0;
							if (!speedHistory.empty()) {
								std::deque<double> sorted = speedHistory;
								std::sort(sorted.begin(), sorted.end());
								medianSpeed = sorted[sorted.size() / 2];
							}
							int percent = (contentLength > 0) ? (int)((totalBytesRead * 100) / contentLength) : 0;
							UnicodeString phase = L"Завантаження: " + formatBytes(totalBytesRead) + " / "
								+ (contentLength > 0 ? formatBytes(contentLength) : UnicodeString("? MB"))
								+ " (" + formatBytes((uintmax_t)medianSpeed) + "/s, " + UnicodeString(percent) + "%)";
							if (progressCb) progressCb(percent, phase);
							lastUpdate = now;
							bytesSinceLastUpdate = 0;
						}
					}
					outFile.close();

					if (cancelled) {
						errMsg = L"Ручна зупинка завантаження.";
						fs::remove(destPath, ec);
					} else {
						if (contentLength == 0 && progressCb)
							progressCb(100, L"Завантаження: " + formatBytes(totalBytesRead) + " (100%)");
						success = true;
					}
				} else {
					errMsg = L"Не вдалось створити файл " + UnicodeString(destPath.c_str());
				}
			}
		} else {
			errMsg = L"Помилка сервера: " + UnicodeString((int)statusCode);
		}
	} else {
		errMsg = L"Помилка мережі: " + UnicodeString((int)GetLastError());
	}

	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hSession);
	return success;
}
//---------------------------------------------------------------------------
bool EsetDownload_ExtractArchive(const fs::path &archivePath, const fs::path &destDir,
	std::atomic<bool> &cancelFlag, UnicodeString &errMsg)
{
	std::error_code ec;
	fs::create_directories(destDir, ec);

	UnicodeString app32 = curDir.get_toolPath() + "\\7zip\\32\\7za.exe";
	UnicodeString app64 = curDir.get_toolPath() + "\\7zip\\64\\7za.exe";
	UnicodeString arg = "x -y \"" + UnicodeString(archivePath.c_str()) + "\" -o\"" + UnicodeString(destDir.c_str()) + "\"";

	RunApp unpack{app32, app64, arg};
	unpack.set_externalStop(&cancelFlag);
	unpack.run(true);
	if (unpack.checkErr()) { errMsg = unpack.resultString(); return false; }
	return true;
}
//---------------------------------------------------------------------------
// упаковка вмісту workDir\dll\* у zip через 7-Zip (workDir - робоча тека
// процесу, тож у архіві шлях зберігається саме як "dll\<файл>", що потім
// шукає BtnEsetUpdateClick)
static bool packZip(const fs::path &outZip, const fs::path &workDir,
	std::atomic<bool> &cancelFlag, UnicodeString &errMsg)
{
	UnicodeString app32 = curDir.get_toolPath() + "\\7zip\\32\\7za.exe";
	UnicodeString app64 = curDir.get_toolPath() + "\\7zip\\64\\7za.exe";
	UnicodeString arg = "a -tzip -y \"" + UnicodeString(outZip.c_str()) + "\" \"dll\\*\"";

	RunApp pack{app32, app64, arg};
	pack.set_dir(UnicodeString(workDir.c_str()));
	pack.set_externalStop(&cancelFlag);
	pack.run(true);
	if (pack.checkErr()) { errMsg = pack.resultString(); return false; }
	return true;
}
// пакування у tar, потім стиснення tar в zstd - симетрично до того, як
// BtnEsetUpdateClick розпаковує *.tar.zstd двома проходами 7-Zip
static bool packTarZstd(const fs::path &outTarZstd, const fs::path &workDir,
	std::atomic<bool> &cancelFlag, UnicodeString &errMsg)
{
	fs::path tarPath = outTarZstd;
	tarPath.replace_extension(""); // update_x64.tar.zstd -> update_x64.tar

	UnicodeString app32 = curDir.get_toolPath() + "\\7zip\\32\\7za.exe";
	UnicodeString app64 = curDir.get_toolPath() + "\\7zip\\64\\7za.exe";

	UnicodeString argTar = "a -ttar -y \"" + UnicodeString(tarPath.c_str()) + "\" \"dll\\*\"";
	RunApp packTar{app32, app64, argTar};
	packTar.set_dir(UnicodeString(workDir.c_str()));
	packTar.set_externalStop(&cancelFlag);
	packTar.run(true);
	if (packTar.checkErr()) { errMsg = packTar.resultString(); return false; }

	UnicodeString argZstd = "a -tzstd -y \"" + UnicodeString(outTarZstd.c_str()) + "\" \"" + UnicodeString(tarPath.c_str()) + "\"";
	RunApp packZstd{app32, app64, argZstd};
	packZstd.set_externalStop(&cancelFlag);
	packZstd.run(true);

	std::error_code ec;
	fs::remove(tarPath, ec);
	if (packZstd.checkErr()) { errMsg = packZstd.resultString(); return false; }
	return true;
}
//---------------------------------------------------------------------------
static bool isBeginU(const UnicodeString &s, const UnicodeString &prefix) {
	if (s.Length() < prefix.Length()) return false;
	return s.SubString(1, prefix.Length()) == prefix;
}
struct FileArchEntry { UnicodeString file, arch; };
// парсер update.ver: секції "[...]" з парами platform=/file=
static std::vector<FileArchEntry> parseUpdateVer(const fs::path &path) {
	std::vector<FileArchEntry> result;
	std::error_code ec;
	if (!fs::exists(path, ec)) return result;

	std::unique_ptr<TStringList> lines(new TStringList);
	lines->LoadFromFile(UnicodeString(path.c_str()), TEncoding::UTF8);

	for (int i = 0; i < lines->Count; i++) {
		if (!isBeginU(lines->Strings[i], "[")) continue;
		if (i + 1 >= lines->Count || !isBeginU(lines->Strings[i + 1], "platform=")) continue;

		UnicodeString archStr = lines->Strings[i + 1].SubString(10, lines->Strings[i + 1].Length() - 9);
		UnicodeString fileStr;
		for (int j = i + 2; j < i + 20 && j < lines->Count; j++) {
			if (isBeginU(lines->Strings[j], "[")) break;
			if (isBeginU(lines->Strings[j], "file=")) {
				fileStr = lines->Strings[j].SubString(6, lines->Strings[j].Length() - 5);
				break;
			}
		}
		if (!fileStr.IsEmpty()) result.push_back({fileStr, archStr});
	}
	return result;
}
// шукає в unpackedDir теку dll, що містить update.ver (структура архіву
// update_full.zip буває вкладена на різну глибину)
static bool findDllDirWithUpdateVer(const fs::path &searchRoot, fs::path &outDllDir) {
	std::error_code ec;
	fs::path candidate = searchRoot;
	for (auto const &entry : fs::recursive_directory_iterator(searchRoot, ec)) {
		if (entry.is_directory() && entry.path().filename() == L"dll") {
			candidate = entry.path();
			break;
		}
	}
	for (auto const &entry : fs::recursive_directory_iterator(candidate, ec)) {
		if (entry.is_regular_file() && entry.path().filename() == L"update.ver") {
			outDllDir = entry.path().parent_path();
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------
bool EsetDownload_SortAndRepack(const fs::path &unpackedDir, UnicodeString arhiveType,
	const fs::path &outX64,
	std::atomic<bool> &cancelFlag, EsetDlProgressCb progressCb, UnicodeString &errMsg)
{
	fs::path dllDir;
	if (!findDllDirWithUpdateVer(unpackedDir, dllDir)) {
		errMsg = L"Архів update_full.zip не містить update.ver/dll - структура не розпізнана.";
		return false;
	}
	fs::path updVerPath = dllDir / L"update.ver";
	std::vector<FileArchEntry> entries = parseUpdateVer(updVerPath);
	if (entries.empty()) {
		errMsg = L"Файл update.ver порожній або не вдалось розпізнати.";
		return false;
	}

	fs::path stagingRoot = unpackedDir.parent_path() / L"staging";
	fs::path stagingX64Root = stagingRoot / L"x64";
	fs::path stagingX64Dll = stagingX64Root / L"dll";
	std::error_code ec;
	fs::create_directories(stagingX64Dll, ec);

	bool anyX64 = false;
	for (auto &e : entries) {
		if (cancelFlag) { errMsg = L"Ручна зупинка."; fs::remove_all(stagingRoot, ec); return false; }
		if (e.arch != "x64") continue; // x86/update_x32 - застарілий функціонал, не генеруємо
		fs::path src = dllDir / fs::path(e.file.c_str());
		if (!fs::exists(src, ec)) continue;
		fs::copy_file(src, stagingX64Dll / src.filename(), fs::copy_options::overwrite_existing, ec);
		anyX64 = true;
	}
	fs::copy_file(updVerPath, stagingX64Dll / L"update.ver", fs::copy_options::overwrite_existing, ec);

	bool zstd = (arhiveType == "zstd");

	if (anyX64) {
		if (progressCb) progressCb(50, L"Пакування x64... (50%)");
		bool ok = zstd ? packTarZstd(outX64, stagingX64Root, cancelFlag, errMsg)
					   : packZip(outX64, stagingX64Root, cancelFlag, errMsg);
		if (!ok) { fs::remove_all(stagingRoot, ec); return false; }
	}

	fs::remove_all(stagingRoot, ec);
	if (progressCb) progressCb(100, L"Пакування завершено (100%)");
	return true;
}
//---------------------------------------------------------------------------
namespace {
	struct CopyProgressCtx {
		EsetDlProgressCb *progressCb;
		std::atomic<bool> *cancelFlag;
		UnicodeString label;
		short updateMs;
		std::chrono::steady_clock::time_point lastUpdate;
	};
}
// CopyFileExW сама періодично викликає цей колбек з поточним прогресом -
// повернення PROGRESS_CANCEL коректно перериває копіювання (CopyFileExW
// поверне FALSE, GetLastError() == ERROR_REQUEST_ABORTED)
static DWORD CALLBACK esetCopyProgressRoutine(
	LARGE_INTEGER totalFileSize, LARGE_INTEGER totalBytesTransferred,
	LARGE_INTEGER, LARGE_INTEGER, DWORD, DWORD,
	HANDLE, HANDLE, LPVOID lpData)
{
	CopyProgressCtx *ctx = reinterpret_cast<CopyProgressCtx*>(lpData);
	if (ctx->cancelFlag && *ctx->cancelFlag) return PROGRESS_CANCEL;

	auto now = std::chrono::steady_clock::now();
	auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - ctx->lastUpdate).count();
	bool done = (totalFileSize.QuadPart > 0 && totalBytesTransferred.QuadPart >= totalFileSize.QuadPart);
	if ((elapsedMs >= ctx->updateMs || done) && ctx->progressCb && *ctx->progressCb) {
		int percent = (totalFileSize.QuadPart > 0)
			? (int)((totalBytesTransferred.QuadPart * 100) / totalFileSize.QuadPart) : 0;
		UnicodeString phase = L"Публікація " + ctx->label + ": "
			+ formatBytes((uintmax_t)totalBytesTransferred.QuadPart) + " / "
			+ formatBytes((uintmax_t)totalFileSize.QuadPart) + " (" + UnicodeString(percent) + "%)";
		(*ctx->progressCb)(percent, phase);
		ctx->lastUpdate = now;
	}
	return PROGRESS_CONTINUE;
}
bool EsetDownload_PublishFile(const fs::path &src, const fs::path &dst, short updateMs,
	std::atomic<bool> &cancelFlag, EsetDlProgressCb progressCb, UnicodeString &errMsg)
{
	CopyProgressCtx ctx;
	ctx.progressCb = &progressCb;
	ctx.cancelFlag = &cancelFlag;
	ctx.label = UnicodeString(dst.filename().c_str());
	ctx.updateMs = updateMs;
	ctx.lastUpdate = std::chrono::steady_clock::now() - std::chrono::hours(1); // форсуємо перший виклик

	BOOL ok = CopyFileExW(src.c_str(), dst.c_str(), esetCopyProgressRoutine, &ctx, NULL, 0);
	if (!ok) {
		DWORD err = GetLastError();
		if (err == ERROR_REQUEST_ABORTED) errMsg = L"Ручна зупинка публікації архіву.";
		else errMsg = L"Не вдалось скопіювати " + ctx.label + L" у теку ПО (код " + UnicodeString((int)err) + ").";
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
