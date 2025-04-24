//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	TListItem *ListIt;

	ListIt = ListView1->Items->Add();
	ListIt->Caption = "Tom";
	ListIt->SubItems->Add("10");
    ListIt->SubItems->Add("Pidor");
}
//---------------------------------------------------------------------------
