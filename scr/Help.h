//---------------------------------------------------------------------------
#ifndef HelpH
#define HelpH

#include "MainForm.h"
#include "Arm.h"
//---------------------------------------------------------------------------
struct histGrub {
	UnicodeString date, user;
};
struct cnfgGrub {
	bool debug;
	bool showLog;
	UnicodeString grubUser;
	std::vector<UnicodeString> partition;
	std::vector<UnicodeString> armClass;
	std::vector<UnicodeString> category;
};
struct infoEset {
	bool autoUpdate;
	UnicodeString dirMirror, lastUpdateDate, lastUpdateUser, lastUpdateArchive;
};
struct errCode {
	bool run=0;
	bool exit=0;
};
struct dir {
	UnicodeString progPath;
	UnicodeString base, basePath;
	UnicodeString baseDate, baseDatePath;
	UnicodeString baseGrub, baseGrubPath;
};
//---------------------------------------------------------------------------
void mainGrub();
//---------------------------------------------------------------------------
errCode app(UnicodeString Tool, UnicodeString ToolArg, int i);
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
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm);
std::vector<UnicodeString> findCategory(TStringList *ini, UnicodeString cat);
bool paramReadAndSet(cnfgGrub &cfg);
bool infoReadAndSet(Arm &curPC);
bool infoSetToFille(const infoEset &cfgEset, const histGrub &lastGrub, const Arm &curPC);
//---------------------------------------------------------------------------
// UnicodeString dirCurGrubName (arm &curPC, UnicodeString date);
//---------------------------------------------------------------------------
#endif
