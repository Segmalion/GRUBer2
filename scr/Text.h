//---------------------------------------------------------------------------
#ifndef TextH
#define TextH

#include "Help.h"
//---------------------------------------------------------------------------

std::string unToStr(UnicodeString str);
bool isBeginUStr(UnicodeString strOR, UnicodeString srtF);
std::vector<UnicodeString> strParamParsing (UnicodeString str);
UnicodeString curDate();
UnicodeString curTime();
UnicodeString fixDirName(UnicodeString str);
//---------------------------------------------------------------------------
#endif
