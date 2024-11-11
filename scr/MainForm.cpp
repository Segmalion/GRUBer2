//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "ComentForm.h"
#include "DialogDirExist.h"

#include "Arm.h"
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
histGrub lastGrub;
cnfgGrub curConfig;
infoEset curEset;
dir curDir;
//обявление переменных
UnicodeString cmdEXE, curentDate;
bool stopBool;
bool dirGrubRewrite;
//---------------------------------------------------------------------------
const short vers1 = 0, vers2 = 2, vers3 = 0, vers4 = 5;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	if (curPC.getInfo()) {
		Form1->ShowName->Text = curPC.desktopName;
      Form1->ShowSerial->Text = curPC.serial;
	}
	else printLog("[!]Не вийшло отримати данні компютера!");
   // Проверка наличия CMD и прав на выполнение
	cmdEXE = cmdCheck();
	if(cmdEXE != "ERROR") printLogDebug(curConfig.debug, "Patch to CMD.EXE set!");
		else printLog("[!]Не мае доступу чи прав на CMD!");
	// Настройка папок
	curDir.progPath = GetCurrentDir();
	curDir.base = "base"; // папка базы
	curDir.basePath = curDir.progPath + "\\" + curDir.base;
	curDir.baseDate = "[" + curDate() + "]"; //папка даты
	curDir.baseDatePath = curDir.basePath + "\\" + curDir.baseDate;
	// Чтение параметров GRUBer'а
	if(paramReadAndSet(curConfig)) printLogDebug(curConfig.debug, "Settings Read!");
		else printLog("[!]Не знайденно GRUBer.ini!");
	// Чтение сохраненной инфы об АРМ
	if(infoReadAndSet(curPC)) {
		printLogDebug(curConfig.debug, "Info Read!");
		Form1->EditDirGrubName->Text = curPC.dirCurGrubName(curDate());;
	} else printLog("[!]Не знайденно GRUBer.ini!");
	// ---
	PageControl1->TabIndex = 0;
	const UnicodeString versionApp = UnicodeString(vers1) + "."
							  + UnicodeString(vers2) + "."
							  + UnicodeString(vers3) + "."
							  + UnicodeString(vers4);
	printLog("[>]Запушенно GRUBer v." + versionApp);
}
//---------------------------------------------------------------------------
/* Кнопки */
// запуск Граба
void __fastcall TForm1::BtnGruberRunClick(TObject *Sender) //Запуск Граба
{
	/* Преварительные процедуры */
	printLogDebug(curConfig.debug, "CLICK{BtnGruberRun}");
   Form1->BtnGruberRun->Enabled = false;
	Form1->BtnGruberStop->Enabled = true;
	Form1->BtnGruberRun->Caption = "Зачекай...";
	/* Переменные */
	int persentStep;
	UnicodeString outFilePath;
	stopBool=false;
	lastGrub.user = curConfig.grubUser;
	/* Настройка прогресбара */
	/* Сохранение введеной инфы о ПК */
	infoSetToFille(curEset, lastGrub, curPC);
	/* Проверка и создание папок */
	if (!DirectoryExists(curDir.basePath)) CreateDir(curDir.basePath);
	if (!DirectoryExists(curDir.baseDatePath)) CreateDir(curDir.baseDatePath);
	// папка граба
	if (DirectoryExists(curDir.baseGrubPath)) {
		FormDirExist->ShowDir->Text=(curDir.baseGrub);
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
		//deleteDir(curDirGrub);
	}
	if (!DirectoryExists(curDir.baseGrubPath)) CreateDir(curDir.baseGrubPath);
	/* 1 - gruber_info.txt */
	if (!stopBool) {
		outFilePath = curDir.baseGrub + "\\gruber_info.txt";
		TStringList *infoFille = new TStringList;
		/* формирование файла */
		// раздел даты и пользователя
		infoFille->Add("[lastGrub]");
		infoFille->Add("lastGrubDate=" + lastGrub.date);
		infoFille->Add("lastGrubUser=" + lastGrub.user);
		// раздел об АРМ-1
		infoFille->Add("[infoGrubARM]");
		infoFille->Add("number=" + UnicodeString(curPC.number));
		infoFille->Add("partition=" + curPC.partitionName);
		infoFille->Add("armClassID=" + UnicodeString(curPC.armClassId));
		infoFille->Add("armClasName=" + curPC.armClassName);
		infoFille->Add("categoryID=" + UnicodeString(curPC.categoryId));
		infoFille->Add("categoryName=" + curPC.categoryName);
		infoFille->Add("licenseWindowsID=" + UnicodeString(curPC.licWindowsId));
		infoFille->Add("licenseWindowsName=" + curPC.licWindowsName);
		infoFille->Add("licenseOfficeID=" + UnicodeString(curPC.licOfficeId));
		infoFille->Add("licenseOfficeName=" + curPC.licOfficeName);
		infoFille->Add("respon=" + curPC.respon);
		// раздел об АРМ-2
		infoFille->Add("[infoARM]");
		infoFille->Add("serialNumber=" + curPC.serial);
		infoFille->Add("desktopName=" + curPC.desktopName);
		// раздел об ESET
		infoFille->Add("[infoESET]");
		infoFille->Add("dirMirror=" + curEset.dirMirror);
		infoFille->Add("autoUpdate=" + UnicodeString(curEset.autoUpdate));
		infoFille->Add("lastUpdateDate=" + curEset.lastUpdateDate);
		infoFille->Add("lastUpdateUser=" + curEset.lastUpdateUser);
		infoFille->Add("lastUpdateArchive=" + curEset.lastUpdateArchive);
		// раздел коментария
		infoFille->Add("[comment]");
		for (auto i : curPC.coment) {
			infoFille->Add(i);
		}
		infoFille->Add("#stop");
		/* конец формирования файла */
		infoFille->SaveToFile(curDir.baseGrub, TEncoding::UTF8); // запись в файл
	}
	/*  */
	/*  */
	/*  */
	/*  */
	/*  */
	/*  */
	/*  */
	Form1->BtnGruberRun->Enabled = true;
	Form1->BtnGruberStop->Enabled = false;
	Form1->BtnGruberRun->Caption = "Запуск GRUBer";
   Form1->CheckBox1->Checked = DirectoryExists(curDir.baseGrubPath);
	Form1->BtnGruberDirOpen->Enabled = DirectoryExists(curDir.baseGrubPath);
}
// просмотр коментария
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	FormComent->EditComent->Lines = Form1->EditComent->Lines;
	FormComent->ShowModal();
}
// открыть папку Граба
void __fastcall TForm1::BtnGruberDirOpenClick(TObject *Sender)
{
	ShellExecuteW(NULL, L"open", curDir.baseGrubPath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// остановка Граба
void __fastcall TForm1::BtnGruberStopClick(TObject *Sender)
{
	stopBool = true;
}
//---------------------------------------------------------------------------
/* Изменение полей */
void __fastcall TForm1::EditNumberChange(TObject *Sender)
{
	curPC.number = Form1->EditNumber->Value;
	Form1->EditDirGrubName->Text = curPC.dirCurGrubName(curDate());
	printLogDebug(curConfig.debug, "SET{cfg.number}=" + UnicodeString(curPC.number));
}
void __fastcall TForm1::EditPartitionChange(TObject *Sender)
{
	curPC.partitionName = Form1->EditPartition->Text;
	Form1->EditDirGrubName->Text = curPC.dirCurGrubName(curDate());
	printLogDebug(curConfig.debug, "SET{curPC.partitionName}=" + UnicodeString(curPC.partitionName));
}
void __fastcall TForm1::EditArmClassChange(TObject *Sender)
{
	curPC.armClassId   = Form1->EditArmClass->ItemIndex;
	curPC.armClassName = Form1->EditArmClass->Text;
	printLogDebug(curConfig.debug, "SET{curPC.armClassId}=" + UnicodeString(curPC.armClassId));
	printLogDebug(curConfig.debug, "SET{curPC.armClassName}=" + UnicodeString(curPC.armClassName));
}
void __fastcall TForm1::EditCategoryChange(TObject *Sender)
{
	curPC.categoryId   = Form1->EditCategory->ItemIndex;
	curPC.categoryName = Form1->EditCategory->Text;
	Form1->EditDirGrubName->Text = curPC.dirCurGrubName(curDate());
	printLogDebug(curConfig.debug, "SET{curPC.categoryId}=" + UnicodeString(curPC.categoryId));
	printLogDebug(curConfig.debug, "SET{curPC.categoryName}=" + UnicodeString(curPC.categoryName));
}
void __fastcall TForm1::EditResponChange(TObject *Sender)
{
	curPC.respon = Form1->EditRespon->Text;
	Form1->EditDirGrubName->Text = curPC.dirCurGrubName(curDate());
	printLogDebug(curConfig.debug, "SET{curPC.respon}=" + UnicodeString(curPC.respon));
}
void __fastcall TForm1::EditLicWinChange(TObject *Sender)
{
	curPC.licWindowsId = Form1->EditLicWin->ItemIndex;
	curPC.licWindowsName = Form1->EditLicWin->Text;
	printLogDebug(curConfig.debug, "SET{curPC.licWindowsId}=" + UnicodeString(curPC.licWindowsId));
	printLogDebug(curConfig.debug, "SET{curPC.licWindowsName}=" + UnicodeString(curPC.licWindowsName));
}
void __fastcall TForm1::EditLicOfficeChange(TObject *Sender)
{
	curPC.licOfficeId = Form1->EditLicOffice->ItemIndex;
	curPC.licOfficeName = Form1->EditLicOffice->Text;
	printLogDebug(curConfig.debug, "SET{curPC.licOfficeId}=" + UnicodeString(curPC.licOfficeId));
	printLogDebug(curConfig.debug, "SET{curPC.licOfficeName}=" + UnicodeString(curPC.licOfficeName));
}
void __fastcall TForm1::EditComentChange(TObject *Sender)
{
	curPC.coment.clear();
	for (auto i : Form1->EditComent->Lines) {
		curPC.coment.push_back(i);
	}
	printLogDebug(curConfig.debug, "SET{curPC.coment}");
}
void __fastcall TForm1::EditDirGrubNameChange(TObject *Sender)
{
	curPC.dirGrubName = Form1->EditDirGrubName->Text;
	curDir.baseGrub = curPC.dirGrubName;
	curDir.baseGrubPath = curDir.baseDatePath + "\\" + curDir.baseGrub;
	Form1->CheckBox1->Checked = DirectoryExists(curDir.baseGrubPath);
	Form1->BtnGruberDirOpen->Enabled = DirectoryExists(curDir.baseGrubPath);
	printLogDebug(curConfig.debug, "SET{curPC.DirGrubName}=" + UnicodeString(curPC.dirGrubName));
}
void __fastcall TForm1::EditGrubUserChange(TObject *Sender)
{
	curConfig.grubUser = Form1->EditGrubUser->Text;
	printLogDebug(curConfig.debug, "SET{curConfig.grubUser}=" + curConfig.grubUser);
}
//---------------------------------------------------------------------------
/* Чекбоксы в настройках */
void __fastcall TForm1::CheckBoxShowLogClick(TObject *Sender)
{
	curConfig.showLog = CheckBoxShowLog->Checked;
	if (curConfig.showLog) Form1->Width = 1024*Form1->ScaleFactor;
	else Form1->Width = 421*Form1->ScaleFactor;
}
void __fastcall TForm1::CheckBoxDebugClick(TObject *Sender)
{
	curConfig.debug = CheckBoxDebug->Checked;
}
//---------------------------------------------------------------------------

