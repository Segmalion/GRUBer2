//---------------------------------------------------------------------------

#ifndef ConfigH
#define ConfigH

#include <vector>
#include "Structures.h"
//---------------------------------------------------------------------------
class Config {
private:
	bool debug, showLog, showEsetUpd;
	bool tempDir;
	bool newGrub, license;
	bool oldGrubComent, oldGrubInfo, oldGrubNet, oldGrubUsb, oldGrubLogs;
	bool enablePrefixPartition;
	short oldGrub, audit, esetLog;
	short iniVersion = 0; // версія GRUBer.ini: 0, якщо ключ ini_version відсутній (старий формат)
	std::vector<StructureDef> structures;
	UnicodeString defaultStructureId;
	UnicodeString grubUser;
	UnicodeString configFile;
	UnicodeString prefixPartition;
	// eset_download - налаштування завантаження баз ESET (кнопка BtnEsetDownload)
	UnicodeString esetDlUrl, esetDlUser, esetDlPass;
	UnicodeString esetDlArhive; // "zip" або "zstd"
	bool esetDlConvert;
	short esetDlUpdateMs;
	// true, якщо секція [eset_download] була знайдена у GRUBer.ini при
	// останньому readFileIni() - використовується, щоб при старті програми
	// один раз запропонувати додати її з типовими значеннями
	bool esetDlSectionExists = false;
	// update - автоперевірка оновлень через приватні GitHub Releases
	bool updAutoCheck = true;
	short updIntervalHours = 24;
	UnicodeString updLastCheckUtc; // порожньо, якщо перевірок ще не було
	UnicodeString updSkipTag;      // тег релізу, який користувач відхилив назавжди ("Скасувати")
	// той самий сенс, що й esetDlSectionExists, але для секції [update]
	bool updSectionExists = false;
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
	bool getTempDir();
	bool getOldGrubComent();
	bool getOldGrubInfo();
	bool getOldGrubNet();
	bool getOldGrubUsb();
	bool getOldGrubLogs();
	bool getNewGrub();
	bool getLicense();
	bool getEnablePrefixPartition();
	short getOldGrub();
	short getAudit();
	short getEsetLog();
	short get_iniVersion();
	std::vector<StructureDef> get_structures();
	UnicodeString get_defaultStructureId();
	UnicodeString getUser();
	UnicodeString getPrefixPartition();
	UnicodeString getEsetDlUrl();
	UnicodeString getEsetDlUser();
	UnicodeString getEsetDlPass();
	UnicodeString getEsetDlArhive();
	bool getEsetDlConvert();
	short getEsetDlUpdateMs();
	bool getEsetDlSectionExists();
	bool getUpdAutoCheck();
	short getUpdIntervalHours();
	UnicodeString getUpdLastCheckUtc();
	UnicodeString getUpdSkipTag();
	bool getUpdSectionExists();
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
	void setTempDir(bool i);
	void setOldGrubComent(bool i);
	void setOldGrubInfo(bool i);
	void setOldGrubNet(bool i);
	void setOldGrubUsb(bool i);
	void setOldGrubLogs(bool i);
	void setNewGrub(bool i);
	void setLicense(bool i);
    void setEnablePrefixPartition(bool i);
	void set_structures(std::vector<StructureDef> v);
	void set_defaultStructureId(UnicodeString id);
	void setAudit(short i);
	void setEsetLog(short i);
	void setOldGrub(short i);
	void setUser(UnicodeString str);
	void setPrefixPartition(UnicodeString str);
	void setEsetDlUrl(UnicodeString str);
	void setEsetDlUser(UnicodeString str);
	void setEsetDlPass(UnicodeString str);
	void setEsetDlArhive(UnicodeString str);
	void setEsetDlConvert(bool i);
	void setEsetDlUpdateMs(short i);
	// заповнює [eset_download] типовими значеннями (з EsetBaseDownloader.ini)
	// і позначає секцію як наявну, щоб стартовий запит більше не з'являвся
	void applyEsetDlDefaults();
	void setUpdAutoCheck(bool i);
	void setUpdIntervalHours(short i);
	void setUpdLastCheckUtc(UnicodeString str);
	void setUpdSkipTag(UnicodeString str);
	// заповнює [update] типовими значеннями і позначає секцію як наявну,
	// щоб стартовий запит більше не з'являвся (аналог applyEsetDlDefaults)
	void applyUpdateDefaults();
	void set_lgpo(std::vector<UnicodeString> vStr); //<--
	void set_usb(std::vector<UnicodeString> vStr); //<--
	void set_user(std::vector<UnicodeString> vStr); //<--
	void set_spz(std::vector<UnicodeString> vStr); //<--
	void set_softBlackList(std::vector<UnicodeString> vStr); //<--
	void set_softWriteList(std::vector<UnicodeString> vStr); //<--
};
//---------------------------------------------------------------------------
#endif
