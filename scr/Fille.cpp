//---------------------------------------------------------------------------
#pragma hdrstop

#include "Fille.h"
#include "Text.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
extern UnicodeString cmdEXE;
/* Работа с файлами */
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
	app(cmdEXE, "/c \"call cacls.exe " + str + " /t /e /g Users:c\"", 0);
   app(cmdEXE, "/c \"call cacls.exe " + str + " /t /e /g Пользователи:c\"", 0);
}
//---------------------------------------------------------------------------
