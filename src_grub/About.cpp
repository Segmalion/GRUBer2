//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"

#include <atomic>
#include "Th_UpdateCheck.h"
#include "Help.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAbout *FormAbout;

extern const UnicodeString versionApp;
extern std::atomic<bool> th_UpdateCheck_run;
//---------------------------------------------------------------------------
__fastcall TFormAbout::TFormAbout(TComponent* Owner)
	: TForm(Owner)
{
	FormAbout->LinkLabel_ThreemaID->Caption = L"Версія " + versionApp +
		L"\n©GreenCapsul\nЗворотній зв'язок через " +
		L"<a href=\"https://threema.id/XPPU95RT\">Threema</a> або " +
		"<a href=\"https://signal.me/#eu/ksKOKIRBGVlFLV99G8Mha2Q6uTdAkNnev3kjL72nCniZt3jsOqVDZqlJ4yzD-CXr\">Signal</a>" +
		L"\n<a href=\"gruber:check-update\">Перевірити оновлення</a>";
}
//---------------------------------------------------------------------------
void __fastcall TFormAbout::LinkLabel_ThreemaIDLinkClick(TObject *Sender, const UnicodeString Link,
          TSysLinkType LinkType)
{
	if (Link == "gruber:check-update") {
		if (th_UpdateCheck_run) return;
		if (!IsAdminMode()) {
			Application->MessageBox(
				L"Перевірка оновлень доступна лише при запуску GRUBer від імені адміністратора.",
				L"Перевірка оновлень", MB_OK | MB_ICONWARNING);
			return;
		}
		// закриваємо About одразу - якщо перевірка знайде оновлення і
		// користувач погодиться, застосування завершиться Application->Terminate()
		// поки ця форма ще була б модальною
		FormAbout->ModalResult = mrOk;
		Th_UpdateCheck *thUpd = new Th_UpdateCheck(true, /*silent*/ false);
		thUpd->Resume();
		return;
	}
    ShellExecute(NULL, L"open", Link.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

