//---------------------------------------------------------------------------

#ifndef AboutH
#define AboutH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TFormAbout : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TImage *Image1;
	TPanel *Panel1;
	TLinkLabel *LinkLabel_ThreemaID;
	void __fastcall LinkLabel_ThreemaIDLinkClick(TObject *Sender, const UnicodeString Link,
          TSysLinkType LinkType);
private:	// User declarations
public:		// User declarations
	__fastcall TFormAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAbout *FormAbout;
//---------------------------------------------------------------------------
#endif
