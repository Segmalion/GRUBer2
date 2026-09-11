//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <map>
#include <System.DateUtils.hpp>

#include "FormQuarantine.h"
#include "MainForm.h"
#include "Fille.h"
#include "Text.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormQuarantine *FormQuarantine;
//---------------------------------------------------------------------------
__fastcall TFormQuarantine::TFormQuarantine(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFormQuarantine::loadDirs(const std::vector<UnicodeString> &quarantineDirs)
{
	dirs = quarantineDirs;
	refreshList();
	// підганяємо ширину лише один раз при відкритті - інакше після видалення
	// чи оновлення (коли рядків стає менше) таблиця стискалась би щоразу
	autoFitColumns();
}
//---------------------------------------------------------------------------
// теку карантину GRUBer читає напряму через FindFirstFile (scanDirToFille) -
// той самий спосіб, яким computeEsetDefection() і так вже читає ці теки для
// підрахунку файлів, тому жодних проблем з доступом тут не виникає.
void TFormQuarantine::refreshList()
{
	groups.clear();
	int totalFiles = 0;
	for (auto &dirRaw : dirs) {
		UnicodeString dir = stripTrailingSlash(dirRaw);
		// друге ім'я теки для стовпця "Тека": системний карантин або ім'я юзера
		UnicodeString label = dir;
		int usersPos = dir.Pos("\\Users\\");
		if (dir.Pos("systemprofile") > 0) {
			label = L"Системний (SYSTEM)";
		} else if (usersPos > 0) {
			UnicodeString rest = dir.SubString(usersPos + 7, dir.Length());
			int slashPos = rest.Pos("\\");
			label = slashPos > 0 ? rest.SubString(1, slashPos - 1) : rest;
		}
		patchList files = scanDirToFille(dir);
		// ESET зберігає кілька файлів (сам об'єкт + метадані на кшталт
		// INFO.NQI) з однаковим базовим ім'ям, але різними розширеннями -
		// групуємо їх у межах теки, щоб видаляти одним об'єктом
		std::map<UnicodeString, size_t> indexByBase;
		for (auto &f : files.list) {
			if (f.dir) continue;
			totalFiles++;
			UnicodeString name = f.str;
			int slashPos = name.LastDelimiter("\\");
			if (slashPos > 0) name = name.SubString(slashPos + 1, name.Length());
			UnicodeString base = name;
			int dotPos = name.LastDelimiter(".");
			if (dotPos > 1) base = name.SubString(1, dotPos - 1);
			auto it = indexByBase.find(base);
			size_t idx;
			if (it == indexByBase.end()) {
				QuarantineGroup g;
				g.label = label;
				g.baseName = base;
				g.date = f.date;
				idx = groups.size();
				groups.push_back(g);
				indexByBase[base] = idx;
			} else idx = it->second;
			groups[idx].size += f.size;
			groups[idx].files.push_back(f.str);
		}
	}
	ListViewQuarantine->Items->BeginUpdate();
	ListViewQuarantine->Items->Clear();
	for (auto &g : groups) {
		TListItem *item = ListViewQuarantine->Items->Add();
		item->Caption = g.label;
		item->SubItems->Add(g.baseName);
		item->SubItems->Add(g.date.FormatString("dd.MM.yyyy HH:mm"));
		item->SubItems->Add(UnicodeString((int)g.files.size()) + L" файл(ів), " +
			UnicodeString((int)((g.size + 1023) / 1024)) + L" КБ");
	}
	ListViewQuarantine->Items->EndUpdate();
	LabelInfo->Caption = L"Знайдено об'єктів: " + UnicodeString((int)groups.size()) +
		L" (файлів: " + UnicodeString(totalFiles) + ")";
}
//---------------------------------------------------------------------------
// підганяє ширину стовпців під найдовший текст (заголовок або вміст), і
// ширину самого вікна - під сумарну ширину таблиці
void TFormQuarantine::autoFitColumns()
{
	TCanvas *canvas = ListViewQuarantine->Canvas;
	int colCount = ListViewQuarantine->Columns->Count;
	std::vector<int> widths(colCount, 0);
	const int padding = 40; // запас під чекбокс/поля стовпця
	for (int c = 0; c < colCount; c++)
		widths[c] = canvas->TextWidth(ListViewQuarantine->Columns->Items[c]->Caption) + padding;
	for (int i = 0; i < ListViewQuarantine->Items->Count; i++) {
		TListItem *item = ListViewQuarantine->Items->Item[i];
		int w0 = canvas->TextWidth(item->Caption) + padding;
		if (w0 > widths[0]) widths[0] = w0;
		for (int c = 1; c < colCount; c++) {
			if (c - 1 >= item->SubItems->Count) continue;
			int w = canvas->TextWidth(item->SubItems->Strings[c - 1]) + padding;
			if (w > widths[c]) widths[c] = w;
		}
	}
	int total = 0;
	for (int c = 0; c < colCount; c++) {
		ListViewQuarantine->Columns->Items[c]->Width = widths[c];
		total += widths[c];
	}
	// ширина вікна - під таблицю, але не менше за потрібне для ряду кнопок
	int desired = total + 60;
	if (desired < 950) desired = 950;
	ClientWidth = desired;
}
//---------------------------------------------------------------------------
void __fastcall TFormQuarantine::ButtonRefreshClick(TObject *Sender)
{
	refreshList();
}
//---------------------------------------------------------------------------
// TListItem в цій VCL не має власного Color - фон рядка міняємо через
// OnCustomDrawItem (Sender->Canvas->Brush->Color перед стандартним малюванням)
void __fastcall TFormQuarantine::ListViewQuarantineCustomDrawItem(
	TCustomListView *Sender, TListItem *Item, TCustomDrawState State, bool &DefaultDraw)
{
	if (Item->Index >= 0 && Item->Index < (int)groups.size() &&
		System::Dateutils::DaysBetween(Now(), groups[Item->Index].date) > 90) {
		Sender->Canvas->Brush->Color = (TColor)0x00EAFFEA; // старше 90 днів - блідо-зелений
	}
	DefaultDraw = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormQuarantine::ButtonSelectAllClick(TObject *Sender)
{
	for (int i = 0; i < ListViewQuarantine->Items->Count; i++)
		ListViewQuarantine->Items->Item[i]->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormQuarantine::ButtonDeleteClick(TObject *Sender)
{
	std::vector<int> checkedIdx;
	int totalFiles = 0;
	for (int i = 0; i < ListViewQuarantine->Items->Count; i++)
		if (ListViewQuarantine->Items->Item[i]->Checked) {
			checkedIdx.push_back(i);
			totalFiles += (int)groups[i].files.size();
		}
	if (checkedIdx.empty()) return;
	UnicodeString text = L"Видалити " + UnicodeString((int)checkedIdx.size()) +
		L" позначених об'єктів карантину (" + UnicodeString(totalFiles) + L" файл(ів))?"
		L"\nЦю дію не можна скасувати.";
	UnicodeString caption = L"Підтвердження видалення";
	if (Application->MessageBox(text.c_str(), caption.c_str(), MB_YESNO) != IDYES) return;
	for (int idx : checkedIdx) {
		for (auto &path : groups[idx].files) {
			FileSetAttr(path, 0);
			DeleteFile(path);
		}
	}
	refreshList();
}
//---------------------------------------------------------------------------
void __fastcall TFormQuarantine::ButtonCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
