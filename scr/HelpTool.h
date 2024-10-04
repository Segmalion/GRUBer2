//---------------------------------------------------------------------------

#ifndef HelpToolH
#define HelpToolH
//---------------------------------------------------------------------------
#endif

bool isBeginUStr(UnicodeString strOR, UnicodeString srtF);
std::vector<UnicodeString> strParamParsing (UnicodeString str);
void printLog(UnicodeString str);
void printLogDebug(UnicodeString str);
bool paramReadAndSet();
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm);
