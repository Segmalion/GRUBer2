//---------------------------------------------------------------------------
#ifndef ArmH
#define ArmH

#include <vector>
//---------------------------------------------------------------------------
class Arm {
private:
	/* ПЕРЕМЕННЫЕ */
	/* При добавлении перемепных:
	** 1 - добавить переменную в приватный раздел
	** 2 - добавить сеттеры и геттеры
	** 3 - добавить чтение и запись в файл
	** 4 - добавить установку прочитаных значений в форму
	*/
	// инфо об ПК (ручная)
	int number = 0;
	UnicodeString partition  = "Без відділу";
	UnicodeString className   = "Без класу";
	UnicodeString categoryName   = "Без категорії";
	UnicodeString licWindowsName = "Не вказано";
	UnicodeString licOfficeName  = "Не вказано";
	int classID   = 0;
	int categoryID   = 0;
	int licWindowsID = 0;
	int licOfficeID  = 0;
	UnicodeString respon = "";
	std::vector<UnicodeString> coment;
	// инфо об ПК (ручная) - по документам
	UnicodeString inNumberARM, inNumberHDD, inNumberDeclr;
	UnicodeString inNumberFormulyar, inNumberWork, inNumberPerson;
	// инфо об ПК (ручная) - по настройкам
	UnicodeString comPoliticInstall, comContrUSB, comMultiUSERS;
	bool politicInstall=0, contrUSB=0, multiUSERS=0;
	// инфо из ПК
	UnicodeString desktopName = "";
	UnicodeString serial = "";
	// структуры
   struct infoEset {
		bool autoUpdate = true;
		UnicodeString dirMirror = "C:\\ESET\\mirror";
		UnicodeString lastUpdateDate, lastUpdateUser, lastUpdateArchive;
	} eset;
   struct histGrub {
		UnicodeString date, user;
	} histGr;
   // функции
	bool readFromFile();
public:
   // конструктор
	Arm();
	// функции
	UnicodeString dirGrubName(UnicodeString prfPart, bool enPrfPart);
	std::vector<UnicodeString> mStrInfoArm();
	std::vector<UnicodeString> mStrInfoArmGrubMini();
	std::vector<UnicodeString> mStrInfoArmGrubFull();
	std::vector<UnicodeString> mStrInfoArmEset();
	std::vector<UnicodeString> mStrLastGrub();
   UnicodeString lastGrub();
	// сеттери
	void setNumber(int i);
	void setPartition(UnicodeString str);
	void setClass(UnicodeString str, int i);
	void setCategory(UnicodeString str, int i);
	void setLicWindows(UnicodeString str, int i);
	void setLicOffice(UnicodeString str, int i);
	void setRespon(UnicodeString str);
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
	void setComPoliticInstall (UnicodeString str);
	void setComContrUSB (UnicodeString str);
	void setComMultiUSERS (UnicodeString str);
	void setPoliticInstall (bool i);
	void setContrUSB (bool i);
	void setMultiUSERS (bool i);
	// геттери
	int getNumber();
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
	std::vector<UnicodeString> getComent();
	UnicodeString getComentStr();
	UnicodeString getDesktopName();
	UnicodeString getSerial();
	UnicodeString getEsetDir();
	bool getEsetAutoUpdate();

	UnicodeString getInNumberARM();
	UnicodeString getInNumberHDD();
	UnicodeString getInNumberDeclr();
	UnicodeString getInNumberFormulyar();
	UnicodeString getInNumberWork();
	UnicodeString getInNumberPerson();
	UnicodeString getComPoliticInstall();
	UnicodeString getComContrUSB();
	UnicodeString getComMultiUSERS();
	bool getPoliticInstall();
	bool getContrUSB();
	bool getMultiUSERS();
};
#endif
