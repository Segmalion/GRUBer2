//---------------------------------------------------------------------------

#ifndef ComentFormH
#define ComentFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormComent : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TMemo *EditComent;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TFormComent(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormComent *FormComent;
//---------------------------------------------------------------------------
#endif
