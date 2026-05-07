//---------------------------------------------------------------------------

#include <System.hpp>
#include <chrono>
#include <filesystem>
#pragma hdrstop

#include "Th_Gruber.h"
#include "MainForm.h"
#include "DialogDirExist.h"

#include "Arm.h"
#include "Config.h"
#include "Dir.h"
#include "RunApp.h"

#include "Help.h"
#include "Text.h"
#include "Fille.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
extern Config curConfig;
extern Arm curPC;
extern Dir curDir;
extern bool th_Gruber_run;
extern bool th_Gruber_runMini, th_Gruber_runUSB;
extern bool stopBool, passBool, dirGrubRewrite, gruberStart;
extern bool grubActive;
double pos, step;
extern bool checkDirExist;
bool jb1, jb2, jb3, jb4, jb5, jb6;
short jb7, jb8;
short countJob, curJob;

//---------------------------------------------------------------------------
void progressBarStep() {
	countJob = 0;
	if (jb1 != 0) countJob += 2;   //gruber_info.ini & soft_all.txt
	if (jb1 != 0) countJob++; 	   //soft_block.txt
	if (jb2 != 0) countJob++;      //coment.txt
	if (jb3 != 0) countJob++;      //info_ps1.txt
	if (jb4 != 0) countJob++;      //usb.txt
	if (jb5 != 0) countJob += 2;   //net1.txt & net2.txt
	if (jb6 != 0) countJob++;      //license.txt
	if (jb7 != 0) countJob++;      //auditMin.html || auditMax.html
	if (jb7 != 0 && x64_sys() && IsAdminMode()) countJob++; //diskInfo.txt
	if (jb8 != 0) countJob++;      //eset-log-mini.zip || eset-log-max.zip
	printLogDebug("{countJob}=" + UnicodeString(countJob));
	step = 100/(double)countJob;
}
void jobDone(short &c, short &n) {
	UnicodeString str;
	if (c > n) str = " [" + UnicodeString(n) + "/" + UnicodeString(c) + "]GRUBer запущено...";
	else if (c == n) str = " [" + UnicodeString(n) + "/" + UnicodeString(c) + "]GRUBer зібрано!!!";
	Form1->StatusBar1->Panels->Items[0]->Text = str;
}
void progressBarGo(int i , bool err) {
    if(stopBool == true || err == true) {
		Form1->ProgressBar_Grub->State = (TProgressBarState) pbsError;
		Form1->Taskbar1->ProgressState = (TTaskBarProgressState) 4;
	}
    Form1->ProgressBar_Grub->Position = i;
	Form1->Taskbar1->ProgressValue = i;
}
void blockGrub(bool i) {
	Form1->BtnGruberRun->Enabled = !i;
	Form1->BtnGruberStop->Enabled = i;
	//Form1->GroupBox_SetingsGRUB->Enabled = !i;
	//-----
	Form1->Edit_NumberARM->Enabled = !i;
	Form1->EditPartition->Enabled = !i;
	Form1->EditCategory->Enabled = !i;
	Form1->EditArmClass->Enabled = !i;
	Form1->EditPurpose->Enabled = !i;
	Form1->EditRespon->Enabled = !i;
	Form1->Edit_Place->Enabled = !i;
	Form1->Edit_Phone->Enabled = !i;
	Form1->EditComent->Enabled = !i;
	//-----
	Form1->Edit_InNumberARM->Enabled = !i;
	Form1->Edit_InNumberHDD->Enabled = !i;
	Form1->Edit_InNumberDeclr->Enabled = !i;
	Form1->Edit_InNumberFormulyar->Enabled = !i;
	Form1->Edit_InNumberWork->Enabled = !i;
	Form1->Edit_InNumberPerson->Enabled = !i;
	Form1->Edit_InRespon->Enabled = !i;
	Form1->Edit_InAdminBP->Enabled = !i;
	//-----
	Form1->ComboBox_PoliticInstall->Enabled = !i;
	Form1->ComboBox_ContrUSB->Enabled = !i;
	Form1->ComboBox_MultiUSERS->Enabled = !i;
	Form1->EditLicWin->Enabled = !i;
	Form1->EditLicOffice->Enabled = !i;
	//-----
	Form1->EditGrubUser->Enabled = !i;
	Form1->CheckBoxOldGrub->Enabled = !i;
	Form1->CheckBoxNewGrub->Enabled = !i;
	Form1->CheckBoxLicense->Enabled = !i;
	Form1->CheckBoxAudit->Enabled = !i;
	Form1->CheckBoxEsetLog->Enabled = !i;
	Form1->CheckBoxPrefixPartition->Enabled = !i;
	Form1->EditPrefixPartition->Enabled = !i;
	Form1->ComboBox_forNumberARM->Enabled = !i;
	//-----
	if (i) Form1->BtnGruberRun->Caption = "Зачекай...";
	else Form1->BtnGruberRun->Caption = "Запуск GRUBer";
}
//----------
__fastcall Th_Gruber::Th_Gruber(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
/* ОСНОВНОЙ КОД ГРАБА */
void __fastcall Th_Gruber::Execute()
{
	FreeOnTerminate = true;
	// -> переменные
	th_Gruber_run = true;
	grubActive = true;
	int persentStep;
	stopBool = false;
	passBool = false;
	bool bigErr = true;
	UnicodeString dirGrubStr = Form1->EditDirGrubName->Text;
	// -> переменные JOB
	jb1 = curConfig.getNewGrub();
	jb2 = curConfig.getOldGrubComent();
	jb3 = curConfig.getOldGrubInfo();
	jb4 = curConfig.getOldGrubUsb();
	jb5 = curConfig.getOldGrubNet();
	jb6 = curConfig.getLicense();
	jb7 = curConfig.getAudit();
	jb8 = curConfig.getEsetLog();
	if (th_Gruber_runMini == true) {
		jb1 = 1; jb2 = 0; jb3 = 0; jb4 = 0; jb5 = 0; jb6 = 0; jb7 = 0; jb8 = 0; }
	if (th_Gruber_runUSB == true) {
		jb1 = 0; jb2 = 0; jb3 = 0; jb4 = 1; jb5 = 0; jb6 = 0; jb7 = 0; jb8 = 0; }
	// -> преварительные процедуры
	// --- настройка прогресбара
	pos = 0;
	progressBarStep();
	Synchronize([this]() {
		Form1->ProgressBar_Grub->State = (TProgressBarState) pbsNormal;
		Form1->Taskbar1->ProgressState = (TTaskBarProgressState) 2;
		progressBarGo(pos);
	});
	// --- проверка нарушений
	checkDefection();
	// ...
	curPC.setLastGrub(curConfig.getUser(), curDateTime());
	Synchronize([=]() {
		blockGrub(true);
		printLog(">>", "GRUBer запущено...");
		jobDone(countJob, curJob);
	});
	// -> сохранение введеной инфы о ПК
	infoSetToFille(curPC);
	// -> проверка имени папки граба
	for (int i = 1; i < dirGrubStr.Length()+1; i++) {
		if (dirGrubStr.IsDelimiter("<>:\"/\\|?* ", i)) {
			Synchronize([this]() {
				blockGrub(false);
				printLog("ER", "Назва папки містить недопустимі символи!!! :'(");
				Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer ERROR:'(";
				progressBarGo(100, true);
			});
            th_Gruber_run = false;
			return;
		}
	}
	UnicodeString GrubDir;
	bool tempDir = Form1->CheckBox_TempDir->Checked;
	if (tempDir) {
		GrubDir = curDir.get_grubTemp();
		if (!DirectoryExists(GrubDir)) CreateDir(GrubDir);
		else deleteDir(GrubDir, false);
	} else GrubDir = curDir.getGrubFull();
	// -> предупреждение о существующей папке
	if (DirectoryExists(curDir.getGrubFull()) && checkDirExist) {
		Synchronize([=]() {
			FormDirExist->ShowDir->Text=(dirGrubStr);
			FormDirExist->ShowModal();
			printLog("!!","Знайденно попередню теку!");
		});
		if (!dirGrubRewrite) { //отказ от перезаписи
			Synchronize([this]() {
				blockGrub(false);
				printLog("SP", "GRUBer зупинено :'(");
				Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer зупинено:'(";
			});
			th_Gruber_run = false;
			return;
		}
		Synchronize([this]() { printLog("!!","Наявні файли буде перезаписанно!"); });
	}
	// -- запуск секундомера
	auto start_time = std::chrono::steady_clock::now();
	// -> создание папок
    curDir.check();
	changeEditDirColor(); //смена заливки поля "папки граба" и активация кнопок
	// -> генерация файлов
	if (jb1 != 0 && !stopBool) job_infoFille(GrubDir);			//gruber_info.txt
	if (jb1 != 0 && !stopBool) job_softFille(GrubDir);
	if (jb2 != 0 && !stopBool) job_comTxt(GrubDir); 		//coment.txt
	if (jb3 != 0 && !stopBool) bigErr *= job_info(GrubDir); 	//info.txt
	if (jb4 != 0 && !stopBool) bigErr *= job_usb(GrubDir);    //usb.txt
	if (jb5 != 0 && !stopBool) bigErr *= job_net1(GrubDir); 	//net1.txt
	if (jb5 != 0 && !stopBool) bigErr *= job_net2(GrubDir); 	//net2.txt
	if (jb6 != 0 && !stopBool) bigErr *= job_license(GrubDir); 	//license.txt
	if (jb7 != 0 && !stopBool) bigErr *= job_audit(GrubDir); 		//audit.html
	if (jb7 != 0 && !stopBool && x64_sys() && IsAdminMode()) bigErr *= job_diskInfo(GrubDir); //CDI.txt
	if (jb8 != 0 && !stopBool) bigErr *= job_esetLog(GrubDir);   //eset-log.zip
	// --
	if (tempDir) {
        TSearchRec sr;
		if (GrubDir.Length()) {
			if (!FindFirst(GrubDir + "\\*.*", faAnyFile, sr)) {
				do {
					if (!(sr.Name == "." || sr.Name == "..")) { // это не трогаем
						// если находим папку граба, добавляем в список
						std::wstring oldFile = unToStr(GrubDir + "\\" + sr.Name);
						std::wstring newFile = unToStr(curDir.getGrubFull() + "\\" + sr.Name);
						std::filesystem::rename(oldFile, newFile);
					}
				} while (!FindNext(sr)); // ищем пока не найдем все
			}
			FindClose(sr);
		}
	}
	// -> обработка ошибок
	if (!bigErr) {
		Synchronize([this]() {
			printLog("ER", "GRUBer виконано з помилками!");
			Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer ERROR!";
            progressBarGo(100, true);
		});
	} else {
		Synchronize([this]() {
			printLog("OK", "GRUBer виконано успішно!");
			//Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer виконано!";
		});
	}
	// --
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	long double speedTimer = (long double)elapsed_ns.count()/1000000000;
	// -> конец граба
	grubActive = false;
	Synchronize([=]() {
		printLog("chrono", "Время выполнения: " + FloatToStrF(speedTimer, ffFixed, 4, 2));
		blockGrub(false);
	});
    th_Gruber_run = false;
}
//---------------------------------------------------------------------------
bool job_infoFille(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\gruber_info.ini";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування gruber_info.ini...");
	TStringList *infoFille = new TStringList;
	for(auto str : fileInfoGrub()) infoFille->Add (str);
	infoFille->SaveToFile(outFilePath, TEncoding::UTF8); // запись в файл
	printLog("Файл СТВОРЕННО!");
	jobDone(countJob, ++curJob);
	progressBarGo(pos += step);
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return true;
}
bool job_softFille(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\soft_all.txt";
	std::vector<UnicodeString> sortList_all;
	std::vector<UnicodeString> sortList_block;
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування soft_all.txt...");
	TStringList *softAllFille = new TStringList;
	for(auto soft : curPC.get_softInstall()) sortToVector(sortList_all, soft.name);
	for(auto str: sortList_all) softAllFille->Add (str);
	softAllFille->SaveToFile(outFilePath, TEncoding::UTF8); // запись в файл
	printLog("Файл СТВОРЕННО!");
    progressBarGo(pos += step);
	if (curPC.get_softBlock().size() > 0) {
		outFilePath = dir + "\\soft_block.txt";
		if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
		printLog("Генерування soft_block.txt...");
		TStringList *softBlockFille = new TStringList;
		for(auto soft : curPC.get_softBlock()) sortToVector(sortList_block, soft.name);
		for(auto str: sortList_block) softBlockFille->Add (str);
		softBlockFille->SaveToFile(outFilePath, TEncoding::UTF8); // запись в файл
		printLog("Файл СТВОРЕННО!");
	}
    curJob += 2;
	jobDone(countJob, curJob);
	progressBarGo(pos += step);
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return true;
}
bool job_comTxt(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\coment.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування coment.txt...");
	TStringList *comTxt = new TStringList;
	comTxt->Add(curPC.getComentStr());
	comTxt->Add(curPC.getRespon());
	comTxt->Add(curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition()));
	comTxt->Add("");
	comTxt->SaveToFile(outFilePath, TEncoding::UTF8);
	printLog("Файл СТВОРЕННО!");
	jobDone(countJob, ++curJob);
	progressBarGo(pos += step);
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return true;
}
bool job_info(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\info_ps1.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування info_ps1.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\scripts\\info_ps1\\Run_toFile.bat";
	UnicodeString arg = "\""+ outFilePath + "\"";
	RunApp info {app32, NULL, arg};
	info.run(); // RUN !!!
//	printLogDebug(info.errorString());
	printLog(info.resultString());
	jobDone(countJob, ++curJob);
	progressBarGo(pos += step, info.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !info.checkErr();
}
bool job_usb(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\usb.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування usb.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\USBDeview\\USBDeview_x32.exe";
	UnicodeString app64 = curDir.getToolFull() + "\\USBDeview\\USBDeview_x64.exe";
	UnicodeString arg = "/stext " + outFilePath + "\"";
	RunApp usb {app32, app64, arg};
	usb.run();
//	printLogDebug(usb.errorString());
	printLog(usb.resultString());
	jobDone(countJob, ++curJob);
	if (FileExists(outFilePath)) {
		Form1->BtnParserOpen->Enabled = DirectoryExists(curDir.getGrubFull());
	}
	progressBarGo(pos += step, usb.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !usb.checkErr();
}
bool job_net1(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\net1.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування net1.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\Network\\NetworkInterfacesView_x32.exe";
	UnicodeString app64 = curDir.getToolFull() + "\\Network\\NetworkInterfacesView_x64.exe";
	UnicodeString arg = "/stext " + outFilePath + "\"";
	RunApp net1 {app32, app64, arg};
	net1.run();
//	printLogDebug(net1.errorString());
	printLog(net1.resultString());
	jobDone(countJob, ++curJob);
	progressBarGo(pos += step, net1.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !net1.checkErr();
}
bool job_net2(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\net2.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування net2.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\Network\\WifiHistoryView.exe";
	UnicodeString app64 = NULL;
	UnicodeString arg = "/stext " + outFilePath + "\"";
	RunApp net2 {app32, app64, arg};
	net2.run();
//	printLogDebug(net2.errorString());
	printLog(net2.resultString());
	jobDone(countJob, ++curJob);
	progressBarGo(pos += step, net2.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !net2.checkErr();
}
bool job_license(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\license.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування license.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\CheckActivationStatus\\CheckActivationStatus.exe";
	UnicodeString app64 = NULL;
	UnicodeString arg = "-pass -log \""+ outFilePath + "\"";
	RunApp lic {app32, app64, arg};
	lic.run();
//	printLogDebug(lic.errorString());
	printLog(lic.resultString());
	jobDone(countJob, ++curJob);
	progressBarGo(pos += step, lic.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !lic.checkErr();
}
bool job_audit(UnicodeString dir) {
	UnicodeString outFilePath, arg;
	if(jb7 == 1) {
		outFilePath = dir + "\\auditMax.html";
		arg = "/r=gsoPxuTUeERNtnzDaIbMpmidcSArHG /f=" + outFilePath + " /L=en\"";
		printLog("Генерування auditMax.html...");
	}
	if(jb7 == 2) {
		outFilePath = dir + "\\auditMin.html";
		arg = "/r=go /f=" + outFilePath + " /L=en\"";
		printLog("Генерування auditMin.html...");
	}
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	UnicodeString app32 = curDir.getToolFull() + "\\WinAudit\\WinAudit.exe";
	UnicodeString app64 = NULL;
	RunApp audit {app32, app64, arg};
	audit.run();
//	printLogDebug(audit.errorString());
	printLog(audit.resultString());
	jobDone(countJob, ++curJob);
	progressBarGo(pos += step, audit.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !audit.checkErr();
}
bool job_diskInfo(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\diskInfo.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування diskInfo.txt...");
	UnicodeString app32 = NULL;
	UnicodeString app64 = curDir.getToolFull() + "\\DiskInfo64\\DiskInfo64.exe";
	UnicodeString arg = "/CopyExit :";
	RunApp cdi {app32, app64, arg};
	cdi.run();
	UnicodeString f1 = curDir.getToolFull() + "\\DiskInfo64\\DiskInfo.txt";
	MoveFile(f1.c_str(), outFilePath.c_str());
//	printLogDebug(cdi.errorString());
	printLog(cdi.resultString());
	jobDone(countJob, ++curJob);
	progressBarGo(pos += step, cdi.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !cdi.checkErr();
}
bool job_esetLog(UnicodeString dir) {
	UnicodeString outFilePath, arg;
	if(jb8 == 1) {
		outFilePath = dir + "\\eset-log-full.zip";
		arg = "/accepteula /Lang:UKR /Age:0 \"" + outFilePath + "\"";
		printLog("Генерування eset-log-full.zip...");
	}
	if(jb8 == 2) {
		outFilePath = dir + "\\eset-log-mini.zip";
		arg = "/accepteula /Lang:UKR /Age:30 /Targets:warn,threat,ondem,dev \"" + outFilePath + "\"";
		printLog("Генерування eset-log-mini.zip...");
	}
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	UnicodeString app32 = curDir.getToolFull() + "\\EsetLogCollector\\ESETLogCollector.exe";
	UnicodeString app64 = NULL;
	RunApp esetLog {app32, app64, arg};
	esetLog.run(false);
//	printLogDebug(esetLog.errorString());
	printLog(esetLog.resultString());
    jobDone(countJob, ++curJob);
	progressBarGo(pos += step, esetLog.checkErr());
//	printLogDebug("{app32}=" + app32);
//	printLogDebug("{arg}=" + arg);
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !esetLog.checkErr();
}
//---------------------------------------------------------------------------