//---------------------------------------------------------------------------
#ifndef ArmH
#define ArmH

#include <vector>
//---------------------------------------------------------------------------
class Arm {
public:
	int number = 0;
	UnicodeString partitionName = "Без відділу";
	UnicodeString armClassName = "Без класу";
	short armClassId = 0;
	UnicodeString categoryName = "Без категорії";
	short categoryId = 0;
	UnicodeString licWindowsName = "Не вказано";
	short licWindowsId = 0;
	UnicodeString licOfficeName = "Не вказано";
	short licOfficeId = 0;
	UnicodeString respon = "";
	std::vector<UnicodeString> coment;
	UnicodeString dirGrubName = "[--][DATE]Partition#Serial#Category";
	UnicodeString desktopName = "Помилка!";
	UnicodeString serial = "Помилка!";

	UnicodeString dirCurGrubName (UnicodeString date);
	bool getInfo();
};
#endif
