//---------------------------------------------------------------------------
#pragma hdrstop

#include "Help.h"
#include "Text.h"
#include "Fille.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
extern UnicodeString cmdEXE;
//---------------------------------------------------------------------------
/* Класс Dir */
Dir::Dir() {
	progFull = GetCurrentDir();
	baseName = "base";
	dateName = "[" + curDate() + "]";
	baseFull = progFull + "\\" + baseName;
	dateFull = baseFull + "\\" + dateName;
}
void Dir::check() {
	if (!DirectoryExists(baseFull)) CreateDir(baseFull);
	if (!DirectoryExists(dateFull)) CreateDir(dateFull);
	if (!DirectoryExists(grubFull)) CreateDir(grubFull);
}
// геттеры
UnicodeString Dir::getGrubFull() { return grubFull; }
UnicodeString Dir::getToolFull() { return (progFull + "\\tool"); }
// сеттеры
void Dir::setGrubFull (UnicodeString str) {
	grubName = str;
	grubFull = dateFull + "\\" + grubName;
}
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
	switch ((short)oldGrubComent + oldGrubInfo + oldGrubNet + oldGrubUsb) {
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
void Config::setPartition(std::vector<UnicodeString> vStr) { partition = vStr;}
void Config::setArmClass(std::vector<UnicodeString> vStr)  { armClass = vStr;}
void Config::setCategory(std::vector<UnicodeString> vStr)  { category = vStr;}
//---------------------------------------------------------------------------
/* Вывод логов */
void printLog(UnicodeString str)
{
	TDateTime* myTimeTemp = new TDateTime(Now());
	UnicodeString logTime = myTimeTemp->FormatString("hh:nn:ss");
	str = "[" + logTime + "] " + str;
	Form1->MemoLOG->Lines->Add(str);
}
void printLogDebug(bool debug, UnicodeString str)
{
	if (debug == 0) return;
	str = "[DEBUG]" + str;
	printLog(str);
}
//---------------------------------------------------------------------------
// проверка и установка CMD
UnicodeString cmdCheck(void)
{
	if (fileOpen("C:\\Windows\\System32\\cmd.exe"))
		return "C:\\Windows\\System32\\cmd.exe";
	if (fileOpen("C:\\Windows\\SysWOW64\\cmd.exe"))
		return "C:\\Windows\\SysWOW64\\cmd.exe";
	return "ERROR";
}
//---------------------------------------------------------------------------
/* Проверка прав админа */
bool IsAdminMode() {
	 bool fRet = false;
	 HANDLE hToken = NULL;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
		  TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
		  if( GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize ) ) {
            fRet = Elevation.TokenIsElevated;
		  }
    }
    if( hToken ) {
        CloseHandle( hToken );
	 }
	 return fRet;
}
//---------------------------------------------------------------------------
void setInfoArmToForm(Arm &curPC) {
	Form1->EditNumber->Value   = curPC.getNumber();
	Form1->EditPartition->Text = curPC.getPartition();
	Form1->EditArmClass->ItemIndex = curPC.getClassID();
	Form1->EditCategory->ItemIndex = curPC.getCategoryID();
	Form1->EditLicWin->ItemIndex    = curPC.getLicWindowsID();
	Form1->EditLicOffice->ItemIndex = curPC.getLicOfficeID();
	Form1->EditArmClass->Text  = curPC.getClassName();
	Form1->EditCategory->Text  = curPC.getCategoryName();
	Form1->EditLicWin->Text    = curPC.getLicWindowsName();
	Form1->EditLicOffice->Text = curPC.getLicOfficeName();
	Form1->EditRespon->Text    = curPC.getRespon();
	Form1->EditComent->Clear();
	for (auto str : curPC.getComent()) {
		Form1->EditComent->Lines->Add(str);
	}
	Form1->CheckBoxEsetAutoUpdate->Checked = curPC.getEsetAutoUpdate();
	if (curPC.getEsetAutoUpdate())
		Form1->StatusBar1->Panels->Items[1]->Text = " ESET оновлюеться самостійно";
	else Form1->StatusBar1->Panels->Items[1]->Text = " Бази не оновлювалися";
	Form1->EditEsetMirrorDir->Text = curPC.getEsetDir();
	//infoSetToFille(curPC);
//...
}
void setConfigToForm(Config &curConfig) {
	Form1->CheckBoxDebug->Checked = curConfig.getDebug();
	Form1->CheckBoxShowLog->Checked = curConfig.getShowLog();
	if (curConfig.getShowLog()) Form1->Width = 1024*Form1->ScaleFactor;
	else Form1->Width = 421*Form1->ScaleFactor;
    Form1->CheckBox_ShowEsetUpdate->Checked = curConfig.getShowEsetUpd();
	Form1->EditGrubUser->Text = curConfig.getUser();
	Form1->CheckBoxOldGrub->State = (TCheckBoxState)curConfig.getOldGrub();
	Form1->ComentTxt->Checked = curConfig.getOldGrubComent();
	Form1->InfoTxt->Checked = curConfig.getOldGrubInfo();
	Form1->NetTxt->Checked = curConfig.getOldGrubNet();
	Form1->UsbTxt->Checked = curConfig.getOldGrubUsb();
	Form1->CheckBoxNewGrub->Checked = curConfig.getNewGrub();
	Form1->CheckBoxLicense->Checked = curConfig.getLicense();
	Form1->CheckBoxAudit->State = (TCheckBoxState)curConfig.getAudit();
	//if (curConfig.getAudit() == 0) Form1->CheckBoxAudit->State = cbUnchecked;
	//if (curConfig.getAudit() == 2) Form1->CheckBoxAudit->State = cbGrayed;
	//if (curConfig.getAudit() == 1) Form1->CheckBoxAudit->State = cbChecked;
	Form1->CheckBoxEsetLog->State = (TCheckBoxState)curConfig.getEsetLog();
	//if (curConfig.getEsetLog() == 0) Form1->CheckBoxEsetLog->State = cbUnchecked;
	//if (curConfig.getEsetLog() == 2) Form1->CheckBoxEsetLog->State = cbGrayed;
	//if (curConfig.getEsetLog() == 1) Form1->CheckBoxEsetLog->State = cbChecked;
	//Form1->CheckBoxEsetLog->State = curConfig.getEsetLog();
	for(auto i : curConfig.getPartition()) Form1->EditPartition->Items->Add(i);
	for(auto i : curConfig.getArmClass()) Form1->EditArmClass->Items->Add(i);
	for(auto i : curConfig.getCategory()) Form1->EditCategory->Items->Add(i);
}
bool infoSetToFille(Arm &curPC)
{
	const UnicodeString dir = "C:\\ProgramData\\GRUBer\\";
	const UnicodeString file = "gruber_info.ini";
	TStringList *infoFille = new TStringList;
	/* формирование файла */
	// раздел даты и пользователя
	for(auto str : curPC.mStrLastGrub()) infoFille->Add(str);
	// раздел об АРМ
	for(auto str : curPC.mStrInfoArmGrubFull()) infoFille->Add(str);
	// раздел об ESET
	for(auto str : curPC.mStrInfoArmEset()) infoFille->Add(str);
	// раздел коментария
   infoFille->Add("[comment]");
	for (auto i : curPC.getComent()) {
		infoFille->Add(i);
	}
	infoFille->Add("#stop");
	/* конец формирования файла */
	if (!DirectoryExists(dir)) CreateDir(dir); 			 // проверка наличия папки
	infoFille->SaveToFile(dir + file, TEncoding::UTF8); // запись в файл
	cacls(dir + file); // [!]изменение прав на файл -- заменить на SetSecurityІnfo!
	return true;
}
//---------------------------------------------------------------------------


