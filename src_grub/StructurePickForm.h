//---------------------------------------------------------------------------

#ifndef StructurePickFormH
#define StructurePickFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormStructurePick : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TLabel *LabelPrompt;
	TComboBox *ComboBoxPick;
	TButton *ButtonOK;
	TButton *ButtonCancel;
private:	// User declarations
public:		// User declarations
	__fastcall TFormStructurePick(TComponent* Owner);
	UnicodeString __fastcall ShowPick(UnicodeString promptText);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormStructurePick *FormStructurePick;
//---------------------------------------------------------------------------
#endif
