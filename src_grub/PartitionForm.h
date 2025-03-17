//---------------------------------------------------------------------------

#ifndef PartitionFormH
#define PartitionFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormPartition : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TMemo *EditPartition;
	TButton *ButtonCancel;
	TButton *ButtonSave;
	void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormPartition(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPartition *FormPartition;
//---------------------------------------------------------------------------
#endif
