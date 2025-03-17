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
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TFormClearTempDir : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_Clean;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TMemo *Memo_LOG;
	void __fastcall Button_CleanClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormClearTempDir(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormClearTempDir *FormClearTempDir;
//---------------------------------------------------------------------------
#endif
