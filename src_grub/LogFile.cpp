//---------------------------------------------------------------------------
#pragma hdrstop

#include <windows.h>
#include <mutex>
#include <memory>

#include "LogFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
static const UnicodeString LOG_ROOT_DIR  = L"C:\\ProgramData\\GRUBer";
static const UnicodeString LOG_DIR       = LOG_ROOT_DIR + L"\\logs\\";
static const UnicodeString OLD_ERROR_DIR = LOG_ROOT_DIR + L"\\error\\";
static const int LOG_MAX_LINES = 10000;

static std::mutex logMutex;
static UnicodeString curLogStart; // "yyyymmddhhnn" початку поточного активного файлу
static UnicodeString curLogPath;  // повний шлях до поточного активного файлу
static int curLogLines = 0;
static bool logInited = false;
//---------------------------------------------------------------------------
// Переносить файли, що лишились у застарілій C:\ProgramData\GRUBer\error, у
// нову теку логів (не перезаписуючи однойменні файли, якщо там вже щось є).
static void migrateOldErrorLogs()
{
	TSearchRec sr;
	if (!FindFirst(OLD_ERROR_DIR + "*.*", faAnyFile, sr)) {
		do {
			if (sr.Name == "." || sr.Name == "..") continue;
			UnicodeString src = OLD_ERROR_DIR + sr.Name;
			UnicodeString dst = LOG_DIR + sr.Name;
			if (!FileExists(dst)) MoveFileW(src.c_str(), dst.c_str());
		} while (!FindNext(sr));
		FindClose(sr);
	}
}
//---------------------------------------------------------------------------
// Шукає в теці логів вже відкритий (не ротований) файл виду
// "logs_<12 цифр>.log" - рівно один timestamp, без другого "_<timestamp>",
// який позначав би вже закритий файл (той теж підпадає під маску
// "logs_*.log", тому й потрібне окреме фільтрування за вмістом імені).
static bool findActiveLogFile(UnicodeString &start, UnicodeString &path, int &lines)
{
	bool found = false;
	UnicodeString foundName;
	TSearchRec sr;
	if (!FindFirst(LOG_DIR + "logs_*.log", faAnyFile, sr)) {
		do {
			UnicodeString name = sr.Name;
			// "logs_" (5 симв.) + <mid> + ".log" (4 симв.)
			UnicodeString mid = name.SubString(6, name.Length() - 9);
			if (mid.Length() == 12 && mid.Pos(L"_") == 0) {
				foundName = name;
				found = true;
				break;
			}
		} while (!FindNext(sr));
		FindClose(sr);
	}
	if (!found) return false;
	start = foundName.SubString(6, 12);
	path = LOG_DIR + foundName;
	lines = 0;
	try {
		std::unique_ptr<TStringList> sl(new TStringList);
		sl->LoadFromFile(path, TEncoding::UTF8);
		lines = sl->Count;
	} catch (...) { lines = 0; }
	return true;
}
//---------------------------------------------------------------------------
static void startNewLogFile()
{
	curLogStart = FormatDateTime("yyyymmddhhnn", Now());
	curLogPath = LOG_DIR + "logs_" + curLogStart + ".log";
	curLogLines = 0;
}
//---------------------------------------------------------------------------
static void ensureInited()
{
	if (logInited) return;
	CreateDirectoryW(LOG_ROOT_DIR.c_str(), NULL);
	CreateDirectoryW(LOG_DIR.c_str(), NULL);
	migrateOldErrorLogs();
	UnicodeString start, path;
	int lines;
	if (findActiveLogFile(start, path, lines)) {
		curLogStart = start;
		curLogPath = path;
		curLogLines = lines;
	} else {
		startNewLogFile();
	}
	logInited = true;
}
//---------------------------------------------------------------------------
static void appendToFile(const UnicodeString &path, const UnicodeString &line)
{
	HANDLE hFile = CreateFileW(path.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ,
		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return;
	SetFilePointer(hFile, 0, NULL, FILE_END);
	UTF8String utf8 = UnicodeString(line + L"\r\n");
	DWORD written;
	WriteFile(hFile, utf8.c_str(), utf8.Length(), &written, NULL);
	CloseHandle(hFile);
}
//---------------------------------------------------------------------------
UnicodeString LogFile_GetLogDir()
{
	return LOG_DIR;
}
//---------------------------------------------------------------------------
void LogFile_Write(const UnicodeString &line)
{
	std::lock_guard<std::mutex> guard(logMutex);
	ensureInited();
	appendToFile(curLogPath, line);
	curLogLines++;
	if (curLogLines > LOG_MAX_LINES) {
		UnicodeString closedName = LOG_DIR + "logs_" + curLogStart + "_"
			+ FormatDateTime("yyyymmddhhnn", Now()) + ".log";
		MoveFileW(curLogPath.c_str(), closedName.c_str());
		startNewLogFile();
	}
}
//---------------------------------------------------------------------------
