//---------------------------------------------------------------------------
#pragma hdrstop

#include "Fille.h"
#include "Text.h"
#include "RunApp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

patchList scanDirToFille(UnicodeString dir)
{
	patchList find;
	std::vector<UnicodeString> list(0);
	TSearchRec sr;
	if (dir.Length()) {
		// проверяем на слеш в конце, и если есть - удаляем
		if (dir.LastDelimiter("\\") == dir.Length()) {
			dir = dir.SubString(0, dir.Length() - 1);
		}
		// процедура поиска
		if (!FindFirst(dir + "\\*.*", faAnyFile, sr))
			do {
				if (!(sr.Name == "." || sr.Name == "..")) { // это не трогаем
					if ((sr.Attr & faDirectory) != 0) {
						patchList tmpFind = scanDirToFille(dir + "\\" + sr.Name); //рекурсия
						find.list.insert(find.list.end(), tmpFind.list.begin(), tmpFind.list.end());
						find.countDir   += tmpFind.countDir;
						find.countFille += tmpFind.countFille;
						find.size       += tmpFind.size;
						find.countDir++;
						find.list.push_back({dir + "\\" + sr.Name, sr.Size, true});
					}
					if (!((sr.Attr & faDirectory) != 0)) {
						find.countFille++;
						find.size += sr.Size;
						find.list.push_back({dir + "\\" + sr.Name, sr.Size, false});
					}
				}
			} while (!FindNext(sr)); // ищем пока не найдем все
		FindClose(sr);
	}
	return find;
}
//---------------------------------------------------------------------------
std::vector<UnicodeString> getLocalDrivePatch()
{
	std::vector<UnicodeString> strDrives;
	const int BUFFER_SIZE = 256;
	CHAR driveStrings[BUFFER_SIZE];
	DWORD result = GetLogicalDriveStringsA(BUFFER_SIZE, driveStrings);
    if (result == 0) {
		// Произошла ошибка
		strDrives.push_back("ERROR" + UnicodeString(result));
		return strDrives;
	} else if (result > BUFFER_SIZE) {
		// Буфер слишком мал. Это маловероятно для обычных систем, но возможно.
        strDrives.push_back("ERROR" + UnicodeString(result));
		return strDrives;
	} else {
		// Перебираем строки дисков. Строки разделены нуль-терминаторами,
        // а весь список завершается двойным нуль-терминатором.
        CHAR* currentDrive = driveStrings;
		while (*currentDrive != '\0') {
			strDrives.push_back(UnicodeString(currentDrive));
			// Переходим к следующей строке, пропуская текущую строку и ее нуль-терминатор
            currentDrive += lstrlenA(currentDrive) + 1;
        }
	}
	return strDrives;
}
//---------------------------------------------------------------------------
bool deleteDir(UnicodeString dirDelName, bool delDir)
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
   if (delDir) RemoveDir(dirDelName);
   return true;
}
//---------------------------------------------------------------------------
// проверка на запуск файла и наличие
bool fileOpen(UnicodeString str)
{
	std::wstring wSrt( unToStr(str) );
	std::string tStr( wSrt.begin(), wSrt.end() );

	if (std::FILE *file = std::fopen(tStr.c_str(), "r"))
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
