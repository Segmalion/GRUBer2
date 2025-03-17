//---------------------------------------------------------------------------
#ifndef FilleH
#define FilleH

#include <vector>
//---------------------------------------------------------------------------
std::vector<UnicodeString> scanDirToFille(UnicodeString dir);

bool deleteDir(UnicodeString dirDelName);
bool fileOpen(UnicodeString str);
void cacls(UnicodeString str);
//---------------------------------------------------------------------------
#endif
