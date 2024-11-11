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
Dir curDir;
histGrub lastGrub;
cnfgGrub curConfig;
infoEset curEset;
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
	Form1->ShowName->Text = curPC.getDesktopName();
	Form1->ShowSerial->Text = curPC.getSerial();
   // Проверка наличия CMD и прав на выполнение
	cmdEXE = cmdCheck();
	if(cmdEXE != "ERROR") printLogDebug(curConfig.debug, "Patch to CMD.EXE set!");
		else printLog("[!]Не мае доступу чи прав на CMD!");
	// Чтение параметров GRUBer'а
	if(paramReadAndSet(curConfig)) printLogDebug(curConfig.debug, "Settings Read!");
		else printLog("[!]Не знайденно GRUBer.ini!");
	// Чтение сохраненной инфы об АРМ
	if(infoReadAndSet(curPC)) {
		printLogDebug(curConfig.debug, "Info Read!");
		Form1->EditDirGrubName->Text = curPC.dirGrubName();
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
std::vector<UnicodeString> TForm1::fileInfoGrub() {
	std::vector<UnicodeString> vStr;
	// раздел даты и пользователя
	vStr.push_back("[lastGrub]");
	vStr.push_back("lastGrubDate=" + lastGrub.date);
	vStr.push_back("lastGrubUser=" + lastGrub.user);
	// раздел об АРМ-1
	vStr.push_back("[infoGrubARM]");
	for(auto str : curPC.mStrInfoArmGrub()) vStr.push_back(str);
	// раздел об АРМ-2
	vStr.push_back("[infoARM]");
	for(auto str : curPC.mStrInfoArm()) vStr.push_back(str);
	// раздел об ESET
	vStr.push_back("[infoESET]");
	vStr.push_back("dirMirror=" + curEset.dirMirror);
	vStr.push_back("autoUpdate=" + UnicodeString(curEset.autoUpdate));
	vStr.push_back("lastUpdateDate=" + curEset.lastUpdateDate);
	vStr.push_back("lastUpdateUser=" + curEset.lastUpdateUser);
	vStr.push_back("lastUpdateArchive=" + curEset.lastUpdateArchive);
	// раздел коментария
	vStr.push_back("[comment]");
	for (auto str : curPC.getComent()) {
		vStr.push_back(str);
	}
	vStr.push_back("#stop");
	return vStr;
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
	curDir.setGrubFull(curPC.dirGrubName());
	// папка граба
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
	if (!stopBool) {
		outFilePath = curDir.getGrubFull() + "\\gruber_info.ini";
		TStringList *infoFille = new TStringList;
		for(auto str : fileInfoGrub()) infoFille->Add (str);
		infoFille->SaveToFile(outFilePath, TEncoding::UTF8); // запись в файл
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
	Form1->CheckBox1->Checked = DirectoryExists(curDir.getGrubFull());
	Form1->BtnGruberDirOpen->Enabled = DirectoryExists(curDir.getGrubFull());
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
	ShellExecuteW(NULL, L"open", curDir.getGrubFull().c_str(), NULL, NULL, SW_SHOWDEFAULT);
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
	curPC.setCategory(EditCategory->Text, EditCategory->ItemIndex);
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
}
void __fastcall TForm1::EditGrubUserChange(TObject *Sender)
{
	curConfig.grubUser = Form1->EditGrubUser->Text;
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

