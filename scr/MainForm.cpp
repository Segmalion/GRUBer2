//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "HelpTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
edit ed;
config cfg;
bool stopBool = 0;
//---------------------------------------------------------------------------
const UnicodeString versionApp = "v.0.2.0.1";
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
   PageControl1->TabIndex = 0;
	printLog("[>]Запушенно GRUBer " + versionApp);
	// Чтение параметров
	if(paramReadAndSet()) {	printLogDebug("Settings Read!"); }
		else { printLog("[!]Не знайденно GRUBer.ini!"); }
	// Чтение сохраненной инфы
   if(infoReadAndSet()) {	printLogDebug("Info Read!"); }
		else { printLog("[!]Не знайденно GRUBer.ini!"); }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/* Кнопки */
void __fastcall TForm1::BtnGruberRunClick(TObject *Sender)
{
	printLogDebug("CLICK{BtnGruberRun}");
}
//---------------------------------------------------------------------------
/* Изменение полей */
void __fastcall TForm1::EditNumberChange(TObject *Sender)
{
	ed.number = Form1->EditNumber->Value;
	printLogDebug("SET{ed.number}=" + UnicodeString(ed.number));
}
void __fastcall TForm1::EditPartitionChange(TObject *Sender)
{
	ed.partitionId   = Form1->EditPartition->ItemIndex;
	ed.partitionName = Form1->EditPartition->Text;
	printLogDebug("SET{ed.partitionId}=" + UnicodeString(ed.partitionId));
	printLogDebug("SET{ed.partitionName}=" + UnicodeString(ed.partitionName));
}
void __fastcall TForm1::EditArmClassChange(TObject *Sender)
{
	ed.armClassId   = Form1->EditArmClass->ItemIndex;
	ed.armClassName = Form1->EditArmClass->Text;
	printLogDebug("SET{ed.armClassId}=" + UnicodeString(ed.armClassId));
	printLogDebug("SET{ed.armClassName}=" + UnicodeString(ed.armClassName));
}
void __fastcall TForm1::EditCategoryChange(TObject *Sender)
{
	ed.categoryId   = Form1->EditCategory->ItemIndex;
	ed.categoryName = Form1->EditCategory->Text;
	printLogDebug("SET{ed.categoryId}=" + UnicodeString(ed.categoryId));
	printLogDebug("SET{ed.categoryName}=" + UnicodeString(ed.categoryName));
}
void __fastcall TForm1::EditResponChange(TObject *Sender)
{
	ed.respon = Form1->EditRespon->Text;
	printLogDebug("SET{ed.respon}=" + UnicodeString(ed.respon));
}
void __fastcall TForm1::EditComentChange(TObject *Sender)
{
	ed.coment = Form1->EditComent->Text;
	printLogDebug("SET{ed.coment}=" + UnicodeString(ed.coment));
}
void __fastcall TForm1::EditDirGrubNameChange(TObject *Sender)
{
	ed.DirGrubName = Form1->EditDirGrubName->Text;
	printLogDebug("SET{ed.DirGrubName}=" + UnicodeString(ed.DirGrubName));
}
//---------------------------------------------------------------------------
/* Чекбоксы в настройках */
void __fastcall TForm1::CheckBoxShowLogClick(TObject *Sender)
{
	cfg.showLog = CheckBoxShowLog->Checked;
	if (cfg.showLog) Form1->Width = 1024*Form1->ScaleFactor;
	else Form1->Width = 421*Form1->ScaleFactor;
}
void __fastcall TForm1::CheckBoxDebugClick(TObject *Sender)
{
	cfg.debug = CheckBoxDebug->Checked;
}
//---------------------------------------------------------------------------

