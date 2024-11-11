//---------------------------------------------------------------------------
#ifndef ArmH
#define ArmH

#include <vector>
//---------------------------------------------------------------------------
class Arm {
private:
	const UnicodeString fileArmInfo = "C:\\ProgramData\\GRUBer\\gruber_info.ini";
	int number = 0;
	UnicodeString partition  = "Без відділу";
	UnicodeString className   = "Без класу";
	UnicodeString categoryName   = "Без категорії";
	UnicodeString licWindowsName = "Не вказано";
	UnicodeString licOfficeName  = "Не вказано";
	UnicodeString respon = "";
	short classId   = 0;
	short categoryId   = 0;
	short licWindowsId = 0;
	short licOfficeId  = 0;
	std::vector<UnicodeString> coment;
	UnicodeString desktopName;
	UnicodeString serial;
   // функции
	void readFromFile(UnicodeString filePatch);
public:
   // конструктор
	Arm();
	// функции
	UnicodeString dirGrubName();
	std::vector<UnicodeString> mStrInfoArm();
	std::vector<UnicodeString> mStrInfoArmGrub();
	// сеттери
	void setNumber(int i);
	void setPartition(UnicodeString str);
	void setClass(UnicodeString str, short i);
	void setCategory(UnicodeString str, short i);
	void setLicWindows(UnicodeString str, short i);
	void setLicOffice(UnicodeString str, short i);
	void setRespon(UnicodeString str);
	void setComent(std::vector<UnicodeString> vStr);
	// геттери
	int getNumber();
	UnicodeString getPartition();
	UnicodeString getClassName();
	UnicodeString getCategoryName();
	UnicodeString getLicWindowsName();
	UnicodeString getLicOfficeName();
	UnicodeString getRespon();
	short getClassId();
	short getCategoryId();
	short getLicWindowsId();
	short getLicOfficeId();
	std::vector<UnicodeString> getComent();
	UnicodeString getDesktopName();
	UnicodeString getSerial();
};
#endif
