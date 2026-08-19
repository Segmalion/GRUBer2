//---------------------------------------------------------------------------
#pragma hdrstop

#include <filesystem>
#include <fstream>
#include <string>

#include "Fille.h"
#include "Text.h"
#include "RunApp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace fs = std::filesystem;
//---------------------------------------------------------------------------
bool checkConfigFileExist() {
	fs::path p_curDir = fs::current_path();
	fs::path p_configIni = p_curDir / "GRUBer.ini";
	if(!exists(p_configIni)) return false;
	return true;
}
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
						find.list.push_back({dir + "\\" + sr.Name, sr.Size, true, sr.CreationTime});
					}
					if (!((sr.Attr & faDirectory) != 0)) {
						find.countFille++;
						find.size += sr.Size;
						find.list.push_back({dir + "\\" + sr.Name, sr.Size, false, sr.CreationTime});
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
// прибирає завершальний(і) слеш(і) - шлях з ними, обгорнутий у лапки для
// командного рядка (напр. "C:\...\Quarantine\"), парситься CommandLineToArgvW
// (її використовують і explorer.exe, і takeown/icacls) НЕПРАВИЛЬНО: '\"' в
// кінці трактується як екранована лапка, а не як закриваюча, і весь рядок
// аргументів після неї ламається. Тому будь-який шлях перед підстановкою в
// лапки для командного рядка треба прогнати через цю функцію.
UnicodeString stripTrailingSlash(UnicodeString path)
{
	while (path.Length() && (path[path.Length()] == L'\\' || path[path.Length()] == L'/'))
		path = path.SubString(1, path.Length() - 1);
	return path;
}
//---------------------------------------------------------------------------
// смена прав на файл/теку - icacls з успадкуванням (OI)(CI), щоб нові файли
// всередині теки автоматично отримували право на запис, а не лише наявні.
// Виконується під поточним токеном процесу (без runas) - його завжди досить,
// бо ACL міняється відразу після створення тим самим процесом.
void cacls(UnicodeString str)
{
	UnicodeString setApp = "C:\\Windows\\System32\\icacls.exe";
	// Шлях до файлу/теки обов'язково в лапках - інакше пробіли в шляху ламають
	// розбір аргументів icacls.exe. stripTrailingSlash() - див. коментар вище.
	UnicodeString path = stripTrailingSlash(str);
	UnicodeString setArg = "\"" + path + "\" /grant Users:(OI)(CI)M /grant \"Пользователи\":(OI)(CI)M /T /C";
	RunApp fix(setApp, NULL, setArg);
	fix.run(true, false);
}
//---------------------------------------------------------------------------
// пробний запис у теку - надійніша перевірка реального доступу, ніж читання ACL
bool hasWriteAccess(UnicodeString path)
{
	fs::path probe = fs::path(path.c_str()) / (L".gruber_write_test_" + std::to_wstring(GetTickCount64()));
	std::error_code ec;
	std::ofstream f(probe, std::ios::out | std::ios::trunc);
	bool ok = f.is_open();
	f.close();
	if (ok) fs::remove(probe, ec);
	return ok;
}
//---------------------------------------------------------------------------
// створення теки (якщо відсутня) + видача прав на запис усім користувачам;
// повертає результат пробного запису - чи справді можна писати в теку
bool ensureDirWithAccess(UnicodeString path)
{
	fs::path p = path.c_str();
	if (!fs::exists(p)) {
		std::error_code ec;
		fs::create_directories(p, ec);
	}
	if (fs::exists(p)) cacls(path);
	return hasWriteAccess(path);
}
//---------------------------------------------------------------------------
