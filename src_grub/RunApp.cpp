//---------------------------------------------------------------------------

#pragma hdrstop

#include "RunApp.h"
#include "Help.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern bool stopBool, passBool;
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
		if (x64()) app = app64;
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
	BOOL shellOk = ShellExecuteExW(&ShExecInfoA);
	if (!shellOk) {
		// Если ShellExecuteEx вернул FALSE, используем GetLastError как код ошибки
		DWORD lastErr = GetLastError();
		error.runCode = std::to_wstring(static_cast<unsigned long long>(lastErr));
		error.run = 1; // ошибка запуска
		error.exit = 1;
		return;
	}
	//Вычислим числовой код результата запуска из hInstApp
	ULONG_PTR errU = reinterpret_cast<ULONG_PTR>(ShExecInfoA.hInstApp);
	error.runCode = std::to_wstring(static_cast<unsigned long long>(errU));
	// По документации: значение > 32 означает успех для ShellExecute-подобных функций.
	// Так же учитывать случай 0 (иногда конкретные вызовы могут возвращать 0 в частных ситуациях).
	if (errU > 32 || errU == 0) error.run = 0;	//good
	else error.run = 1;							//error
	//Если процесс не был получен (на всякий случай), завершить
	if (ShExecInfoA.hProcess == NULL) {
		// Нет процесса для ожидания; просто вернуть (код запуска уже в error.runCode)
		if (error.run == 0) error.exit = 0; // считать, что выполнено успешно, но процесса ждать неоткуда
		else error.exit = 1;
		return;
	}
	//Ожидание в фоне ПО
	HANDLE hHandles[] = { ShExecInfoA.hProcess };
	MSG msg;
	while(1) {
		DWORD dwRet = ::MsgWaitForMultipleObjects(1, hHandles, FALSE, 50, QS_ALLINPUT);
		if (stopBool || passBool) {
			TerminateProcess(ShExecInfoA.hProcess, 1);
			if (passBool) { passBool = false; passBoolTmp = true;}
            error.exit = -1;
			break;
		}
		if(dwRet == WAIT_OBJECT_0) {
			break;
		}
		else if(dwRet == WAIT_OBJECT_0 + 1) {
			// There is a window message available. Dispatch it.
			while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	//Тут результат выполнения ПО
	if (!GetExitCodeProcess(ShExecInfoA.hProcess, &exitCode)) {
		// Ошибка получения кода выхода
		error.exitCode = std::to_wstring((int)-1);
		error.exit = 1;
	} else {
		error.exitCode = std::to_wstring(exitCode);
		if (exitCode == 0) {
			error.exit = 0; //good
		}
		else {
			if (passBoolTmp || stopBool) error.exit = -1;
			else error.exit = 1; //error
		}
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
		return "[!!]Щось пішло НЕ так, під час запуску...)";
	} else {
		if (error.exit == 1) return "[!!]Щось пішло НЕ так, під час створення файлу...";
		if (error.exit == 0) return "Файл СТВОРЕННО!";
		if (error.exit == -1) return "[!!]Ручна зупинка Граба...";
	}
	return "[:(]Якась хуйня.."; // заглушка
}
bool RunApp::checkErr() {
	if(error.run == 1 || error.exit == 1) return true;
	else return false;
}
//---------------------------------------------------------------------------
