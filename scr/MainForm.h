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

#include <vector>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TProgressBar *ProgressBar1;
	TStatusBar *StatusBar1;
	TPageControl *PageControl1;
	TTabSheet *TabGRUBer;
	TTabSheet *TabSettings;
	TMemo *MemoLOG;
	TGridPanel *GridPanel2;
	TGridPanel *GridPanelMain;
	TGroupBox *GroupBox1;
	TButton *BtnGruberDirOpen;
	TButton *BtnParserOpen;
	TGridPanel *GridPanel3;
	TEdit *EditDirGrubName;
	TButton *BtnGruberRun;
	TButton *BtnGruberStop;
	TButton *BtnEsetUpdate;
	TGridPanel *GridPanel5;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *EditRespon;
	TLabel *Label5;
	TNumberBox *EditNumber;
	TComboBox *EditPartition;
	TComboBox *EditCategory;
	TGroupBox *GroupBox2;
	TLabel *Label7;
	TComboBox *EditArmClass;
	TButton *BtnKiberConsolOpen;
	TGridPanel *GridPanel6;
	TLabel *Label6;
	TEdit *ShowSerial;
	TButton *BtnInfo;
	TLabel *Label8;
	TEdit *ShowName;
	TButton *BtnLicense;
	TCheckBox *CheckBoxDebug;
	TLabel *Label9;
	TComboBox *EditLicWin;
	TLabel *Label10;
	TComboBox *EditLicOffice;
	TCheckBox *CheckBoxShowLog;
	TMemo *EditComent;
	TLabeledEdit *EditGrubUser;
	TGridPanel *GridPanel8;
	TGroupBox *GroupBox3;
	TCheckBox *CheckBoxAudit;
	TCheckBox *CheckBoxEsetLog;
	TButton *BtnSaveSetteings;
	TCheckBox *CheckBoxOldGrub;
	TCheckBox *CheckBoxNewGrub;
	TCheckBox *CheckBoxLicense;
	TButton *BtnEditPartition;
	TGroupBox *GroupBox4;
	TLabeledEdit *EditEsetMirrorDir;
	TButton *BtnEditEsetMirrorDir;
	TCheckBox *CheckBoxEsetAutoUpdate;
	TFileOpenDialog *DirOpenEsetMirror;
	TTabSheet *Tool;
	TGridPanel *GridPanel7;
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
	TButton *BtnApp_3;
	TButton *BtnApp_4;
	TGroupBox *GroupBox_AppUSB;
	TPopupMenu *PopupMenu_SysTool;
	TMenuItem *Perfmon;
	TCheckBox *CheckBox_ShowEsetUpdate;
	TMenuItem *MsConfig;
	TMenuItem *sysdmCpl;
	TCheckBox *CheckBox_RunAs;
	TTaskbar *Taskbar1;
	TPopupMenu *PopupMenu_StopGrub;
	TMenuItem *Рass;
	TPopupMenu *PopupMenu_mailGrubFile;
	TMenuItem *ComentTxt;
	TMenuItem *InfoTxt;
	TMenuItem *NetTxt;
	TMenuItem *UsbTxt;
	TButton *Button1;
	TEdit *EditPrefixPartition;
	TCheckBox *CheckBoxPrefixPartition;
	TButton *BtnAboutGruber;
	TButton *BtnClearPC;
	void __fastcall CheckBoxDebugClick(TObject *Sender);
	void __fastcall BtnGruberRunClick(TObject *Sender);
	void __fastcall EditNumberChange(TObject *Sender);
	void __fastcall EditPartitionChange(TObject *Sender);
	void __fastcall EditArmClassChange(TObject *Sender);
	void __fastcall EditCategoryChange(TObject *Sender);
	void __fastcall EditResponChange(TObject *Sender);
	void __fastcall EditComentChange(TObject *Sender);
	void __fastcall EditDirGrubNameChange(TObject *Sender);
	void __fastcall CheckBoxShowLogClick(TObject *Sender);
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
	void __fastcall BtnParserOpenClick(TObject *Sender);
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
	void __fastcall PerfmonClick(TObject *Sender);
	void __fastcall CheckBox_ShowEsetUpdateClick(TObject *Sender);
	void __fastcall MsConfigClick(TObject *Sender);
	void __fastcall sysdmCplClick(TObject *Sender);
	void __fastcall РassClick(TObject *Sender);
	void __fastcall ComentTxtClick(TObject *Sender);
	void __fastcall InfoTxtClick(TObject *Sender);
	void __fastcall NetTxtClick(TObject *Sender);
	void __fastcall UsbTxtClick(TObject *Sender);
	void __fastcall EditPrefixPartitionChange(TObject *Sender);
	void __fastcall CheckBoxPrefixPartitionClick(TObject *Sender);
	void __fastcall BtnAboutGruberClick(TObject *Sender);
private:	// User declarations
	std::vector<UnicodeString> fileInfoGrub();
	void mainGRUBer();
   int progressBarStep();
   void progressBarGo(int i, bool err = false);
   void progressBarEr();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

//---------------------------------------------------------------------------
#endif
