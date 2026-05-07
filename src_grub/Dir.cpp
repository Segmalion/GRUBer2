//---------------------------------------------------------------------------

#pragma hdrstop

#include "Dir.h"
#include "Text.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace fs = std::filesystem;
//---------------------------------------------------------------------------
// обявление
Dir::Dir() {
	p_tool = fs::current_path() / "tool";
	p_grubTemp = "C:\\ProgramData\\GRUBer\\TempGRUB";
}
//---------------------------------------------------------------------------
// проверка директорий
void Dir::check() {
	std::error_code ec;
	fs::create_directories(p_grub, ec);
}
//---------------------------------------------------------------------------
// геттеры
UnicodeString Dir::get_grubPath() { return UnicodeString(p_grub.c_str()); }
UnicodeString Dir::get_toolPath() { return UnicodeString(p_tool.c_str()); }
UnicodeString Dir::get_grubPathTemp() { return UnicodeString(p_grubTemp.c_str()); }
// сеттеры
void Dir::set_grubPath (UnicodeString grubName) {
	UnicodeString dateName = "[" + curDate() + "]";
	fs::path p_dateFull = fs::current_path() / "base" / dateName.c_str();
	p_grub = p_dateFull / grubName.c_str();
}
//---------------------------------------------------------------------------
