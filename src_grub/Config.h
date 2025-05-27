//---------------------------------------------------------------------------

#ifndef ConfigH
#define ConfigH

#include <vector>
//---------------------------------------------------------------------------
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
	UnicodeString prefixPartition;
	bool enablePrefixPartition;
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
	UnicodeString getPrefixPartition();
	bool getEnablePrefixPartition();
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
	void setPrefixPartition(UnicodeString str);
	void setEnablePrefixPartition(bool i);
};
//---------------------------------------------------------------------------
#endif
