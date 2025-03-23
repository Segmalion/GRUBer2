//---------------------------------------------------------------------------

#ifndef FormSerialH
#define FormSerialH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_Serial : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel_Serial;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
private:	// User declarations
public:		// User declarations
	__fastcall TForm_Serial(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Serial *Form_Serial;
//---------------------------------------------------------------------------
#endif
