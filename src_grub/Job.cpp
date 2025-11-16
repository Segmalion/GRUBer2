//---------------------------------------------------------------------------

#pragma hdrstop

#include "Job.h"
#include "MainForm.h"

#include "Text.h"
#include "Arm.h"
#include "RunApp.h"
#include "Help.h"
#include "Dir.h"
#include "Config.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
extern Arm curPC;
extern Dir curDir;
extern Config curConfig;
extern double pos, step;
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
