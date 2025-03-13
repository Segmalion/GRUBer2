//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "ComentForm.h"
#include "PartitionForm.h"
#include "DialogDirExist.h"
#include "About.h"
#include "ClearTemp.h"

#include "Arm.h"
#include "RunApp.h"
#include "Help.h"
#include "Text.h"
#include "Fille.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
//---------------------------------------------------------------------------
//обявление переменных типа структуры
Arm curPC;
Dir curDir;
Config curConfig;
// infoEset curEset;
//обявление переменных
UnicodeString cmdEXE, curentDate;
bool stopBool, passBool, dirGrubRewrite, gruberStart=0;
std::vector<UnicodeString> vStrPartition;
bool x64 = GetSystemWow64DirectoryW(nullptr, 0u);
bool grubActive = 0;
//---------------------------------------------------------------------------
extern const short vers1 = 0, vers2 = 2, vers3 = 2, vers4 = 0;
extern const UnicodeString versionApp = UnicodeString(vers1) + "."
							  + UnicodeString(vers2) + "."
							  + UnicodeString(vers3) + "."
							  + UnicodeString(vers4);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Form1->ShowName->Text = curPC.getDesktopName();
	Form1->ShowSerial->Text = curPC.getSerial();
	// Проверка наличия CMD и прав на выполнение
	cmdEXE = cmdCheck();
	if(cmdEXE == "ERROR") printLog("[!]Не мае доступу чи прав на CMD!");
	// выводим настройки & сохраненую инфу об АРМ
	setConfigToForm(curConfig);
	setInfoArmToForm(curPC);
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
	if (DirectoryExists(curDir.getGrubFull())) {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x006E00;
		Form1->EditDirGrubName->Color = (TColor) 0xEAFFEA;
	} else {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x00006E;
		Form1->EditDirGrubName->Color = (TColor) 0xEAEAFF;
	}
	// ---
	PageControl1->TabIndex = 0;
	printLog("[>]Запушенно GRUBer v." + versionApp);
	printLog("[>]Останій граб: " + curPC.lastGrub());
	if(IsAdminMode()) {
		printLogDebug(curConfig.getDebug(), "Запущено з правами Адміністратора!");
        BtnClearPC->Enabled = true;
	} else printLogDebug(curConfig.getDebug(), "Запущено без прав Адміністратора!");
	StatusBar1->Panels->Items[2]->Text = "v." + versionApp + " ";
	double height = 621*Form1->ScaleFactor;
	double width  = 420*Form1->ScaleFactor;
	Form1->Height = height;
	Form1->Width  = width;
	Form1->Constraints->MinHeight = height;
	Form1->Constraints->MinWidth  = width;
	gruberStart = 1;

}
//---------------------------------------------------------------------------
std::vector<UnicodeString> TForm1::fileInfoGrub() {
	std::vector<UnicodeString> vStr;
	// раздел даты и пользователя
	for(auto str : curPC.mStrLastGrub()) vStr.push_back(str);
	// раздел об АРМ-1
	for(auto str : curPC.mStrInfoArmGrubMini()) vStr.push_back(str);
	// раздел об АРМ-2
	for(auto str : curPC.mStrInfoArm()) vStr.push_back(str);
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
int TForm1::progressBarStep() {
	short i = 0;
	if (curConfig.getNewGrub()) i++;
	if (curConfig.getOldGrub()) i = i + 5;
	if (curConfig.getLicense()) i++;
	if (curConfig.getAudit()) i = i + 2;
	if (curConfig.getEsetLog()) i++;
	int step = 100 / i;
	return step;
}
void TForm1::progressBarGo(int i , bool err) {
	if(stopBool == false) {
		ProgressBar1->Position = i;
		Taskbar1->ProgressValue = i;
	}
	if(stopBool == true || err == true) {
		ProgressBar1->State = (TProgressBarState) pbsError;
		Taskbar1->ProgressState = (TTaskBarProgressState) 4;
	}
}
//---------------------------------------------------------------------------
void TForm1::mainGRUBer() {
	/* Преварительные процедуры */
	curPC.setLastGrub(curConfig.getUser(), curDateTime());
	Form1->BtnGruberRun->Enabled = false;
	Form1->BtnGruberStop->Enabled = true;
	Form1->BtnGruberRun->Caption = "Зачекай...";
	printLog("[>]GRUBer запущено...");
	printLog("Поточна тека: " + curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition()));
	StatusBar1->Panels->Items[0]->Text = " GRUBer запущено...";
	/* Переменные */
	grubActive = true;
	int persentStep;
	UnicodeString outFilePath;
	UnicodeString app32, app64, arg;
	stopBool = false;
	passBool = false;
	bool bigErr = true;
	// lastGrub.user = curConfig.grubUser;
	/* Настройка прогресбара */
	int pos = 0;
	ProgressBar1->State = (TProgressBarState) pbsNormal;
	Taskbar1->ProgressState = (TTaskBarProgressState) 2;
	progressBarGo(pos);
	/* Сохранение введеной инфы о ПК */
	infoSetToFille(curPC);
	/* Проверка и создание папок */
	curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
	// папки
	if (DirectoryExists(curDir.getGrubFull())) {
		FormDirExist->ShowDir->Text=(curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition()));
		FormDirExist->ShowModal();
		printLog("Знайденно попередню теку!");
		if (!dirGrubRewrite) {
			Form1->BtnGruberRun->Enabled = true;
			Form1->BtnGruberStop->Enabled = false;
			Form1->BtnGruberRun->Caption = "Запуск GRUBer";
			printLog("[!]GRUBer зупинено :'(");
			return;
		}
		printLog("Видаляю попередні файли...");
	}
	curDir.check();
	//Form1->CheckBox1->Checked = DirectoryExists(curDir.getGrubFull());
	if(DirectoryExists(curDir.getGrubFull())) {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x006E00;
		Form1->EditDirGrubName->Color = (TColor) 0xEAFFEA;
	} else {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x00006E;
		Form1->EditDirGrubName->Color = (TColor) 0xEAEAFF;
	}
	Form1->BtnGruberDirOpen->Enabled = DirectoryExists(curDir.getGrubFull());
	/* 1 - gruber_info.txt */
	if (curConfig.getNewGrub() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\gruber_info.ini";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування gruber_info.ini...");
		TStringList *infoFille = new TStringList;
		for(auto str : fileInfoGrub()) infoFille->Add (str);
		infoFille->SaveToFile(outFilePath, TEncoding::UTF8); // запись в файл
		printLog("Файл СТВОРЕННО!");
		progressBarGo(pos = pos + progressBarStep());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	}
	/* 2 - coment.txt */
	if (curConfig.getOldGrubComent() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\coment.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування coment.txt...");
		TStringList *comTxt = new TStringList;
		comTxt->Add(curPC.getComentStr());
		comTxt->Add(curPC.getRespon());
		comTxt->Add(curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition()));
		comTxt->Add("");
		comTxt->SaveToFile(outFilePath, TEncoding::UTF8);
		printLog("Файл СТВОРЕННО!");
		progressBarGo(pos = pos + progressBarStep());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	}
	/* 3 -  info.txt */
	if (curConfig.getOldGrubInfo() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\info.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування info.txt...");
		app32 = curDir.getToolFull() + "\\scripts\\Info.bat";
		arg = "\""+ outFilePath + "\"";
		RunApp info {app32, NULL, arg};
		info.run(); // RUN !!!
		printLogDebug(curConfig.getDebug(), info.errorString());
		printLog(info.resultString());
		progressBarGo(pos = pos + progressBarStep(), info.checkErr());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
		bigErr *= !info.checkErr();
	}
	/* 4 - usb.txt */
	if (curConfig.getOldGrubUsb() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\usb.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування usb.txt...");
		app32 = curDir.getToolFull() + "\\USBDeview\\USBDeview_x32.exe";
		app64 = curDir.getToolFull() + "\\USBDeview\\USBDeview_x64.exe";
		arg = "/stext " + outFilePath + "\"";
		RunApp usb {app32, app64, arg};
		usb.run();
		printLogDebug(curConfig.getDebug(), usb.errorString());
		printLog(usb.resultString());
		if (FileExists(outFilePath)) {
			Form1->BtnParserOpen->Enabled = DirectoryExists(curDir.getGrubFull());
		}
		progressBarGo(pos = pos + progressBarStep(), usb.checkErr());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
		bigErr *= !usb.checkErr();
	}
   /* 5 - net1.txt & net2.txt */
	if (curConfig.getOldGrubNet() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\net1.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування net1.txt...");
		app32 = curDir.getToolFull() + "\\Network\\NetworkInterfacesView_x32.exe";
		app64 = curDir.getToolFull() + "\\Network\\NetworkInterfacesView_x64.exe";
		arg = "/stext " + outFilePath + "\"";
		RunApp net1 {app32, app64, arg};
		net1.run();
		printLogDebug(curConfig.getDebug(), net1.errorString());
		printLog(net1.resultString());
		progressBarGo(pos = pos + progressBarStep(), net1.checkErr());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
		bigErr *= !net1.checkErr();
	}
	if (curConfig.getOldGrubNet() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\net2.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування net2.txt...");
		app32 = curDir.getToolFull() + "\\Network\\WifiHistoryView.exe";
		app64 = NULL;
		arg = "/stext " + outFilePath + "\"";
		RunApp net2 {app32, app64, arg};
		net2.run();
		printLogDebug(curConfig.getDebug(), net2.errorString());
		printLog(net2.resultString());
		progressBarGo(pos = pos + progressBarStep(), net2.checkErr());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
		bigErr *= !net2.checkErr();
	}
	/* 6 - license.txt */
	if (curConfig.getLicense() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\license.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування license.txt...");
		if (FileExists("C:\\Windows\\System32\\wbem\\wmic.exe")) {
			app32 = curDir.getToolFull() + "\\scripts\\Info-License-to-File.bat";
			app64 = NULL;
			arg = "\""+ outFilePath + "\"";
			RunApp lic {app32, app64, arg};
			lic.run();
			printLogDebug(curConfig.getDebug(), lic.errorString());
			printLog(lic.resultString());
			progressBarGo(pos = pos + progressBarStep(), lic.checkErr());
			printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
			bigErr *= !lic.checkErr();
		} else {
			printLog("[!]ERROR!");
			bigErr *= 0;
		}
	}
	/* 7 - audit.html */
	if (curConfig.getAudit() && !stopBool) {
		if(curConfig.getAudit() == 1) {
			outFilePath = curDir.getGrubFull() + "\\auditMax.html";
			arg = "/r=gsoPxuTUeERNtnzDaIbMpmidcSArHG /f=" + outFilePath + " /L=en\"";
		}
		if(curConfig.getAudit() == 2) {
			outFilePath = curDir.getGrubFull() + "\\auditMin.html";
			arg = "/r=go /f=" + outFilePath + " /L=en\"";
		}
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування audit.html...");
		app32 = curDir.getToolFull() + "\\WinAudit\\WinAudit.exe";
		app64 = NULL;
		RunApp audit {app32, app64, arg};
		audit.run();
		printLogDebug(curConfig.getDebug(), audit.errorString());
		printLog(audit.resultString());
		progressBarGo(pos = pos + progressBarStep(), audit.checkErr());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
		bigErr *= !audit.checkErr();
	}
	/* 8 - CDI.txt */
	if (curConfig.getAudit() && !stopBool && x64 && IsAdminMode()) { //111
		outFilePath = curDir.getGrubFull() + "\\diskInfo.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування diskInfo.txt...");
		app32 = NULL;
		app64 = curDir.getToolFull() + "\\DiskInfo64\\DiskInfo64.exe";
		arg = "/CopyExit :";
		RunApp cdi {app32, app64, arg};
		cdi.run();
		UnicodeString f1 = curDir.getToolFull() + "\\DiskInfo64\\DiskInfo.txt";
		MoveFile(f1.c_str(), outFilePath.c_str());
		printLogDebug(curConfig.getDebug(), cdi.errorString());
		printLog(cdi.resultString());
		progressBarGo(pos = pos + progressBarStep(), cdi.checkErr());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
		bigErr *= !cdi.checkErr();
	}
	/* 9 - eset-log.zip */
	if (curConfig.getEsetLog() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\eset-log.zip";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування eset-log.zip...");
		app32 = curDir.getToolFull() + "\\EsetLogCollector\\ESETLogCollector.exe";
		app64 = NULL;
		if(curConfig.getEsetLog() == 1)
			arg = "/accepteula /Lang:UKR /Age:0 " + outFilePath + "\"";
		if(curConfig.getEsetLog() == 2)
			arg = "/accepteula /Lang:UKR /Age:30 /Targets:warn,threat,ondem,dev " + outFilePath + "\"";
		RunApp esetLog {app32, app64, arg};
		esetLog.run(false);
		printLogDebug(curConfig.getDebug(), esetLog.errorString());
		printLog(esetLog.resultString());
		progressBarGo(pos = 100, esetLog.checkErr());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
		bigErr *= !esetLog.checkErr();
	};
	/*  */
	/*  */
	if (!bigErr) {
		printLog("[ERR]GRUBer виконано з помилками!");
		StatusBar1->Panels->Items[0]->Text = " GRUBer ERROR!";
	} else {
		printLog("[OK]GRUBer виконано успішно!");
		StatusBar1->Panels->Items[0]->Text = " GRUBer виконано!";
	}
	grubActive = false;
	Form1->BtnGruberRun->Enabled = true;
	Form1->BtnGruberStop->Enabled = false;
	Form1->BtnGruberRun->Caption = "Запуск GRUBer";
}
//---------------------------------------------------------------------------
/* Кнопки */
// запуск Граба
void __fastcall TForm1::BtnGruberRunClick(TObject *Sender) //Запуск Граба
{
	mainGRUBer();
}
// открыть редактор подразделений
void __fastcall TForm1::BtnEditPartitionClick(TObject *Sender)
{
	FormPartition->EditPartition->Lines = Form1->EditPartition->Items;
	FormPartition->ShowModal();
}
// открыть папку Граба
void __fastcall TForm1::BtnGruberDirOpenClick(TObject *Sender)
{
	ShellExecuteW(NULL, L"open", curDir.getGrubFull().c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// остановка Граба
void __fastcall TForm1::BtnGruberStopClick(TObject *Sender)
{
	stopBool = true;
}
void __fastcall TForm1::РassClick(TObject *Sender)
{
	passBool = true;
}
// сохранение настроек
void __fastcall TForm1::BtnSaveSetteingsClick(TObject *Sender)
{
	curConfig.saveFileIni();
}
// запуск парсера
void __fastcall TForm1::BtnParserOpenClick(TObject *Sender)
{
	UnicodeString setApp = GetCurrentDir() + "\\GRUBer-Parser.exe";
	UnicodeString setArg = "/run /b " + curDir.getGrubFull();
	ShellExecuteW(NULL, L"open", setApp.c_str(), setArg.c_str(), NULL, SW_SHOWDEFAULT);
}
// запуск консоли
void __fastcall TForm1::BtnKiberConsolOpenClick(TObject *Sender)
{
	UnicodeString setApp = curDir.getToolFull() + "\\KiberConsole.msc";
	ShellExecuteW(NULL, L"runas", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::PerfmonClick(TObject *Sender)
{
	UnicodeString setApp = "perfmon.exe";
	UnicodeString setArg = "/rel";
	ShellExecuteW(NULL, L"runas", setApp.c_str(), setArg.c_str(), NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::MsConfigClick(TObject *Sender)
{
	UnicodeString setApp = "C:\\Windows\\System32\\msconfig.exe";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::sysdmCplClick(TObject *Sender)
{
	UnicodeString setApp = "sysdm.cpl";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// провека лицензий
void __fastcall TForm1::BtnLicenseClick(TObject *Sender)
{
	UnicodeString setApp = curDir.getToolFull() + "\\scripts\\INFO-license-run.bat";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// общее инфо
void __fastcall TForm1::BtnInfoClick(TObject *Sender)
{
	UnicodeString setApp = curDir.getToolFull() + "\\scripts\\INFO-PC-all.bat";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// about form
void __fastcall TForm1::BtnAboutGruberClick(TObject *Sender)
{
	FormAbout->Position = (TPosition)7;
	FormAbout->ShowModal();
}
void __fastcall TForm1::BtnClearPCClick(TObject *Sender)
{
	FormClearTempDir->Position = (TPosition)7;
	FormClearTempDir->ShowModal();
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
	if (!FileExists(GetCurrentDir() + "\\update.7z")) {
		printLog("[ESET-Update][!]Немає архіву з базами!");
		return;
	}
	printLog("[ESET-Update][>]Оновленя бази Eset...");
	BtnEsetUpdate->Enabled = false;
	StatusBar1->Panels->Items[1]->Text = " Оновленя бази Eset...";
	if (FileExists(curPC.getEsetDir() + "\\dll\\update.ver"))
		deleteDir(curPC.getEsetDir());
	//запуск обновления
	UnicodeString app32 = curDir.getToolFull() + "\\7zip\\32\\7za.exe";
	UnicodeString app64 = curDir.getToolFull() + "\\7zip\\64\\7za.exe";
	if (curConfig.getShowEsetUpd()) app32 = curDir.getToolFull() + "\\7zip\\32\\7zG.exe";
	if (curConfig.getShowEsetUpd()) app64 = curDir.getToolFull() + "\\7zip\\64\\7zG.exe";
	RunApp esetBaseUnpack {app32, app64,
		"x -y -o\"" + curPC.getEsetDir() + "\" \"" + GetCurrentDir() + "\\update.7z\""};
	esetBaseUnpack.run(!curConfig.getShowEsetUpd());
	//------
	if (esetBaseUnpack.checkErr()){
		//ошибочка вышла...
		printLog("[ESET-Update][!]Щось пішло НЕ так...");
		BtnEsetUpdate->Enabled = true;
		return;
	}
	printLog("[ESET-Update][OK]Бази оновленно!");
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
void __fastcall TForm1::EditNumberChange(TObject *Sender)
{
	curPC.setNumber(EditNumber->Value);
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
	curDir.setGrubFull(curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition()));
	//Form1->CheckBox1->Checked = DirectoryExists(curDir.getGrubFull());
	if(DirectoryExists(curDir.getGrubFull())) {
		EditDirGrubName->Font->Color = (TColor) 0x006E00;
		EditDirGrubName->Color = (TColor) 0xEAFFEA;
		if (!grubActive) StatusBar1->Panels->Items[0]->Text = " GRUBer вже зібрано!";
	} else {
		EditDirGrubName->Font->Color = (TColor) 0x00006E;
		EditDirGrubName->Color = (TColor) 0xEAEAFF;
		StatusBar1->Panels->Items[0]->Text = " GRUBer не зібрано:(";
	}
	Form1->BtnGruberDirOpen->Enabled = DirectoryExists(curDir.getGrubFull());
	Form1->BtnParserOpen->Enabled = DirectoryExists(curDir.getGrubFull());
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
void __fastcall TForm1::Edit_ComPoliticInstallChange(TObject *Sender)
{
	curPC.setComPoliticInstall(Edit_ComPoliticInstall->Text);
}
void __fastcall TForm1::Edit_ComContrUSBChange(TObject *Sender)
{
	curPC.setComContrUSB(Edit_ComContrUSB->Text);
}
void __fastcall TForm1::Edit_ComMultiUSERSChange(TObject *Sender)
{
   curPC.setComMultiUSERS(Edit_ComMultiUSERS->Text);
}
void __fastcall TForm1::CheckBox_PoliticInstallClick(TObject *Sender)
{
   curPC.setPoliticInstall(CheckBox_PoliticInstall->Checked);
}
void __fastcall TForm1::CheckBox_ContrUSBClick(TObject *Sender)
{
   curPC.setContrUSB(CheckBox_ContrUSB->Checked);
}
void __fastcall TForm1::CheckBox_MultiUSERSClick(TObject *Sender)
{
   curPC.setMultiUSERS(CheckBox_MultiUSERS->Checked);
}
//---------------------------------------------------------------------------
/* Чекбоксы в настройках */
void __fastcall TForm1::CheckBoxShowLogClick(TObject *Sender)
{
	curConfig.setShowLog(CheckBoxShowLog->Checked);
	if (curConfig.getShowLog()) Form1->Width = 1024*Form1->ScaleFactor;
	else Form1->Width = 420*Form1->ScaleFactor;
}
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
//---------------------------------------------------------------------------
/* Запуск ПО */
// INFO
void __fastcall TForm1::BtnApp_HWiNFOClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64) setApp = curDir.getToolFull() + "\\HWiNFO\\HWiNFO64.exe";
	else setApp = curDir.getToolFull() + "\\HWiNFO\\HWiNFO32.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_CPUZClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64) setApp = curDir.getToolFull() + "\\CPU-Z\\cpuz_x64.exe";
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
	if (x64) setApp = curDir.getToolFull() + "\\SysinternalsSuite\\procexp64.exe";
	else setApp = curDir.getToolFull() + "\\SysinternalsSuite\\procexp.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_autorunsClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64) setApp = curDir.getToolFull() + "\\SysinternalsSuite\\Autoruns64.exe";
	else setApp = curDir.getToolFull() + "\\SysinternalsSuite\\Autoruns.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_tcpviewClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64) setApp = curDir.getToolFull() + "\\SysinternalsSuite\\tcpview64.exe";
	else setApp = curDir.getToolFull() + "\\SysinternalsSuite\\tcpview.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// File system
void __fastcall TForm1::BtnApp_TotalClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64) setApp = curDir.getToolFull() + "\\totalcmd\\TOTALCMD64.EXE";
	else setApp = curDir.getToolFull() + "\\totalcmd\\TOTALCMD.EXE";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_EverythingClick(TObject *Sender)
{
	UnicodeString setApp = curDir.getToolFull() + "\\Everything\\Everything.exe";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditPrefixPartitionChange(TObject *Sender)
{
	curConfig.setPrefixPartition(EditPrefixPartition->Text);
    EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBoxPrefixPartitionClick(TObject *Sender)
{
	EditPrefixPartition->Enabled=CheckBoxPrefixPartition->State;
	curConfig.setEnablePrefixPartition(CheckBoxPrefixPartition->State);
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

