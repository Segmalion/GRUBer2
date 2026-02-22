//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.Hash.hpp>
#include <thread> // Required for std::this_thread::sleep_for
#include <chrono> // Required for std::chrono::seconds
#include <filesystem>
#pragma hdrstop

#include "MainForm.h"
#include "ComentForm.h"
#include "PartitionForm.h"
#include "DialogDirExist.h"
#include "About.h"
#include "ClearTemp.h"
#include "FormSerial.h"
#include "InstallSoft.h"
#include "Users.h"

#include "Arm.h"
#include "Config.h"
#include "Dir.h"

#include "RunApp.h"
#include "Help.h"
#include "Text.h"
#include "Fille.h"

#include "Th_Gruber.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
//---------------------------------------------------------------------------
//bool x64 = GetSystemWow64DirectoryW(nullptr, 0u);
//bool x64run;
//обявление переменных типа структуры
Config curConfig;
Arm curPC;
Dir curDir;
// infoEset curEset;
//обявление переменных
UnicodeString cmdEXE, curentDate;
bool th_Gruber_run=0, th_ClearFile_run=0, th_EsetUpdate_run=0;
bool th_Gruber_runMini, th_Gruber_runUSB;
bool stopBool=0, passBool=0, dirGrubRewrite, gruberStart=0;
bool checkDirExist;
std::vector<UnicodeString> vStrPartition;
bool grubActive = 0;
extern std::vector<UnicodeString> blockProgrammsNames;
struct defection {
	bool user;
	bool soft;
	bool eset;
} curDefection;
//---------------------------------------------------------------------------
extern const short vers1 = 0, vers2 = 3, vers3 = 1, vers4 = 3;
extern const UnicodeString versionApp = UnicodeString(vers1) + "."
							  + UnicodeString(vers2) + "."
							  + UnicodeString(vers3) + "."
							  + UnicodeString(vers4);
//---------------------------------------------------------------------------
std::vector<UnicodeString> fileInfoGrub() {
	std::vector<UnicodeString> vStr;
	// раздел версии файла
	for(auto str : curPC.mStrIniVersionNumber()) vStr.push_back(str);
	// раздел даты и пользователя
	for(auto str : curPC.mStrLastGrub()) vStr.push_back(str);
	// раздел номеров ПК
	for(auto str : curPC.mStrNumberARM()) vStr.push_back(str);
	// раздел серийников
	for(auto str : curPC.mStrSerial()) vStr.push_back(str);
	// раздел об АРМ-1
	for(auto str : curPC.mStrInfoArm()) vStr.push_back(str);
	// раздел об АРМ-2
	for(auto str : curPC.mStrInfoArmGrub()) vStr.push_back(str);
	// раздел об ESET
	for(auto str : curPC.mStrInfoArmEset()) vStr.push_back(str);
	// раздел коментария
	vStr.push_back("[comment]");
	for (auto str : curPC.getComent()) {
		vStr.push_back(str);
	}
	vStr.push_back("#stop");
	return vStr;
}
void changeEditDirColor() {
	if(DirectoryExists(curDir.getGrubFull())) {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x006E00;
		Form1->EditDirGrubName->Color = (TColor) 0xEAFFEA;
		if (!grubActive) Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer вже зібрано!";
	} else {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x00006E;
		Form1->EditDirGrubName->Color = (TColor) 0xEAEAFF;
		Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer не зібрано:(";
	}
	Form1->BtnGruberDirOpen->Enabled = DirectoryExists(curDir.getGrubFull());
	Form1->BtnParserOpen->Enabled = FileExists(curDir.getGrubFull() + "\\usb.txt");
}
UnicodeString appPath()
{
    TCHAR patch[_MAX_PATH+1];
	GetModuleFileName(NULL, patch, _MAX_PATH);
	return UnicodeString(patch);
}
void RestartApplicationRunas()
{
	UnicodeString setApp = appPath();
	ShellExecuteW(NULL, L"runas", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
	exit(1);
}
void showSoft() {
	bool i;
	std::vector<UnicodeString> sortList;
	std::vector<program> blockedInstalledSoft = curPC.get_softBlock();
	Form1->Memo1->Clear();
	if (blockedInstalledSoft.size() == 0) {
		Form1->Memo1->Lines->Add("Не знайдено!");
		curDefection.soft = false;
	} else {
		for(auto soft: blockedInstalledSoft) sortToVector(sortList, soft.name);
		for(auto str: sortList) Form1->Memo1->Lines->Add(str);
		curDefection.soft = true;
	}
}
void showUsers() {
	std::vector<User> usersList = curPC.get_users();
	Form1->Memo2->Clear();
	if (usersList.size() == 0) Form1->Memo2->Lines->Add("Нема юзерів... О_о");
	else {
		short admin_t = 0, user_t = 0, guest_t = 0;
		for(auto user: usersList) {
			UnicodeString str;
			if (user.priv == "ADMIN") {
				str = "Admin: ";
				admin_t++;
			}
			if (user.priv == "USER"){
				str = "User:  ";
				user_t++;
			}
			if (user.priv == "GUEST"){
				str = "Guest: ";
				guest_t++;
			}
			str = str + user.name;
			if (!(user.fullName.IsEmpty() || user.fullName == user.name)) str = str + " ("+ user.fullName + ")";
			if (user.password_age > 42 && user.priv != "ADMIN") str = str + " [Days PASS - " + user.password_age + "]";
			Form1->Memo2->Lines->Add(str);
		}
		if (admin_t == 1 && (user_t + guest_t) > 0) curDefection.user = false;
		if (admin_t == 1 && (user_t + guest_t) == 0) curDefection.user = true;
		if (admin_t > 1) curDefection.user = true;
	}
}
void checkEsetQuarantine() {
	UnicodeString dirSysQuarantine  = "C:\\Windows\\System32\\config\\systemprofile\\AppData\\Local\\ESET\\ESET Security\\Quarantine\\";
	UnicodeString dirUserQuarantine = "AppData\\Local\\ESET\\ESET Security\\Quarantine\\";
	patchList sysList, userList;
    // --- готовим список пользовательских папок (userDirList)---
	std::vector<UnicodeString> userListBad { //запрещеные пользователи
		"All Users",
		"Default",
		"Default User",
		"Public"
	};
	std::vector<UnicodeString> userDirList; //создаем вектор с папками пользователей
	// процедура поиска папок пользователей
	UnicodeString dirUser = "C:\\Users";
	TSearchRec srUser;
	if (!FindFirst(dirUser + "\\*.*", faAnyFile, srUser))
		do {
			if (!(srUser.Name == "." || srUser.Name == ".." || srUser.Name == "INFO.NQI")) { // это не трогаем
				if ((srUser.Attr & faDirectory) != 0) {
					if (!compareVectorAndString(srUser.Name, userListBad)) {
						userDirList.push_back(dirUser + "\\" + srUser.Name);
					}
				}
			}
		} while (!FindNext(srUser)); // ищем пока не найдем все
	FindClose(srUser);
	// --- готовим список всех файлов во временых папках ---
	// папка системного карантина
	patchList temp = scanDirToFille(dirSysQuarantine);
	sysList.list.insert(sysList.list.end(), temp.list.begin(), temp.list.end());
	sysList.countDir += temp.countDir ;
	sysList.countFille += temp.countFille ;
	sysList.size += temp.size;
	// папки карантина пользователей
	for (auto userDir: userDirList) {
		patchList temp = scanDirToFille(userDir + "\\" + dirUserQuarantine);
		userList.list.insert(userList.list.end(), temp.list.begin(), temp.list.end());
		userList.countDir += temp.countDir;
		userList.countFille += temp.countFille;
		userList.size += temp.size;
	}
	// подщет файлов в карантине
	int countSysQuarantineFille = 0;
	int countUserQuarantineFille = 0;
	int countQuarantineFille = 0;
	for (auto file: sysList.list) {
		if (!(compareInSring(file.str, "INFO.NQI") || file.dir)) countSysQuarantineFille ++;
	}
	for (auto file: userList.list) {
		if (!(compareInSring(file.str, "INFO.NQI") || file.dir)) countUserQuarantineFille ++;
	}
	countSysQuarantineFille = countSysQuarantineFille / 3;
	countUserQuarantineFille = countUserQuarantineFille / 3;
	countQuarantineFille = countSysQuarantineFille + countUserQuarantineFille;
	// вывод информации по карантину
	if (countQuarantineFille > 0) {
		Form1->Show_ESETQuarantine->Text = UnicodeString(countQuarantineFille);
		UnicodeString str = "В системі " + UnicodeString(countSysQuarantineFille)
			+ ", у користувачів " + UnicodeString(countUserQuarantineFille) + "...";
		Form1->Show_ESETQuarantine->Hint = str;
		curDefection.eset = true;
	} else {
		Form1->Show_ESETQuarantine->Text = "0";
		UnicodeString str = "Карантин порожній!";
		Form1->Show_ESETQuarantine->Hint = str;
        curDefection.eset = false;
	}
}
void checkDefection() {
	showSoft();
	showUsers();
    checkEsetQuarantine();
	Form1->PageControl_InfoTabs->Pages[1]->Caption = u"Перевірки"; // \uE10A(B) - все норм
	if (curDefection.soft || curDefection.user || curDefection.eset) {
		Form1->PageControl_InfoTabs->Pages[1]->Caption = u"\uE10AПеревірки\uE10A"; // \uE10A(B) - все норм
	}
	if (curDefection.soft) {
		Form1->Label_DefectionSoft->Font->Color = (TColor)clRed;
		Form1->Label_DefectionSoft->Font->Style = TFontStyles() << fsBold;
	} else {
		Form1->Label_DefectionSoft->Font->Color = (TColor)clWindowText;
		Form1->Label_DefectionSoft->Font->Style = TFontStyles() >> fsBold;
	}
	if (curDefection.user) {
		Form1->Label_DefectionUser->Font->Color = (TColor)clRed;
		Form1->Label_DefectionUser->Font->Style = TFontStyles() << fsBold;
	}else {
		Form1->Label_DefectionUser->Font->Color = (TColor)clWindowText;
		Form1->Label_DefectionUser->Font->Style = TFontStyles() >> fsBold;
	}
	if (curDefection.eset) {
		Form1->Label_checkQuarantineEset_1->Font->Color = (TColor)clRed;
		Form1->Label_checkQuarantineEset_1->Font->Style = TFontStyles() << fsBold;
	}else {
		Form1->Label_checkQuarantineEset_1->Font->Color = (TColor)clWindowText;
		Form1->Label_checkQuarantineEset_1->Font->Style = TFontStyles() >> fsBold;
	}
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	PageControl_SetInfo->TabIndex = 0;
	PageControl_InfoTabs->TabIndex = 0;
	// === проверка на необходимые файлы и папки
	if(checkConfigFileExist()) printLogDebug("Config fille OK");
	else {
		UnicodeString text = "Не вистачае файлів...";
		UnicodeString formCaption = "Щось пішло попі*ді...";
		if(Application->MessageBox( text.c_str(), formCaption.c_str(), MB_OK) == IDOK) {
			exit(0);
		}
	}
	// === выводим настройки & сохраненую инфу об АРМ
	setConfigToForm(curConfig);
	setInfoArmToForm(curPC);
	printLogDebug("{Count}=" + UnicodeString(Form1->CheckListBox_SPZ->Items->Count));
	//printLogDebug("{Count}=" + (Form1->CheckListBox_SPZ->Items->Strings[2]));
	/* === */
	if (x64() && (appPath() == GetCurrentDir() + "\\GRUBer_x32.exe")) {
		UnicodeString setApp = GetCurrentDir() + "\\GRUBer_x64.exe";
		ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
		exit(1);
	}
	/* === проверка прав админа === */
	UnicodeString admMode;
	if(IsAdminMode()) {
		printLogDebug("Запущено з правами Адміністратора!");
		Button_RestartAssAdmin->Enabled = false;
		BtnClearPC->Enabled = true;
		admMode = "AdminMode";
	} else {
		printLogDebug("Запущено без прав Адміністратора!");
		int number = Form1->Edit_NumberARM->Value;
		UnicodeString text = "Перезапустити GRUBer з правами Адміністратора?\n( ПК: "
			+ UnicodeString(number)
			+ ", Відділ.: " + UnicodeString(curPC.getPartition()) + " )";
		UnicodeString formCaption = "Нема прав Адміна.. :'(";
		if(Application->MessageBox( text.c_str(), formCaption.c_str(), MB_YESNO) == IDYES) {
				RestartApplicationRunas();
		}
		admMode = "UserMode";
	}
	/* === наполняем форму === */
	printLog(">>", "Запушенно GRUBer v." + versionApp);
	printLog(">>", "Останій граб: " + curPC.lastGrub());
	// --- проверка нарушений
	checkDefection();
	// --- заполняем строку с именем папки граба
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
	if (DirectoryExists(curDir.getGrubFull())) {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x006E00;
		Form1->EditDirGrubName->Color = (TColor) 0xEAFFEA;
	} else {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x00006E;
		Form1->EditDirGrubName->Color = (TColor) 0xEAEAFF;
	}
	// --- статус бар
	if (x64_run()) StatusBar1->Panels->Items[2]->Text = "v." + versionApp + " (x64_" + admMode + ") ";
	else StatusBar1->Panels->Items[2]->Text = "v." + versionApp + " (x32_" + admMode + ") ";
	// --- разное
	Label_infoForNumberARM->Caption = ComboBox_forNumberARM->Text; // тип номера ПК
	/* --- вывод дебаг инфы
	printLogDebug(curConfig.getDebug(), "{forNumberARM}=" + UnicodeString(curConfig.get_forNumberARMid()));
	printLogDebug(curConfig.getDebug(), "{number_UVs}=" + UnicodeString(curPC.getNumber_UVs()));
	printLogDebug(curConfig.getDebug(), "{number_UVs_logist}=" + UnicodeString(curPC.getNumber_UVs_logist()));
	printLogDebug(curConfig.getDebug(), "{number_OK}=" + UnicodeString(curPC.getNumber_OK()));
	printLogDebug(curConfig.getDebug(), "{number_OK_logist}=" + UnicodeString(curPC.getNumber_OK_logist()));
	*/
	gruberStart = 1;
}
//---------------------------------------------------------------------------
/* КНОПКИ */
// === запуск Граба
void __fastcall TForm1::BtnGruberRunClick(TObject *Sender) //Запуск Граба
{
	if (th_Gruber_run == false) {
		checkDirExist = true;
		th_Gruber_runMini = false; th_Gruber_runUSB=false;
		Th_Gruber *Thr = new Th_Gruber(true);
		Thr->Resume();
	}
}
void __fastcall TForm1::Gruber_MiniClick(TObject *Sender)
{
	//запускаем граб
	if (th_Gruber_run == false) {
		checkDirExist = false;
		th_Gruber_runMini = true; th_Gruber_runUSB=false;
		Th_Gruber *Thr = new Th_Gruber(true);
		Thr->Resume();
	}
}
void __fastcall TForm1::Gruber_USBClick(TObject *Sender)
{
	//запускаем граб
	if (th_Gruber_run == false) {
		checkDirExist = false;
		th_Gruber_runMini = false; th_Gruber_runUSB=true;
		Th_Gruber *Thr = new Th_Gruber(true);
		Thr->Resume();
	}
}
// === открыть редактор подразделений
void __fastcall TForm1::BtnEditPartitionClick(TObject *Sender)
{
	FormPartition->EditPartition->Lines = Form1->EditPartition->Items;
	FormPartition->ShowModal();
}
// === открыть папку Граба
void __fastcall TForm1::BtnGruberDirOpenClick(TObject *Sender)
{
	ShellExecuteW(NULL, L"open", curDir.getGrubFull().c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// === остановка Граба
// --- полная
void __fastcall TForm1::BtnGruberStopClick(TObject *Sender)
{
	stopBool = true;
}
// --- частичная
void __fastcall TForm1::РassClick(TObject *Sender)
{
	passBool = true;
}
// === сохранение настроек
void __fastcall TForm1::BtnSaveSetteingsClick(TObject *Sender)
{
	curConfig.saveFileIni();
}
// === запуск парсера
void __fastcall TForm1::BtnParserOpenClick(TObject *Sender)
{
	UnicodeString setApp = GetCurrentDir() + "\\GRUBer-Parser.exe";
	UnicodeString setArg = "/run /b " + curDir.getGrubFull();
	ShellExecuteW(NULL, L"open", setApp.c_str(), setArg.c_str(), NULL, SW_SHOWDEFAULT);
}
// === провека лицензий
void __fastcall TForm1::BtnLicenseClick(TObject *Sender)
{
	UnicodeString setApp = curDir.getToolFull() + "\\CheckActivationStatus\\CheckActivationStatus.exe";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// === общее инфо
void __fastcall TForm1::BtnInfoClick(TObject *Sender)
{
	UnicodeString setApp = curDir.getToolFull() + "\\scripts\\info_ps1\\Run.bat";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// === about form
void __fastcall TForm1::BtnAboutGruberClick(TObject *Sender)
{
	FormAbout->Position = (TPosition)7;
	FormAbout->ShowModal();
}
// === очистка временых файлов
void __fastcall TForm1::BtnClearPCClick(TObject *Sender)
{
	FormClearTempDir->Position = (TPosition)7;
	FormClearTempDir->ShowModal();
}
// === перезапуск от админа
void __fastcall TForm1::Button_RestartAssAdminClick(TObject *Sender)
{
	RestartApplicationRunas();
}
//---------------------------------------------------------------------------
/* Обновление ESET */
void __fastcall TForm1::BtnEditEsetMirrorDirClick(TObject *Sender)
{
	DirOpenEsetMirror->DefaultFolder = EditEsetMirrorDir->Text;
	DirOpenEsetMirror->Execute();
}
void __fastcall TForm1::DirOpenEsetMirrorFileOkClick(TObject *Sender, bool &CanClose)
{
	EditEsetMirrorDir->Text = DirOpenEsetMirror->FileName;
}
void __fastcall TForm1::CheckBox_ShowEsetUpdateClick(TObject *Sender)
{
	curConfig.setShowEsetUpd(CheckBox_ShowEsetUpdate->Checked);
}
void __fastcall TForm1::BtnEsetUpdateClick(TObject *Sender)
{
	bool oldUPDarch = 0; // 0-old 1-new
	UnicodeString archUpd;
	if (FileExists(GetCurrentDir() + "\\update.7z")) {
		archUpd = GetCurrentDir() + "\\update.7z";
	} else if (FileExists(GetCurrentDir() + "\\update_x32.upd")
		 && FileExists(GetCurrentDir() + "\\update_x64.upd")) {
		if (x64()) archUpd = GetCurrentDir() + "\\update_x64.upd";
		else archUpd = GetCurrentDir() + "\\update_x32.upd";
	} else {
		printLog("!!", "ESET-Update: Немає архіву з базами!");
		return;
    }

	printLog(">>", "ESET-Update: Оновленя бази Eset...");
	BtnEsetUpdate->Enabled = false;
	StatusBar1->Panels->Items[1]->Text = " Оновленя бази Eset...";
	if (FileExists(curPC.getEsetDir() + "\\dll\\update.ver"))
		deleteDir(curPC.getEsetDir());
	//запуск обновления
	UnicodeString app32 = curDir.getToolFull() + "\\7zip\\32\\7za.exe";
	UnicodeString app64 = curDir.getToolFull() + "\\7zip\\64\\7za.exe";
	if (curConfig.getShowEsetUpd()) app32 = curDir.getToolFull() + "\\7zip\\32\\7zG.exe";
	if (curConfig.getShowEsetUpd()) app64 = curDir.getToolFull() + "\\7zip\\64\\7zG.exe";
	RunApp esetBaseUnpack {
		app32,
		app64,
		"x -y -o\"" + curPC.getEsetDir() + "\" \"" + archUpd};
	esetBaseUnpack.run(!curConfig.getShowEsetUpd());
	//------
	if (esetBaseUnpack.checkErr()){
		//ошибочка вышла...
		printLog("!!", "ESET-Update: Щось пішло НЕ так...");
		BtnEsetUpdate->Enabled = true;
		return;
	}
	printLog("OK", "ESET-Update: Бази оновленно!");
    BtnEsetUpdate->Enabled = true;
	StatusBar1->Panels->Items[1]->Text = " Бази оновленно!";
	if (FileExists("c:\\Program Files\\ESET\\ESET Security\\ermm.exe")) {
		RunApp esetBaseUpdate {"c:\\Program Files\\ESET\\ESET Security\\ermm.exe",
			NULL, "start update"};
		esetBaseUpdate.run();
	}
}
//---------------------------------------------------------------------------
/* Изменение полей */
void __fastcall TForm1::Edit_NumberARMChange(TObject *Sender)
{
	//curPC.setNumber_OK(Edit_NumberARM->Value);
	if (ComboBox_forNumberARM->ItemIndex == 1) {
		curPC.setNumber_UVs(Edit_NumberARM->Value);
	}
	if (ComboBox_forNumberARM->ItemIndex == 2) {
		curPC.setNumber_UVs_logist(Edit_NumberARM->Value);
	}
	if (ComboBox_forNumberARM->ItemIndex == 3) {
		curPC.setNumber_OK(Edit_NumberARM->Value);
	}
	if (ComboBox_forNumberARM->ItemIndex == 4) {
		curPC.setNumber_OK_logist(Edit_NumberARM->Value);
	}
	LabEdit_NumUVs->Text = curPC.getNumber_UVs();
	LabEdit_NumUVsO->Text = curPC.getNumber_UVs_logist();
	LabEdit_NumOK->Text = curPC.getNumber_OK();
	LabEdit_NumOKO->Text = curPC.getNumber_OK_logist();
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
}
void __fastcall TForm1::EditPartitionChange(TObject *Sender)
{
	curPC.setPartition(EditPartition->Text);
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
}
void __fastcall TForm1::EditArmClassChange(TObject *Sender)
{
	curPC.setClass(EditArmClass->Text, EditArmClass->ItemIndex);
}
void __fastcall TForm1::EditCategoryChange(TObject *Sender)
{
	short indx = EditCategory->ItemIndex;
	curPC.setCategory(EditCategory->Items->Strings[indx], indx);
	if (indx == 0 || indx == 2 || indx == 3 || indx == 4) {
		EditArmClass->Enabled = true;
		if (indx == 0) EditArmClass->ItemIndex = 0;
		if (indx == 2) EditArmClass->ItemIndex = 3;
		if (indx == 3) EditArmClass->ItemIndex = 2;
        if (indx == 4) EditArmClass->ItemIndex = 1;
	}
	else {
		EditArmClass->Enabled = false;
		EditArmClass->ItemIndex = 1;
	}
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
}
void __fastcall TForm1::EditResponChange(TObject *Sender)
{
	curPC.setRespon(EditRespon->Text);
}
void __fastcall TForm1::EditPurposeChange(TObject *Sender)
{
	curPC.setPurpose(EditPurpose->Text);
}
void __fastcall TForm1::Edit_PlaceChange(TObject *Sender) // <===
{
	curPC.setPlace(Edit_Place->Text);
}
void __fastcall TForm1::Edit_PhoneChange(TObject *Sender) // <===
{
	curPC.setPhone(Edit_Phone->Text);
}
void __fastcall TForm1::EditLicWinChange(TObject *Sender)
{
	curPC.setLicWindows(EditLicWin->Text, EditLicWin->ItemIndex);
}
void __fastcall TForm1::EditLicOfficeChange(TObject *Sender)
{
	curPC.setLicOffice(EditLicOffice->Text, EditLicOffice->ItemIndex);
}
void __fastcall TForm1::EditComentChange(TObject *Sender)
{
	std::vector<UnicodeString> vStr;
	for (auto i : Form1->EditComent->Lines) {
		vStr.push_back(i);
	}
	curPC.setComent(vStr);
}
void __fastcall TForm1::EditComentDblClick(TObject *Sender)
{
	FormComent->EditComent->Lines = Form1->EditComent->Lines;
	FormComent->ShowModal();
}
void __fastcall TForm1::EditDirGrubNameChange(TObject *Sender)
{
	UnicodeString dirGrub = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
	UnicodeString dirEdit = EditDirGrubName->Text;
	if (dirGrub != dirEdit) curDir.setGrubFull(dirEdit);
	else curDir.setGrubFull(dirGrub);
	changeEditDirColor(); //смена заливки поля "папки граба" и активация кнопок
}
void __fastcall TForm1::EditGrubUserChange(TObject *Sender)
{
	curConfig.setUser(Form1->EditGrubUser->Text);
}
void __fastcall TForm1::EditEsetMirrorDirChange(TObject *Sender)
{
	curPC.setEsetDir(Form1->EditEsetMirrorDir->Text);
	if(gruberStart) infoSetToFille(curPC);
}
/* Изменение полей на GRUBer+*/
void __fastcall TForm1::Edit_InNumberARMChange(TObject *Sender)
{
	curPC.setInNumberARM(Edit_InNumberARM->Text);
}
void __fastcall TForm1::Edit_InNumberHDDChange(TObject *Sender)
{
	curPC.setInNumberHDD(Edit_InNumberHDD->Text);
}
void __fastcall TForm1::Edit_InNumberDeclrChange(TObject *Sender)
{
	curPC.setInNumberDeclr(Edit_InNumberDeclr->Text);
}
void __fastcall TForm1::Edit_InNumberFormulyarChange(TObject *Sender)
{
	curPC.setInNumberFormulyar(Edit_InNumberFormulyar->Text);
}
void __fastcall TForm1::Edit_InNumberWorkChange(TObject *Sender)
{
	curPC.setInNumberWork(Edit_InNumberWork->Text);
}
void __fastcall TForm1::Edit_InNumberPersonChange(TObject *Sender)
{
	curPC.setInNumberPerson(Edit_InNumberPerson->Text);
}
void __fastcall TForm1::Edit_InResponChange(TObject *Sender) // <===
{
	curPC.setInRespon(Edit_InRespon->Text);
}
void __fastcall TForm1::Edit_InAdminBPChange(TObject *Sender) // <===
{
	curPC.setInAdminBP(Edit_InAdminBP->Text);
}
// -----
void __fastcall TForm1::ComboBox_PoliticInstallChange(TObject *Sender)
{
	curPC.set_lgpo(ComboBox_PoliticInstall->Text);
}
void __fastcall TForm1::ComboBox_ContrUSBChange(TObject *Sender)
{
	curPC.set_controlUSB(ComboBox_ContrUSB->Text);
}
void __fastcall TForm1::ComboBox_MultiUSERSChange(TObject *Sender)
{
	curPC.set_multiUser(ComboBox_MultiUSERS->Text);
}
// -----
void __fastcall TForm1::ShowSerialGenarateDblClick(TObject *Sender)
{
	Form_Serial->Edit1->Text = curPC.getSerialMain();
	Form_Serial->Edit2->Text = curPC.getUUID();
	Form_Serial->Edit3->Text = curPC.getSerial_mrb();
	Form_Serial->Edit4->Text = curPC.getCPUID();
	// генерация уникального серийника
	Form_Serial->Edit5->Text = curPC.getUnSerial();
	//Form_Serial->Edit5->Text = "test";
	// открытие окна с серийниками
	Form_Serial->Position = (TPosition)7;
	Form_Serial->ShowModal();
}
//---------------------------------------------------------------------------
/* Чекбоксы в настройках */
void __fastcall TForm1::CheckBoxDebugClick(TObject *Sender)
{
	curConfig.setDebug(CheckBoxDebug->Checked);
}
void __fastcall TForm1::CheckBoxAuditClick(TObject *Sender)
{
	// 0 - off, 1 - full, 2 - mini
	curConfig.setAudit(CheckBoxAudit->State);
}
void __fastcall TForm1::CheckBoxEsetLogClick(TObject *Sender)
{
	// 0 - off, 1 - full, 2 - mini
	curConfig.setEsetLog(CheckBoxEsetLog->State);
}
void __fastcall TForm1::CheckBoxOldGrubClick(TObject *Sender)
{
	// 0 - off, 1 - full, 2 - mini
	curConfig.setOldGrub(CheckBoxOldGrub->State);
	if (CheckBoxOldGrub->State!=2) {
		if (curConfig.getOldGrub()==0) {
			if (ComentTxt->Checked) {ComentTxt->Checked = 0; curConfig.setOldGrubComent(ComentTxt->Checked);}
			if (InfoTxt->Checked) {InfoTxt->Checked = 0; curConfig.setOldGrubInfo(InfoTxt->Checked);}
			if (NetTxt->Checked) {NetTxt->Checked = 0; curConfig.setOldGrubNet(NetTxt->Checked);}
			if (UsbTxt->Checked) {UsbTxt->Checked = 0; curConfig.setOldGrubUsb(UsbTxt->Checked);}
		}
		if (curConfig.getOldGrub()==1) {
			if (!ComentTxt->Checked) {ComentTxt->Checked = 1; curConfig.setOldGrubComent(ComentTxt->Checked);}
			if (!InfoTxt->Checked) {InfoTxt->Checked = 1; curConfig.setOldGrubInfo(InfoTxt->Checked);}
			if (!NetTxt->Checked) {NetTxt->Checked = 1; curConfig.setOldGrubNet(NetTxt->Checked);}
			if (!UsbTxt->Checked) {UsbTxt->Checked = 1; curConfig.setOldGrubUsb(UsbTxt->Checked);}
		}
	}
}
void __fastcall TForm1::ComentTxtClick(TObject *Sender)
{
	ComentTxt->Checked = !ComentTxt->Checked;
	curConfig.setOldGrubComent(ComentTxt->Checked);
	CheckBoxOldGrub->State = (TCheckBoxState)curConfig.checkOldGrubState();
}
void __fastcall TForm1::InfoTxtClick(TObject *Sender)
{
	InfoTxt->Checked = !InfoTxt->Checked;
	curConfig.setOldGrubInfo(InfoTxt->Checked);
	CheckBoxOldGrub->State = (TCheckBoxState)curConfig.checkOldGrubState();
}
void __fastcall TForm1::NetTxtClick(TObject *Sender)
{
	NetTxt->Checked = !NetTxt->Checked;
	curConfig.setOldGrubNet(NetTxt->Checked);
	CheckBoxOldGrub->State = (TCheckBoxState)curConfig.checkOldGrubState();
}
void __fastcall TForm1::UsbTxtClick(TObject *Sender)
{
	UsbTxt->Checked = !UsbTxt->Checked;
	curConfig.setOldGrubUsb(UsbTxt->Checked);
	CheckBoxOldGrub->State = (TCheckBoxState)curConfig.checkOldGrubState();
}
void __fastcall TForm1::CheckBoxNewGrubClick(TObject *Sender)
{
	curConfig.setNewGrub(CheckBoxNewGrub->Checked);
}
void __fastcall TForm1::CheckBoxLicenseClick(TObject *Sender)
{
	curConfig.setLicense(CheckBoxLicense->Checked);
}
void __fastcall TForm1::CheckBoxEsetAutoUpdateClick(TObject *Sender)
{
	bool i = Form1->CheckBoxEsetAutoUpdate->Checked;
	if(Form1->CheckBoxEsetAutoUpdate->Checked)
		StatusBar1->Panels->Items[1]->Text = " ESET оновлюеться самостійно";
	else StatusBar1->Panels->Items[1]->Text = " Бази не оновлювалися";
	Form1->EditEsetMirrorDir->Enabled = !i;
	Form1->BtnEditEsetMirrorDir->Enabled = !i;
	Form1->BtnEsetUpdate->Enabled = !i;
	curPC.setEsetAutoUpdate(i);
	if(gruberStart) infoSetToFille(curPC);
}
void __fastcall TForm1::ComboBox_forNumberARMChange(TObject *Sender)
{
	short id = ComboBox_forNumberARM->ItemIndex;
	curConfig.set_forNumberARMid(ComboBox_forNumberARM->ItemIndex);
	curPC.set_useForNumberARMid(id);
	if (id == 0) {
		Edit_NumberARM->Value = 0;
		Edit_NumberARM->Enabled = false;
//		Label_NumberARM->Caption = "Номер АРМ(...):";
	}
	if (id == 1) {
		Edit_NumberARM->Value = curPC.getNumber_UVs();
		Edit_NumberARM->Enabled = true;
//		Label_NumberARM->Caption = "Номер АРМ(УВс\"П\"):";
	}
	if (id == 2) {
		Edit_NumberARM->Value = curPC.getNumber_UVs_logist();
		Edit_NumberARM->Enabled = true;
//		Label_NumberARM->Caption = "Номер АРМ(УВс\"П\"-лог):";
	}
		if (id == 3) {
		Edit_NumberARM->Value = curPC.getNumber_OK();
		Edit_NumberARM->Enabled = true;
//		Label_NumberARM->Caption = "Номер АРМ(ОК\"П\"):";
	}
	if (id == 4) {
		Edit_NumberARM->Value = curPC.getNumber_OK_logist();
		Edit_NumberARM->Enabled = true;
//		Label_NumberARM->Caption = "Номер АРМ(ОК\"П\"-лог):";
	}
	Label_infoForNumberARM->Caption = ComboBox_forNumberARM->Text;
}
//---------------------------------------------------------------------------
/* Запуск ПО */
// INFO
void __fastcall TForm1::BtnApp_HWiNFOClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64()) setApp = curDir.getToolFull() + "\\HWiNFO\\HWiNFO64.exe";
	else setApp = curDir.getToolFull() + "\\HWiNFO\\HWiNFO32.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_CPUZClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64()) setApp = curDir.getToolFull() + "\\CPU-Z\\cpuz_x64.exe";
	else setApp = curDir.getToolFull() + "\\CPU-Z\\cpuz_x32.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_GPUZClick(TObject *Sender)
{
	LPCWSTR oper = L"open";
	UnicodeString setApp = curDir.getToolFull() + "\\GPU-Z\\GPU-Z.2.60.0.exe";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_procexpClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64()) setApp = curDir.getToolFull() + "\\SysinternalsSuite\\procexp64.exe";
	else setApp = curDir.getToolFull() + "\\SysinternalsSuite\\procexp.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_autorunsClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64()) setApp = curDir.getToolFull() + "\\SysinternalsSuite\\Autoruns64.exe";
	else setApp = curDir.getToolFull() + "\\SysinternalsSuite\\Autoruns.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_tcpviewClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64()) setApp = curDir.getToolFull() + "\\SysinternalsSuite\\tcpview64.exe";
	else setApp = curDir.getToolFull() + "\\SysinternalsSuite\\tcpview.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// File system
void __fastcall TForm1::BtnApp_TotalClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64()) setApp = curDir.getToolFull() + "\\totalcmd\\TOTALCMD64.EXE";
	else setApp = curDir.getToolFull() + "\\totalcmd\\TOTALCMD.EXE";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_EverythingClick(TObject *Sender)
{
	UnicodeString setApp = curDir.getToolFull() + "\\Everything\\Everything.exe";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
//
void __fastcall TForm1::BtnApp_UscDevUClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64()) setApp = curDir.getToolFull() + "\\USBDeview\\USBDeview_x64.exe";
	else setApp = curDir.getToolFull() + "\\USBDeview\\USBDeview_x32.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_DeviceCleanupClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64()) setApp = curDir.getToolFull() + "\\DeviceCleanup\\x64\\DeviceCleanup.exe";
	else setApp = curDir.getToolFull() + "\\DeviceCleanup\\Win32\\DeviceCleanup.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_UsbTreeViewClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64()) setApp = curDir.getToolFull() + "\\UsbTreeView\\x64\\UsbTreeView.exe";
	else setApp = curDir.getToolFull() + "\\UsbTreeView\\UsbTreeView.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// --- запуск консоли
void __fastcall TForm1::BtnKiberConsolOpenClick(TObject *Sender)
{
    LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = curDir.getToolFull() + "\\KiberConsole.msc";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_ControlPanelClick(TObject *Sender)
{
	LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "control.exe";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_setingsPCClick(TObject *Sender)
{
    LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "sysdm.cpl";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_msconfigClick(TObject *Sender)
{
    LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "msconfig.exe";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_CrashMonitorClick(TObject *Sender)
{
	LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "perfmon.exe";
	UnicodeString setArg = "/rel";
	ShellExecuteW(NULL, oper, setApp.c_str(), setArg.c_str(), NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_ResMonClick(TObject *Sender)
{
        LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "resmon.exe";
	UnicodeString setArg = "/rel";
	ShellExecuteW(NULL, oper, setApp.c_str(), setArg.c_str(), NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditPrefixPartitionChange(TObject *Sender)
{
	curConfig.setPrefixPartition(EditPrefixPartition->Text);
    EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
}
void __fastcall TForm1::CheckBoxPrefixPartitionClick(TObject *Sender)
{
	EditPrefixPartition->Enabled=CheckBoxPrefixPartition->State;
	curConfig.setEnablePrefixPartition(CheckBoxPrefixPartition->State);
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
}
//---------------------------------------------------------------------------
/* перезапуск проверки нарушений на ПК */
void __fastcall TForm1::Button_CheckDefectionClick(TObject *Sender)
{
	checkDefection();
}//--------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckListBox_SPZClickCheck(TObject *Sender)
{
	std::vector<UnicodeString> tm_vStr;
	for (int i = 0; i < Form1->CheckListBox_SPZ->Items->Count; i++)
		if(Form1->CheckListBox_SPZ->Checked[i])
			tm_vStr.push_back(Form1->CheckListBox_SPZ->Items->Strings[i]);
	curPC.set_spzInstal(tm_vStr);
}
//---------------------------------------------------------------------------

