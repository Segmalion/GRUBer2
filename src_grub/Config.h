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
	bool enablePrefixPartition;
	short oldGrub, audit, esetLog;
	short forNumberARMid;
	UnicodeString grubUser;
	UnicodeString configFile;
	UnicodeString prefixPartition;
	std::vector<UnicodeString> partition;
	std::vector<UnicodeString> lgpo;        //<==
	std::vector<UnicodeString> usb;         //<==
	std::vector<UnicodeString> user;        //<==
	std::vector<UnicodeString> spz;         //<==
	std::vector<UnicodeString> softBlackList; //<==
	std::vector<UnicodeString> softWriteList; //<==
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
	bool getOldGrubComent();
	bool getOldGrubInfo();
	bool getOldGrubNet();
	bool getOldGrubUsb();
	bool getNewGrub();
	bool getLicense();
	bool getEnablePrefixPartition();
	short getOldGrub();
	short getAudit();
	short getEsetLog();
	short get_forNumberARMid();
	UnicodeString getUser();
	UnicodeString getPrefixPartition();
	std::vector<UnicodeString> getPartition();
	std::vector<UnicodeString> get_lgpo(); //<--
	std::vector<UnicodeString> get_usb();  //<--
	std::vector<UnicodeString> get_user(); //<--
	std::vector<UnicodeString> get_spz();  //<--
	std::vector<UnicodeString> get_softBlackList(); //<--
	std::vector<UnicodeString> get_softWriteList(); //<--
	// сеттеры
	void setDebug(bool i);
	void setShowLog(bool i);
	void setShowEsetUpd(bool i);
	void setOldGrubComent(bool i);
	void setOldGrubInfo(bool i);
	void setOldGrubNet(bool i);
	void setOldGrubUsb(bool i);
	void setNewGrub(bool i);
	void setLicense(bool i);
    void setEnablePrefixPartition(bool i);
	void set_forNumberARMid(short i);
	void setAudit(short i);
	void setEsetLog(short i);
	void setOldGrub(short i);
	void setUser(UnicodeString str);
	void setPrefixPartition(UnicodeString str);
	void setPartition(std::vector<UnicodeString> vStr);
	void set_lgpo(std::vector<UnicodeString> vStr); //<--
	void set_usb(std::vector<UnicodeString> vStr); //<--
	void set_user(std::vector<UnicodeString> vStr); //<--
	void set_spz(std::vector<UnicodeString> vStr); //<--
	void set_softBlackList(std::vector<UnicodeString> vStr); //<--
	void set_softWriteList(std::vector<UnicodeString> vStr); //<--
};
//---------------------------------------------------------------------------
#endif
