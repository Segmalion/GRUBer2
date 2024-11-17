//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PartitionForm.h"
#include "MainForm.h"
#include "Help.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPartition *FormPartition;

extern Config curConfig;
//---------------------------------------------------------------------------
__fastcall TFormPartition::TFormPartition(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPartition::ButtonCancelClick(TObject *Sender)
{
	FormPartition->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormPartition::ButtonSaveClick(TObject *Sender)
{
	std::vector<UnicodeString> vStr;
	for(auto str : FormPartition->EditPartition->Lines) vStr.push_back(str);
	curConfig.setPartition(vStr);
	Form1->EditPartition->Items = FormPartition->EditPartition->Lines;
	FormPartition->Close();
}
//---------------------------------------------------------------------------
