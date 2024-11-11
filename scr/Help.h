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
//---------------------------------------------------------------------------
class Dir {
private:
	UnicodeString progFull;
	UnicodeString baseName, baseFull;
	UnicodeString dateName, dateFull;
	UnicodeString grubName, grubFull;
public:
	Dir();
	void check();
	//сеттеры
	void setGrubFull(UnicodeString str);
	//геттеры
	UnicodeString getGrubFull();
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
bool paramReadAndSet(cnfgGrub &cfg);
bool infoReadAndSet(Arm &curPC);
bool infoSetToFille(infoEset &cfgEset, histGrub &lastGrub, Arm &curPC);
//---------------------------------------------------------------------------
// UnicodeString dirCurGrubName (arm &curPC, UnicodeString date);
//---------------------------------------------------------------------------
#endif
