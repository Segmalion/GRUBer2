//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Form1);
USEFORM("PartitionForm.cpp", FormPartition);
USEFORM("ComentForm.cpp", FormComent);
USEFORM("DialogDirExist.cpp", FormDirExist);
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
