//---------------------------------------------------------------------------

#pragma hdrstop

#include "Config.h"
#include "Text.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/* Класс Config */
Config::Config() {
	debug = false;
	showLog = false;
	showEsetUpd = true;
	configFile = GetCurrentDir() + "\\GRUBer.ini";
	readFileIni();
}
void Config::readFileIni() {
	if (FileExists(configFile))
	{
		UnicodeString findStr;
		TStringList *infoFille = new TStringList;
		infoFille->LoadFromFile(configFile, TEncoding::UTF8);
		findStr = findParam(infoFille, "[settings]", "debug");
		if(findStr == 0 || findStr == 1) {
			debug = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[settings]", "showLog");
		if(findStr == 0 || findStr == 1) {
			showLog = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[settings]", "showEsetUpd");
		if(findStr == 0 || findStr == 1) {
			showEsetUpd = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[settings]", "grubUser");
		if(findStr != "0") {
			grubUser = findStr;
		}
		findStr = findParam(infoFille, "[genfile]", "oldGrub");
		if(findStr == 0 || findStr == 1 || findStr == 2) {
			oldGrub = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[genfile]", "oldGrubComent");
		if(findStr == 0 || findStr == 1) {
			oldGrubComent = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[genfile]", "oldGrubInfo");
		if(findStr == 0 || findStr == 1) {
			oldGrubInfo = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[genfile]", "oldGrubNet");
		if(findStr == 0 || findStr == 1) {
			oldGrubNet = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[genfile]", "oldGrubUsb");
		if(findStr == 0 || findStr == 1) {
			oldGrubUsb = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[genfile]", "newGrub");
		if(findStr == 0 || findStr == 1) {
			newGrub = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[genfile]", "license");
		if(findStr == 0 || findStr == 1) {
			license = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[genfile]", "audit");
		if(findStr == 0 || findStr == 1 || findStr == 2) {
			audit = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[genfile]", "esetLog");
		if(findStr == 0 || findStr == 1 || findStr == 2) {
			esetLog = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[arm]", "partition");
		if(findStr != "0") {
			partition = vStrGenFromStr(findStr);
		}
		findStr = findParam(infoFille, "[settings]", "prefixPartition");
		if(findStr != "ERROR") {
			prefixPartition = findStr;
		}
		findStr = findParam(infoFille, "[settings]", "enablePrefixPartition");
		if(findStr == 0 || findStr == 1) {
			enablePrefixPartition = findStr.ToInt();
		}
		findStr = findParam(infoFille, "[settings]", "forNumberARMid");  // <===
		if(findStr.ToIntDef(-1) >= 0 && findStr.ToIntDef(-1) <= 4) {
			forNumberARMid = findStr.ToInt();
		} else forNumberARMid = 0;
	}
}
void Config::saveFileIni() {
	TStringList *infoFille = new TStringList;
	/* формирование файла */
	// раздел
	infoFille->Add("[settings]");
	infoFille->Add("debug=" + UnicodeString(debug));
	infoFille->Add("showLog=" + UnicodeString(showLog));
	infoFille->Add("showEsetUpd=" + UnicodeString(showEsetUpd));
	infoFille->Add("grubUser=" + grubUser);
	infoFille->Add("prefixPartition=" + prefixPartition);
	infoFille->Add("enablePrefixPartition=" + UnicodeString(enablePrefixPartition));
	infoFille->Add("forNumberARMid=" + UnicodeString(forNumberARMid)); // <===
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
	infoFille->Add("[arm]");
	infoFille->Add("partition=" + strGenFromVStr(partition));
	// infoFille->Add("class=" + strGenFromVStr(armClass));
	// infoFille->Add("category=" + strGenFromVStr(category));
	/* конец формирования файла */
	infoFille->SaveToFile(configFile, TEncoding::UTF8); // запись в файл
	cacls(configFile); // [!]изменение прав на файл -- заменить на SetSecurityІnfo!
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
bool Config::getDebug()   { return debug; }
bool Config::getShowLog() { return showLog; }
bool Config::getShowEsetUpd() { return showEsetUpd; }
short Config::getOldGrub() { return oldGrub; }
bool Config::getOldGrubComent() { return oldGrubComent; };
bool Config::getOldGrubInfo()   { return oldGrubInfo; };
bool Config::getOldGrubNet()    { return oldGrubNet; };
bool Config::getOldGrubUsb()    { return oldGrubUsb; };
bool Config::getNewGrub()  { return newGrub; }
bool Config::getLicense()  { return license; }
short Config::getAudit()   { return audit; }
short Config::getEsetLog() { return esetLog; }
UnicodeString Config::getUser() { return grubUser; }
std::vector<UnicodeString> Config::getPartition() { return partition; }
std::vector<UnicodeString> Config::getArmClass()  { return armClass; }
std::vector<UnicodeString> Config::getCategory()  { return category; }
UnicodeString Config::getPrefixPartition() { return prefixPartition; }
bool Config::getEnablePrefixPartition() { return enablePrefixPartition; }
short Config::get_forNumberARMid() { return forNumberARMid; } // <===
// сеттеры
void Config::setDebug(bool i)   { debug = i; }
void Config::setShowLog(bool i) { showLog = i; }
void Config::setShowEsetUpd(bool i) { showEsetUpd = i; }
void Config::setOldGrub(short i) { oldGrub = i; }
void Config::setOldGrubComent(bool i) { oldGrubComent = i; }
void Config::setOldGrubInfo(bool i)   { oldGrubInfo = i; }
void Config::setOldGrubNet(bool i)    { oldGrubNet = i; }
void Config::setOldGrubUsb(bool i)    { oldGrubUsb = i; }
void Config::setNewGrub(bool i) { newGrub = i; }
void Config::setLicense(bool i) { license = i; }
void Config::setAudit(short i)   { audit = i; }
void Config::setEsetLog(short i) { esetLog = i; }
void Config::setUser(UnicodeString str) { grubUser = str; }
void Config::setPartition(std::vector<UnicodeString> vStr) { partition = vStr; }
void Config::setArmClass(std::vector<UnicodeString> vStr)  { armClass = vStr; }
void Config::setCategory(std::vector<UnicodeString> vStr)  { category = vStr; }
void Config::setPrefixPartition(UnicodeString str) { prefixPartition = str; }
void Config::setEnablePrefixPartition(bool i) { enablePrefixPartition = i; }
void Config::set_forNumberARMid(short i) { forNumberARMid = i; } // <===
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
