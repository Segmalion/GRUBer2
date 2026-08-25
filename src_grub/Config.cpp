//---------------------------------------------------------------------------

#pragma hdrstop

#include <memory>

#include "Config.h"
#include "Text.h"
#include "CrashHandler.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// поточна версія формату GRUBer.ini - завжди пишеться при збереженні;
// файли без ключа ini_version (тобто старіші за появу цього поля) читаються як версія 0
const short CONFIG_INI_VERSION_CURRENT = 1;
//---------------------------------------------------------------------------
/* Класс Config */
// curConfig - глобальний об'єкт, конструктор виконується ще до WinMain (та
// ж причина, що й для Arm::Arm() в Arm.cpp - дивись коментар там), тому
// винятки тут ловимо прямо на місці, а не покладаємось на try/catch у
// WinMain чи SetUnhandledExceptionFilter, які на цьому етапі ще не діють.
Config::Config() {
try
{
	debug = false;
	showLog = false;
	showEsetUpd = true;
	configFile = GetCurrentDir() + "\\GRUBer.ini";
	readFileIni();
}
catch (Exception &e)
{
	LogCrash("Config::Config", e.ClassName() + ": " + e.Message);
}
catch (std::exception &e)
{
	LogCrash("Config::Config", UnicodeString(e.what()));
}
catch (...)
{
	LogCrash("Config::Config", "невідомий виняток");
}
}
void Config::readFileIni() {
	if (FileExists(configFile))
	{
		UnicodeString findStr;
		std::unique_ptr<TStringList> infoFilleOwner(new TStringList);
		TStringList *infoFille = infoFilleOwner.get();
		infoFille->LoadFromFile(configFile, TEncoding::UTF8);
		// ini_version - відсутній ключ = застарілий формат (версія 0)
		findStr = findParam(infoFille, "[settings]", "ini_version");
		iniVersion = findStr.ToIntDef(0);
		// debug
		findStr = findParam(infoFille, "[settings]", "debug");
		if(findStr == 0 || findStr == 1) debug = findStr.ToInt();
		// showLog
		findStr = findParam(infoFille, "[settings]", "showLog");
		if(findStr == 0 || findStr == 1) showLog = findStr.ToInt();
		// showEsetUpd
		findStr = findParam(infoFille, "[settings]", "showEsetUpd");
		if(findStr == 0 || findStr == 1) showEsetUpd = findStr.ToInt();
		// tempDir
		findStr = findParam(infoFille, "[settings]", "tempDir");
		if(findStr == 0 || findStr == 1) tempDir = findStr.ToInt();
		// grubUser
		findStr = findParam(infoFille, "[settings]", "grubUser");
		if(findStr != "0") grubUser = findStr;
		// oldGrub
		findStr = findParam(infoFille, "[genfile]", "oldGrub");
		if(findStr == 0 || findStr == 1 || findStr == 2) oldGrub = findStr.ToInt();
		// oldGrubComent
		findStr = findParam(infoFille, "[genfile]", "oldGrubComent");
		if(findStr == 0 || findStr == 1) oldGrubComent = findStr.ToInt();
		// oldGrubInfo
		findStr = findParam(infoFille, "[genfile]", "oldGrubInfo");
		if(findStr == 0 || findStr == 1) oldGrubInfo = findStr.ToInt();
		// oldGrubNet
		findStr = findParam(infoFille, "[genfile]", "oldGrubNet");
		if(findStr == 0 || findStr == 1) oldGrubNet = findStr.ToInt();
		// oldGrubUsb
		findStr = findParam(infoFille, "[genfile]", "oldGrubUsb");
		if(findStr == 0 || findStr == 1) oldGrubUsb = findStr.ToInt();
		// newGrub
		findStr = findParam(infoFille, "[genfile]", "newGrub");
		if(findStr == 0 || findStr == 1) newGrub = findStr.ToInt();
		// license
		findStr = findParam(infoFille, "[genfile]", "license");
		if(findStr == 0 || findStr == 1) license = findStr.ToInt();
		// audit
		findStr = findParam(infoFille, "[genfile]", "audit");
		if(findStr == 0 || findStr == 1 || findStr == 2) audit = findStr.ToInt();
		// esetLog
		findStr = findParam(infoFille, "[genfile]", "esetLog");
		if(findStr == 0 || findStr == 1 || findStr == 2) esetLog = findStr.ToInt();
		// prefixPartition
		findStr = findParam(infoFille, "[settings]", "prefixPartition");
		if(findStr != "ERROR") prefixPartition = findStr;
		// enablePrefixPartition
		findStr = findParam(infoFille, "[settings]", "enablePrefixPartition");
		if(findStr == 0 || findStr == 1) enablePrefixPartition = findStr.ToInt();
		// defaultStructureId
		findStr = findParam(infoFille, "[settings]", "defaultStructureId");
		defaultStructureId = errCheck(findStr);
		// lgpo <--
		findStr = findParam(infoFille, "[list]", "lgpo");
		if(!findStr.IsEmpty()) lgpo = vStrGenFromStr(findStr);
		// usb <--
		findStr = findParam(infoFille, "[list]", "usb");
		if(!findStr.IsEmpty()) usb = vStrGenFromStr(findStr);
		// user <--
		findStr = findParam(infoFille, "[list]", "user");
		if(!findStr.IsEmpty()) user = vStrGenFromStr(findStr);
		// spz <--
		findStr = findParam(infoFille, "[list]", "spz");
		if(!findStr.IsEmpty()) spz = vStrGenFromStr(findStr);
		// soft-blackList <--
		findStr = findParam(infoFille, "[list]", "softBlackList");
		if(!findStr.IsEmpty()) softBlackList = vStrGenFromStr(findStr);
		// soft-writeList <--
		findStr = findParam(infoFille, "[list]", "softWriteList");
		if(!findStr.IsEmpty()) softWriteList = vStrGenFromStr(findStr);
		// structures <--
		structures.clear();
		for (auto &id : findSectionIds(infoFille, "[structur_")) {
			UnicodeString sec = "[structur_" + id + "]";
			StructureDef s;
			s.id = id;
			s.name = errCheck(findParam(infoFille, sec, "name"));
			s.partition = vStrGenFromStr(errCheck(findParam(infoFille, sec, "partition")));
			structures.push_back(s);
		}
	}
	if (structures.empty()) {
		structures = defaultStructures();
		defaultStructureId = STRUCT_ID_UVS;
	}
	if (defaultStructureId.IsEmpty() && !structures.empty()) defaultStructureId = structures[0].id;
}
void Config::saveFileIni() {
	std::unique_ptr<TStringList> infoFille(new TStringList);
	/* формирование файла */
	// раздел
	infoFille->Add("[settings]");
	infoFille->Add("ini_version=" + UnicodeString(CONFIG_INI_VERSION_CURRENT));
	infoFille->Add("debug=" + UnicodeString(debug));
	infoFille->Add("showLog=" + UnicodeString(showLog));
	infoFille->Add("showEsetUpd=" + UnicodeString(showEsetUpd));
	infoFille->Add("tempDir=" + UnicodeString(tempDir));
	infoFille->Add("grubUser=" + grubUser);
	infoFille->Add("prefixPartition=" + prefixPartition);
	infoFille->Add("enablePrefixPartition=" + UnicodeString(enablePrefixPartition));
	infoFille->Add("defaultStructureId=" + defaultStructureId); // <===
	// раздел
	infoFille->Add("[genfile]");
	infoFille->Add("oldGrub=" + UnicodeString(oldGrub));
	infoFille->Add("oldGrubComent=" + UnicodeString(oldGrubComent));
	infoFille->Add("oldGrubInfo=" + UnicodeString(oldGrubInfo));
	infoFille->Add("oldGrubNet=" + UnicodeString(oldGrubNet));
	infoFille->Add("oldGrubUsb=" + UnicodeString(oldGrubUsb));
	infoFille->Add("newGrub=" + UnicodeString(newGrub));
	infoFille->Add("license=" + UnicodeString(license));
	infoFille->Add("audit=" + UnicodeString(audit));
	infoFille->Add("esetLog=" + UnicodeString(esetLog));
	//for(auto str : curPC.mStrInfoArmGrub()) infoFille->Add(str);
	// раздел
	infoFille->Add("[list]");
	infoFille->Add("lgpo=" + strGenFromVStr(lgpo)); //<--
	infoFille->Add("usb=" + strGenFromVStr(usb));   //<--
	infoFille->Add("user=" + strGenFromVStr(user)); //<--
	infoFille->Add("spz=" + strGenFromVStr(spz));   //<--
	infoFille->Add("softBlackList=" + strGenFromVStr(softBlackList)); //<--
	infoFille->Add("softWriteList=" + strGenFromVStr(softWriteList)); //<--
	// раздел структур
	for (auto &s : structures) {
		infoFille->Add("[structur_" + s.id + "]");
		infoFille->Add("name=" + s.name);
		infoFille->Add("partition=" + strGenFromVStr(s.partition));
	}
	/* конец формирования файла */
	infoFille->SaveToFile(configFile, TEncoding::UTF8); // запись в файл
	cacls(configFile); // [!]изменение прав на файл -- заменить на SetSecurityІnfo!
	iniVersion = CONFIG_INI_VERSION_CURRENT;
}
short Config::checkOldGrubState() {
	switch ((short)oldGrubComent + (short)oldGrubInfo + (short)oldGrubNet + (short)oldGrubUsb) {
	case 0:
		return 0;
	case 1:
	case 2:
	case 3:
		return 2;
	case 4:
		return 1;
    default:
		return 0;
	}
}
// геттеры
bool Config::getDebug()			{ return debug; }
bool Config::getShowLog() 		{ return showLog; }
bool Config::getShowEsetUpd()	{ return showEsetUpd; }
bool Config::getTempDir()		{ return tempDir; }
bool Config::getOldGrubComent() { return oldGrubComent; };
bool Config::getOldGrubInfo()   { return oldGrubInfo; };
bool Config::getOldGrubNet()    { return oldGrubNet; };
bool Config::getOldGrubUsb()    { return oldGrubUsb; };
bool Config::getNewGrub()  		{ return newGrub; }
bool Config::getLicense()  		{ return license; }
bool Config::getEnablePrefixPartition() { return enablePrefixPartition; }
short Config::getAudit()   { return audit; }
short Config::getEsetLog() { return esetLog; }
short Config::getOldGrub() { return oldGrub; }
short Config::get_iniVersion() { return iniVersion; }
std::vector<StructureDef> Config::get_structures() { return structures; }
UnicodeString Config::get_defaultStructureId() { return defaultStructureId; }
UnicodeString Config::getUser() { return grubUser; }
UnicodeString Config::getPrefixPartition() { return prefixPartition; }
std::vector<UnicodeString> Config::get_lgpo() { return lgpo; }; //<--
std::vector<UnicodeString> Config::get_usb()  { return usb; };  //<--
std::vector<UnicodeString> Config::get_user() { return user; }; //<--
std::vector<UnicodeString> Config::get_spz()  { return spz; };  //<--
std::vector<UnicodeString> Config::get_softBlackList() { return softBlackList; }; //<--
std::vector<UnicodeString> Config::get_softWriteList() { return softWriteList; }; //<--
// сеттеры
void Config::setDebug(bool i)   { debug = i; }
void Config::setShowLog(bool i) { showLog = i; }
void Config::setShowEsetUpd(bool i) { showEsetUpd = i; }
void Config::setTempDir(bool i) { tempDir = i; }
void Config::setOldGrubComent(bool i) { oldGrubComent = i; }
void Config::setOldGrubInfo(bool i)   { oldGrubInfo = i; }
void Config::setOldGrubNet(bool i)    { oldGrubNet = i; }
void Config::setOldGrubUsb(bool i)    { oldGrubUsb = i; }
void Config::setNewGrub(bool i) { newGrub = i; }
void Config::setLicense(bool i) { license = i; }
void Config::setEnablePrefixPartition(bool i) { enablePrefixPartition = i; }
void Config::set_structures(std::vector<StructureDef> v) { structures = v; }
void Config::set_defaultStructureId(UnicodeString id) { defaultStructureId = id; }
void Config::setOldGrub(short i) { oldGrub = i; }
void Config::setAudit(short i)   { audit = i; }
void Config::setEsetLog(short i) { esetLog = i; }
void Config::setUser(UnicodeString str) { grubUser = str; }
void Config::setPrefixPartition(UnicodeString str) { prefixPartition = str; }
void Config::set_lgpo(std::vector<UnicodeString> vStr) { lgpo = vStr; } //<--
void Config::set_usb(std::vector<UnicodeString> vStr) { usb = vStr; }   //<--
void Config::set_user(std::vector<UnicodeString> vStr) { user = vStr; } //<--
void Config::set_spz(std::vector<UnicodeString> vStr) { spz = vStr; }   //<--
void Config::set_softBlackList(std::vector<UnicodeString> vStr) { softBlackList = vStr; } //<--
void Config::set_softWriteList(std::vector<UnicodeString> vStr) { softWriteList = vStr; } //<--

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
