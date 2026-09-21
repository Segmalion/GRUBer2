//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <algorithm>

#include "DeviceDetailsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDeviceDetails *FormDeviceDetails;
//---------------------------------------------------------------------------
__fastcall TFormDeviceDetails::TFormDeviceDetails(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
// Наповнює ComboBox_Devices усіма пристроями того ж containerId (або лише самим
// пристроєм, якщо контейнер відсутній/некоректний - ті самі спецзначення, що вже
// перевіряє Button_FilterContainerIDClick у MainDevLister.cpp) і вибирає в ньому
// пристрій, по якому клікнули (initialId).
void __fastcall TFormDeviceDetails::LoadContainer(TFDConnection *conn, const UnicodeString &containerId, int initialId)
{
	bool hasContainer = !containerId.IsEmpty() && containerId != L"No Container" && containerId != L"GUID Error";

	FDQuery_Container->Active = false;
	FDQuery_Container->Connection = conn;
	FDQuery_Container->SQL->Clear();
	if (hasContainer) {
		FDQuery_Container->SQL->Text = L"SELECT * FROM devices WHERE containerId = :cid ORDER BY friendly_name;";
		FDQuery_Container->ParamByName(L"cid")->AsString = containerId;
	} else {
		FDQuery_Container->SQL->Text = L"SELECT * FROM devices WHERE id = :did;";
		FDQuery_Container->ParamByName(L"did")->AsInteger = initialId;
	}
	FDQuery_Container->Open();

	ComboBox_Devices->Items->BeginUpdate();
	ComboBox_Devices->Items->Clear();
	m_deviceIds.clear();
	int selectIndex = 0;
	UnicodeString containerName;
	FDQuery_Container->First();
	while (!FDQuery_Container->Eof) {
		UnicodeString display = BuildDeviceDisplayName(
			FDQuery_Container->FieldByName(L"friendly_name")->AsString,
			FDQuery_Container->FieldByName(L"dev_desc")->AsString);
		if (display.IsEmpty()) display = FDQuery_Container->FieldByName(L"dev_instance_id")->AsString;
		ComboBox_Devices->Items->Add(display);
		int rowId = FDQuery_Container->FieldByName(L"id")->AsInteger;
		if (rowId == initialId) selectIndex = (int)m_deviceIds.size();
		m_deviceIds.push_back(rowId);
		if (containerName.IsEmpty()) containerName = FDQuery_Container->FieldByName(L"containerName")->AsString;
		FDQuery_Container->Next();
	}
	ComboBox_Devices->Items->EndUpdate();

	if (hasContainer) {
		Label_ContainerInfo->Caption = L"Контейнер: " + containerName + L" - " + containerId +
			L" - " + UnicodeString((int)m_deviceIds.size()) + L" пристроїв";
	} else {
		Label_ContainerInfo->Caption = L"Пристрій без контейнера";
	}

	ComboBox_Devices->ItemIndex = selectIndex;
	ComboBox_DevicesChange(nullptr);
}
//---------------------------------------------------------------------------
void __fastcall TFormDeviceDetails::ComboBox_DevicesChange(TObject *Sender)
{
	int idx = ComboBox_Devices->ItemIndex;
	if (idx < 0 || idx >= (int)m_deviceIds.size()) return;
	if (FDQuery_Container->Locate(L"id", m_deviceIds[idx], TLocateOptions())) {
		FillPropertyGrid();
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFormDeviceDetails::IsDataRow(int row)
{
	return row > 0 && row < (int)m_rowIsHeader.size() && !m_rowIsHeader[row];
}
//---------------------------------------------------------------------------
// Пункт ComboBox_Devices: "<Ім'я пристрою> - <Опис>", або лише та частина, що не
// порожня, якщо друга відсутня.
UnicodeString __fastcall TFormDeviceDetails::BuildDeviceDisplayName(const UnicodeString &friendlyName, const UnicodeString &devDesc)
{
	if (!friendlyName.IsEmpty() && !devDesc.IsEmpty()) {
		return friendlyName + L" - " + devDesc;
	}
	if (!friendlyName.IsEmpty()) return friendlyName;
	if (!devDesc.IsEmpty()) return devDesc;
	return L"";
}
//---------------------------------------------------------------------------
// Копіює значення (другу колонку) поточного вибраного рядка в буфер обміну -
// викликається і з пункту контекстного меню, і по Ctrl+C.
void __fastcall TFormDeviceDetails::CopySelectedValue()
{
	int row = Grid_Properties->Row;
	if (!IsDataRow(row)) return;
	Clipboard()->AsText = Grid_Properties->Cells[1][row];
}
//---------------------------------------------------------------------------
void __fastcall TFormDeviceDetails::Grid_PropertiesKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == (WORD)'C' && Shift.Contains(ssCtrl)) {
		CopySelectedValue();
		Key = 0;
	}
}
//---------------------------------------------------------------------------
// Правий клік сам по собі не переносить виділення грида під курсор - робимо це
// вручну, інакше контекстне меню копіювало б значення рядка, вибраного раніше
// лівим кліком, а не того, по якому клікнули правою кнопкою.
void __fastcall TFormDeviceDetails::Grid_PropertiesMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	if (Button != mbRight) return;
	int col, row;
	Grid_Properties->MouseToCell(X, Y, col, row);
	if (row >= 0) {
		Grid_Properties->Row = row;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormDeviceDetails::PopupMenu_GridPopup(TObject *Sender)
{
	MenuItem_CopyValue->Enabled = IsDataRow(Grid_Properties->Row);
}
//---------------------------------------------------------------------------
void __fastcall TFormDeviceDetails::MenuItem_CopyValueClick(TObject *Sender)
{
	CopySelectedValue();
}
//---------------------------------------------------------------------------
// Перемальовує Grid_Properties із поточного (щойно Locate-нутого) рядка
// FDQuery_Container - три розділи (Основне/Ідентифікатори/Дати), підписи полів ті
// самі, що вже вживає optimizeGridColumns() у MainDevLister.cpp, щоб не плодити
// другий переклад тих самих назв.
void __fastcall TFormDeviceDetails::FillPropertyGrid()
{
	struct FieldSpec { UnicodeString label; UnicodeString field; bool isDate; };
	struct Section { UnicodeString title; std::vector<FieldSpec> fields; };

	static const std::vector<Section> sections = {
		{ L"Основне", {
			{ L"Статус", L"status", false },
			{ L"Клас", L"class_name", false },
			{ L"Ім'я пристрою", L"friendly_name", false },
			{ L"Опис", L"dev_desc", false },
			{ L"Категорія", L"regCatName", false },
			{ L"Реєстрація", L"regName", false },
		}},
		{ L"Ідентифікатори", {
			{ L"Instance ID", L"dev_instance_id", false },
			{ L"Серійний номер", L"serial_number", false },
			{ L"Контейнер", L"containerName", false },
			{ L"Container ID", L"containerId", false },
			{ L"Enumerator", L"enumerator_name", false },
		}},
		{ L"Дати", {
			{ L"Перше підключення", L"first_install", true },
			{ L"Останнє встановлення", L"last_install", true },
			{ L"Останнє підключення", L"last_connect", true },
			{ L"Останнє відключення", L"last_disconnect", true },
		}},
	};

	m_rowIsHeader.clear();
	Grid_Properties->RowCount = 1;
	Grid_Properties->Cells[0][0] = L"Властивість";
	Grid_Properties->Cells[1][0] = L"Значення";
	m_rowIsHeader.push_back(false);

	int row = 1;
	for (auto &section : sections) {
		Grid_Properties->RowCount = row + 1;
		Grid_Properties->Cells[0][row] = section.title;
		Grid_Properties->Cells[1][row] = L"";
		m_rowIsHeader.push_back(true);
		row++;

		for (auto &f : section.fields) {
			Grid_Properties->RowCount = row + 1;
			UnicodeString value;
			if (FDQuery_Container->FindField(f.field)) {
				TField *fld = FDQuery_Container->FieldByName(f.field);
				if (f.isDate && !fld->IsNull) {
					value = fld->AsDateTime.FormatString(L"dd.MM.yyyy HH:nn");
				} else {
					value = fld->AsString;
				}
			}
			Grid_Properties->Cells[0][row] = f.label;
			Grid_Properties->Cells[1][row] = value;
			m_rowIsHeader.push_back(false);
			row++;
		}
	}
}
//---------------------------------------------------------------------------
// Grid_Properties малюється вручну (DefaultDrawing = False у .dfm), за зразком
// Grid_UsersDrawCell у src_grub/MainForm.cpp: рядок 0 - заголовок стовпців,
// рядки-роздільники розділів (m_rowIsHeader[ARow]) - виділені кольором і жирним.
void __fastcall TFormDeviceDetails::Grid_PropertiesDrawCell(TObject *Sender, int ACol, int ARow,
	const TRect &Rect, TGridDrawState State)
{
	TStringGrid *grid = (TStringGrid *)Sender;
	bool isSectionHeader = ARow >= 0 && ARow < (int)m_rowIsHeader.size() && m_rowIsHeader[ARow];

	grid->Canvas->Font->Style = TFontStyles();
	if (ARow == 0) {
		grid->Canvas->Brush->Color = clBtnFace;
		grid->Canvas->Font->Color = clWindowText;
		grid->Canvas->Font->Style = TFontStyles() << fsBold;
	} else if (isSectionHeader) {
		grid->Canvas->Brush->Color = (TColor)0x00EDD7C9; // блідо-синій - заголовок розділу
		grid->Canvas->Font->Color = clWindowText;
		grid->Canvas->Font->Style = TFontStyles() << fsBold;
	} else if (State.Contains(gdSelected)) {
		grid->Canvas->Brush->Color = clHighlight;
		grid->Canvas->Font->Color = clHighlightText;
	} else {
		grid->Canvas->Brush->Color = clWindow;
		grid->Canvas->Font->Color = clWindowText;
	}
	grid->Canvas->FillRect(Rect);
	UnicodeString text = grid->Cells[ACol][ARow];
	int textTop = Rect.Top + (Rect.Height() - grid->Canvas->TextHeight(text)) / 2;
	grid->Canvas->TextOut(Rect.Left + 6, textTop, text);
}
//---------------------------------------------------------------------------
