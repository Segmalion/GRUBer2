//---------------------------------------------------------------------------

#ifndef MainDevListerH
#define MainDevListerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.SQLite.hpp>
#include <FireDAC.Phys.SQLiteDef.hpp>
#include <FireDAC.Phys.SQLiteWrapper.Stat.hpp>
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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>

// --- ДОБАВЬТЕ ЭТИ СТРОКИ СЮДА ---
#include <map>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
// ---------------------------------

#include <cfgmgr32.h> // Добавляем заголовок для CM_Get_DevNode_Status
//---------------------------------------------------------------------------
namespace fs = std::filesystem;
struct deviceInfo {
	UnicodeString friendlyName;
	UnicodeString className;
	UnicodeString devDesc;
	UnicodeString enumeratorName;
	UnicodeString devInstanceID;
	UnicodeString serialNumber;
	UnicodeString status;
	UnicodeString containerId;
    UnicodeString containerName;
	UnicodeString regName;
	UnicodeString regCatName;
	short regCatNumber = 0;
	bool serialKnow = false;
	bool serialErr  = false;
	TDateTime firstInstallDate;  // <-- ДОБАВИЛИ: Первая установка устройства
	TDateTime installDate;       // <-- ДОБАВИЛИ: Последняя установка/обновление
	TDateTime lastConnect;
	TDateTime lastDisconnect;
};
struct registeredUsb {
	UnicodeString name;
	UnicodeString catName;
	short catNumber = 0;
	UnicodeString serial;
};
struct indefPCtype {
	String desktopName, sn_Main, sn_UUID, sn_serialMrb, sn_CPUID, sn_hash;
	short catPC;
};

extern std::map<UnicodeString, short> m_catNumber;
extern std::vector<UnicodeString> v_allertName;
extern indefPCtype indefPC;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_DeviceUpdateCurPC;
	TGridPanel *GridPanel_Main;
	TFDConnection *FDConnection1;
	TFDQuery *FDQuery1;
	TFDPhysSQLiteDriverLink *FDPhysSQLiteDriverLink1;
	TDBGrid *DBGrid1;
	TDataSource *DataSource1;
	TListBox *ListBox_Filter;
	TGridPanel *GridPanel_Filter;
	TLabel *Label1;
	TGridPanel *GridPanel_FilterButton;
	TButton *Button_FilterContainerID;
	TGroupBox *GroupBox_FilterCheckBox;
	TGridPanel *GridPanel_FilterCheckBox;
	TCheckBox *CheckBox_FilterMotherboard;
	TCheckBox *CheckBox_WIP2;
	TCheckBox *CheckBox_WIP3;
	TCheckBox *CheckBox_WIP4;
	TCheckBox *CheckBox_AutoUpdateDev;
	TTrackBar *TrackBar_CountErrSerial;
	TGridPanel *GridPanel_Else;
	TGroupBox *GroupBox_CountErrSerial;
	TMemo *Memo_LOG;
	TStatusBar *StatusBar1;
	TGroupBox *GroupBox_CategPC;
	TComboBox *ComboBox_CategPC;
	TTimer *Timer1;
	TGridPanel *GridPanel_RunButton;
	TButton *Button_DelDevice;
	TButton *Button_ShowUnknowUSB;
	TButton *Button_ShowAllert;
	TButton *Button_ShowUSB;
	TButton *Button_SaveToJSON;
	TOpenDialog *OpenDialog_FromJSON;
	TSaveDialog *SaveDialog_ToJSON;
	TButton *Button_LoadFromJSON;
	void __fastcall Button_DeviceUpdateCurPCClick(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
	void __fastcall ListBox_FilterClick(TObject *Sender);
	void __fastcall Button_FilterContainerIDClick(TObject *Sender);
	void __fastcall CheckBox_FilterMotherboardClick(TObject *Sender);
	void __fastcall TrackBar_CountErrSerialChange(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall ComboBox_CategPCChange(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button_DelDeviceClick(TObject *Sender);
	void __fastcall Button_ShowUSBClick(TObject *Sender);
	void __fastcall Button_ShowUnknowUSBClick(TObject *Sender);
	void __fastcall Button_ShowAllertClick(TObject *Sender);
	void __fastcall Button_SaveToJSONClick(TObject *Sender);
	void __fastcall Button_LoadFromJSONClick(TObject *Sender);
	void __fastcall FDQuery1AfterOpen(TDataSet *DataSet);
private:	// User declarations
	void __fastcall WndProc(Winapi::Messages::TMessage &Message) override;
	bool __fastcall RemoveDeviceFromWindows(UnicodeString instanceId);
	bool __fastcall RemoveContainerDevicesFromWindows(UnicodeString targetContainerId);
	void __fastcall DelDevice();
	void __fastcall DelContainerDevice();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    void __fastcall createDB(); //подключение к БД
	void __fastcall vectorToBD(std::vector<deviceInfo> &devicesList);
    void __fastcall refrechDBGrid();
	void __fastcall UpdateClassFilterList();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

TDateTime fileTimeToDateTime (const FILETIME &ft);
void printLog(UnicodeString str);
std::vector<deviceInfo> scanDevices();
void checkRegDevice(std::vector<deviceInfo> &devList);
void optimizeGridColumns(TDBGrid* grid);
std::vector<registeredUsb> readRegUsbFile(fs::path &p_file);
short categoryStrToNum (UnicodeString catStr);
bool CompareStr_DamerayLevenshtaine(const UnicodeString &m, const UnicodeString &n, short a=0);
bool compareStrInSring(UnicodeString &strFull, UnicodeString &strSearch);
bool compareStrInVector (UnicodeString &strFull, std::vector<UnicodeString> &v_str);

String getFastHash_CRC32(const String& Input);
void getInfoPC();

bool SaveDataToJSON(const String& FilePath, const indefPCtype& indefPC, const std::vector<deviceInfo>& DataVector);
bool LoadDataFromJSON(const UnicodeString& filePath);
//---------------------------------------------------------------------------
#endif
