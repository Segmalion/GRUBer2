//---------------------------------------------------------------------------
#pragma hdrstop

#include "Text.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/* Работа со строками */
//---------------------------------------------------------------------------
/* UnicodeString в std::string */
std::string unToStr(UnicodeString str)
{
	UTF8String uStr = str;
	return uStr.c_str();
}
//---------------------------------------------------------------------------
/* Проверка на старт строки */
bool isBeginUStr(UnicodeString strOR, UnicodeString srtF)
{
	UnicodeString strORsh = strOR.SubString(0, srtF.Length());
	if (strORsh == srtF) return true;
	return false;
}
//---------------------------------------------------------------------------
/* Парсинг строки */
std::vector<UnicodeString> strParamParsing (UnicodeString str)
{
	std::vector<UnicodeString> fStr;
	while (str.Pos(";") != 0) {
		fStr.push_back(str.SubString(1, str.Pos(";")-1));
		str = str.SubString(str.Pos(";")+2, str.Length());
	}
	fStr.push_back(str);
	return fStr;
}
//---------------------------------------------------------------------------
/* Дата и время */
UnicodeString curDate()
{
	TDateTime *myDate = new TDateTime(Now());
	return myDate->FormatString("dd.mm.yy");
}
UnicodeString curTime()
{
	TDateTime* myTime = new TDateTime(Now());
	return myTime->FormatString("hh:nn:ss");
}
//---------------------------------------------------------------------------
UnicodeString fixDirName(UnicodeString str)
{
	for (int i = 1; i < str.Length()+1; i++) {
		if (str.IsDelimiter("<>:\"/\\|?* ", i)) {
			str = str.Delete(i, 1);
			i--;
		}
	}
	return str;
}
//---------------------------------------------------------------------------
/* Парсинг параметров */
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm)
{
	UnicodeString resultStr, findStr;
	bool findCat = false;
	for (int i = 0; i < ini->Count; i++) {
		findStr = ini->Strings[i];
		//printLog(str);
		if (findCat == false && findStr == cat) {
			findCat = true;
			continue;
		}
		if (findCat == true && isBeginUStr(findStr, "[")) {
			break;
		}
		if (findCat == true && isBeginUStr(findStr, prm)) {
			resultStr = findStr.SubString(prm.Length()+2,findStr.Length());
			return resultStr;
		}
	}
	return "0";
}
std::vector<UnicodeString> findCategory(TStringList *ini, UnicodeString cat) {
	std::vector<UnicodeString> findMulStr;
	UnicodeString findStr;
	bool findCat = false;
	for (int i = 0; i < ini->Count; i++) {
		findStr = ini->Strings[i];
		if (findCat == false && findStr == cat) {
			findCat = true;
			continue;
		}
		if (findCat == true && isBeginUStr(findStr, "#stop")) {
			return findMulStr;
		}
		if (findCat == true) {
			findMulStr.push_back(findStr);
			continue;
		}
	}
	findMulStr.push_back("ERROR");
	return findMulStr;
}
//---------------------------------------------------------------------------
