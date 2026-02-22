//---------------------------------------------------------------------------
#ifndef FilleH
#define FilleH

#include <vector>
//---------------------------------------------------------------------------

struct fille {
	UnicodeString str;
	long long size;
	bool dir;
};
struct patchList {
	std::vector<fille> list;
	int countDir = 0;
	int countFille = 0;
	long long size = 0;
};

bool checkConfigFileExist();
//std::vector<UnicodeString> scanDirToFille(UnicodeString dir);
patchList scanDirToFille(UnicodeString dir);
std::vector<UnicodeString> getLocalDrivePatch();

bool deleteDir(UnicodeString dirDelName, bool delDir = true);
bool fileOpen(UnicodeString str);
void cacls(UnicodeString str);
//---------------------------------------------------------------------------
#endif
