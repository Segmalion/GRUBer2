//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("MainForm.cpp", Form1);
USEFORM("PartitionForm.cpp", FormPartition);
USEFORM("ComentForm.cpp", FormComent);
USEFORM("ClearTemp.cpp", FormClearTempDir);
USEFORM("About.cpp", FormAbout);
USEFORM("DialogDirExist.cpp", FormDirExist);
USEFORM("FormSerial.cpp", Form_Serial);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TFormComent), &FormComent);
		Application->CreateForm(__classid(TFormDirExist), &FormDirExist);
		Application->CreateForm(__classid(TFormPartition), &FormPartition);
		Application->CreateForm(__classid(TFormClearTempDir), &FormClearTempDir);
		Application->CreateForm(__classid(TFormAbout), &FormAbout);
		Application->CreateForm(__classid(TForm_Serial), &Form_Serial);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
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
