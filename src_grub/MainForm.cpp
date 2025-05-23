//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.Hash.hpp>
#pragma hdrstop

#include "MainForm.h"
#include "ComentForm.h"
#include "PartitionForm.h"
#include "DialogDirExist.h"
#include "About.h"
#include "ClearTemp.h"
#include "FormSerial.h"

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
double pos, step;
//---------------------------------------------------------------------------
extern const short vers1 = 0, vers2 = 2, vers3 = 2, vers4 = 4;
extern const UnicodeString versionApp = UnicodeString(vers1) + "."
							  + UnicodeString(vers2) + "."
							  + UnicodeString(vers3) + "."
							  + UnicodeString(vers4);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	// ---
	Form1->Height = 621*Form1->ScaleFactor;
	if (curConfig.getShowLog()) Form1->Width = 1024*Form1->ScaleFactor;
	else Form1->Width = 420*Form1->ScaleFactor;

	Form1->Constraints->MinHeight = 621*Form1->ScaleFactor;
	Form1->Constraints->MinWidth  = 420*Form1->ScaleFactor;
	//
	Form1->ShowName->Text = curPC.getDesktopName();
	Form1->ShowSerial->Text = curPC.getSerial();
	// Проверка наличия CMD и прав на выполнение
	cmdEXE = cmdCheck();
	if(cmdEXE == "ERROR") printLog("[!]Не мае доступу чи прав на CMD!");
	// выводим настройки & сохраненую инфу об АРМ
	setConfigToForm(curConfig);
	setInfoArmToForm(curPC);
	// ---
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
		Button_RestartAssAdmin->Enabled = false;
		BtnClearPC->Enabled = true;
	} else {
		printLogDebug(curConfig.getDebug(), "Запущено без прав Адміністратора!");
		UnicodeString text = "Перезапустити GRUBer з правами Адміністратора?\n( ПК: "
			+ UnicodeString(curPC.getNumber())
			+ ", Відділ.: " + UnicodeString(curPC.getPartition()) + " )";
		UnicodeString formCaption = "Нема прав Адміна.. :'(";
		if(Application->MessageBox( text.c_str(), formCaption.c_str(), MB_YESNO) == IDYES) {
				RestartApplicationRunas();
		}
	}
	StatusBar1->Panels->Items[2]->Text = "v." + versionApp + " ";
	gruberStart = 1;
}
//---------------------------------------------------------------------------
std::vector<UnicodeString> fileInfoGrub() {
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
double progressBarStep() {
	short i = 0;
	if (curConfig.getNewGrub()) i++;
	if (curConfig.getOldGrubComent()) i++;
	if (curConfig.getOldGrubInfo()) i++;
	if (curConfig.getOldGrubUsb()) i++;
	if (curConfig.getOldGrubNet()) i += 2;
	if (curConfig.getLicense()) i++;
	if (curConfig.getAudit()) i ++;
	if (curConfig.getAudit() && x64 && IsAdminMode()) i ++;
	if (curConfig.getEsetLog()) i++;
	printLogDebug(curConfig.getDebug(), "{count}=" + UnicodeString(i));
	return 100/(double)i;
}
void progressBarGo(int i , bool err) {
    if(stopBool == false) {
		Form1->ProgressBar1->Position = i;
		Form1->Taskbar1->ProgressValue = i;
	}
	if(stopBool == true || err == true) {
		Form1->ProgressBar1->State = (TProgressBarState) pbsError;
		Form1->Taskbar1->ProgressState = (TTaskBarProgressState) 4;
	}
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
void RestartApplicationRunas()
{
	TCHAR patch[_MAX_PATH+1];
	GetModuleFileName(NULL, patch, _MAX_PATH);
	UnicodeString setApp = UnicodeString(patch);
	ShellExecuteW(NULL, L"runas", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
	exit(1);
}
//---------------------------------------------------------------------------
bool job_infoFille() {
	UnicodeString outFilePath = curDir.getGrubFull() + "\\gruber_info.ini";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування gruber_info.ini...");
	TStringList *infoFille = new TStringList;
	for(auto str : fileInfoGrub()) infoFille->Add (str);
	infoFille->SaveToFile(outFilePath, TEncoding::UTF8); // запись в файл
	printLog("Файл СТВОРЕННО!");
	progressBarGo(pos += step);
	printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	return true;
}
bool job_comTxt() {
	UnicodeString outFilePath = curDir.getGrubFull() + "\\coment.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування coment.txt...");
	TStringList *comTxt = new TStringList;
	comTxt->Add(curPC.getComentStr());
	comTxt->Add(curPC.getRespon());
	comTxt->Add(curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition()));
	comTxt->Add("");
	comTxt->SaveToFile(outFilePath, TEncoding::UTF8);
	printLog("Файл СТВОРЕННО!");
	progressBarGo(pos += step);
	printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	return true;
}
bool job_info() {
	UnicodeString outFilePath = curDir.getGrubFull() + "\\info_ps1.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування info_ps1.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\scripts\\info_ps1\\Run_toFile.bat";
	UnicodeString arg = "\""+ outFilePath + "\"";
	RunApp info {app32, NULL, arg};
	info.run(); // RUN !!!
	printLogDebug(curConfig.getDebug(), info.errorString());
	printLog(info.resultString());
	progressBarGo(pos += step, info.checkErr());
	printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	return !info.checkErr();
}
bool job_usb() {
	UnicodeString outFilePath = curDir.getGrubFull() + "\\usb.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування usb.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\USBDeview\\USBDeview_x32.exe";
	UnicodeString app64 = curDir.getToolFull() + "\\USBDeview\\USBDeview_x64.exe";
	UnicodeString arg = "/stext " + outFilePath + "\"";
	RunApp usb {app32, app64, arg};
	usb.run();
	printLogDebug(curConfig.getDebug(), usb.errorString());
	printLog(usb.resultString());
	if (FileExists(outFilePath)) {
		Form1->BtnParserOpen->Enabled = DirectoryExists(curDir.getGrubFull());
	}
	progressBarGo(pos += step, usb.checkErr());
	printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	return !usb.checkErr();
}
bool job_net1() {
	UnicodeString outFilePath = curDir.getGrubFull() + "\\net1.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування net1.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\Network\\NetworkInterfacesView_x32.exe";
	UnicodeString app64 = curDir.getToolFull() + "\\Network\\NetworkInterfacesView_x64.exe";
	UnicodeString arg = "/stext " + outFilePath + "\"";
	RunApp net1 {app32, app64, arg};
	net1.run();
	printLogDebug(curConfig.getDebug(), net1.errorString());
	printLog(net1.resultString());
	progressBarGo(pos += step, net1.checkErr());
	printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	return !net1.checkErr();
}
bool job_net2() {
	UnicodeString outFilePath = curDir.getGrubFull() + "\\net2.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування net2.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\Network\\WifiHistoryView.exe";
	UnicodeString app64 = NULL;
	UnicodeString arg = "/stext " + outFilePath + "\"";
	RunApp net2 {app32, app64, arg};
	net2.run();
	printLogDebug(curConfig.getDebug(), net2.errorString());
	printLog(net2.resultString());
	progressBarGo(pos += step, net2.checkErr());
	printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	return !net2.checkErr();
}
bool job_license() {
	UnicodeString outFilePath = curDir.getGrubFull() + "\\license.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування license.txt...");
	if (FileExists("C:\\Windows\\System32\\wbem\\wmic.exe")) {
		UnicodeString app32 = curDir.getToolFull() + "\\scripts\\Info-License-to-File.bat";
		UnicodeString app64 = NULL;
		UnicodeString arg = "\""+ outFilePath + "\"";
		RunApp lic {app32, app64, arg};
		lic.run();
		printLogDebug(curConfig.getDebug(), lic.errorString());
		printLog(lic.resultString());
		progressBarGo(pos += step, lic.checkErr());
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
		return !lic.checkErr();
	} else {
		progressBarGo(pos += step, true);
		printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
		printLog("[!]ERROR!");
		return 0;
	}
}
bool job_audit() {
	UnicodeString outFilePath, arg;
	if(curConfig.getAudit() == 1) {
		outFilePath = curDir.getGrubFull() + "\\auditMax.html";
		arg = "/r=gsoPxuTUeERNtnzDaIbMpmidcSArHG /f=" + outFilePath + " /L=en\"";
		printLog("Генерування auditMax.html...");
	}
	if(curConfig.getAudit() == 2) {
		outFilePath = curDir.getGrubFull() + "\\auditMin.html";
		arg = "/r=go /f=" + outFilePath + " /L=en\"";
		printLog("Генерування auditMin.html...");
	}
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	UnicodeString app32 = curDir.getToolFull() + "\\WinAudit\\WinAudit.exe";
	UnicodeString app64 = NULL;
	RunApp audit {app32, app64, arg};
	audit.run();
	printLogDebug(curConfig.getDebug(), audit.errorString());
	printLog(audit.resultString());
	progressBarGo(pos += step, audit.checkErr());
	printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	return !audit.checkErr();
}
bool job_diskInfo() {
	UnicodeString outFilePath = curDir.getGrubFull() + "\\diskInfo.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування diskInfo.txt...");
	UnicodeString app32 = NULL;
	UnicodeString app64 = curDir.getToolFull() + "\\DiskInfo64\\DiskInfo64.exe";
	UnicodeString arg = "/CopyExit :";
	RunApp cdi {app32, app64, arg};
	cdi.run();
	UnicodeString f1 = curDir.getToolFull() + "\\DiskInfo64\\DiskInfo.txt";
	MoveFile(f1.c_str(), outFilePath.c_str());
	printLogDebug(curConfig.getDebug(), cdi.errorString());
	printLog(cdi.resultString());
	progressBarGo(pos += step, cdi.checkErr());
	printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	return !cdi.checkErr();
}
bool job_esetLog() {
	UnicodeString outFilePath, arg;
	if(curConfig.getEsetLog() == 1) {
		outFilePath = curDir.getGrubFull() + "\\eset-log-full.zip";
		arg = "/accepteula /Lang:UKR /Age:0 \"" + outFilePath + "\"";
		printLog("Генерування eset-log-full.zip...");
	}
	if(curConfig.getEsetLog() == 2) {
		outFilePath = curDir.getGrubFull() + "\\eset-log-mini.zip";
		arg = "/accepteula /Lang:UKR /Age:30 /Targets:warn,threat,ondem,dev \"" + outFilePath + "\"";
		printLog("Генерування eset-log-mini.zip...");
	}
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	UnicodeString app32 = curDir.getToolFull() + "\\EsetLogCollector\\ESETLogCollector.exe";
	UnicodeString app64 = NULL;
	RunApp esetLog {app32, app64, arg};
	esetLog.run(false);
	printLogDebug(curConfig.getDebug(), esetLog.errorString());
	printLog(esetLog.resultString());
	progressBarGo(pos += step, esetLog.checkErr());
	printLogDebug(curConfig.getDebug(), "{app32}=" + app32);
	printLogDebug(curConfig.getDebug(), "{arg}=" + arg);
	printLogDebug(curConfig.getDebug(), "{pos}=" + UnicodeString(pos));
	return !esetLog.checkErr();
}
//---------------------------------------------------------------------------
void TForm1::mainGRUBer(bool i) {
	// -> переменные
	grubActive = true;
	int persentStep;
	stopBool = false;
	passBool = false;
	bool bigErr = true;
	UnicodeString dirGrubStr = EditDirGrubName->Text;
	printLogDebug(curConfig.getDebug(), "{dirGrubStr}=" + dirGrubStr);
	// -> преварительные процедуры
	curPC.setLastGrub(curConfig.getUser(), curDateTime());
	Form1->BtnGruberRun->Enabled = false;
	Form1->BtnGruberStop->Enabled = true;
	Form1->BtnGruberRun->Caption = "Зачекай...";
	printLog("[>]GRUBer запущено...");
	printLog("Поточна тека: " + dirGrubStr);
	StatusBar1->Panels->Items[0]->Text = " GRUBer запущено...";
	// -> настройка прогресбара
	pos = 0;
	step = progressBarStep();
	ProgressBar1->State = (TProgressBarState) pbsNormal;
	Taskbar1->ProgressState = (TTaskBarProgressState) 2;
	progressBarGo(pos);
	// -> вывод дебаг инфы
	printLogDebug(curConfig.getDebug(), "{step}=" + UnicodeString(step));
	printLogDebug(curConfig.getDebug(), "{NewGrub}=" + UnicodeString(curConfig.getNewGrub()));
	printLogDebug(curConfig.getDebug(), "{OldGrubComent}=" + UnicodeString(curConfig.getOldGrubComent()));
	printLogDebug(curConfig.getDebug(), "{OldGrubInfo}=" + UnicodeString(curConfig.getOldGrubInfo()));
	printLogDebug(curConfig.getDebug(), "{OldGrubUsb}=" + UnicodeString(curConfig.getOldGrubUsb()));
	printLogDebug(curConfig.getDebug(), "{OldGrubNet}=" + UnicodeString(curConfig.getOldGrubNet()));
	printLogDebug(curConfig.getDebug(), "{License}=" + UnicodeString(curConfig.getLicense()));
	printLogDebug(curConfig.getDebug(), "{Audit}=" + UnicodeString(curConfig.getAudit()));
	printLogDebug(curConfig.getDebug(), "{EsetLog}=" + UnicodeString(curConfig.getEsetLog()));
	// -> сохранение введеной инфы о ПК
	infoSetToFille(curPC);
	// -> проверка имени папки граба
	for (int i = 1; i < dirGrubStr.Length()+1; i++) {
		if (dirGrubStr.IsDelimiter("<>:\"/\\|?* ", i)) {
            Form1->BtnGruberRun->Enabled = true;
			Form1->BtnGruberStop->Enabled = false;
			Form1->BtnGruberRun->Caption = "Запуск GRUBer";
			printLog("[!]Назва папки містить недопустимі символи!!! :'(");
            progressBarGo(100, true);
			return;
		}
	}
	// -> предупреждение о существующей папке
	if (DirectoryExists(curDir.getGrubFull()) && i) {
		FormDirExist->ShowDir->Text=(dirGrubStr);
		FormDirExist->ShowModal();
		printLog("Знайденно попередню теку!");
		if (!dirGrubRewrite) { //отказ от перезаписи
			Form1->BtnGruberRun->Enabled = true;
			Form1->BtnGruberStop->Enabled = false;
			Form1->BtnGruberRun->Caption = "Запуск GRUBer";
			printLog("[!]GRUBer зупинено :'(");
			return;
		}
		printLog("Наявні файли буде перезаписанно!");
	}
	// -> создание папок
    curDir.check();
	changeEditDirColor(); //смена заливки поля "папки граба" и активация кнопок
	// -> генерация файлов
	if (curConfig.getNewGrub() && !stopBool) job_infoFille();			//gruber_info.txt
	if (curConfig.getOldGrubComent() && !stopBool) job_comTxt(); 		//coment.txt
	if (curConfig.getOldGrubInfo() && !stopBool) bigErr *= job_info(); 	//info.txt
	if (curConfig.getOldGrubUsb() && !stopBool) bigErr *= job_usb();    //usb.txt
	if (curConfig.getOldGrubNet() && !stopBool) bigErr *= job_net1(); 	//net1.txt
	if (curConfig.getOldGrubNet() && !stopBool) bigErr *= job_net2(); 	//net2.txt
	if (curConfig.getLicense() && !stopBool) bigErr *= job_license(); 	//license.txt
	if (curConfig.getAudit() && !stopBool) bigErr *= job_audit(); 		//audit.html
	if (curConfig.getAudit() && !stopBool && x64 && IsAdminMode()) bigErr *= job_diskInfo(); //CDI.txt
	if (curConfig.getEsetLog() && !stopBool) bigErr *= job_esetLog();   //eset-log.zip
	// -> обработка ошибок
	if (!bigErr) {
		printLog("[ERR]GRUBer виконано з помилками!");
		StatusBar1->Panels->Items[0]->Text = " GRUBer ERROR!";
	} else {
		printLog("[OK]GRUBer виконано успішно!");
		StatusBar1->Panels->Items[0]->Text = " GRUBer виконано!";
	}
	// -> конец граба
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
	mainGRUBer(true);
}
void __fastcall TForm1::MiniGrubClick(TObject *Sender)
{
	bool tm1, tm2, tm3, tm4, tm5, tm6, tm7, tm8;
	tm1 = curConfig.getNewGrub();
	tm2 = curConfig.getOldGrubComent();
	tm3 = curConfig.getOldGrubInfo();
	tm4 = curConfig.getOldGrubUsb();
	tm5 = curConfig.getOldGrubNet();
	tm6 = curConfig.getLicense();
	tm7 = curConfig.getAudit();
	tm8 = curConfig.getEsetLog();
	curConfig.setNewGrub(1);
	curConfig.setOldGrubComent(0);
	curConfig.setOldGrubInfo(0);
	curConfig.setOldGrubUsb(0);
	curConfig.setOldGrubNet(0);
	curConfig.setLicense(0);
	curConfig.setAudit(0);
	curConfig.setEsetLog(0);
	mainGRUBer(false);
	curConfig.setNewGrub(tm1);
	curConfig.setOldGrubComent(tm2);
	curConfig.setOldGrubInfo(tm3);
	curConfig.setOldGrubUsb(tm4);
	curConfig.setOldGrubNet(tm5);
	curConfig.setLicense(tm6);
	curConfig.setAudit(tm7);
	curConfig.setEsetLog(tm8);
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
	UnicodeString setApp = curDir.getToolFull() + "\\scripts\\info_ps1\\Run.bat";
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
// ----
void __fastcall TForm1::Button_SerialClick(TObject *Sender)
{
	Form_Serial->Edit1->Text = curPC.getSerialMain();
	Form_Serial->Edit2->Text = curPC.getUUID();
	Form_Serial->Edit3->Text = curPC.getSerial_mrb();
	Form_Serial->Edit4->Text = curPC.getCPUID();
	//ustr = L"Hey! this unicode string will be hashed";
	UnicodeString hash_sha = curPC.getSerialMain() + curPC.getUUID();
	Form_Serial->Edit5->Text = THashSHA1::GetHashString(hash_sha);
	//Form_Serial->Edit5->Text = std::hash(hash_sha);
	Form_Serial->Position = (TPosition)7;
	Form_Serial->ShowModal();
}
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
		if (x64) archUpd = GetCurrentDir() + "\\update_x64.upd";
		else archUpd = GetCurrentDir() + "\\update_x32.upd";
	} else {
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
	RunApp esetBaseUnpack {
		app32,
		app64,
		"x -y -o\"" + curPC.getEsetDir() + "\" \"" + archUpd};
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
//
void __fastcall TForm1::BtnApp_UscDevUClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64) setApp = curDir.getToolFull() + "\\USBDeview\\USBDeview_x64.exe";
	else setApp = curDir.getToolFull() + "\\USBDeview\\USBDeview_x32.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_DeviceCleanupClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64) setApp = curDir.getToolFull() + "\\DeviceCleanup\\x64\\DeviceCleanup.exe";
	else setApp = curDir.getToolFull() + "\\DeviceCleanup\\Win32\\DeviceCleanup.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_UsbTreeViewClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64) setApp = curDir.getToolFull() + "\\UsbTreeView\\x64\\UsbTreeView.exe";
	else setApp = curDir.getToolFull() + "\\UsbTreeView\\UsbTreeView.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
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
