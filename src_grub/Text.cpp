//---------------------------------------------------------------------------
#pragma hdrstop

#include "Text.h"
#include "HashCRC32.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/* Работа со строками */
//---------------------------------------------------------------------------
/* Расчет hashCRC32 */
UnicodeString GetHashCRC32(UnicodeString str) {
	UnicodeString hashCRC32;
	Crc32Builder crc_builder;
	std::string temp_data = unToStr(str);
//	std::string temp_data = "12345678";
	uint32_t crc_value = crc_builder.calculate_crc(
		reinterpret_cast<const uint8_t*>(temp_data.data()), temp_data.length());
	//crc_value = 0x1234ABCD;
	//std::string tempStr = crc_value.ToString("X4");
    char outputString[9];
	itoa(crc_value, outputString, 16);
	hashCRC32 = UnicodeString(outputString).Insert("-",5);
	return hashCRC32.UpperCase();
}
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
/* Парсинг строки в масив*/
std::vector<UnicodeString> vStrGenFromStr (UnicodeString str) {
	std::vector<UnicodeString> vStr;
	while (str.Pos(";") != 0) {
		vStr.push_back(str.SubString(1, str.Pos(";")-1));
		str = str.SubString(str.Pos(";")+2, str.Length());
	}
	vStr.push_back(str);
	return vStr;
}
/* Обратный парсинг масива в строку */
UnicodeString strGenFromVStr (std::vector<UnicodeString> vStr) {
	UnicodeString str;
	for (auto i : vStr) {
		if (str.IsEmpty()) str = i;
		else str = str + "; " + i;
	}
	return str;
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
UnicodeString curDateTime()
{
	TDateTime* myTime = new TDateTime(Now());
	return myTime->FormatString("dd.mm.yy hh:nn:ss");
}
//---------------------------------------------------------------------------
// Чистка строки имени папки от запрещеных символов
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
UnicodeString findParam(TStringList* ini, UnicodeString cat, UnicodeString prm)
{
	UnicodeString resultStr, findStr;
	bool findCat = false;
	for (int i = 0; i < ini->Count; i++) {
		findStr = ini->Strings[i];
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
	return "ERROR";
}
std::vector<UnicodeString> findCategory(TStringList* ini, UnicodeString cat) {
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
UnicodeString byteToStr(long long i) {
	UnicodeString str;
	if (i < 1024) {
		str = FloatToStrF((double)i, ffFixed, 4, 1) + "b";
		return str;
	}
	if (i < pow(1024,2)) {
		str = FloatToStrF((double)i/1024, ffFixed, 4, 1) + "Kb";
		return str;
	}
	if (i < pow(1024,3)) {
		str = FloatToStrF((double)i/(pow(1024,2)), ffFixed, 4, 1) + "Mb";
		return str;
	}
	if (i < pow(1024,4)) {
		str = FloatToStrF((double)i/(pow(1024,3)), ffFixed, 4, 1) + "Gb";
		return str;
	}
	str = FloatToStrF((double)i/(pow(1024,4)), ffFixed, 4, 1) + "Тb";
	return str;
}
//---------------------------------------------------------------------------
/* Проверка строки на ERROR */
UnicodeString errCheck(const UnicodeString &str) {
	if (str == "ERROR") return "";
	else return str;
}
//---------------------------------------------------------------------------
