//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "ComentForm.h"
#include "PartitionForm.h"
#include "DialogDirExist.h"

#include "Arm.h"
#include "RunApp.h"
#include "Help.h"
#include "Text.h"
#include "Fille.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DosCommand"
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
bool stopBool;
bool dirGrubRewrite;
std::vector<UnicodeString> vStrPartition;
//---------------------------------------------------------------------------
const short vers1 = 0, vers2 = 2, vers3 = 1, vers4 = 1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	const UnicodeString versionApp = UnicodeString(vers1) + "."
							  + UnicodeString(vers2) + "."
							  + UnicodeString(vers3) + "."
							  + UnicodeString(vers4);
	Form1->ShowName->Text = curPC.getDesktopName();
	Form1->ShowSerial->Text = curPC.getSerial();
	// Проверка наличия CMD и прав на выполнение
	cmdEXE = cmdCheck();
	if(cmdEXE == "ERROR") printLog("[!]Не мае доступу чи прав на CMD!");
	// выводим настройки & сохраненую инфу об АРМ
   setConfigToForm(curConfig);
	setInfoArmToForm(curPC);
   EditDirGrubName->Text = curPC.dirGrubName();
	// ---
	PageControl1->TabIndex = 0;
	printLog("[>]Запушенно GRUBer v." + versionApp);
	printLog("[>]Останій граб: " + curPC.lastGrub());
	if(IsAdminMode()) printLogDebug(curConfig.getDebug(), "Запущено з правами Адміністратора!");
	else printLogDebug(curConfig.getDebug(), "Запущено без прав Адміністратора!");
	StatusBar1->Panels->Items[2]->Text = "v." + versionApp + " ";
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
	if (curConfig.getAudit()) i++;
	if (curConfig.getEsetLog()) i++;
	int step = 100 / i;
	return step;
}
//---------------------------------------------------------------------------
void TForm1::mainGRUBer() {
	/* Преварительные процедуры */
	ProgressBar1->Position = 0;
	curPC.setLastGrub(curConfig.getUser(), curDateTime());
	Form1->BtnGruberRun->Enabled = false;
	Form1->BtnGruberStop->Enabled = true;
	Form1->BtnGruberRun->Caption = "Зачекай...";
	printLog("[>]GRUBer запущено...");
	printLog("Поточна тека: " + curPC.dirGrubName());
	StatusBar1->Panels->Items[0]->Text = " GRUBer запущено...";
	/* Переменные */
	int persentStep;
	UnicodeString outFilePath;
	stopBool = false;
	// lastGrub.user = curConfig.grubUser;
	/* Настройка прогресбара */
	/* Сохранение введеной инфы о ПК */
	infoSetToFille(curPC);
	/* Проверка и создание папок */
	curDir.setGrubFull(curPC.dirGrubName());
	// папки
	if (DirectoryExists(curDir.getGrubFull())) {
		FormDirExist->ShowDir->Text=(curPC.dirGrubName());
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
	/* 1 - gruber_info.txt */
	if (curConfig.getNewGrub() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\gruber_info.ini";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування gruber_info.ini...");
		TStringList *infoFille = new TStringList;
		for(auto str : fileInfoGrub()) infoFille->Add (str);
		infoFille->SaveToFile(outFilePath, TEncoding::UTF8); // запись в файл
		printLog("Файл СТВОРЕННО!");
		ProgressBar1->Position = ProgressBar1->Position + progressBarStep();
	}
	/* 2 - coment.txt */
	if (curConfig.getOldGrub() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\coment.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування coment.txt...");
		TStringList *comTxt = new TStringList;
		comTxt->Add(curPC.getComentStr());
		comTxt->Add(curPC.getRespon());
		comTxt->Add(curPC.dirGrubName());
		comTxt->Add("");
		comTxt->SaveToFile(outFilePath, TEncoding::UTF8);
		printLog("Файл СТВОРЕННО!");
		ProgressBar1->Position = ProgressBar1->Position + progressBarStep();
	}
	/* 3 -  info.txt */
	if (curConfig.getOldGrub() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\info.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування info.txt...");
		RunApp info;
		info.setApp(curDir.getToolFull() + "\\Info.bat");
		info.setArg("\""+ outFilePath + "\"");
		info.run();
		if (info.error.run || info.error.exit)
			printLog("[!]Щось пішло НЕ так...");
		else printLog("Файл СТВОРЕННО!");
		printLogDebug(curConfig.getDebug(),
			"run-[" + UnicodeString(info.error.runCode) + ", " + UnicodeString(info.error.run) + "] "
			+ "exit-[" + UnicodeString(info.error.exitCode) + ", " + UnicodeString(info.error.exit) + "] ");
		ProgressBar1->Position = ProgressBar1->Position + progressBarStep();
	}
	/* 4 - usb.txt */
	if (curConfig.getOldGrub() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\usb.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування usb.txt...");
		RunApp usb;
		usb.setApp(curDir.getToolFull() + "\\USBDeview_x32.exe");
		usb.setArg("/stext " + outFilePath + "\"");
		usb.run();
		if (usb.error.run || usb.error.exit) printLog("[!]Щось пішло НЕ так...");
		else printLog("Файл СТВОРЕННО!");
      printLogDebug(curConfig.getDebug(),
			"run-[" + UnicodeString(usb.error.runCode) + ", " + UnicodeString(usb.error.run) + "] "
			+ "exit-[" + UnicodeString(usb.error.exitCode) + ", " + UnicodeString(usb.error.exit) + "] ");
		ProgressBar1->Position = ProgressBar1->Position + progressBarStep();
	}
	/* old - devctrllog.dat */
	/*if (!stopBool) {
		// Копируем - C:\ProgramData\ESET\ESET Security\Logs\devctrllog.dat в папку граба
		UnicodeString devLogFileDAT = "devctrllog.dat";
		UnicodeString copyFrom = "C:\\ProgramData\\ESET\\ESET Security\\Logs\\" + devLogFileDAT;
		UnicodeString copyToDir = curDir.getGrubFull() + "\\eset-log";
		UnicodeString devDAT = copyToDir + "\\" + devLogFileDAT;
		printLog("Копіюемо devctrllog.dat...");
		if (FileExists(copyFrom)) {
			if (!DirectoryExists(copyToDir)) CreateDir(copyToDir);
			if (FileExists(devDAT)) FileSetAttr(devDAT, 0) && DeleteFile(devDAT);
			CopyFile(copyFrom.c_str(), devDAT.c_str(), false);
			printLog("Файл СКОПІЙОВАНО!");
		} else printLog("[!]Файлу не мае...");
	} */
   /* 5 - net1.txt & net2.txt */
	if (curConfig.getOldGrub() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\net1.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування net1.txt...");
		RunApp net1;
		net1.setApp(curDir.getToolFull() + "\\NetworkInterfacesView_x32.exe");
		net1.setArg("/stext " + outFilePath + "\"");
		net1.run();
		if (net1.error.run || net1.error.exit) printLog("[!]Щось пішло НЕ так...");
		else printLog("Файл СТВОРЕННО!");
      printLogDebug(curConfig.getDebug(),
			"run-[" + UnicodeString(net1.error.runCode) + ", " + UnicodeString(net1.error.run) + "] "
			+ "exit-[" + UnicodeString(net1.error.exitCode) + ", " + UnicodeString(net1.error.exit) + "] ");
		ProgressBar1->Position = ProgressBar1->Position + progressBarStep();
	}
	if (curConfig.getOldGrub() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\net2.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування net2.txt...");
		RunApp net2;
		net2.setApp(curDir.getToolFull() + "\\WifiHistoryView.exe");
		net2.setArg("/stext " + outFilePath + "\"");
		net2.run();
		if (net2.error.run || net2.error.exit) printLog("[!]Щось пішло НЕ так...");
		else printLog("Файл СТВОРЕННО!");
      printLogDebug(curConfig.getDebug(),
			"run-[" + UnicodeString(net2.error.runCode) + ", " + UnicodeString(net2.error.run) + "] "
			+ "exit-[" + UnicodeString(net2.error.exitCode) + ", " + UnicodeString(net2.error.exit) + "] ");
		ProgressBar1->Position = ProgressBar1->Position + progressBarStep();
	}
	/* 6 - license.txt */
	if (curConfig.getLicense() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\license.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування license.txt...");
		RunApp lic;
		lic.setApp(curDir.getToolFull() + "\\Info-License-to-File.bat");
		lic.setArg("\""+ outFilePath + "\"");
		lic.run();
		if (lic.error.run || lic.error.exit) printLog("[!]Щось пішло НЕ так...");
		else printLog("Файл СТВОРЕННО!");
		printLogDebug(curConfig.getDebug(),
			"run-[" + UnicodeString(lic.error.runCode) + ", " + UnicodeString(lic.error.run) + "] "
			+ "exit-[" + UnicodeString(lic.error.exitCode) + ", " + UnicodeString(lic.error.exit) + "] ");
		ProgressBar1->Position = ProgressBar1->Position + progressBarStep();
	}
	/* 7 - audit.html */
	if (curConfig.getAudit() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\audit.html";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування audit.html...");
		RunApp audit;
		audit.setApp(curDir.getToolFull() + "\\WinAudit.exe");
		if(curConfig.getAudit() == 1)
			audit.setArg("/r=gsoPxuTUeERNtnzDaIbMpmidcSArHG /f=" + outFilePath + " /L=en\"");
		if(curConfig.getAudit() == 2)
			audit.setArg("/r=go /f=" + outFilePath + " /L=en\"");
		audit.run();
		if (audit.error.run || audit.error.exit) printLog("[!]Щось пішло НЕ так...");
		else printLog("Файл СТВОРЕННО!");
      printLogDebug(curConfig.getDebug(),
			"run-[" + UnicodeString(audit.error.runCode) + ", " + UnicodeString(audit.error.run) + "] "
			+ "exit-[" + UnicodeString(audit.error.exitCode) + ", " + UnicodeString(audit.error.exit) + "] ");
		ProgressBar1->Position = ProgressBar1->Position + progressBarStep();
	}
	/* 8 - eset-log.zip */
	if (curConfig.getEsetLog() && !stopBool) {
		outFilePath = curDir.getGrubFull() + "\\eset-log.zip";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування eset-log.zip...");
		RunApp esetLog;
		esetLog.setApp(curDir.getToolFull() + "\\ESETLogCollector.exe");
		if(curConfig.getEsetLog() == 1)
			esetLog.setArg("/accepteula /Lang:UKR /Age:0 " + outFilePath + "\"");
		if(curConfig.getEsetLog() == 2)
			esetLog.setArg("/accepteula /Lang:UKR /Age:30 /Targets:warn,threat,ondem,dev " + outFilePath + "\"");
		esetLog.run(false);
		if (esetLog.error.run || esetLog.error.exit) printLog("[!]Щось пішло НЕ так...");
		else printLog("Файл СТВОРЕННО!");
		printLogDebug(curConfig.getDebug(),
			"run-[" + UnicodeString(esetLog.error.runCode) + ", " + UnicodeString(esetLog.error.run) + "] "
			+ "exit-[" + UnicodeString(esetLog.error.exitCode) + ", " + UnicodeString(esetLog.error.exit) + "] ");
		ProgressBar1->Position = ProgressBar1->Position + progressBarStep();
	}
	/*  */
	/*  */
	/*  */
	printLog("[OK]GRUBer ЗАВЕРШЕННО!");
	StatusBar1->Panels->Items[0]->Text = " GRUBer виконано!";
	ProgressBar1->Position = 100;
	Form1->BtnGruberRun->Enabled = true;
	Form1->BtnGruberStop->Enabled = false;
	Form1->BtnGruberRun->Caption = "Запуск GRUBer";
	Form1->CheckBox1->Checked = DirectoryExists(curDir.getGrubFull());
	Form1->BtnGruberDirOpen->Enabled = DirectoryExists(curDir.getGrubFull());
	Form1->BtnParserOpen->Enabled = DirectoryExists(curDir.getGrubFull());
}
//---------------------------------------------------------------------------
/* Кнопки */
// запуск Граба
void __fastcall TForm1::BtnGruberRunClick(TObject *Sender) //Запуск Граба
{
	mainGRUBer();
}
// просмотр коментария
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	FormComent->EditComent->Lines = Form1->EditComent->Lines;
	FormComent->ShowModal();
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
// сохранение настроек
void __fastcall TForm1::BtnSaveSetteingsClick(TObject *Sender)
{
	curConfig.saveFileIni();
}
// eset update
void __fastcall TForm1::BtnEsetUpdateClick(TObject *Sender)
{
	if(FileExists(GetCurrentDir() + "\\update.7z")) {
		printLog("[ESET-Update][>]Оновленя бази Eset...");
		StatusBar1->Panels->Items[1]->Text = " Оновленя бази Eset...";
		if(FileExists(curPC.getEsetDir() + "\\dll\\update.ver")) deleteDir(curPC.getEsetDir());
		//ShellExecuteW(NULL, L"open", fille.c_str(), param.c_str(), NULL, SW_SHOWDEFAULT);
		RunApp esetBaseUnpack;
		esetBaseUnpack.setApp(curDir.getToolFull() + "\\7za.exe");
		esetBaseUnpack.setArg("x -y -o\"" + curPC.getEsetDir() + "\" \"" + GetCurrentDir() + "\\update.7z\"");
		esetBaseUnpack.run();
		if (esetBaseUnpack.error.run || esetBaseUnpack.error.run)
			printLog("[ESET-Update][!]Щось пішло НЕ так...");
		else {
			printLog("[ESET-Update][OK]Бази оновленно!");
			StatusBar1->Panels->Items[1]->Text = " Бази оновленно!";
         if (FileExists("c:\\Program Files\\ESET\\ESET Security\\ermm.exe")) {
				RunApp esetBaseUpdate;
				esetBaseUpdate.setApp("c:\\Program Files\\ESET\\ESET Security\\ermm.exe");
				esetBaseUpdate.setArg("start update");
				esetBaseUpdate.run();
			}
		}
	}
	else printLog("[ESET-Update][!]Немає архіву з базами!");
}
// запуск парсера
void __fastcall TForm1::BtnParserOpenClick(TObject *Sender)
{
	RunApp parser;
	parser.setApp(GetCurrentDir() + "\\GRUBer-Parser.exe");
	parser.setArg("/run /b " + curDir.getGrubFull());
	parser.run(0);
	if (parser.error.run || parser.error.run)
		printLog("[!]Щось пішло НЕ так...");
}
// запуск консоли
void __fastcall TForm1::BtnKiberConsolOpenClick(TObject *Sender)
{
	RunApp console;
	console.setApp(curDir.getToolFull() + "\\KiberConsole.msc");
	console.setArg(NULL);
	console.run(0, 1);
	if (console.error.run || console.error.run)
		printLog("[!]Щось пішло НЕ так...");
}
// провека лицензий
void __fastcall TForm1::BtnLicenseClick(TObject *Sender)
{
	RunApp licenseShow;
	licenseShow.setApp(curDir.getToolFull() + "\\INFO-license-run.bat");
	licenseShow.setArg(NULL);
	licenseShow.run(0);
	if (licenseShow.error.run || licenseShow.error.run)
		printLog("[!]Щось пішло НЕ так...");
}
// общее инфо
void __fastcall TForm1::BtnInfoClick(TObject *Sender)
{
	RunApp infoShow;
	infoShow.setApp(curDir.getToolFull() + "\\INFO-PC-all.bat");
	infoShow.setArg(NULL);
	infoShow.run(0);
	if (infoShow.error.run || infoShow.error.run)
		printLog("[!]Щось пішло НЕ так...");
}
//---------------------------------------------------------------------------
/* Изменение полей */
void __fastcall TForm1::EditNumberChange(TObject *Sender)
{
	curPC.setNumber(EditNumber->Value);
	EditDirGrubName->Text = curPC.dirGrubName();
}
void __fastcall TForm1::EditPartitionChange(TObject *Sender)
{
	curPC.setPartition(EditPartition->Text);
	EditDirGrubName->Text = curPC.dirGrubName();
}
void __fastcall TForm1::EditArmClassChange(TObject *Sender)
{
	curPC.setClass(EditArmClass->Text, EditArmClass->ItemIndex);
}
void __fastcall TForm1::EditCategoryChange(TObject *Sender)
{
	short indx = EditCategory->ItemIndex;
	curPC.setCategory(EditCategory->Items->Strings[indx], indx);
	EditDirGrubName->Text = curPC.dirGrubName();
}
void __fastcall TForm1::EditResponChange(TObject *Sender)
{
	curPC.setRespon(EditRespon->Text);
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
void __fastcall TForm1::EditDirGrubNameChange(TObject *Sender)
{
	curDir.setGrubFull(curPC.dirGrubName());
	Form1->CheckBox1->Checked = DirectoryExists(curDir.getGrubFull());
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
	infoSetToFille(curPC);
}
//---------------------------------------------------------------------------
/* Чекбоксы в настройках */
void __fastcall TForm1::CheckBoxShowLogClick(TObject *Sender)
{
	curConfig.setShowLog(CheckBoxShowLog->Checked);
	if (curConfig.getShowLog()) Form1->Width = 1024*Form1->ScaleFactor;
	else Form1->Width = 421*Form1->ScaleFactor;
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
	curConfig.setOldGrub(CheckBoxOldGrub->Checked);
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
	infoSetToFille(curPC);
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

//---------------------------------------------------------------------------

