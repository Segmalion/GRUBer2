//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CommentForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormComment *FormComment;
//---------------------------------------------------------------------------
__fastcall TFormComment::TFormComment(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
