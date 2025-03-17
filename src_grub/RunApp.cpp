//---------------------------------------------------------------------------

#pragma hdrstop

#include "RunApp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern bool stopBool, passBool;
extern bool x64;
//---------------------------------------------------------------------------
bool RunApp::check() {
	if(app.IsEmpty()) return false;
	//if(arg.IsEmpty()) return false;
	return true;
}

RunApp::RunApp(UnicodeString apSx32, UnicodeString apSx64, UnicodeString arS) {
	app32 = apSx32;
	app64 = apSx64;
	arg = arS;
	if (app64 == NULL) { app = app32; }
	else {
		if (x64) app = app64;
		else app = app32;
    }
}

void RunApp::run(bool h, bool r) {
	//Переменные
	if (h == true) 	hide = 0;
	if (h == false) hide = 1;
	runas = r;
	if (!check()) return;
	HINSTANCE errRun;
	DWORD exitCode;
	bool passBoolTmp = false;
	//параметры для запуска
	SHELLEXECUTEINFOW ShExecInfoA = {0};
	ShExecInfoA.cbSize = sizeof(SHELLEXECUTEINFOW);
	ShExecInfoA.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfoA.hwnd = NULL;
	if (runas) ShExecInfoA.lpVerb = L"runas";
		  else ShExecInfoA.lpVerb = NULL;
	ShExecInfoA.lpFile = app.c_str();
	if (arg.IsEmpty()) ShExecInfoA.lpParameters = NULL;
				  else ShExecInfoA.lpParameters = arg.c_str();
	if (dir.IsEmpty()) ShExecInfoA.lpDirectory = NULL;
				  else ShExecInfoA.lpDirectory = dir.c_str();
	ShExecInfoA.nShow = hide;
	ShExecInfoA.hInstApp = errRun;
	//Запуск ПО
	ShellExecuteExW(&ShExecInfoA);
	//Ожидание в фоне ПО
	HANDLE hHandles[] = { ShExecInfoA.hProcess };
	MSG msg;
	while(1) {
		DWORD dwRet = ::MsgWaitForMultipleObjects(1, hHandles, FALSE, INFINITE, QS_ALLINPUT);
		if(dwRet == WAIT_OBJECT_0) {
			break;
		}
		else
			if(dwRet == WAIT_OBJECT_0 + 1){
				// There is a window message available. Dispatch it.
				while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				if (stopBool || passBool) {
					TerminateProcess(ShExecInfoA.hProcess, 1);
					if (passBool) { passBool = false; passBoolTmp = true;}
				}
			} else break;
	}
	//Тут проверка на запуск програмы
	ULONG_PTR errU = reinterpret_cast<ULONG_PTR>(errRun);
	error.runCode = UnicodeString(errU);
	if (error.runCode.ToDouble() >32 || error.runCode==0) error.run = 0;      //good
		else error.run = 1;           //error
	//Тут результат выполнения ПО
	GetExitCodeProcess(ShExecInfoA.hProcess, &exitCode);
	error.exitCode = UnicodeString(exitCode);
	if (error.exitCode.ToDouble() == 0) {
		error.exit = 0; //good
	} else {
		if (passBoolTmp || stopBool) error.exit = -1;
		else error.exit = 1; //error
	}
	//Закрытие приложения
	CloseHandle(ShExecInfoA.hProcess);
}
UnicodeString RunApp::errorString() {
	if (error.run) {
		return "[code: \"" + error.runCode + "\"]";
	} else {
		if (error.exit == 1) {
			return "[code: \"" + error.exitCode + "\"]";
		} else {
			return "[code:\"" + error.runCode + ", " + error.exitCode + "\"]";
		}
	}
}
UnicodeString RunApp::resultString() {
	if (error.run) {
		return "[!]Щось пішло НЕ так, під час запуску...)";
	} else {
		if (error.exit == 1) return "[!]Щось пішло НЕ так, під час створення файлу...";
		if (error.exit == 0) return "Файл СТВОРЕННО!";
		if (error.exit == -1) return "[!]Ручна зупинка Граба...";
	}
	return "[:(]Якась хуйня.."; // заглушка
}
bool RunApp::checkErr() {
	if(error.run == 1 || error.exit == 1) return true;
	else return false;
}
//---------------------------------------------------------------------------
