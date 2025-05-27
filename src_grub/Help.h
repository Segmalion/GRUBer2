//---------------------------------------------------------------------------
#ifndef HelpH
#define HelpH

#include <vector>

#include "Arm.h"
#include "Config.h"
//---------------------------------------------------------------------------
struct eC {
	bool run=0;
	bool exit=0;
	UnicodeString exitCode;
	UnicodeString runCode;
};
//---------------------------------------------------------------------------
UnicodeString cmdCheck(void);
//---------------------------------------------------------------------------
bool fileOpen(UnicodeString str);
void cacls(UnicodeString str);
//---------------------------------------------------------------------------
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm);
//---------------------------------------------------------------------------
void printLog(UnicodeString str);
void printLogDebug(bool debug, UnicodeString str);
//---------------------------------------------------------------------------
bool IsAdminMode();
//---------------------------------------------------------------------------
void setInfoArmToForm(Arm &curPC);
void setConfigToForm(Config &curConfig);
bool infoReadAndSet(Arm &curPC);
bool infoSetToFille(Arm &curPC);
//---------------------------------------------------------------------------
// UnicodeString dirCurGrubName (arm &curPC, UnicodeString date);
//---------------------------------------------------------------------------
bool compareVectorAndString(UnicodeString str, std::vector<UnicodeString> vct);
//---------------------------------------------------------------------------
#endif
