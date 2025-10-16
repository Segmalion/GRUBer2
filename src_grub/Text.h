//---------------------------------------------------------------------------
#ifndef TextH
#define TextH

#include "Help.h"
//---------------------------------------------------------------------------
std::wstring unToStr(UnicodeString str);
bool isBeginUStr(UnicodeString strOR, UnicodeString srtF);
std::vector<UnicodeString> vStrGenFromStr (UnicodeString str);
UnicodeString strGenFromVStr (std::vector<UnicodeString> vStr);
UnicodeString curDate();
UnicodeString curTime();
UnicodeString curDateTime();
UnicodeString fixDirName(UnicodeString str);
UnicodeString byteToStr(long long i);
UnicodeString GetHashCRC32(UnicodeString str);
UnicodeString errCheck(const UnicodeString &str);
bool compareInSring(UnicodeString strFull, UnicodeString strSearch);
//---------------------------------------------------------------------------
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm);
std::vector<UnicodeString> findCategory(TStringList *ini, UnicodeString cat);
//---------------------------------------------------------------------------
#endif
