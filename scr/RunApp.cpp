//---------------------------------------------------------------------------

#pragma hdrstop

#include "RunApp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern bool stopBool;
//---------------------------------------------------------------------------
bool RunApp::check() {
	if(app.IsEmpty()) return false;
	if(arg.IsEmpty()) return false;
	return true;
}

void RunApp::setApp(UnicodeString apS) { app = apS; }
void RunApp::setArg(UnicodeString arS) { arg = arS; }
void RunApp::run(bool h, bool r) {
	hide = !h;
	runas = r;
	if (!check()) return;
	HINSTANCE errRun;
	DWORD exitCode;
	SHELLEXECUTEINFOW ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	if (runas) ShExecInfo.lpVerb = L"runas";
	else ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = app.c_str();
	ShExecInfo.lpParameters = arg.c_str();
	if (dir.IsEmpty()) ShExecInfo.lpDirectory = NULL;
	else ShExecInfo.lpDirectory = dir.c_str();
	ShExecInfo.nShow = hide;
	ShExecInfo.hInstApp = errRun;
	ShellExecuteExW(&ShExecInfo);
   HANDLE hHandles[] = { ShExecInfo.hProcess };
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
				if (stopBool) {
					TerminateProcess(ShExecInfo.hProcess, 1);
				}
			} else break;
	}
	//тут проверка на запуск програмы
	ULONG_PTR errU = reinterpret_cast<ULONG_PTR>(errRun);
	error.runCode = UnicodeString(errU);
	if (error.runCode.ToDouble() >32 || error.runCode==0) error.run = 0;      //good
		else error.run = 1;           //error
	//тут результат выполнения ПО
	GetExitCodeProcess(ShExecInfo.hProcess, &exitCode);
	error.exitCode = UnicodeString(exitCode);
	if (error.exitCode.ToDouble() == 0) error.exit = 0; //good
		else error.exit = 1;          //error
	CloseHandle(ShExecInfo.hProcess);
}
//---------------------------------------------------------------------------
