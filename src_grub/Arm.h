//---------------------------------------------------------------------------
#ifndef ArmH
#define ArmH

#include <vector>

#include "InstallSoft.h"
#include "Users.h"
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
		int number_UVs = 0;
		int number_OK = 0;
		int number_UVs_logist = 0;
		int number_OK_logist = 0;
		short useForNumberARMid = 0;
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
		UnicodeString date, user;
	} histGr;
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
	std::vector<UnicodeString> mStrIniVersionNumber();
	std::vector<UnicodeString> mStrInfoArm();
	std::vector<UnicodeString> mStrSerial();
	std::vector<UnicodeString> mStrNumberARM();
	std::vector<UnicodeString> mStrInfoArmGrub();
	std::vector<UnicodeString> mStrInfoArmEset();
	std::vector<UnicodeString> mStrLastGrub();
	UnicodeString lastGrub();
	// === сеттери
	void set_useForNumberARMid(short i);
	void setNumber_UVs(int i);
	void setNumber_OK(int i);
	void setNumber_UVs_logist(int i);
	void setNumber_OK_logist(int i);
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
	short get_useForNumberARMid();
	int getNumber_UVs();
	int getNumber_OK();
	int getNumber_UVs_logist();
	int getNumber_OK_logist();
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
