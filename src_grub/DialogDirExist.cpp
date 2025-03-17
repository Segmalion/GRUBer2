//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DialogDirExist.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDirExist *FormDirExist;

extern bool dirGrubRewrite;
//---------------------------------------------------------------------------
__fastcall TFormDirExist::TFormDirExist(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDirExist::ButtonOKClick(TObject *Sender)
{
	dirGrubRewrite = true;
	FormDirExist->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormDirExist::ButtonCancelClick(TObject *Sender)
{
	dirGrubRewrite = false;
   FormDirExist->Close();
}
//---------------------------------------------------------------------------
