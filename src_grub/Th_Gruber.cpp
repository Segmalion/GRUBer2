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
extern bool stopBool, passBool, dirGrubRewrite, gruberStart;
extern bool grubActive;
extern double pos, step;
extern bool checkDirExist;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Th_Gruber::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
double progressBarStep() {
	short i = 0;
	if (curConfig.getNewGrub()) i += 2;
	if (curConfig.getOldGrubComent()) i++;
	if (curConfig.getOldGrubInfo()) i++;
	if (curConfig.getOldGrubUsb()) i++;
	if (curConfig.getOldGrubNet()) i += 2;
	if (curConfig.getLicense()) i++;
	if (curConfig.getAudit()) i ++;
	if (curConfig.getAudit() && x64() && IsAdminMode()) i ++;
	if (curConfig.getEsetLog()) i++;
	//printLogDebug("{count}=" + UnicodeString(i));
	return 100/(double)i;
}
void progressBarGo(int i , bool err) {
    if(stopBool == true || err == true) {
		Form1->ProgressBar_Grub->State = (TProgressBarState) pbsError;
		Form1->Taskbar1->ProgressState = (TTaskBarProgressState) 4;
	}
    Form1->ProgressBar_Grub->Position = i;
	Form1->Taskbar1->ProgressValue = i;
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
	// -> переменные
	grubActive = true;
	int persentStep;
	stopBool = false;
	passBool = false;
	bool bigErr = true;
	UnicodeString dirGrubStr = Form1->EditDirGrubName->Text;
	//printLogDebug("{dirGrubStr}=" + dirGrubStr);
	// -> преварительные процедуры
	// --- проверка нарушений
	checkDefection();
	// ...
	curPC.setLastGrub(curConfig.getUser(), curDateTime());
	Form1->BtnGruberRun->Enabled = false;
	Form1->BtnGruberStop->Enabled = true;
	Form1->BtnGruberRun->Caption = "Зачекай...";
	printLog(">>", "GRUBer запущено...");
	printLog("Поточна тека: " + dirGrubStr);
	Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer запущено...";
	// -> настройка прогресбара
	pos = 0;
	step = progressBarStep();
	Form1->ProgressBar_Grub->State = (TProgressBarState) pbsNormal;
	Form1->Taskbar1->ProgressState = (TTaskBarProgressState) 2;
	progressBarGo(pos);
	// -> сохранение введеной инфы о ПК
	infoSetToFille(curPC);
	// -> проверка имени папки граба
	for (int i = 1; i < dirGrubStr.Length()+1; i++) {
		if (dirGrubStr.IsDelimiter("<>:\"/\\|?* ", i)) {
            Form1->BtnGruberRun->Enabled = true;
			Form1->BtnGruberStop->Enabled = false;
			Form1->BtnGruberRun->Caption = "Запуск GRUBer";
			printLog("ER", "Назва папки містить недопустимі символи!!! :'(");
            progressBarGo(100, true);
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
		FormDirExist->ShowDir->Text=(dirGrubStr);
		FormDirExist->ShowModal();
		printLog("!!","Знайденно попередню теку!");
		if (!dirGrubRewrite) { //отказ от перезаписи
			Form1->BtnGruberRun->Enabled = true;
			Form1->BtnGruberStop->Enabled = false;
			Form1->BtnGruberRun->Caption = "Запуск GRUBer";
			printLog("ER", "GRUBer зупинено :'(");
			return;
		}
		printLog("!!","Наявні файли буде перезаписанно!");
	}
	// -- запуск секундомера
	auto start_time = std::chrono::steady_clock::now();
	// -> создание папок
    curDir.check();
	changeEditDirColor(); //смена заливки поля "папки граба" и активация кнопок
	// -> генерация файлов
	if (curConfig.getNewGrub() && !stopBool) job_infoFille(GrubDir);			//gruber_info.txt
	if (curConfig.getNewGrub() && !stopBool) job_softFille(GrubDir);
	if (curConfig.getOldGrubComent() && !stopBool) job_comTxt(GrubDir); 		//coment.txt
	if (curConfig.getOldGrubInfo() && !stopBool) bigErr *= job_info(GrubDir); 	//info.txt
	if (curConfig.getOldGrubUsb() && !stopBool) bigErr *= job_usb(GrubDir);    //usb.txt
	if (curConfig.getOldGrubNet() && !stopBool) bigErr *= job_net1(GrubDir); 	//net1.txt
	if (curConfig.getOldGrubNet() && !stopBool) bigErr *= job_net2(GrubDir); 	//net2.txt
	if (curConfig.getLicense() && !stopBool) bigErr *= job_license(GrubDir); 	//license.txt
	if (curConfig.getAudit() && !stopBool) bigErr *= job_audit(GrubDir); 		//audit.html
	if (curConfig.getAudit() && !stopBool && x64() && IsAdminMode()) bigErr *= job_diskInfo(GrubDir); //CDI.txt
	if (curConfig.getEsetLog() && !stopBool) bigErr *= job_esetLog(GrubDir);   //eset-log.zip
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
		printLog("ER", "GRUBer виконано з помилками!");
		Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer ERROR!";
	} else {
		printLog("OK", "GRUBer виконано успішно!");
		Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer виконано!";
	}
	// --
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	long double speedTimer = (long double)elapsed_ns.count()/1000000000;
	printLog("chrono", "Время выполнения: " + FloatToStrF(speedTimer, ffFixed, 4, 2));
	// -> конец граба
	grubActive = false;
	Form1->BtnGruberRun->Enabled = true;
	Form1->BtnGruberStop->Enabled = false;
	Form1->BtnGruberRun->Caption = "Запуск GRUBer";
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
	progressBarGo(pos += step, net2.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !net2.checkErr();
}
bool job_license(UnicodeString dir) {
	UnicodeString outFilePath = dir + "\\license.txt";
	if (FileExists(outFilePath)) FileSetAttr(outFilePath, 0) && DeleteFile(outFilePath);
	printLog("Генерування license.txt...");
	UnicodeString app32 = curDir.getToolFull() + "\\scripts\\Info-License-to-File.bat";
	UnicodeString app64 = NULL;
	UnicodeString arg = "\""+ outFilePath + "\"";
	RunApp lic {app32, app64, arg};
	lic.run();
//	printLogDebug(lic.errorString());
	printLog(lic.resultString());
	progressBarGo(pos += step, lic.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !lic.checkErr();
}
bool job_audit(UnicodeString dir) {
	UnicodeString outFilePath, arg;
	if(curConfig.getAudit() == 1) {
		outFilePath = dir + "\\auditMax.html";
		arg = "/r=gsoPxuTUeERNtnzDaIbMpmidcSArHG /f=" + outFilePath + " /L=en\"";
		printLog("Генерування auditMax.html...");
	}
	if(curConfig.getAudit() == 2) {
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
	progressBarGo(pos += step, cdi.checkErr());
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !cdi.checkErr();
}
bool job_esetLog(UnicodeString dir) {
	UnicodeString outFilePath, arg;
	if(curConfig.getEsetLog() == 1) {
		outFilePath = dir + "\\eset-log-full.zip";
		arg = "/accepteula /Lang:UKR /Age:0 \"" + outFilePath + "\"";
		printLog("Генерування eset-log-full.zip...");
	}
	if(curConfig.getEsetLog() == 2) {
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
	progressBarGo(pos += step, esetLog.checkErr());
//	printLogDebug("{app32}=" + app32);
//	printLogDebug("{arg}=" + arg);
//	printLogDebug("{pos}=" + UnicodeString(pos));
	return !esetLog.checkErr();
}
//---------------------------------------------------------------------------