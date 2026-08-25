//---------------------------------------------------------------------------
#ifndef ArmH
#define ArmH

#include <vector>

#include "InstallSoft.h"
#include "Users.h"
#include "Net.h"
#include "Structures.h"
//---------------------------------------------------------------------------
class Arm {
private:
	/* ПЕРЕМЕННЫЕ */
	/* При добавлении перемепных:
	** 1 - добавить переменную в приватный раздел
	** 2 - добавить сеттеры и геттеры
	** 3 - добавить чтение и запись в файл
	** 4 - добавить установку прочитаных значений в форму
	** 5 - запись изменений в клас при изменении формы
	*/
	// --- инфо об ПК (ручная)
		std::vector<StructurePcData> structures;
		UnicodeString curStructureId, curStructureName;
		bool pendingLegacyMigration = false;
		UnicodeString pendingLegacyPartition, pendingLegacyPlace, pendingLegacyPhone;
		int pendingLegacyNumber = 0;
		UnicodeString partition  = "Без відділу";
		UnicodeString className   = "Без класу";
		UnicodeString categoryName   = "Особистий";
		UnicodeString categoryNameShort = "ОС";
		UnicodeString licWindowsName = "Не вказано";
		UnicodeString licOfficeName  = "Не вказано";
		int classID   = 0;
		int categoryID   = 0;
		int licWindowsID = 0;
		int licOfficeID  = 0;
		UnicodeString respon = "";
		UnicodeString purpose = "";
		UnicodeString place = "";
		UnicodeString phone = "";
		std::vector<UnicodeString> coment;
	// --- инфо об ПК (ручная) - по документам
		UnicodeString inNumberARM, inNumberHDD, inNumberDeclr;
		UnicodeString inNumberFormulyar, inNumberWork, inNumberPerson;
		UnicodeString inRespon, inAdminBP;
	// --- инфо об ПК (ручная) - по настройкам
		UnicodeString lgpo, controlUSB, multiUser; //<---
		std::vector<UnicodeString> spzInstal; //<---
	// --- инфо из ПК
		UnicodeString desktopName = "";
		UnicodeString serial, serialMain, UUID, serial_mrb, CPUID, unSerial;
		UnicodeString manufacturer, productName;
	// --- установленное ПО
		std::vector<program> softInstall;
		std::vector<program> softBlock;
	// --- пользователи
		std::vector<User> users;
	// === структуры
	struct infoEset {
		bool autoUpdate = true;
		UnicodeString dirMirror = "C:\\ESET\\mirror";
		UnicodeString lastUpdateDate, lastUpdateUser, lastUpdateArchive;
	} eset;
	struct histGrub {
        TDateTime date;
		UnicodeString user;
	} histGr;
	std::vector <histGrub> allGrubDate;
	struct ArmDevESET
	{
		std::vector<TDateTime> dateTime;
		UnicodeString device_details;
		UnicodeString serial;
		short catNum = 0;
		bool Status;
	};
	std::vector<ArmDevESET> devEset;
	struct ArmDevUSB
	{
		TDateTime regDateTime1, regDateTime2;
		UnicodeString name, description, type, serial;
		UnicodeString nameDev, cat;
		short catNum = 0;
		bool know = false;
		bool errN = false;
	};
	std::vector<ArmDevUSB> devUSB;
	struct NetDevise
	{
		UnicodeString description;
		UnicodeString ipAddress;
		UnicodeString macAddress;
		UnicodeString Status;
	};
	std::vector<NetDevise> netInterfase;
	// усі фізичні мережеві адаптери (LAN/WAN/USB), активні й неактивні -
	// оновлюється при кожному запуску в read_net(); для неактивних lastActive
	// зберігається з попереднього разу, коли адаптер ще був активним.
	std::vector<NetAdapterInfo> netAdapters;
	// === функции
	// -- чтение из файла на ПК (c:\ProgramData\GRUBer\gruber_info.ini)
	bool readFromFile();
public:
	// === конструктор
	Arm();
	// === функции
	UnicodeString dirGrubName(UnicodeString prfPart, bool enPrfPart);
	void read_soft();
	void read_user();
	void read_net();
	std::vector<UnicodeString> mStrIniVersionNumber();
	std::vector<UnicodeString> mStrInfoArm();
	std::vector<UnicodeString> mStrSerial();
	std::vector<UnicodeString> mStrStructures();
	std::vector<UnicodeString> mStrCurStructure();
	std::vector<UnicodeString> mStrInfoArmGrub();
	std::vector<UnicodeString> mStrInfoArmEset();
	std::vector<UnicodeString> mStrInfoArmNet();
	std::vector<UnicodeString> mStrLastGrub();
	UnicodeString lastGrub();
	// === сеттери
	void set_structures(std::vector<StructurePcData> v);
	void setStructureNumber(UnicodeString id, UnicodeString name, int number);
	void setStructurePartition(UnicodeString id, UnicodeString name, UnicodeString partition);
	void setStructurePlace(UnicodeString id, UnicodeString name, UnicodeString place);
	void setStructurePhone(UnicodeString id, UnicodeString name, UnicodeString phone);
	void setCurStructureSelection(UnicodeString id, UnicodeString name);
	void applyPendingLegacyMigration(UnicodeString targetStructureId, UnicodeString targetStructureName);
	void clearPendingLegacyMigration();
	void setPartition(UnicodeString str);
	void setClass(UnicodeString str, int i);
	void setCategory(UnicodeString str, int i);
	void setLicWindows(UnicodeString str, int i);
	void setLicOffice(UnicodeString str, int i);
	void setRespon(UnicodeString str);
	void setPurpose(UnicodeString str);
	void setPlace(UnicodeString str);
	void setPhone(UnicodeString str);
	void setComent(std::vector<UnicodeString> vStr);
	void setEsetDir(UnicodeString str);
	void setEsetAutoUpdate(bool i);
	void setLastGrub(UnicodeString date, UnicodeString user);
	void setInNumberARM (UnicodeString str);
	void setInNumberHDD (UnicodeString str);
	void setInNumberDeclr (UnicodeString str);
	void setInNumberFormulyar (UnicodeString str);
	void setInNumberWork (UnicodeString str);
	void setInNumberPerson (UnicodeString str);
	void setInRespon (UnicodeString str);
	void setInAdminBP (UnicodeString str);
	void set_lgpo (UnicodeString str);		   //<--
	void set_controlUSB (UnicodeString str);  //<--
	void set_multiUser (UnicodeString str);  //<--
	void set_spzInstal(std::vector<UnicodeString> vStr); //<--
	// === геттери
	std::vector<StructurePcData> get_structures();
	StructurePcData getStructure(UnicodeString id);
	UnicodeString getCurStructureId();
	UnicodeString getCurStructureName();
	bool needsLegacyMigrationPrompt();
	UnicodeString getPartition();
	UnicodeString getClassName();
	UnicodeString getCategoryName();
	UnicodeString getLicWindowsName();
	UnicodeString getLicOfficeName();
	int getClassID();
	int getCategoryID();
	int getLicWindowsID();
	int getLicOfficeID();
	UnicodeString getRespon();
	UnicodeString getPurpose();
	UnicodeString getPlace();
	UnicodeString getPhone();
	std::vector<UnicodeString> getComent();
	UnicodeString getComentStr();
	UnicodeString getDesktopName();

	UnicodeString getEsetDir();
	bool getEsetAutoUpdate();

	UnicodeString getInNumberARM();
	UnicodeString getInNumberHDD();
	UnicodeString getInNumberDeclr();
	UnicodeString getInNumberFormulyar();
	UnicodeString getInNumberWork();
	UnicodeString getInNumberPerson();
	UnicodeString getInRespon();
	UnicodeString getInAdminBP();

	UnicodeString get_lgpo(); 		//<--
	UnicodeString get_controlUSB(); //<--
	UnicodeString get_multiUser();  //<--
	std::vector<UnicodeString> get_spzInstal(); //<--
	// серийники
	UnicodeString getSerial();
	UnicodeString getSerialMain();
	UnicodeString getUUID();
	UnicodeString getSerial_mrb();
	UnicodeString getCPUID();
	UnicodeString getUnSerial();

	UnicodeString get_manufacturer();
	UnicodeString get_productName();

	// усі фізичні мережеві адаптери
	std::vector<NetAdapterInfo> get_netAdapters();

	bool getPoliticInstall();
	bool getContrUSB();
	bool getMultiUSERS();
	// софт
	std::vector<program> get_softInstall();
	std::vector<program> get_softBlock();
	// пользователи
	std::vector<User> get_users();
};
#endif
