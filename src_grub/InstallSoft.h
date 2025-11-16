//---------------------------------------------------------------------------

#ifndef InstallSoftH
#define InstallSoftH

#include <vector>

#include "MainForm.h"
//---------------------------------------------------------------------------
struct program {
	UnicodeString type;
	UnicodeString name;
	UnicodeString version;
	UnicodeString publisher;
};

std::vector<program> installSoft();
std::vector<program> read_hKey(HKEY hKey, UnicodeString type);
std::vector<program> blockInstallSoft(std::vector<program> listSoft);

//---------------------------------------------------------------------------
#endif

