//---------------------------------------------------------------------------
#ifndef DeviceDetailsFormH
#define DeviceDetailsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Clipbrd.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.ExprFuncs.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <vector>
//---------------------------------------------------------------------------
class TFormDeviceDetails : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel_Main;
	TLabel *Label_ContainerInfo;
	TComboBox *ComboBox_Devices;
	TStringGrid *Grid_Properties;
	TPanel *Panel_Buttons;
	TButton *Button_Close;
	TFDQuery *FDQuery_Container;
	TPopupMenu *PopupMenu_Grid;
	TMenuItem *MenuItem_CopyValue;
	void __fastcall ComboBox_DevicesChange(TObject *Sender);
	void __fastcall Grid_PropertiesDrawCell(TObject *Sender, int ACol, int ARow,
		const TRect &Rect, TGridDrawState State);
	void __fastcall Grid_PropertiesKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Grid_PropertiesMouseDown(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall PopupMenu_GridPopup(TObject *Sender);
	void __fastcall MenuItem_CopyValueClick(TObject *Sender);
private:	// User declarations
	std::vector<int> m_deviceIds;      // паралельно ComboBox_Devices->Items: id рядка БД на кожен пункт
	std::vector<bool> m_rowIsHeader;   // паралельно рядкам Grid_Properties: чи є рядок заголовком розділу
	void __fastcall FillPropertyGrid();
	bool __fastcall IsDataRow(int row);
	void __fastcall CopySelectedValue();
	UnicodeString __fastcall BuildDeviceDisplayName(const UnicodeString &friendlyName, const UnicodeString &devDesc);
public:		// User declarations
	__fastcall TFormDeviceDetails(TComponent* Owner);
	void __fastcall LoadContainer(TFDConnection *conn, const UnicodeString &containerId, int initialId);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDeviceDetails *FormDeviceDetails;
//---------------------------------------------------------------------------
#endif
