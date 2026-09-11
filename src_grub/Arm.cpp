//---------------------------------------------------------------------------

#pragma hdrstop

#include <memory>
#include <algorithm>

//#include "MainForm.h"
//#include "Help.h"
#include "Arm.h"
#include "Text.h"
#include "GetSMB.h"
#include "CrashHandler.h"

//===========================================================================
#pragma package(smart_init)
/* конструктор */
// curPC - глобальний об'єкт, тому цей конструктор виконується під час
// статичної ініціалізації, ЩЕ ДО виклику WinMain - жоден try/catch у самому
// WinMain чи SetUnhandledExceptionFilter (CrashHandler.h) фізично не встигає
// встановитися настільки рано. Якщо тут вилетить необроблений виняток (як
// сталося з некоректним значенням дати в gruber_info.ini) - процес падає
// миттєво, без жодного вікна й без шансу це впіймати ззовні. Тому весь вміст
// конструктора обгорнуто тут: у гіршому разі об'єкт лишиться частково
// заповненим (значення, присвоєні до моменту винятку - на місці, решта -
// дефолтні), але застосунок хоча б стартує і подробиці підуть у crash.log.
// (звичайний try/catch у тілі, а не function-try-block на самому Arm::Arm() -
// у function-try-block конструктора catch не може "проковтнути" виняток,
// той автоматично перекидається далі; а нам якраз треба, щоб об'єкт
// добудувався і застосунок стартував)
Arm::Arm()
{
try
{
	readFromFile();
	// получаем DesktopName
	DWORD bufCharCount = 32767;
	TCHAR infoBuf[32767];
	if( GetComputerName( infoBuf, &bufCharCount ) ) {
		desktopName = UnicodeString(infoBuf);
	} else desktopName = "ErrorNAME";
	// получаем данные из SMB - serial
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
		serialMain = L"Помилка SMBIOS_DATA!";
		UUID = L"Помилка SMBIOS_DATA!";
		serial_mrb = L"Помилка SMBIOS_DATA!";
		CPUID = L"Помилка SMBIOS_DATA!";
		manufacturer = L"Помилка SMBIOS_DATA!";
		productName = L"Помилка SMBIOS_DATA!";
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
//	unSerial = GetHashCRC32(toHash);
	unSerial = GetFastHash_CRC32(toHash);
	manufacturer = g.GetBiosString(dataSMB, SMB_TABLE_SYSTEM, 4);
	productName  = g.GetBiosString(dataSMB, SMB_TABLE_SYSTEM, 5);
	LocalFree(dataSMB); // GetSmbiosData() виділяє буфер через LocalAlloc
	// установленый софт
	read_soft();
	// пользователи системы
    read_user();
	// поточне мережеве з'єднання
	read_net();
}
catch (Exception &e)
{
	LogCrash("Arm::Arm", e.ClassName() + ": " + e.Message);
}
catch (std::exception &e)
{
	LogCrash("Arm::Arm", UnicodeString(e.what()));
}
catch (...)
{
	LogCrash("Arm::Arm", L"невідомий виняток");
}
}
//---------------------------------------------------------------------------
/* функции */
UnicodeString Arm::dirGrubName(UnicodeString prfPart, bool enPrfPart)
{
	UnicodeString str;
	str = "[";
	int number = Form1->Edit_NumberARM->Value;
	// number
	if (number == 0) {
		str = str + "--";
	} else str = str + UnicodeString(number);
	str = str + "][" + curDate() + "]";
	// partition
	if (prfPart.IsEmpty() || !enPrfPart) {
		str = str + partition;
	} else str = str + prfPart + "_" + partition;
	// serial
	if (serial == "ErrorSN") {
		str = str + "#(" + unSerial + ")" + L"БезСН";
	}
	else str = str + "#(" + unSerial + ")" + serial;
	// category
	str = str + "#" + categoryNameShort;
	return fixDirName(str);
}
void Arm::read_soft() {
	softInstall = installSoft();
	softBlock = blockInstallSoft(softInstall);
}
void Arm::read_user() {
	users = currentUsers();
}
// Перечитуємо усі фізичні адаптери з системи. Для кожного активного зараз -
// оновлюємо дату останньої активності на "зараз". Для неактивних - шукаємо
// цей самий адаптер (за MAC) серед раніше збережених (readFromFile() вже
// виконано в конструкторі раніше) і успадковуємо його lastActive, тобто
// показуємо "коли він востаннє був активним".
void Arm::read_net() {
	std::vector<NetAdapterInfo> live = getAllNetAdapters();
	std::vector<NetAdapterInfo> prevAdapters = netAdapters;
	std::vector<NetAdapterInfo> merged;
	for (auto entry : live) {
		if (entry.active) {
			entry.lastActive = Now();
		} else if (!entry.mac.IsEmpty()) {
			for (auto &prev : prevAdapters) {
				if (prev.mac == entry.mac) {
					entry.lastActive = prev.lastActive;
					break;
				}
			}
		}
		merged.push_back(entry);
	}
	// активні - першими, далі за іменем
	std::sort(merged.begin(), merged.end(), [](const NetAdapterInfo &a, const NetAdapterInfo &b) {
		if (a.active != b.active) return a.active > b.active;
		return a.name < b.name;
	});
	netAdapters = merged;
}
//генерация строк в инфо файлы
std::vector<UnicodeString> Arm::mStrIniVersionNumber() {
	const int iniVersionNumber = 6;
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
	mStr.push_back("manufacturer=" + manufacturer);
	mStr.push_back("productName=" + productName);
	return mStr;
}
std::vector<UnicodeString> Arm::mStrSerial() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("[serial]");
	mStr.push_back("serialMain=" + serialMain);
	mStr.push_back("UUID=" + UUID);
	mStr.push_back("serial_mrb=" + serial_mrb);
	mStr.push_back("CPUID=" + CPUID);
	mStr.push_back("unSerial=" + unSerial);
	return mStr;
}
std::vector<UnicodeString> Arm::mStrStructures() {
	std::vector<UnicodeString> mStr;
	for (auto &s : structures) {
		if (s.number == 0 && s.partition.IsEmpty() && s.place.IsEmpty() && s.phone.IsEmpty()) continue;
		mStr.push_back("[structur_" + s.id + "]");
		mStr.push_back("name=" + s.name);
		mStr.push_back("number=" + UnicodeString(s.number));
		mStr.push_back("partition=" + s.partition);
		mStr.push_back("place=" + s.place);
		mStr.push_back("phone=" + s.phone);
	}
	return mStr;
}
std::vector<UnicodeString> Arm::mStrCurStructure() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("[curStructure]");
	mStr.push_back("id=" + curStructureId);
	mStr.push_back("name=" + curStructureName);
	return mStr;
}
std::vector<UnicodeString> Arm::mStrInfoArmGrub() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("[infoGrubARM]");
	mStr.push_back("partition=" + partition);
	mStr.push_back("className=" + className);
	mStr.push_back("classID=" + UnicodeString(classID));
	mStr.push_back("categoryName=" + categoryName);
	mStr.push_back("categoryNameShort=" + categoryNameShort);
	mStr.push_back("categoryID=" + UnicodeString(categoryID));
	mStr.push_back("licWindowsName=" + licWindowsName);
	mStr.push_back("licWindowsID=" + UnicodeString(licWindowsID));
	mStr.push_back("licOfficeName=" + licOfficeName);
	mStr.push_back("licOfficeID=" + UnicodeString(licOfficeID));
	mStr.push_back("respon=" + respon);
	mStr.push_back("purpose=" + purpose);
	mStr.push_back("place=" + place);
	mStr.push_back("phone=" + phone);
	mStr.push_back("inNumberARM=" + inNumberARM);
	mStr.push_back("inNumberHDD=" + inNumberHDD);
	mStr.push_back("inNumberDeclr=" + inNumberDeclr);
	mStr.push_back("inNumberFormulyar=" + inNumberFormulyar);
	mStr.push_back("inNumberWork=" + inNumberWork);
	mStr.push_back("inNumberPerson=" + inNumberPerson);
	mStr.push_back("inRespon=" + inRespon);
	mStr.push_back("inAdminBP=" + inAdminBP);
	mStr.push_back("lgpo=" + lgpo);             //<---
	mStr.push_back("controlUSB=" + controlUSB); //<---
	mStr.push_back("multiUser=" + multiUser);   //<---
	mStr.push_back("spzInstal=" + strGenFromVStr(spzInstal)); //<---
	return mStr;
}
std::vector<UnicodeString> Arm::mStrLastGrub() {
	std::vector<UnicodeString> mStr;
	mStr.push_back("[lastGrub]");
	mStr.push_back("lastGrubDate=" + histGr.date.FormatString("dd.MM.yy HH:mm"));
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
std::vector<UnicodeString> Arm::mStrInfoArmNet() {
	std::vector<UnicodeString> mStr;
	for (size_t i = 0; i < netAdapters.size(); i++) {
		NetAdapterInfo &a = netAdapters[i];
		mStr.push_back("[net-" + UnicodeString((int)(i + 1)) + "]");
		mStr.push_back("name=" + a.name);
		mStr.push_back("ip=" + a.ip);
		mStr.push_back("mac=" + a.mac);
		mStr.push_back("active=" + UnicodeString((int)a.active));
		mStr.push_back("lastActive=" + (a.lastActive == TDateTime(0.0) ? UnicodeString("") : a.lastActive.FormatString("dd.MM.yy HH:mm")));
	}
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
		std::unique_ptr<TStringList> fileOwner(new TStringList);
		TStringList *file = fileOwner.get();
		file->LoadFromFile(dir + "gruber_info.ini", TEncoding::UTF8);
		// определение версии файла
		int vers = findParam(file, "[iniVersion]", "version").ToIntDef(1);
        // общии для всех версий
		// findParam повертає "ERROR" якщо ключа нема - без errCheck() і перевірки
		// на порожній рядок TDateTime впаде на спробі розпарсити "ERROR" як дату
		// (EConvertError під час конструктора Arm(), тобто ще до появи вікна)
		UnicodeString lastGrubDateStr = errCheck(findParam(file, "[lastGrub]", "lastGrubDate"));
		if (!lastGrubDateStr.IsEmpty()) histGr.date = StrToDateTimeSafe(lastGrubDateStr, TDateTime(0.0));
		histGr.user = findParam(file, "[lastGrub]", "lastGrubUser");
		partition = findParam(file, "[infoGrubARM]", "partition");
		classID = findParam(file, "[infoGrubARM]", "classID").ToIntDef(0);
		categoryID = findParam(file, "[infoGrubARM]", "categoryID").ToIntDef(0);
		licWindowsID = findParam(file, "[infoGrubARM]", "licWindowsID").ToIntDef(0);
		licOfficeID = findParam(file, "[infoGrubARM]", "licOfficeID").ToIntDef(0);

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
		eset.autoUpdate = findParam(file, "[infoESET]", "autoUpdate").ToIntDef(1);
		eset.dirMirror = findParam(file, "[infoESET]", "dirMirror");
		// мережеві адаптери - секції [net-1], [net-2]... поки є ім'я в секції
		netAdapters.clear();
		for (int netIdx = 1; ; netIdx++) {
			UnicodeString netSection = "[net-" + UnicodeString(netIdx) + "]";
			UnicodeString netName = errCheck(findParam(file, netSection, "name"));
			if (netName.IsEmpty()) break; // секції більше немає
			NetAdapterInfo netEntry;
			netEntry.name = netName;
			netEntry.ip = errCheck(findParam(file, netSection, "ip"));
			netEntry.mac = errCheck(findParam(file, netSection, "mac"));
			netEntry.active = errCheck(findParam(file, netSection, "active")).ToIntDef(0);
			// findParam повертає "ERROR" якщо ключа нема - errCheck() прибирає
			// це до порожнього рядка, щоб TDateTime не впав на спробі
			// розпарсити "ERROR" як дату.
			UnicodeString netLastActiveStr = errCheck(findParam(file, netSection, "lastActive"));
			if (!netLastActiveStr.IsEmpty()) netEntry.lastActive = StrToDateTimeSafe(netLastActiveStr, TDateTime(0.0));
			netAdapters.push_back(netEntry);
		}
		coment = findCategory(file, "[comment]");
		// class FIX
		classID = findParam(file, "[infoGrubARM]", "classID").ToIntDef(0);
		className = findParam(file, "[infoGrubARM]", "className");
		if (className == L"АС-1") className = L"АС-1 (Без підключення)";
		if (className == L"АС-2") className = L"АС-2 (Локальна мережа)";
		if (className == L"АС-3") className = L"АС-3 (Глобальна мережа)";
		// версия --2--
		if (vers <= 3) {
			lgpo = findParam(file, "[infoGrubARM]", "comPoliticInstall");
			controlUSB = findParam(file, "[infoGrubARM]", "comContrUSB");
			multiUser = findParam(file, "[infoGrubARM]", "comMultiUSERS");
        }
		if (vers == 1) {
			pendingLegacyNumber = findParam(file, "[infoGrubARM]", "number").ToIntDef(0);
        }
		if (vers >= 1) {
			if (categoryID == 0) {categoryNameShort = L"ОС";}
			if (categoryID == 1) {categoryNameShort = L"НТ-БП";}
			if (categoryID == 2) {categoryNameShort = L"НТ-ІСД";}
			if (categoryID == 3) {categoryNameShort = L"НТ-ЕКМ";}
			if (categoryID == 4) {categoryNameShort = L"ДСК";}
			if (categoryID == 5) {categoryNameShort = L"Т";}
			if (categoryID == 6) {categoryNameShort = L"ЦТ";}
		}
		if (vers >= 2) {
			// useForNumberARMid зі старого формату свідомо не читаємо - в новій
			// моделі структур немає єдиного "активного" типу, обраного per-ПК
			if (vers < 6) {
				int uvs   = findParam(file, "[numberARM]", "UVs").ToIntDef(0);
				int uvsL  = findParam(file, "[numberARM]", "UVs_logist").ToIntDef(0);
				int ok    = findParam(file, "[numberARM]", "OK").ToIntDef(0);
				int okL   = findParam(file, "[numberARM]", "OK_logist").ToIntDef(0);
				setStructureNumber(STRUCT_ID_UVS,        L"УВ(с) \"Південь\"",             uvs);
				setStructureNumber(STRUCT_ID_UVS_LOGIST, L"УВ(с) \"Південь\" - Логістика", uvsL);
				setStructureNumber(STRUCT_ID_OK,         L"ОК \"Південь\"",                ok);
				setStructureNumber(STRUCT_ID_OK_LOGIST,  L"ОК \"Південь\" - Логістика",     okL);
			}
			place = findParam(file, "[infoGrubARM]", "place");
			phone = findParam(file, "[infoGrubARM]", "phone");
			inRespon = findParam(file, "[infoGrubARM]", "inRespon");
			inAdminBP = findParam(file, "[infoGrubARM]", "inAdminBP");
		}
		if (vers >= 3) {
			categoryNameShort = findParam(file, "[infoGrubARM]", "categoryNameShort");
		}
		if (vers >= 4) {
			lgpo = findParam(file, "[infoGrubARM]", "lgpo");			 //<--
			controlUSB = findParam(file, "[infoGrubARM]", "controlUSB"); //<--
			multiUser = findParam(file, "[infoGrubARM]", "multiUser");   //<--
			spzInstal = vStrGenFromStr(findParam(file, "[infoGrubARM]", "spzInstal"));//<---
		}
		if (vers < 6) {
			// partition/place/phone (та, для vers==1, окремий "number") у старих
			// версіях завжди єдині - якій зі структур їх віднести, неоднозначно,
			// тож просимо техніка обрати при старті форми (FormCreate)
			if (!partition.IsEmpty() || !place.IsEmpty() || !phone.IsEmpty() || pendingLegacyNumber != 0) {
				pendingLegacyMigration = true;
				pendingLegacyPartition = partition;
				pendingLegacyPlace = place;
				pendingLegacyPhone = phone;
			}
		}
		if (vers >= 6) {
			structures.clear();
			for (auto &id : findSectionIds(file, "[structur_")) {
				UnicodeString sec = "[structur_" + id + "]";
				StructurePcData s;
				s.id = id;
				s.name = errCheck(findParam(file, sec, "name"));
				s.number = findParam(file, sec, "number").ToIntDef(0);
				s.partition = errCheck(findParam(file, sec, "partition"));
				s.place = errCheck(findParam(file, sec, "place"));
				s.phone = errCheck(findParam(file, sec, "phone"));
				structures.push_back(s);
			}
		}
		return true;
	}
	//старые файлы
	if (FileExists(dir + "info_001.dat")) {
		std::unique_ptr<TStringList> infoDatIm(new TStringList);
		infoDatIm->LoadFromFile(dir + "info_001.dat", TEncoding::UTF8);
		pendingLegacyNumber = (infoDatIm->Strings[1]).ToIntDef(0);
		partition = infoDatIm->Strings[2];
		if (!partition.IsEmpty() || pendingLegacyNumber != 0) {
			pendingLegacyMigration = true;
			pendingLegacyPartition = partition;
		}
		categoryID = (infoDatIm->Strings[3]).ToIntDef(0) + 1;
		if (categoryID == 0) {categoryName = L"Особистий"; categoryNameShort = L"ОС";}
		if (categoryID == 1) {categoryName = L"НТ без підключеня"; categoryNameShort = L"НТ-БП";}
		if (categoryID == 2) {categoryName = L"НТ з \"Інтернет\""; categoryNameShort = L"НТ-ІСД";}
		if (categoryID == 3) {categoryName = L"НТ з \"Дніпро\""; categoryNameShort = L"НТ-ЕКМ";}
		if (categoryID == 4) {categoryName = L"ДСК"; categoryNameShort = L"ДСК";}
		if (categoryID == 5) {categoryName = L"Таємно"; categoryNameShort = L"Т";}
		if (categoryID == 6) {categoryName = L"Цілком Таємно"; categoryNameShort = L"ЦТ";}
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
		if (!infoDatIm->Strings[0].IsEmpty()) histGr.date = StrToDateTimeSafe(infoDatIm->Strings[0], TDateTime(0.0));
		return true;
	}
	return false;
}
//---[сеттери]------------------------------------------------------------------------
/* сеттери */
// ручной ввод по компу
void Arm::set_structures(std::vector<StructurePcData> v) { structures = v; }
static std::vector<StructurePcData>::iterator findStructureIt(std::vector<StructurePcData> &v, UnicodeString id) {
	for (auto it = v.begin(); it != v.end(); ++it) if (it->id == id) return it;
	return v.end();
}
void Arm::setStructureNumber(UnicodeString id, UnicodeString name, int number) {
	auto it = findStructureIt(structures, id);
	if (it == structures.end()) {
		StructurePcData s; s.id = id; s.name = name; s.number = number;
		structures.push_back(s);
	} else { it->name = name; it->number = number; }
}
void Arm::setStructurePartition(UnicodeString id, UnicodeString name, UnicodeString partitionVal) {
	auto it = findStructureIt(structures, id);
	if (it == structures.end()) {
		StructurePcData s; s.id = id; s.name = name; s.partition = partitionVal;
		structures.push_back(s);
	} else { it->name = name; it->partition = partitionVal; }
}
void Arm::setStructurePlace(UnicodeString id, UnicodeString name, UnicodeString placeVal) {
	auto it = findStructureIt(structures, id);
	if (it == structures.end()) {
		StructurePcData s; s.id = id; s.name = name; s.place = placeVal;
		structures.push_back(s);
	} else { it->name = name; it->place = placeVal; }
}
void Arm::setStructurePhone(UnicodeString id, UnicodeString name, UnicodeString phoneVal) {
	auto it = findStructureIt(structures, id);
	if (it == structures.end()) {
		StructurePcData s; s.id = id; s.name = name; s.phone = phoneVal;
		structures.push_back(s);
	} else { it->name = name; it->phone = phoneVal; }
}
void Arm::setCurStructureSelection(UnicodeString id, UnicodeString name) { curStructureId = id; curStructureName = name; }
void Arm::applyPendingLegacyMigration(UnicodeString targetStructureId, UnicodeString targetStructureName) {
	if (!targetStructureId.IsEmpty()) {
		if (pendingLegacyNumber != 0) setStructureNumber(targetStructureId, targetStructureName, pendingLegacyNumber);
		if (!pendingLegacyPartition.IsEmpty()) setStructurePartition(targetStructureId, targetStructureName, pendingLegacyPartition);
		if (!pendingLegacyPlace.IsEmpty()) setStructurePlace(targetStructureId, targetStructureName, pendingLegacyPlace);
		if (!pendingLegacyPhone.IsEmpty()) setStructurePhone(targetStructureId, targetStructureName, pendingLegacyPhone);
	}
	clearPendingLegacyMigration();
}
void Arm::clearPendingLegacyMigration() {
	pendingLegacyMigration = false;
	pendingLegacyPartition = ""; pendingLegacyPlace = ""; pendingLegacyPhone = "";
	pendingLegacyNumber = 0;
}
void Arm::setPartition(UnicodeString str) { partition = str; }
void Arm::setClass(UnicodeString str, int i) { className = str; classID = i; }
void Arm::setCategory(UnicodeString str, int i) {
	categoryName = str;
	categoryID = i;
	if (categoryID == 0) categoryNameShort = L"ОС";
	if (categoryID == 1) categoryNameShort = L"НТ-БП";
	if (categoryID == 2) categoryNameShort = L"НТ-ІСД";
	if (categoryID == 3) categoryNameShort = L"НТ-ЕКМ";
	if (categoryID == 4) categoryNameShort = L"ДСК";
	if (categoryID == 5) categoryNameShort = L"Т";
	if (categoryID == 6) categoryNameShort = L"ЦТ";
}
void Arm::setLicWindows(UnicodeString str, int i) { licWindowsName = str; licWindowsID = i; }
void Arm::setLicOffice(UnicodeString str, int i) { licOfficeName = str; licOfficeID = i; }
void Arm::setRespon(UnicodeString str) { respon = str; }
void Arm::setPurpose(UnicodeString str) { purpose = str; }
void Arm::setPlace(UnicodeString str) { place = str; }
void Arm::setPhone(UnicodeString str) { phone = str; }
// коментарий
void Arm::setComent(std::vector<UnicodeString> vStr) { coment = vStr; }
// есет
void Arm::setEsetDir(UnicodeString str) { eset.dirMirror = str; }
void Arm::setEsetAutoUpdate(bool i) { eset.autoUpdate = i; }
// последний граб
void Arm::setLastGrub(UnicodeString user, UnicodeString date) { histGr.date = StrToDateTimeSafe(date, TDateTime(0.0)); histGr.user = user; }
// по докам
void Arm::setInNumberARM (UnicodeString str) { inNumberARM=str; }
void Arm::setInNumberHDD (UnicodeString str) { inNumberHDD=str; }
void Arm::setInNumberDeclr (UnicodeString str) { inNumberDeclr=str; }
void Arm::setInNumberFormulyar (UnicodeString str) { inNumberFormulyar=str; }
void Arm::setInNumberWork (UnicodeString str) { inNumberWork=str; }
void Arm::setInNumberPerson (UnicodeString str) { inNumberPerson=str; }
void Arm::setInRespon (UnicodeString str) { inRespon = str; }
void Arm::setInAdminBP (UnicodeString str) { inAdminBP = str; }
// ---
void Arm::set_lgpo (UnicodeString str) { lgpo=str; }             //<--
void Arm::set_controlUSB (UnicodeString str) { controlUSB=str; } //<--
void Arm::set_multiUser (UnicodeString str) { multiUser=str; }   //<--
void Arm::set_spzInstal (std::vector<UnicodeString> vStr) { spzInstal=vStr; } //<--
//---[геттери]---------------------------------------------------------------
UnicodeString Arm::getDesktopName() { return desktopName; }
// ручной ввод по компу
std::vector<StructurePcData> Arm::get_structures() { return structures; }
StructurePcData Arm::getStructure(UnicodeString id) {
	for (auto &s : structures) if (s.id == id) return s;
	StructurePcData empty;
	empty.id = id;
	return empty;
}
UnicodeString Arm::getCurStructureId() { return curStructureId; }
UnicodeString Arm::getCurStructureName() { return curStructureName; }
bool Arm::needsLegacyMigrationPrompt() { return pendingLegacyMigration; }
UnicodeString Arm::getPartition() { return partition; }
UnicodeString Arm::getClassName() { return className; }
UnicodeString Arm::getCategoryName() { return categoryName; }
int Arm::getClassID() { return classID; }
int Arm::getCategoryID() { return categoryID; }
UnicodeString Arm::getRespon() { return errCheck(respon); }
UnicodeString Arm::getPurpose() { return errCheck(purpose); }
UnicodeString Arm::getPlace() { return errCheck(place); }
UnicodeString Arm::getPhone() { return errCheck(phone); }
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
UnicodeString Arm::get_manufacturer() { return manufacturer; }
UnicodeString Arm::get_productName() { return productName; }
// усі фізичні мережеві адаптери
std::vector<NetAdapterInfo> Arm::get_netAdapters() { return netAdapters; }
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
UnicodeString Arm::getInRespon() { return errCheck(inRespon); }
UnicodeString Arm::getInAdminBP() { return errCheck(inAdminBP); }
// по настройкам
UnicodeString Arm::get_lgpo() { return errCheck(lgpo); }			 //<--
UnicodeString Arm::get_controlUSB() { return errCheck(controlUSB); } //<--
UnicodeString Arm::get_multiUser() { return errCheck(multiUser); }   //<--
std::vector<UnicodeString> Arm::get_spzInstal() { return spzInstal; } //<--
// по лицензиям ПО
int Arm::getLicWindowsID() { return licWindowsID; }
int Arm::getLicOfficeID() { return licOfficeID; }
UnicodeString Arm::getLicWindowsName() { return licWindowsName; }
UnicodeString Arm::getLicOfficeName() { return licOfficeName; }
// софт
std::vector<program> Arm::get_softInstall() { return softInstall; }
std::vector<program> Arm::get_softBlock() { return softBlock; }
// пользователи
std::vector<User> Arm::get_users() { return users; }
//===========================================================================
