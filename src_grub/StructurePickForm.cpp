//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StructurePickForm.h"
#include "Config.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormStructurePick *FormStructurePick;

extern Config curConfig;
//---------------------------------------------------------------------------
__fastcall TFormStructurePick::TFormStructurePick(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TFormStructurePick::ShowPick(UnicodeString promptText)
{
	LabelPrompt->Caption = promptText;
	std::vector<StructureDef> structs = curConfig.get_structures();
	ComboBoxPick->Items->Clear();
	for (auto &s : structs) ComboBoxPick->Items->Add(s.name);
	// заміна колишньої ButtonCancel - останній пункт списку, індекс якого
	// свідомо виходить за межі structs.size(), тож перевірка нижче вже
	// трактує його як "не переносити дані" без додаткового спецвипадку
	ComboBoxPick->Items->Add("Не переносити дані");
	if (ComboBoxPick->Items->Count > 0) ComboBoxPick->ItemIndex = 0;
	if (ShowModal() == mrOk && ComboBoxPick->ItemIndex >= 0 &&
		ComboBoxPick->ItemIndex < (int)structs.size())
		return structs[ComboBoxPick->ItemIndex].id;
	return "";
}
//---------------------------------------------------------------------------
