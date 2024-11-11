//---------------------------------------------------------------------------

#pragma hdrstop

#include "Arm.h"
#include "Text.h"
#include "GetSMB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/* конструктор */
Arm::Arm()
{
	if (FileExists(fileArmInfo)) readFromFile(fileArmInfo);
	// Get DesktopName
	TCHAR infoBuf[32767];
	DWORD bufCharCount = 32767;
	if( GetComputerName( infoBuf, &bufCharCount ) ) {
		desktopName = UnicodeString(infoBuf);
	} else desktopName = "Помилка!";
	// Get SMB - serial
	GetSMB g;
	PRAW_SMBIOS_DATA dataSMB = g.GetSmbiosData();
	if (dataSMB == NULL) {
		serial = "Помилка!";
	}
	serial = g.PrintBiosString(dataSMB, SMB_TABLE_CHASSIS, 7);
}
//---------------------------------------------------------------------------
/* функции */
UnicodeString Arm::dirGrubName ()
{
	UnicodeString str;
	str = "[";
	// number
	if (number == 0) {
		str = str + "--";
	} else str = str + UnicodeString(number);
	str = str + "][" + curDate() + "]";
	// partition
	str = str + partition;
	// serial
	str = str + "#" + serial;
	// category
	str = str + "#" + categoryName;
	return fixDirName(str);
}
std::vector<UnicodeString> Arm::mStrInfoArm() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("serialNumber=" + serial);
	mStr.push_back("desktopName=" + desktopName);
	return mStr;
}
std::vector<UnicodeString> Arm::mStrInfoArmGrub() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("number=" + UnicodeString(number));
	mStr.push_back("partition=" + partition);
	mStr.push_back("classId=" + UnicodeString(classId));
	mStr.push_back("className=" + className);
	mStr.push_back("categoryId=" + UnicodeString(categoryId));
	mStr.push_back("categoryName=" + categoryName);
	mStr.push_back("licWindowsId=" + UnicodeString(licWindowsId));
	mStr.push_back("licWindowsName=" + licWindowsName);
	mStr.push_back("licOfficeId=" + UnicodeString(licOfficeId));
	mStr.push_back("licOfficeName=" + licOfficeName);
	mStr.push_back("respon=" + respon);
	return mStr;
}
void Arm::readFromFile(UnicodeString filePatch) {
	TStringList *file = new TStringList;
	file->LoadFromFile(filePatch, TEncoding::UTF8);
	number = findParam(file, "[infoGrubARM]", "number").ToInt();
	partition = findParam(file, "[infoGrubARM]", "partition");
	className = findParam(file, "[infoGrubARM]", "className");
	classId   = findParam(file, "[infoGrubARM]", "classId").ToInt();
	categoryName = findParam(file, "[infoGrubARM]", "categoryName");
	categoryId   = findParam(file, "[infoGrubARM]", "categoryId").ToInt();
	licWindowsName = findParam(file, "[infoGrubARM]", "licWindowsName");
	licWindowsId   = findParam(file, "[infoGrubARM]", "licWindowsId").ToInt();
	licOfficeName = findParam(file, "[infoGrubARM]", "licOfficeName");
	licOfficeId   = findParam(file, "[infoGrubARM]", "licOfficeId").ToInt();
	respon = findParam(file, "[infoGrubARM]", "respon");
	coment = findCategory(file, "[comment]");
}
//---------------------------------------------------------------------------
/* сеттери */
void Arm::setNumber(int i) {
	number = i;
}
void Arm::setPartition(UnicodeString str) {
	partition = str;
}
void Arm::setClass(UnicodeString str, short i) {
	className = str;
	classId = i;
}
void Arm::setCategory(UnicodeString str, short i) {
	categoryName = str;
	categoryId = i;
}
void Arm::setLicWindows(UnicodeString str, short i) {
	licWindowsName = str;
	licWindowsId = i;
}
void Arm::setLicOffice(UnicodeString str, short i) {
	licOfficeName = str;
	licOfficeId = i;
}
void Arm::setRespon(UnicodeString str) {
	respon = str;
}
void Arm::setComent(std::vector<UnicodeString> vStr) {
	coment = vStr;
}
//---------------------------------------------------------------------------
/* геттери */
int Arm::getNumber() {
	return number;
}
UnicodeString Arm::getPartition() {
	return partition;
}
UnicodeString Arm::getClassName() {
	return className;
}
UnicodeString Arm::getCategoryName() {
	return categoryName;
}
UnicodeString Arm::getLicWindowsName() {
	return licWindowsName;
}
UnicodeString Arm::getLicOfficeName() {
	return licOfficeName;
}
UnicodeString Arm::getRespon() {
	return respon;
}
short Arm::getClassId() {
	return classId;
}
short Arm::getCategoryId() {
	return categoryId;
}
short Arm::getLicWindowsId() {
	return licWindowsId;
}
short Arm::getLicOfficeId() {
	return licOfficeId;
}
std::vector<UnicodeString> Arm::getComent() {
	return coment;
}
UnicodeString Arm::getDesktopName() {
	return desktopName;
}
UnicodeString Arm::getSerial() {
	return serial;
}
//---------------------------------------------------------------------------
