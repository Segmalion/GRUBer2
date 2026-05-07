//---------------------------------------------------------------------------

#ifndef DirH
#define DirH

#include "Global.h"
//---------------------------------------------------------------------------

class Dir {
private:
	//UnicodeString progFull;
	fs::path p_grub, p_grubTemp, p_tool;
public:
	Dir();
	void check();
	//сеттеры
	void set_grubPath(UnicodeString str);
	//геттеры
	UnicodeString get_grubPath();
	UnicodeString get_toolPath();
	UnicodeString get_grubPathTemp();
};
#endif
