//---------------------------------------------------------------------------

#ifndef StructuresFormH
#define StructuresFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include <vector>

#include "Structures.h"
//---------------------------------------------------------------------------
class TFormStructures : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanelMain;
	TGridPanel *GridPanelContent;
	TListBox *ListBoxStructures;
	TGridPanel *GridPanelDetail;
	TLabeledEdit *EditStructName;
	TLabel *LabelStructPartition;
	TMemo *MemoStructPartition;
	TLabeledEdit *LabEdit_StructNumber;
	TGridPanel *GridPanelButtons;
	TButton *ButtonAddStruct;
	TButton *ButtonDeleteStruct;
	TButton *ButtonSaveStructures;
	TButton *ButtonCloseStructures;
	void __fastcall ListBoxStructuresClick(TObject *Sender);
	void __fastcall EditStructNameChange(TObject *Sender);
	void __fastcall MemoStructPartitionChange(TObject *Sender);
	void __fastcall ButtonAddStructClick(TObject *Sender);
	void __fastcall ButtonDeleteStructClick(TObject *Sender);
	void __fastcall ButtonSaveStructuresClick(TObject *Sender);
	void __fastcall ButtonCloseStructuresClick(TObject *Sender);
private:	// User declarations
	std::vector<StructureDef> workingStructures;
	bool populating = false; // true під час програмного заповнення полів у showSelected() -
	                          // OnChange-обробники ігнорують зміни, поки він true, інакше
	                          // MemoStructPartitionChange встигає перезаписати
	                          // workingStructures[i].partition просто в процесі
	                          // покрокового Lines->Add(), інвалідуючи ітератор, яким
	                          // showSelected() ще й досі перебирає той самий вектор
	void refreshList(int selectIndex);
	void showSelected();
	bool isFixedId(UnicodeString id);
public:		// User declarations
	__fastcall TFormStructures(TComponent* Owner);
	void loadStructures();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormStructures *FormStructures;
//---------------------------------------------------------------------------
#endif
