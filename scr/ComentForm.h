//---------------------------------------------------------------------------

#ifndef ComentFormH
#define ComentFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "MainForm.h"
//---------------------------------------------------------------------------
class TFormComent : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TMemo *EditComent;
	TButton *ButtonCancel;
	TButton *ButtonSave;
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormComent(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormComent *FormComent;
//---------------------------------------------------------------------------
#endif
