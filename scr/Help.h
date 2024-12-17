//---------------------------------------------------------------------------
#ifndef HelpH
#define HelpH

#include "MainForm.h"
#include "Arm.h"
//---------------------------------------------------------------------------
struct eC {
	bool run=0;
	bool exit=0;
	UnicodeString exitCode;
	UnicodeString runCode;
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
	UnicodeString getToolFull();
};
class Config {
private:
	bool debug, showLog, showEsetUpd;
	bool newGrub, license;
	bool oldGrubComent, oldGrubInfo, oldGrubNet, oldGrubUsb;
	short oldGrub, audit, esetLog;
	UnicodeString grubUser;
	std::vector<UnicodeString> partition;
	std::vector<UnicodeString> armClass;
	std::vector<UnicodeString> category;
	UnicodeString configFile;
	// функции
	void readFileIni();
public:
	Config();
	void saveFileIni();
    short checkOldGrubState();
	// геттеры
	bool getDebug();
	bool getShowLog();
	bool getShowEsetUpd();
	short getOldGrub();
	bool getOldGrubComent();
	bool getOldGrubInfo();
	bool getOldGrubNet();
	bool getOldGrubUsb();
	bool getNewGrub();
	bool getLicense();
	short getAudit();
	short getEsetLog();
	UnicodeString getUser();
	std::vector<UnicodeString> getPartition();
	std::vector<UnicodeString> getArmClass();
	std::vector<UnicodeString> getCategory();
	// сеттеры
	void setDebug(bool i);
	void setShowLog(bool i);
	void setShowEsetUpd(bool i);
	void setAudit(short i);
	void setEsetLog(short i);
	void setOldGrub(short i);
	void setOldGrubComent(bool i);
	void setOldGrubInfo(bool i);
	void setOldGrubNet(bool i);
	void setOldGrubUsb(bool i);
	void setNewGrub(bool i);
	void setLicense(bool i);
	void setUser(UnicodeString str);
	void setPartition(std::vector<UnicodeString> vStr);
	void setArmClass(std::vector<UnicodeString> vStr);
	void setCategory(std::vector<UnicodeString> vStr);
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
#endif
