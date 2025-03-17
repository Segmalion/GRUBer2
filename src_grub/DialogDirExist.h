//---------------------------------------------------------------------------

#ifndef DialogDirExistH
#define DialogDirExistH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormDirExist : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TLabel *Label1;
	TEdit *ShowDir;
	TGridPanel *GridPanel2;
	TButton *ButtonCancel;
	TButton *ButtonOpen;
	TButton *ButtonOK;
	void __fastcall ButtonOKClick(TObject *Sender);
	void __fastcall ButtonCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormDirExist(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDirExist *FormDirExist;
//---------------------------------------------------------------------------
#endif
