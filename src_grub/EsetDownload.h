//---------------------------------------------------------------------------

#ifndef EsetDownloadH
#define EsetDownloadH

#include <atomic>
#include <functional>
#include <filesystem>

namespace fs = std::filesystem;
//---------------------------------------------------------------------------
// колбек прогресу одного кроку (завантаження/пакування): percent 0..100,
// phase - короткий текст поточної дії для StatusBar/логу
typedef std::function<void(int percent, UnicodeString phase)> EsetDlProgressCb;

// WinHTTP-завантаження файлу з опційною Basic-авторизацією; докачка
// пропускається, якщо локальний файл вже має розмір Content-Length.
bool EsetDownload_DownloadFile(UnicodeString url, const fs::path &destPath,
	UnicodeString user, UnicodeString pass, short updateMs,
	std::atomic<bool> &cancelFlag, EsetDlProgressCb progressCb, UnicodeString &errMsg);

// розпакування довільного архіву (напр. update_full.zip) через вбудований
// 7-Zip (той самий 7za.exe, яким уже користується BtnEsetUpdateClick)
bool EsetDownload_ExtractArchive(const fs::path &archivePath, const fs::path &destDir,
	std::atomic<bool> &cancelFlag, UnicodeString &errMsg);

// знаходить у розпакованому update_full.zip теку dll/update.ver, сортує
// перелічені в update.ver файли по x86/x64 і пакує їх у update_x32.*/
// update_x64.* (формат "zip" або "zstd", згідно arhiveType) поруч з exe
bool EsetDownload_SortAndRepack(const fs::path &unpackedDir, UnicodeString arhiveType,
	const fs::path &outX32, const fs::path &outX64,
	std::atomic<bool> &cancelFlag, EsetDlProgressCb progressCb, UnicodeString &errMsg);

#endif
