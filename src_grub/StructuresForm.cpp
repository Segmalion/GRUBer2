//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StructuresForm.h"
#include "Arm.h"
#include "Config.h"
#include "Text.h"
#include "Help.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormStructures *FormStructures;

extern Config curConfig;
extern Arm curPC;
//---------------------------------------------------------------------------
__fastcall TFormStructures::TFormStructures(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool TFormStructures::isFixedId(UnicodeString id)
{
	return id == STRUCT_ID_UVS || id == STRUCT_ID_UVS_LOGIST ||
	       id == STRUCT_ID_OK  || id == STRUCT_ID_OK_LOGIST;
}
//---------------------------------------------------------------------------
void TFormStructures::refreshList(int selectIndex)
{
	ListBoxStructures->Items->Clear();
	for (auto &s : workingStructures) ListBoxStructures->Items->Add(s.name);
	if (selectIndex < 0) selectIndex = 0;
	if (selectIndex >= ListBoxStructures->Items->Count) selectIndex = ListBoxStructures->Items->Count - 1;
	if (ListBoxStructures->Items->Count > 0) {
		ListBoxStructures->ItemIndex = selectIndex;
		showSelected();
	}
}
//---------------------------------------------------------------------------
void TFormStructures::showSelected()
{
	int i = ListBoxStructures->ItemIndex;
	if (i < 0 || i >= (int)workingStructures.size()) return;
	// копія, не референс - Lines->Add() нижче синхронно фірить OnChange, який
	// перезаписує workingStructures[i].partition; ітерування по референсу на
	// той самий вектор, що переписується під час ітерації, - undefined behavior
	StructureDef s = workingStructures[i];
	populating = true;
	EditStructName->Text = s.name;
	MemoStructPartition->Lines->Clear();
	for (auto &p : s.partition) MemoStructPartition->Lines->Add(p);
	LabEdit_StructNumber->Text = UnicodeString(curPC.getStructure(s.id).number);
	populating = false;
	ButtonDeleteStruct->Enabled = !isFixedId(s.id);
}
//---------------------------------------------------------------------------
void TFormStructures::loadStructures()
{
	workingStructures = curConfig.get_structures();
	refreshList(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormStructures::ListBoxStructuresClick(TObject *Sender)
{
	showSelected();
}
//---------------------------------------------------------------------------
void __fastcall TFormStructures::EditStructNameChange(TObject *Sender)
{
	if (populating) return;
	int i = ListBoxStructures->ItemIndex;
	if (i < 0 || i >= (int)workingStructures.size()) return;
	workingStructures[i].name = EditStructName->Text;
	ListBoxStructures->Items->Strings[i] = EditStructName->Text;
}
//---------------------------------------------------------------------------
void __fastcall TFormStructures::MemoStructPartitionChange(TObject *Sender)
{
	if (populating) return;
	int i = ListBoxStructures->ItemIndex;
	if (i < 0 || i >= (int)workingStructures.size()) return;
	std::vector<UnicodeString> vStr;
	for (auto line : MemoStructPartition->Lines) vStr.push_back(line);
	workingStructures[i].partition = vStr;
}
//---------------------------------------------------------------------------
void __fastcall TFormStructures::ButtonAddStructClick(TObject *Sender)
{
	StructureDef s;
	s.id = generateStructureId();
	s.name = L"Нова структура";
	workingStructures.push_back(s);
	refreshList((int)workingStructures.size() - 1);
	EditStructName->SetFocus();
	EditStructName->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TFormStructures::ButtonDeleteStructClick(TObject *Sender)
{
	int i = ListBoxStructures->ItemIndex;
	if (i < 0 || i >= (int)workingStructures.size()) return;
	if (isFixedId(workingStructures[i].id)) {
		Application->MessageBox(
			L"Цю структуру неможливо видалити - вона є стандартною.",
			L"Неможливо видалити", MB_OK);
		return;
	}
	UnicodeString text = L"Видалити структуру \"" + workingStructures[i].name + L"\"?";
	if (Application->MessageBox(text.c_str(), L"Підтвердження", MB_YESNO) != IDYES) return;
	workingStructures.erase(workingStructures.begin() + i);
	refreshList(i);
}
//---------------------------------------------------------------------------
void __fastcall TFormStructures::ButtonSaveStructuresClick(TObject *Sender)
{
	curConfig.set_structures(workingStructures);
	curConfig.saveFileIni();
	populateStructureCombos(curConfig);
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormStructures::ButtonCloseStructuresClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
