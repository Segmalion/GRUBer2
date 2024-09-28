//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.NumberBox.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TProgressBar *ProgressBar1;
	TStatusBar *StatusBar1;
	TPageControl *PageControl1;
	TTabSheet *grid;
	TTabSheet *Налаштування;
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
	TEdit *EditComent;
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
	void __fastcall CheckBoxDebugClick(TObject *Sender);
	void __fastcall BtnGruberRunClick(TObject *Sender);
	void __fastcall EditNumberChange(TObject *Sender);
	void __fastcall EditPartitionChange(TObject *Sender);
	void __fastcall EditArmClassChange(TObject *Sender);
	void __fastcall EditCategoryChange(TObject *Sender);
	void __fastcall EditResponChange(TObject *Sender);
	void __fastcall EditComentChange(TObject *Sender);
	void __fastcall EditDirGrubNameChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
struct edit {
	int number;
	UnicodeString  partitionName;
	short partitionId;
	UnicodeString  categoryName;
	short categoryId;
	UnicodeString  armClassName;
	short armClassId;
	UnicodeString respon;
	UnicodeString coment;
	UnicodeString DirGrubName;
};
//---------------------------------------------------------------------------
#endif
