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
UnicodeString GetAppVersion();
UnicodeString GetFullAppVersion();
//---------------------------------------------------------------------------
bool fileOpen(UnicodeString str);
void cacls(UnicodeString str);
//---------------------------------------------------------------------------
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm);
//---------------------------------------------------------------------------
void printLog(UnicodeString str);
void printLogDebug(UnicodeString str);
void printLog(UnicodeString info, UnicodeString str);
//---------------------------------------------------------------------------
bool IsAdminMode();
bool warnIfNoAccess(UnicodeString path);
//---------------------------------------------------------------------------
void setInfoArmToForm(Arm &curPC);
void setConfigToForm(Config &curConfig);
bool infoReadAndSet(Arm &curPC);
bool infoSetToFille(Arm &curPC);
//---------------------------------------------------------------------------
void populateStructureCombos(Config &curConfig);
void applyCurStructureSelectionToForm(UnicodeString id);
std::vector<StructurePcData> findUnknownStructures(Arm &curPC, Config &curConfig);
//---------------------------------------------------------------------------
// UnicodeString dirCurGrubName (arm &curPC, UnicodeString date);
//---------------------------------------------------------------------------
bool compareVectorAndString(UnicodeString str, std::vector<UnicodeString> vct);
//---------------------------------------------------------------------------
bool x64_sys();
bool x64_app();
#endif
