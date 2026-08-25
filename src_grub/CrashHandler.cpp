//---------------------------------------------------------------------------
#pragma hdrstop

#include <windows.h>

#include "CrashHandler.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// НАВМИСНО не static/глобальні: LogCrash() може викликатися з конструкторів
// глобальних об'єктів (curPC, curConfig) під час статичної ініціалізації,
// коли порядок конструювання файлових static-об'єктів між різними .cpp не
// гарантований ("static initialization order fiasco"). Локальні змінні
// конструюються рівно в момент виконання цього рядка, тому завжди готові.
void LogCrash(const UnicodeString &source, const UnicodeString &message)
{
	const UnicodeString crashLogDir  = "C:\\ProgramData\\GRUBer\\error\\";
	const UnicodeString crashLogFile = crashLogDir + "crash.log";

	// Без ensureDirWithAccess()/cacls() (Fille.h) - щоб не тягнути залежність
	// від RunApp у модуль, який має лишатись максимально простим і безпечним
	// для виклику з будь-якого, навіть аварійного, контексту. ACL успадко-
	// вуються від C:\ProgramData\GRUBer, яку інші частини програми вже
	// налаштовують через cacls().
	CreateDirectoryW(L"C:\\ProgramData\\GRUBer", NULL);
	CreateDirectoryW(crashLogDir.c_str(), NULL);

	HANDLE hFile = CreateFileW(crashLogFile.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ,
		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return;
	SetFilePointer(hFile, 0, NULL, FILE_END);

	UnicodeString ts = TDateTime(Now()).FormatString("yyyy-MM-dd hh:nn:ss");
	UTF8String line = UnicodeString("[" + ts + "] [" + source + "] " + message + "\r\n");
	DWORD written;
	WriteFile(hFile, line.c_str(), line.Length(), &written, NULL);
	CloseHandle(hFile);
}
//---------------------------------------------------------------------------
static LONG WINAPI TopLevelExceptionFilter(EXCEPTION_POINTERS *ep)
{
	DWORD code = (ep && ep->ExceptionRecord) ? ep->ExceptionRecord->ExceptionCode : 0;
	void *addr = (ep && ep->ExceptionRecord) ? ep->ExceptionRecord->ExceptionAddress : NULL;
	UnicodeString msg = "code=0x" + IntToHex((unsigned)code, 8) +
		" addr=0x" + IntToHex((unsigned __int64)(UIntPtr)addr, 16);
	LogCrash("UnhandledSEH", msg);

	MessageBoxW(NULL,
		L"GRUBer зазнав критичної помилки і буде закрито.\n\n"
		L"Деталі записано у файл:\nC:\\ProgramData\\GRUBer\\error\\crash.log\n\n"
		L"Передайте цей файл розробнику для діагностики.",
		L"GRUBer - критична помилка", MB_OK | MB_ICONERROR | MB_TOPMOST);

	return EXCEPTION_EXECUTE_HANDLER;
}
//---------------------------------------------------------------------------
void InstallCrashHandler()
{
	SetUnhandledExceptionFilter(TopLevelExceptionFilter);
}
