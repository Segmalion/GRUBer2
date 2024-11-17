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
	TGridPanel *GridPanel4;
	TCheckBox *CheckBox1;
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
	TGridPanel *GridPanel7;
	TButton *Button1;
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
	void __fastcall Button1Click(TObject *Sender);
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
private:	// User declarations
	std::vector<UnicodeString> fileInfoGrub();
	void mainGRUBer();
   int progressBarStep();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

//---------------------------------------------------------------------------
#endif
