//---------------------------------------------------------------------------

#ifndef ClearTempH
#define ClearTempH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.FileCtrl.hpp>
//---------------------------------------------------------------------------
class TFormClearTempDir : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
private:	// User declarations
public:		// User declarations
	__fastcall TFormClearTempDir(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormClearTempDir *FormClearTempDir;
//---------------------------------------------------------------------------
#endif
