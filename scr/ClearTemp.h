//---------------------------------------------------------------------------

#ifndef ClearTempH
#define ClearTempH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.CheckLst.hpp>
//---------------------------------------------------------------------------
class TFormClearTempDir : public TForm
{
__published:	// IDE-managed Components
	TCheckListBox *CheckListBox1;
	TLabel *Label1;
	TButton *Button1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
private:	// User declarations
public:		// User declarations
	__fastcall TFormClearTempDir(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormClearTempDir *FormClearTempDir;
//---------------------------------------------------------------------------
#endif
