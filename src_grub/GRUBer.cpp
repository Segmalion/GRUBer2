//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "CrashHandler.h"
USEFORM("MainForm.cpp", Form1);
USEFORM("StructuresForm.cpp", FormStructures);
USEFORM("StructurePickForm.cpp", FormStructurePick);
USEFORM("ComentForm.cpp", FormComent);
USEFORM("ClearTemp.cpp", FormClearTempDir);
USEFORM("About.cpp", FormAbout);
USEFORM("DialogDirExist.cpp", FormDirExist);
USEFORM("FormSerial.cpp", Form_Serial);
USEFORM("FormQuarantine.cpp", FormQuarantine);
#include "MainForm.h" // повний тип TForm1 - потрібен нижче для Form1->AppExceptionHandler
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	// Останній рубіж для необроблених SEH-винятків (access violation тощо).
	// НЕ ловить винятки з конструкторів глобальних об'єктів (curConfig, curPC) -
	// вони виконуються ще до першого рядка цієї функції, дивись CrashHandler.h.
	InstallCrashHandler();
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm1), &Form1);
		// з цього моменту Application->OnException пише кожен виняток, спійманий
		// під час Application->Run() (наприклад, в обробнику кліку), у crash.log
		// перед показом стандартного діалогу.
		Application->OnException = Form1->AppExceptionHandler;
		Application->CreateForm(__classid(TFormComent), &FormComent);
		Application->CreateForm(__classid(TFormDirExist), &FormDirExist);
		Application->CreateForm(__classid(TFormStructures), &FormStructures);
		Application->CreateForm(__classid(TFormStructurePick), &FormStructurePick);
		Application->CreateForm(__classid(TFormClearTempDir), &FormClearTempDir);
		Application->CreateForm(__classid(TFormAbout), &FormAbout);
		Application->CreateForm(__classid(TForm_Serial), &Form_Serial);
		Application->CreateForm(__classid(TFormQuarantine), &FormQuarantine);
		Application->Run();
	}
	catch (Exception &exception)
	{
		LogCrash("WinMain", exception.ClassName() + ": " + exception.Message);
		Application->ShowException(&exception);
	}
	catch (...)
	{
		LogCrash("WinMain", L"невідомий виняток (не System::Sysutils::Exception)");
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
