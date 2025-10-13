//---------------------------------------------------------------------------

#ifndef InstallSoftH
#define InstallSoftH

#include <vector>

#include "MainForm.h"
//---------------------------------------------------------------------------

std::vector<InstalledProgram> installSoft();
std::vector<InstalledProgram> read_hKey(HKEY hKey, UnicodeString type);
std::vector<InstalledProgram> blockInstallSoft();

//---------------------------------------------------------------------------
#endif

