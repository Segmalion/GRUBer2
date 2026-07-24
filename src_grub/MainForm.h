//---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.NumberBox.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ButtonGroup.hpp>
#include <Vcl.Menus.hpp>
#include <System.Win.TaskbarCore.hpp>
#include <Vcl.Taskbar.hpp>
#include <Vcl.CheckLst.hpp>

#include <vector>
#include <set>
//---------------------------------------------------------------------------

#include "Global.h"

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel_forPage;
	TProgressBar *ProgressBar_Grub;
	TStatusBar *StatusBar1;
	TPageControl *PageControl_SetInfo;
	TTabSheet *TabGRUBer;
	TGridPanel *GridPanelMain;
	TButton *BtnGruberDirOpen;
	TButton *BtnDevListerOpen;
	TEdit *EditDirGrubName;
	TButton *BtnGruberRun;
	TButton *BtnGruberStop;
	TButton *BtnEsetUpdate;
	TGridPanel *GridPanel_EditInfo;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label_ResponNow;
	TEdit *EditRespon;
	TComboBox *EditPartition;
	TComboBox *EditCategory;
	TLabel *Label7;
	TComboBox *EditArmClass;
	TButton *BtnKiberConsolOpen;
	TEdit *ShowSerial;
	TButton *BtnInfo;
	TEdit *ShowName;
	TButton *BtnLicense;
	TCheckBox *CheckBoxDebug;
	TLabel *Label9;
	TComboBox *EditLicWin;
	TMemo *EditComent;
	TLabeledEdit *EditGrubUser;
	TGridPanel *GridPanel_Settings;
	TGroupBox *GroupBox_SetingsGRUB;
	TCheckBox *CheckBoxAudit;
	TCheckBox *CheckBoxEsetLog;
	TButton *BtnSaveSetteings;
	TCheckBox *CheckBoxOldGrub;
	TCheckBox *CheckBoxNewGrub;
	TCheckBox *CheckBoxLicense;
	TButton *BtnEditPartition;
	TGroupBox *GroupBox_SetingsESET;
	TLabeledEdit *EditEsetMirrorDir;
	TButton *BtnEditEsetMirrorDir;
	TCheckBox *CheckBoxEsetAutoUpdate;
	TFileOpenDialog *DirOpenEsetMirror;
	TGridPanel *GridPanel_Soft;
	TGroupBox *GroupBox_AppInfo;
	TGridPanel *GridPanel9;
	TButton *BtnApp_HWiNFO;
	TButton *BtnApp_procexp;
	TButton *BtnApp_CPUZ;
	TButton *BtnApp_autoruns;
	TButton *BtnApp_GPUZ;
	TButton *BtnApp_tcpview;
	TGroupBox *GroupBox_AppFille;
	TGridPanel *GridPanel10;
	TButton *BtnApp_Total;
	TButton *BtnApp_Everything;
	TGroupBox *GroupBox_AppUSB;
	TCheckBox *CheckBox_ShowEsetUpdate;
	TCheckBox *CheckBox_RunAs;
	TTaskbar *Taskbar1;
	TPopupMenu *PopupMenu_StopGrub;
	TMenuItem *Рass;
	TPopupMenu *PopupMenu_mailGrubFile;
	TMenuItem *ComentTxt;
	TMenuItem *InfoTxt;
	TMenuItem *NetTxt;
	TMenuItem *UsbTxt;
	TEdit *EditPrefixPartition;
	TCheckBox *CheckBoxPrefixPartition;
	TButton *BtnAboutGruber;
	TButton *BtnClearPC;
	TTabSheet *TabGRUBerP;
	TGridPanel *GridPanel_EditInfoDoc;
	TLabel *Label11;
	TEdit *Edit_InNumberARM;
	TLabel *Label13;
	TEdit *Edit_InNumberHDD;
	TLabel *Label14;
	TEdit *Edit_InNumberDeclr;
	TLabel *Label15;
	TEdit *Edit_InNumberFormulyar;
	TLabel *Label16;
	TEdit *Edit_InNumberWork;
	TLabel *Label17;
	TEdit *Edit_InNumberPerson;
	TGroupBox *GroupBox6;
	TGroupBox *GroupBox7;
	TGridPanel *GridPanel_EditInfoBezp;
	TGridPanel *GridPanel_EditInfoLic;
	TLabel *Label10;
	TComboBox *EditLicOffice;
	TLabel *Label_Purpose;
	TEdit *EditPurpose;
	TGridPanel *GridPanel14;
	TButton *BtnApp_UscDevU;
	TButton *BtnApp_DeviceCleanup;
	TButton *BtnApp_UsbTreeView;
	TButton *Button4;
	TPopupMenu *PopupMenu_GrubButton;
	TMenuItem *Gruber_Mini;
	TGridPanel *GridPanel15;
	TButton *Button_RestartAssAdmin;
	TPageControl *PageControl_InfoTabs;
	TTabSheet *TabSheet_Info;
	TTabSheet *TabSheet_Log;
	TTabSheet *TabSheet_Settings;
	TTabSheet *TabSheet_Soft;
	TGridPanel *GridPanel_forButGrub;
	TTabSheet *TabSheet1;
	TGridPanel *GridPanel1;
	TRichEdit *RichEdit_LOG;
	TLabel *Label_Respon;
	TEdit *Edit_InRespon;
	TEdit *Edit_InAdminBP;
	TLabel *Label_AdminBP;
	TLabel *Label_Place;
	TLabel *Label_Phone;
	TEdit *Edit_Place;
	TEdit *Edit_Phone;
	TLabel *Label_NumberARM;
	TNumberBox *Edit_NumberARM;
	TGroupBox *GroupBox_SettingsPC;
	TGridPanel *GridPanel_SettingsPC;
	TButton *Button_ControlPanel;
	TButton *Button_setingsPC;
	TButton *Button_msconfig;
	TButton *Button_CrashMonitor;
	TButton *Button_ResMon;
	TComboBox *ComboBox_forNumberARM;
	TLabel *Label_ForNumberARM;
	TGridPanel *GridPanel2;
	TLabel *Label_infoForNumberARM;
	TCheckBox *CheckBox_TempDir;
	TMemo *Memo1;
	TMemo *Memo2;
	TGridPanel *GridPanel_Info;
	TGridPanel *GridPanel3;
	TGroupBox *GroupBox_Number;
	TLabeledEdit *LabEdit_NumUVs;
	TLabeledEdit *LabEdit_NumUVsO;
	TLabeledEdit *LabEdit_NumOK;
	TLabeledEdit *LabEdit_NumOKO;
	TGroupBox *GroupBox_InfoARM;
	TGridPanel *GridPanel_InfoArm;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label8;
	TEdit *ShowSerialGenarate;
	TGridPanel *GridPanel_CheckInfo;
	TGridPanel *GridPanel_ESETQuarantine;
	TLabel *Label_checkQuarantineEset_1;
	TLabel *Label_DefectionUser;
	TLabel *Label_DefectionSoft;
	TEdit *Show_ESETQuarantine;
	TGroupBox *GroupBox_ConsoleUtil;
	TGridPanel *GridPanel_ConsoleUtil;
	TTabSheet *TabSheet_CheckList;
	TLabel *Label1;
	TEdit *ShowManufacturer;
	TLabel *Label4;
	TEdit *ShowProductName;
	TButton *Button_CheckDefection;
	TMenuItem *Gruber_USB;
	TGroupBox *GroupBox1;
	TGridPanel *GridPanel4;
	TLabel *Label12;
	TComboBox *ComboBox_ThemeChange;
	TGroupBox *GroupBox_SPZ;
	TCheckListBox *CheckListBox_SPZ;
	TComboBox *ComboBox_PoliticInstall;
	TComboBox *ComboBox_ContrUSB;
	TComboBox *ComboBox_MultiUSERS;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	void __fastcall CheckBoxDebugClick(TObject *Sender);
	void __fastcall BtnGruberRunClick(TObject *Sender);
	void __fastcall EditPartitionChange(TObject *Sender);
	void __fastcall EditArmClassChange(TObject *Sender);
	void __fastcall EditCategoryChange(TObject *Sender);
	void __fastcall EditResponChange(TObject *Sender);
	void __fastcall EditComentChange(TObject *Sender);
	void __fastcall EditDirGrubNameChange(TObject *Sender);
	void __fastcall EditLicWinChange(TObject *Sender);
	void __fastcall EditLicOfficeChange(TObject *Sender);
	void __fastcall EditGrubUserChange(TObject *Sender);
	void __fastcall BtnGruberDirOpenClick(TObject *Sender);
	void __fastcall BtnGruberStopClick(TObject *Sender);
	void __fastcall CheckBoxAuditClick(TObject *Sender);
	void __fastcall CheckBoxEsetLogClick(TObject *Sender);
	void __fastcall BtnEditPartitionClick(TObject *Sender);
	void __fastcall BtnSaveSetteingsClick(TObject *Sender);
	void __fastcall CheckBoxOldGrubClick(TObject *Sender);
	void __fastcall CheckBoxNewGrubClick(TObject *Sender);
	void __fastcall CheckBoxLicenseClick(TObject *Sender);
	void __fastcall CheckBoxEsetAutoUpdateClick(TObject *Sender);
	void __fastcall EditEsetMirrorDirChange(TObject *Sender);
	void __fastcall BtnEsetUpdateClick(TObject *Sender);
	void __fastcall BtnEditEsetMirrorDirClick(TObject *Sender);
	void __fastcall DirOpenEsetMirrorFileOkClick(TObject *Sender, bool &CanClose);
	void __fastcall BtnDevListerOpenClick(TObject *Sender);
	void __fastcall BtnKiberConsolOpenClick(TObject *Sender);
	void __fastcall BtnLicenseClick(TObject *Sender);
	void __fastcall BtnInfoClick(TObject *Sender);
	void __fastcall EditComentDblClick(TObject *Sender);
	void __fastcall BtnApp_HWiNFOClick(TObject *Sender);
	void __fastcall BtnApp_CPUZClick(TObject *Sender);
	void __fastcall BtnApp_GPUZClick(TObject *Sender);
	void __fastcall BtnApp_procexpClick(TObject *Sender);
	void __fastcall BtnApp_autorunsClick(TObject *Sender);
	void __fastcall BtnApp_tcpviewClick(TObject *Sender);
	void __fastcall BtnApp_TotalClick(TObject *Sender);
	void __fastcall BtnApp_EverythingClick(TObject *Sender);
	void __fastcall CheckBox_ShowEsetUpdateClick(TObject *Sender);
	void __fastcall РassClick(TObject *Sender);
	void __fastcall ComentTxtClick(TObject *Sender);
	void __fastcall InfoTxtClick(TObject *Sender);
	void __fastcall NetTxtClick(TObject *Sender);
	void __fastcall UsbTxtClick(TObject *Sender);
	void __fastcall EditPrefixPartitionChange(TObject *Sender);
	void __fastcall CheckBoxPrefixPartitionClick(TObject *Sender);
	void __fastcall BtnAboutGruberClick(TObject *Sender);
	void __fastcall Edit_InNumberARMChange(TObject *Sender);
	void __fastcall Edit_InNumberHDDChange(TObject *Sender);
	void __fastcall Edit_InNumberDeclrChange(TObject *Sender);
	void __fastcall Edit_InNumberFormulyarChange(TObject *Sender);
	void __fastcall Edit_InNumberWorkChange(TObject *Sender);
	void __fastcall Edit_InNumberPersonChange(TObject *Sender);
	void __fastcall EditPurposeChange(TObject *Sender);
	void __fastcall BtnClearPCClick(TObject *Sender);
	void __fastcall Gruber_MiniClick(TObject *Sender);
	void __fastcall Button_RestartAssAdminClick(TObject *Sender);
	void __fastcall BtnApp_UscDevUClick(TObject *Sender);
	void __fastcall BtnApp_DeviceCleanupClick(TObject *Sender);
	void __fastcall BtnApp_UsbTreeViewClick(TObject *Sender);
	void __fastcall Button_ControlPanelClick(TObject *Sender);
	void __fastcall Button_setingsPCClick(TObject *Sender);
	void __fastcall Button_msconfigClick(TObject *Sender);
	void __fastcall Button_CrashMonitorClick(TObject *Sender);
	void __fastcall Button_ResMonClick(TObject *Sender);
	void __fastcall Edit_NumberARMChange(TObject *Sender);
	void __fastcall Edit_PlaceChange(TObject *Sender);
	void __fastcall Edit_PhoneChange(TObject *Sender);
	void __fastcall Edit_InResponChange(TObject *Sender);
	void __fastcall Edit_InAdminBPChange(TObject *Sender);
	void __fastcall ComboBox_forNumberARMChange(TObject *Sender);
	void __fastcall ShowSerialGenarateDblClick(TObject *Sender);
	//void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall Button_CheckDefectionClick(TObject *Sender);
	void __fastcall Gruber_USBClick(TObject *Sender);
	void __fastcall ComboBox_PoliticInstallChange(TObject *Sender);
	void __fastcall ComboBox_ContrUSBChange(TObject *Sender);
	void __fastcall ComboBox_MultiUSERSChange(TObject *Sender);
	void __fastcall CheckListBox_SPZClickCheck(TObject *Sender);
private:	// User declarations
	std::vector<UnicodeString> fileInfoGrub();
	std::set<int> DisabledItemsClass;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

std::vector<UnicodeString> fileInfoGrub();
void changeEditDirColor();
void RestartApplicationRunas();

// ---------------------------------------------------------------------------
// Разделение проверки "нарушений" (soft/users/eset quarantine) на:
//  - "тяжёлую" часть без обращения к VCL (compute*) - можно спокойно вызывать
//    из фонового потока (Th_Gruber), т.к. она только читает диск/данные и
//    ничего не пишет в форму;
//  - "лёгкую" часть (apply*), которая только обновляет Memo/Label на форме и
//    обязана вызываться из главного потока (через Synchronize).
// Старые showSoft()/showUsers()/checkEsetQuarantine()/checkDefection()
// сохранены как есть (compute+apply вместе) для существующих мест вызова
// из главного потока (конструктор формы, обработчик кнопки).
// ---------------------------------------------------------------------------
struct SoftDefectionResult {
	std::vector<UnicodeString> lines;
	bool bad = false;
};
struct UsersDefectionResult {
	std::vector<UnicodeString> lines;
	bool bad = false;
};
struct EsetDefectionResult {
	int countTotal = 0;
	int countSys = 0;
	int countUser = 0;
	bool bad = false;
};
struct DefectionResult {
	SoftDefectionResult soft;
	UsersDefectionResult users;
	EsetDefectionResult eset;
};

// "тяжёлые" части - без VCL, безопасны для вызова из фонового потока
SoftDefectionResult computeSoftDefection();
UsersDefectionResult computeUsersDefection();
EsetDefectionResult computeEsetDefection();
DefectionResult computeDefection();

// "лёгкие" части - трогают Form1, вызывать только из главного потока
void applySoftDefection(const SoftDefectionResult &r);
void applyUsersDefection(const UsersDefectionResult &r);
void applyEsetDefection(const EsetDefectionResult &r);
void applyDefectionLabels(const DefectionResult &r);

void showSoft();
void showUsers();
void checkDefection ();
//---------------------------------------------------------------------------
#endif
