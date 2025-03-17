//---------------------------------------------------------------------------
#pragma hdrstop

#include "Fille.h"
#include "Text.h"
#include "RunApp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool deleteDir(UnicodeString dirDelName)
{
   TSearchRec sr;
	if (dirDelName.Length()) {
		if (!FindFirst(dirDelName+"\\*.*",faAnyFile,sr)) do
      {
         if (!(sr.Name=="." || sr.Name==".."))
         {// это не удаляем
				if (((sr.Attr & faDirectory)==faDirectory)||(sr.Attr == faDirectory))
				{  // найдена папка
					FileSetAttr(dirDelName+"\\"+sr.Name, faDirectory );
					deleteDir(dirDelName+"\\"+sr.Name);//рекурсивно удаляем найденную папку
					RemoveDir(dirDelName + "\\"+sr.Name);// удаляем уже пустую папку
            } else
            {  // найден файл
					FileSetAttr(dirDelName+"\\"+sr.Name, 0);
					DeleteFile(dirDelName+"\\"+sr.Name);// удаляем файл
            }
         }
      }
      while (!FindNext(sr));// ищем пока не найдем все
      FindClose(sr);
   }
   RemoveDir(dirDelName);
   return true;
}
//---------------------------------------------------------------------------
// проверка на запуск файла и наличие
bool fileOpen(UnicodeString str)
{
	if (std::FILE *file = std::fopen(unToStr(str).c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	else return false;
}
//---------------------------------------------------------------------------
// смена прав на файл через CMD
void cacls(UnicodeString str)
{
	UnicodeString setApp = "C:\\Windows\\System32\\cacls.exe";
	UnicodeString setArg = str + " /t /e /g Users:c\"";
	ShellExecuteW(NULL, L"open", setApp.c_str(), setArg.c_str(), NULL, SW_HIDE);
	setArg = str + " /t /e /g Пользователи:c\"";
	ShellExecuteW(NULL, L"open", setApp.c_str(), setArg.c_str(), NULL, SW_HIDE);
}
//---------------------------------------------------------------------------
