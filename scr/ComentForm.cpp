//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ComentForm.h"
#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormComent *FormComent;
//---------------------------------------------------------------------------
__fastcall TFormComent::TFormComent(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormComent::ButtonSaveClick(TObject *Sender)
{
	Form1->EditComent->Lines = FormComent->EditComent->Lines;
	FormComent->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormComent::ButtonCancelClick(TObject *Sender)
{
   FormComent->Close();
}
//---------------------------------------------------------------------------
