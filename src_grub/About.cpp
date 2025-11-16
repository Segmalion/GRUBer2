//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAbout *FormAbout;

extern const UnicodeString versionApp;
//---------------------------------------------------------------------------
__fastcall TFormAbout::TFormAbout(TComponent* Owner)
	: TForm(Owner)
{
	FormAbout->LinkLabel_ThreemaID->Caption = "Версія " + versionApp +
		"\n©GreenCapsul\nЗворотній зв'язок через " +
		"<a href=\"https://threema.id/XPPU95RT\">Threema</a> або " +
		"<a href=\"https://signal.me/#eu/ksKOKIRBGVlFLV99G8Mha2Q6uTdAkNnev3kjL72nCniZt3jsOqVDZqlJ4yzD-CXr\">Signal</a>";
}
//---------------------------------------------------------------------------
void __fastcall TFormAbout::LinkLabel_ThreemaIDLinkClick(TObject *Sender, const UnicodeString Link,
          TSysLinkType LinkType)
{
    ShellExecute(NULL, L"open", Link.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

