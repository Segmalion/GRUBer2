//---------------------------------------------------------------------------

#ifndef HelpToolH
#define HelpToolH

//---------------------------------------------------------------------------
struct eC app(UnicodeString Tool, UnicodeString ToolArg, int i);
//---------------------------------------------------------------------------
bool isBeginUStr(UnicodeString strOR, UnicodeString srtF);
std::vector<UnicodeString> strParamParsing (UnicodeString str);
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm);
//---------------------------------------------------------------------------
void printLog(UnicodeString str);
void printLogDebug(UnicodeString str);
//---------------------------------------------------------------------------
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm);
bool paramReadAndSet();
bool infoReadAndSet();
//---------------------------------------------------------------------------
#endif
