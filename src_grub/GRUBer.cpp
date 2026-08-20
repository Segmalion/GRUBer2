//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("MainForm.cpp", Form1);
USEFORM("StructuresForm.cpp", FormStructures);
USEFORM("StructurePickForm.cpp", FormStructurePick);
USEFORM("ComentForm.cpp", FormComent);
USEFORM("ClearTemp.cpp", FormClearTempDir);
USEFORM("About.cpp", FormAbout);
USEFORM("DialogDirExist.cpp", FormDirExist);
USEFORM("FormSerial.cpp", Form_Serial);
USEFORM("FormQuarantine.cpp", FormQuarantine);
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
