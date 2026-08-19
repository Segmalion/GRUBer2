//---------------------------------------------------------------------------

#pragma hdrstop

#include "Dir.h"
#include "Text.h"
#include "Fille.h"
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
bool Dir::check() {
	std::error_code ec;
	bool created = fs::create_directories(p_grub, ec);
	// теку могли раніше створити під іншим рівнем прав (адмін/юзер) - видаємо
	// право на запис одразу, щоб наступний запис у неї не впирався в ACL
	if (fs::exists(p_grub)) cacls(UnicodeString(p_grub.c_str()));
	return created;
}
//---------------------------------------------------------------------------
// геттеры
UnicodeString Dir::get_grubPath() { return UnicodeString(p_grub.c_str()); }
fs::path Dir::get_p_grubPath() { return p_grub.c_str(); }
UnicodeString Dir::get_toolPath() { return UnicodeString(p_tool.c_str()); }
UnicodeString Dir::get_grubPathTemp() { return UnicodeString(p_grubTemp.c_str()); }
// сеттеры
void Dir::set_grubPath (UnicodeString grubName) {
	UnicodeString dateName = "[" + curDate() + "]";
	fs::path p_dateFull = fs::current_path() / "base" / dateName.c_str();
	p_grub = p_dateFull / grubName.c_str();
}
//---------------------------------------------------------------------------
