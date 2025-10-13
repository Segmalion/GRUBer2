//---------------------------------------------------------------------------

#pragma hdrstop

#include "Dir.h"
#include "Text.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// обявление
Dir::Dir() {
	progFull = GetCurrentDir();
	baseName = "base";
	dateName = "[" + curDate() + "]";
	baseFull = progFull + "\\" + baseName;
	dateFull = baseFull + "\\" + dateName;
	grubTemp = "C:\\ProgramData\\GRUBer\\TempGRUB";
}
//---------------------------------------------------------------------------
// проверка директорий
void Dir::check() {
	if (!DirectoryExists(baseFull)) CreateDir(baseFull);
	if (!DirectoryExists(dateFull)) CreateDir(dateFull);
	if (!DirectoryExists(grubFull)) CreateDir(grubFull);
}
//---------------------------------------------------------------------------
// геттеры
UnicodeString Dir::getGrubFull() { return grubFull; }
UnicodeString Dir::getToolFull() { return (progFull + "\\tool"); }
UnicodeString Dir::get_grubTemp() { return grubTemp; }
//---------------------------------------------------------------------------
// сеттеры
void Dir::setGrubFull (UnicodeString str) {
	grubName = str;
	grubFull = dateFull + "\\" + grubName;
}
//---------------------------------------------------------------------------
