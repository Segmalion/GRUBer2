//---------------------------------------------------------------------------

#pragma hdrstop

#include "UpdateInstall.h"

#include <memory>

#include "Fille.h"
#include "Help.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
static const fs::path UPDATE_ROOT = L"C:\\ProgramData\\GRUBer\\update";
static const UnicodeString UPDATE_LOG_DIR  = L"C:\\ProgramData\\GRUBer\\logs\\";
static const UnicodeString UPDATE_LOG_FILE = UPDATE_LOG_DIR + L"update.log";
//---------------------------------------------------------------------------
void Update_Log(const UnicodeString &message)
{
	// без залежності від VCL/Form1 - за зразком LogCrash() з CrashHandler.cpp,
	// щоб лишатись безпечним для виклику з фонового потоку в будь-який момент
	CreateDirectoryW(L"C:\\ProgramData\\GRUBer", NULL);
	CreateDirectoryW(UPDATE_LOG_DIR.c_str(), NULL);

	HANDLE hFile = CreateFileW(UPDATE_LOG_FILE.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ,
		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return;
	SetFilePointer(hFile, 0, NULL, FILE_END);

	UnicodeString ts = TDateTime(Now()).FormatString("yyyy-mm-dd hh:mm:ss");
	UTF8String line = UnicodeString(L"[" + ts + L"] " + message + L"\r\n");
	DWORD written;
	WriteFile(hFile, line.c_str(), line.Length(), &written, NULL);
	CloseHandle(hFile);
}
//---------------------------------------------------------------------------
fs::path Update_StagingDir(UnicodeString tag)
{
	fs::path dir = UPDATE_ROOT / fs::path(tag.c_str());
	ensureDirWithAccess(UnicodeString(dir.c_str()));
	return dir;
}
//---------------------------------------------------------------------------
void Update_CleanStaleStaging(UnicodeString keepTag)
{
	std::error_code ec;
	if (!fs::exists(UPDATE_ROOT, ec)) return;
	for (auto const &entry : fs::directory_iterator(UPDATE_ROOT, ec)) {
		if (!entry.is_directory()) continue;
		if (UnicodeString(entry.path().filename().c_str()) == keepTag) continue;
		fs::remove_all(entry.path(), ec);
	}
}
//---------------------------------------------------------------------------
bool Update_InstallDirWritable(const fs::path &installDir)
{
	return hasWriteAccess(UnicodeString(installDir.c_str()));
}
//---------------------------------------------------------------------------
// Генерований хелпер - БЕЗ жодного літерального шляху в тексті скрипта:
// install dir/PID приходять аргументами (%~1/%~2, Unicode-safe через
// ShellExecuteW), власна тека - через %~dp0. Це навмисно, щоб кирилиця в
// шляху встановлення (напр. "D:\Тест ГРАБер\") не ламала кодування ASCII-
// файлу скрипта. Бекап+відкат - обов'язкові: недоладна половинчаста заміна
// на робочому ноутбуці техніка в полі - найгірший можливий наслідок цієї
// фічі.
bool Update_WriteHelperCmd(const fs::path &stageDir, fs::path &outCmd, UnicodeString &errMsg)
{
	std::unique_ptr<TStringList> s(new TStringList);
	s->Add(L"@echo off");
	// enabledelayedexpansion - потрібен, бо TS (дата/час логу, див. нижче)
	// переобчислюється й читається в межах одного й того ж дужкового
	// if(...)-блоку (waitmain/waitdl timeout), де звичайний %TS% підставився
	// б ще ДО виконання for /f (значення з моменту розбору блоку, а не з
	// моменту виконання) - тому скрізь нижче використовується !TS!, а не %TS%
	s->Add(L"setlocal enabledelayedexpansion");
	s->Add(L"set \"INSTALL=%~1\"");
	s->Add(L"set \"PID=%~2\"");
	s->Add(L"set \"LOG=%ProgramData%\\GRUBer\\logs\\update.log\"");
	s->Add(L"");
	// %date%/%time% форматуються за локаллю ОС (у логу з'являлось "17.09.2026
	// 17:46:23,16" замість "2026-09-17 17:46:23", як в решти файлових логів
	// програми) - тому дата/час тут беруться через PowerShell Get-Date у
	// фіксованому форматі "yyyy-MM-dd HH:mm:ss", той самий, що й скрізь
	// інде (див. LogFile.cpp/CrashHandler.cpp)
	s->Add(L"for /f %%a in ('powershell -NoProfile -Command \"(Get-Date).ToString('yyyy-MM-dd HH:mm:ss')\"') do set \"TS=%%a\"");
	s->Add(L"echo [!TS!] apply_update: start pid=%PID% install=%INSTALL% >> \"%LOG%\" 2>nul");
	s->Add(L"");
	s->Add(L"set WAITED=0");
	s->Add(L":waitmain");
	s->Add(L"tasklist /FI \"PID eq %PID%\" 2>nul | find \"%PID%\" >nul");
	s->Add(L"if errorlevel 1 goto waitmain_done");
	s->Add(L"set /a WAITED=%WAITED%+1");
	s->Add(L"if %WAITED% GEQ 60 (");
	s->Add(L"  for /f %%a in ('powershell -NoProfile -Command \"(Get-Date).ToString('yyyy-MM-dd HH:mm:ss')\"') do set \"TS=%%a\"");
	s->Add(L"  echo [!TS!] apply_update: GRUBer.exe pid %PID% still running after 60s - abort >> \"%LOG%\" 2>nul");
	s->Add(L"  goto :eof");
	s->Add(L")");
	s->Add(L"ping -n 2 127.0.0.1 >nul");
	s->Add(L"goto waitmain");
	s->Add(L":waitmain_done");
	s->Add(L"");
	s->Add(L"set WAITED=0");
	s->Add(L":waitdl");
	s->Add(L"tasklist /FI \"IMAGENAME eq DeviceLister.exe\" 2>nul | find /I \"DeviceLister.exe\" >nul");
	s->Add(L"if errorlevel 1 goto waitdl_done");
	s->Add(L"set /a WAITED=%WAITED%+1");
	s->Add(L"if %WAITED% GEQ 60 (");
	s->Add(L"  for /f %%a in ('powershell -NoProfile -Command \"(Get-Date).ToString('yyyy-MM-dd HH:mm:ss')\"') do set \"TS=%%a\"");
	s->Add(L"  echo [!TS!] apply_update: DeviceLister.exe still running after 60s - abort >> \"%LOG%\" 2>nul");
	s->Add(L"  goto :eof");
	s->Add(L")");
	s->Add(L"ping -n 2 127.0.0.1 >nul");
	s->Add(L"goto waitdl");
	s->Add(L":waitdl_done");
	s->Add(L"");
	s->Add(L"copy /Y \"%INSTALL%\\GRUBer.exe\" \"%INSTALL%\\GRUBer.exe.bak\" >nul 2>&1");
	s->Add(L"copy /Y \"%INSTALL%\\DeviceLister.exe\" \"%INSTALL%\\DeviceLister.exe.bak\" >nul 2>&1");
	s->Add(L"");
	s->Add(L"copy /Y \"%~dp0GRUBer.exe\" \"%INSTALL%\\GRUBer.exe\" >nul");
	s->Add(L"if errorlevel 1 goto rollback");
	s->Add(L"copy /Y \"%~dp0DeviceLister.exe\" \"%INSTALL%\\DeviceLister.exe\" >nul");
	s->Add(L"if errorlevel 1 goto rollback");
	s->Add(L"");
	s->Add(L"del \"%INSTALL%\\GRUBer.exe.bak\" >nul 2>&1");
	s->Add(L"del \"%INSTALL%\\DeviceLister.exe.bak\" >nul 2>&1");
	s->Add(L"for /f %%a in ('powershell -NoProfile -Command \"(Get-Date).ToString('yyyy-MM-dd HH:mm:ss')\"') do set \"TS=%%a\"");
	s->Add(L"echo [!TS!] apply_update: success >> \"%LOG%\" 2>nul");
	s->Add(L"start \"\" \"%INSTALL%\\GRUBer.exe\"");
	s->Add(L"goto cleanup");
	s->Add(L"");
	s->Add(L":rollback");
	s->Add(L"for /f %%a in ('powershell -NoProfile -Command \"(Get-Date).ToString('yyyy-MM-dd HH:mm:ss')\"') do set \"TS=%%a\"");
	s->Add(L"echo [!TS!] apply_update: copy FAILED - rolling back >> \"%LOG%\" 2>nul");
	s->Add(L"copy /Y \"%INSTALL%\\GRUBer.exe.bak\" \"%INSTALL%\\GRUBer.exe\" >nul 2>&1");
	s->Add(L"copy /Y \"%INSTALL%\\DeviceLister.exe.bak\" \"%INSTALL%\\DeviceLister.exe\" >nul 2>&1");
	s->Add(L"del \"%INSTALL%\\GRUBer.exe.bak\" >nul 2>&1");
	s->Add(L"del \"%INSTALL%\\DeviceLister.exe.bak\" >nul 2>&1");
	s->Add(L"start \"\" \"%INSTALL%\\GRUBer.exe\"");
	s->Add(L"");
	s->Add(L":cleanup");
	s->Add(L"(goto) 2>nul & del \"%~f0\"");

	fs::path cmdPath = stageDir / L"apply_update.cmd";
	try {
		s->SaveToFile(UnicodeString(cmdPath.c_str()), TEncoding::ASCII);
	} catch (Exception &e) {
		errMsg = L"Не вдалось згенерувати скрипт оновлення: " + e.Message;
		return false;
	}
	outCmd = cmdPath;
	return true;
}
//---------------------------------------------------------------------------
bool Update_LaunchHelper(const fs::path &cmdPath, const fs::path &installDir,
	DWORD gruberPid, bool needElevation, UnicodeString &errMsg)
{
	UnicodeString args = L"\"" + UnicodeString(installDir.c_str()) + L"\" " + UnicodeString((int)gruberPid);
	HINSTANCE res = ShellExecuteW(NULL, needElevation ? L"runas" : L"open",
		cmdPath.c_str(), args.c_str(), NULL, SW_HIDE);
	if ((INT_PTR)res <= 32) {
		errMsg = L"Не вдалось запустити встановлювач оновлення (код " + UnicodeString((int)(INT_PTR)res) + L").";
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
