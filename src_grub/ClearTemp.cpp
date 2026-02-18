//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ClearTemp.h"
#include "Fille.h"
#include "Th_ClearFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormClearTempDir *FormClearTempDir;
//---------------------------------------------------------------------------
patchList fullList, tempList, recycleList;
bool newOpenFormClean;
extern bool th_ClearFile_run;
//---------------------------------------------------------------------------
__fastcall TFormClearTempDir::TFormClearTempDir(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFormClearTempDir::Button_CleanClick(TObject *Sender)
{
	if (th_ClearFile_run == false) {
		newOpenFormClean = false;
		Th_ClearFile *Thr = new Th_ClearFile(true);
		Thr->Resume();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormClearTempDir::FormShow(TObject *Sender)
{
	if (th_ClearFile_run == false) {
		newOpenFormClean = true;
		Th_ClearFile *Thr = new Th_ClearFile(true);
		Thr->Resume();
	}
}
//---------------------------------------------------------------------------

