//---------------------------------------------------------------------------

#pragma hdrstop

#include "MainForm.h"
#include "Help.h"
#include "Arm.h"
#include "Text.h"
#include "GetSMB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/* конструктор */
Arm::Arm()
{
	readFromFile();
	// Get DesktopName
	DWORD bufCharCount = 32767;
	TCHAR infoBuf[32767];
	if( GetComputerName( infoBuf, &bufCharCount ) ) {
		desktopName = UnicodeString(infoBuf);
	} else desktopName = "Помилка!";
	// Get SMB - serial
	UnicodeString errSer[] = {
		"To Be Filled By O.E.M.",
		"Not Applicable",
		"System Serial Number",
		"Default string",
		"serial number"
	};
	GetSMB g;
	PRAW_SMBIOS_DATA dataSMB = g.GetSmbiosData();
	if (dataSMB == NULL) {
		serialMain = "Помилка SMBIOS_DATA!";
		UUID = "Помилка SMBIOS_DATA!";
		serial_mrb = "Помилка SMBIOS_DATA!";
		CPUID = "Помилка SMBIOS_DATA!";
	}
	serialMain = g.GetBiosString(dataSMB, SMB_TABLE_SYSTEM, 7);
	serial = serialMain;
    for (auto errSerStr: errSer) {
		if (serial.LowerCase() == errSerStr.LowerCase()) serial = "ErrorSN";
	}
	UUID = g.GetBiosValue(dataSMB, SMB_TABLE_SYSTEM, 8, 16);
	serial_mrb = g.GetBiosString(dataSMB, SMB_TABLE_BASEBOARD, 7);
	CPUID = g.GetBiosValue(dataSMB, SMB_TABLE_PROCESSOR, 8, 8);
	UnicodeString toHash  = serialMain +
							UUID +
							serial_mrb +
							CPUID;
	unSerial = GetHashCRC32(toHash);
}
//---------------------------------------------------------------------------
/* функции */
UnicodeString Arm::dirGrubName(UnicodeString prfPart, bool enPrfPart)
{
	UnicodeString str;
	str = "[";
	// number
	if (number_UVs == 0) {
		str = str + "--";
	} else str = str + UnicodeString(number_UVs);
	str = str + "][" + curDate() + "]";
	// partition
	if (prfPart.IsEmpty() || !enPrfPart) {
		str = str + partition;
	} else str = str + prfPart + "_" + partition;
	// serial
	if (serial == "ErrorSN") {
		str = str + "#БезСН";
	}
	else str = str + "#" + serial;
	// category
	if (categoryID == 0) str = str + "#ОС";
	if (categoryID == 1) str = str + "#НТ-БП";
	if (categoryID == 2) str = str + "#НТ-ІСД";
	if (categoryID == 3) str = str + "#НТ-ЕКМ";
	if (categoryID == 4) str = str + "#ДСК";
	if (categoryID == 5) str = str + "#Т";
	if (categoryID == 6) str = str + "#ЦТ";
	return fixDirName(str);
}
//генерация строк в инфо файлы
std::vector<UnicodeString> Arm::mStrIniVersionNumber() {
	const int iniVersionNumber = 2;
	std::vector<UnicodeString> mStr;
	mStr.push_back("[iniVersion]");
	mStr.push_back("version=" + UnicodeString(iniVersionNumber));
	return mStr;
}
std::vector<UnicodeString> Arm::mStrInfoArm() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("[infoARM]");
	mStr.push_back("serialNumber=" + serial);
	mStr.push_back("desktopName=" + desktopName);
	mStr.push_back("[serial]");
	mStr.push_back("serialMain=" + serialMain);
	mStr.push_back("UUID=" + UUID);
	mStr.push_back("serial_mrb=" + serial_mrb);
	mStr.push_back("CPUID=" + CPUID);
	mStr.push_back("unSerial=" + unSerial);
	return mStr;
}
std::vector<UnicodeString> Arm::mStrInfoArmGrub() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("[infoGrubARM]");
	mStr.push_back("number_UVs=" + UnicodeString(number_UVs));
	mStr.push_back("number_OK=" + UnicodeString(number_OK));
	mStr.push_back("partition=" + partition);
	mStr.push_back("className=" + className);
	mStr.push_back("classID=" + UnicodeString(classID));
	mStr.push_back("categoryName=" + categoryName);
	mStr.push_back("categoryID=" + UnicodeString(categoryID));
	mStr.push_back("licWindowsName=" + licWindowsName);
	mStr.push_back("licWindowsID=" + UnicodeString(licWindowsID));
	mStr.push_back("licOfficeName=" + licOfficeName);
	mStr.push_back("licOfficeID=" + UnicodeString(licOfficeID));
	mStr.push_back("respon=" + respon);
	mStr.push_back("purpose=" + purpose);
	mStr.push_back("place=" + place); // <===
	mStr.push_back("phone=" + phone); // <===
	mStr.push_back("inNumberARM=" + inNumberARM);
	mStr.push_back("inNumberHDD=" + inNumberHDD);
	mStr.push_back("inNumberDeclr=" + inNumberDeclr);
	mStr.push_back("inNumberFormulyar=" + inNumberFormulyar);
	mStr.push_back("inNumberWork=" + inNumberWork);
	mStr.push_back("inNumberPerson=" + inNumberPerson);
	mStr.push_back("inRespon=" + inRespon); // <===
	mStr.push_back("inAdminBP=" + inAdminBP); // <===
	mStr.push_back("comPoliticInstall=" + comPoliticInstall);
	mStr.push_back("comContrUSB=" + comContrUSB);
	mStr.push_back("comMultiUSERS=" + comMultiUSERS);
	mStr.push_back("politicInstall=" + UnicodeString(politicInstall));
	mStr.push_back("contrUSB=" + UnicodeString(contrUSB));
	mStr.push_back("multiUSERS=" + UnicodeString(multiUSERS));
	return mStr;
}
std::vector<UnicodeString> Arm::mStrLastGrub() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("[lastGrub]");
	mStr.push_back("lastGrubDate=" + histGr.date);
	mStr.push_back("lastGrubUser=" + histGr.user);
	return mStr;
}
std::vector<UnicodeString> Arm::mStrInfoArmEset() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("[infoESET]");
	mStr.push_back("dirMirror=" + eset.dirMirror);
	mStr.push_back("autoUpdate=" + UnicodeString(eset.autoUpdate));
	mStr.push_back("lastUpdateDate=");
	mStr.push_back("lastUpdateUser=");
	mStr.push_back("lastUpdateArchive=");
	return mStr;
}
//генерация строки с датой последнего Граба
UnicodeString Arm::lastGrub() {
	UnicodeString str = histGr.date;
	if (histGr.user.IsEmpty() == false) {
		str = str + " (" + histGr.user + ")";
	}
	return str;
}
//чтение даных из файла
bool Arm::readFromFile() {
	UnicodeString dir = "C:\\ProgramData\\GRUBer\\";
	//новый INI файл
	if (FileExists(dir + "gruber_info.ini")) {
		TStringList *file = new TStringList;
		file->LoadFromFile(dir + "gruber_info.ini", TEncoding::UTF8);
        int vers = findParam(file, "[iniVersion]", "version").ToIntDef(1);
		if (vers >= 2) {
			number_UVs = findParam(file, "[infoGrubARM]", "number_UVs").ToIntDef(0);
			number_OK = findParam(file, "[infoGrubARM]", "number_OK").ToIntDef(0);
			place = findParam(file, "[infoGrubARM]", "place");
			phone = findParam(file, "[infoGrubARM]", "phone");
			inRespon = findParam(file, "[infoGrubARM]", "inRespon");
			inAdminBP = findParam(file, "[infoGrubARM]", "inAdminBP");
		} else {
			number_UVs = findParam(file, "[infoGrubARM]", "number").ToIntDef(0);
        }
		histGr.date = findParam(file, "[lastGrub]", "lastGrubDate");
		histGr.user = findParam(file, "[lastGrub]", "lastGrubUser");
		partition = findParam(file, "[infoGrubARM]", "partition");
		classID = findParam(file, "[infoGrubARM]", "classID").ToIntDef(0);
		categoryID = findParam(file, "[infoGrubARM]", "categoryID").ToIntDef(0); //?
		licWindowsID = findParam(file, "[infoGrubARM]", "licWindowsID").ToIntDef(0);
		licOfficeID = findParam(file, "[infoGrubARM]", "licOfficeID").ToIntDef(0);
		className = findParam(file, "[infoGrubARM]", "className");
		categoryName = findParam(file, "[infoGrubARM]", "categoryName");
		licWindowsName = findParam(file, "[infoGrubARM]", "licWindowsName");
		licOfficeName = findParam(file, "[infoGrubARM]", "licOfficeName");
		respon = findParam(file, "[infoGrubARM]", "respon");
		purpose = findParam(file, "[infoGrubARM]", "purpose"); // ***
		inNumberARM = findParam(file, "[infoGrubARM]", "inNumberARM");
		inNumberHDD = findParam(file, "[infoGrubARM]", "inNumberHDD");
		inNumberDeclr = findParam(file, "[infoGrubARM]", "inNumberDeclr");
		inNumberFormulyar = findParam(file, "[infoGrubARM]", "inNumberFormulyar");
		inNumberWork = findParam(file, "[infoGrubARM]", "inNumberWork");
		inNumberPerson = findParam(file, "[infoGrubARM]", "inNumberPerson");
		comPoliticInstall = findParam(file, "[infoGrubARM]", "comPoliticInstall");
		comContrUSB = findParam(file, "[infoGrubARM]", "comContrUSB");
		comMultiUSERS = findParam(file, "[infoGrubARM]", "comMultiUSERS");
		politicInstall = findParam(file, "[infoGrubARM]", "politicInstall").ToIntDef(0);
		contrUSB = findParam(file, "[infoGrubARM]", "contrUSB").ToIntDef(0);
		multiUSERS = findParam(file, "[infoGrubARM]", "multiUSERS").ToIntDef(0);
		eset.autoUpdate = findParam(file, "[infoESET]", "autoUpdate").ToIntDef(1);
		eset.dirMirror = findParam(file, "[infoESET]", "dirMirror");
		coment = findCategory(file, "[comment]");
		return true;
	}
	//старые файлы
	if (FileExists(dir + "info_001.dat")) {
		TStringList *infoDatIm = new TStringList;
		infoDatIm->LoadFromFile(dir + "info_001.dat", TEncoding::UTF8);
		number_UVs = (infoDatIm->Strings[1]).ToIntDef(0);
		partition = infoDatIm->Strings[2];
		categoryID = (infoDatIm->Strings[3]).ToIntDef(0) + 1;
		if (categoryID == 0) categoryName = "Особистий";
		if (categoryID == 1) categoryName = "НТ без підключеня";
		if (categoryID == 2) categoryName = "НТ з \"Інтернет\"";
		if (categoryID == 3) categoryName = "НТ з \"Дніпро\"";
		if (categoryID == 4) categoryName = "ДСК";
		if (categoryID == 5) categoryName = "Таємно";
		if (categoryID == 6) categoryName = "Цілком Таємно";
		coment.push_back(infoDatIm->Strings[4]);
		respon = infoDatIm->Strings[5];
		if(infoDatIm->Count == 7) {
			if (infoDatIm->Strings[6] == "auto")
				eset.autoUpdate = true;
			else {
				eset.autoUpdate = false;
				if(!infoDatIm->Strings[6].IsEmpty()) eset.dirMirror = infoDatIm->Strings[6];
			}
		}
		histGr.date = infoDatIm->Strings[0];
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
/* сеттери */
// ручной ввод по компу
void Arm::setNumber_UVs(int i) { number_UVs = i; }
void Arm::setNumber_OK(int i) { number_OK = i; }
void Arm::setPartition(UnicodeString str) { partition = str; }
void Arm::setClass(UnicodeString str, int i) { className = str; classID = i; }
void Arm::setCategory(UnicodeString str, int i) { categoryName = str; categoryID = i; }
void Arm::setLicWindows(UnicodeString str, int i) { licWindowsName = str; licWindowsID = i; }
void Arm::setLicOffice(UnicodeString str, int i) { licOfficeName = str; licOfficeID = i; }
void Arm::setRespon(UnicodeString str) { respon = str; }
void Arm::setPurpose(UnicodeString str) { purpose = str; }
void Arm::setPlace(UnicodeString str) { place = str; } // <===
void Arm::setPhone(UnicodeString str) { phone = str; } // <===
// коментарий
void Arm::setComent(std::vector<UnicodeString> vStr) { coment = vStr; }
// есет
void Arm::setEsetDir(UnicodeString str) { eset.dirMirror = str; }
void Arm::setEsetAutoUpdate(bool i) { eset.autoUpdate = i; }
// последний граб
void Arm::setLastGrub(UnicodeString user, UnicodeString date) { histGr.date = date; histGr.user = user; }
// по докам
void Arm::setInNumberARM (UnicodeString str) { inNumberARM=str; }
void Arm::setInNumberHDD (UnicodeString str) { inNumberHDD=str; }
void Arm::setInNumberDeclr (UnicodeString str) { inNumberDeclr=str; }
void Arm::setInNumberFormulyar (UnicodeString str) { inNumberFormulyar=str; }
void Arm::setInNumberWork (UnicodeString str) { inNumberWork=str; }
void Arm::setInNumberPerson (UnicodeString str) { inNumberPerson=str; }
void Arm::setInRespon (UnicodeString str) { inRespon = str; } // <===
void Arm::setInAdminBP (UnicodeString str) { inAdminBP = str; } // <===
// ---
void Arm::setComPoliticInstall (UnicodeString str) { comPoliticInstall=str; }
void Arm::setComContrUSB (UnicodeString str) { comContrUSB=str; }
void Arm::setComMultiUSERS (UnicodeString str) { comMultiUSERS=str; }
void Arm::setPoliticInstall (bool i) { politicInstall = i; }
void Arm::setContrUSB (bool i) { contrUSB = i; }
void Arm::setMultiUSERS (bool i) { multiUSERS = i; }
//---------------------------------------------------------------------------
/* геттери */
UnicodeString Arm::getDesktopName() { return desktopName; }
// ручной ввод по компу
int Arm::getNumber_UVs() { return number_UVs; }
int Arm::getNumber_OK() { return number_OK; }
UnicodeString Arm::getPartition() { return partition; }
UnicodeString Arm::getClassName() { return className; }
UnicodeString Arm::getCategoryName() { return categoryName; }
int Arm::getClassID() { return classID; }
int Arm::getCategoryID() { return categoryID; }
UnicodeString Arm::getRespon() { return errCheck(respon); }
UnicodeString Arm::getPurpose() { return errCheck(purpose); }
UnicodeString Arm::getPlace() { return errCheck(place); } // <===
UnicodeString Arm::getPhone() { return errCheck(phone); } // <===
// коментарий
std::vector<UnicodeString> Arm::getComent() { return coment; }
UnicodeString Arm::getComentStr() {
   if (coment.empty()) return "";
	else return coment[0];
}
// серийники
UnicodeString Arm::getSerial() { return serial; }
UnicodeString Arm::getSerialMain() { return serialMain; }
UnicodeString Arm::getUUID() { return UUID; }
UnicodeString Arm::getSerial_mrb() { return serial_mrb; }
UnicodeString Arm::getCPUID() { return CPUID; }
UnicodeString Arm::getUnSerial() { return unSerial; }
// есет
UnicodeString Arm::getEsetDir() { return eset.dirMirror; }
bool Arm::getEsetAutoUpdate() { return eset.autoUpdate; }
// по докам
UnicodeString Arm::getInNumberARM() { return errCheck(inNumberARM); }
UnicodeString Arm::getInNumberHDD() { return errCheck(inNumberHDD); }
UnicodeString Arm::getInNumberDeclr() { return errCheck(inNumberDeclr); }
UnicodeString Arm::getInNumberFormulyar() { return errCheck(inNumberFormulyar); }
UnicodeString Arm::getInNumberWork() { return errCheck(inNumberWork); }
UnicodeString Arm::getInNumberPerson() { return errCheck(inNumberPerson); }
UnicodeString Arm::getInRespon() { return errCheck(inRespon); }// <===
UnicodeString Arm::getInAdminBP() { return errCheck(inAdminBP); }// <===
// по настройкам
UnicodeString Arm::getComPoliticInstall() { return errCheck(comPoliticInstall); }
UnicodeString Arm::getComContrUSB() { return errCheck(comContrUSB); }
UnicodeString Arm::getComMultiUSERS() { return errCheck(comMultiUSERS); }
bool Arm::getPoliticInstall() { return politicInstall; }
bool Arm::getContrUSB() { return contrUSB; }
bool Arm::getMultiUSERS() { return multiUSERS; }
// по лицензиям ПО
int Arm::getLicWindowsID() { return licWindowsID; }
int Arm::getLicOfficeID() { return licOfficeID; }
UnicodeString Arm::getLicWindowsName() { return licWindowsName; }
UnicodeString Arm::getLicOfficeName() { return licOfficeName; }
//---------------------------------------------------------------------------
