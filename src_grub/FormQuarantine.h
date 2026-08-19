//---------------------------------------------------------------------------
#ifndef FormQuarantineH
#define FormQuarantineH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <vector>
//---------------------------------------------------------------------------
class TFormQuarantine : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TListView *ListViewQuarantine;
	TGridPanel *GridPanel2;
	TLabel *LabelInfo;
	TButton *ButtonDelete;
	TButton *ButtonRefresh;
	TButton *ButtonClose;
	TButton *ButtonSelectAll;
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall ButtonRefreshClick(TObject *Sender);
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall ButtonSelectAllClick(TObject *Sender);
private:	// User declarations
	// ESET зберігає ~3 супутні файли на один об'єкт карантину (з різними
	// розширеннями, спільним базовим ім'ям) - видаляти їх окремо не має сенсу,
	// тому групуємо по базовому імені файлу (без розширення) в межах теки.
	struct QuarantineGroup {
		UnicodeString label;               // тека (для стовпця "Тека")
		UnicodeString baseName;            // ім'я файлу без розширення
		TDateTime date;
		long long size = 0;                // сумарний розмір усіх файлів групи
		std::vector<UnicodeString> files;  // усі супутні файли (вкл. INFO.NQI) - видаляються разом
	};
	std::vector<UnicodeString> dirs;       // теки карантину для сканування
	std::vector<QuarantineGroup> groups;   // індекс = індекс рядка ListView
	void refreshList();
	void autoFitColumns();
public:		// User declarations
	__fastcall TFormQuarantine(TComponent* Owner);
	void loadDirs(const std::vector<UnicodeString> &quarantineDirs);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormQuarantine *FormQuarantine;
//---------------------------------------------------------------------------
#endif
