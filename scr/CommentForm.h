//---------------------------------------------------------------------------

#ifndef CommentFormH
#define CommentFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormComment : public TForm
{
__published:	// IDE-managed Components
	TGridPanel *GridPanel1;
	TMemo *EditComment;
	TButton *ButtonCancel;
	TButton *ButtonSave;
private:	// User declarations
public:		// User declarations
	__fastcall TFormComment(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormComment *FormComment;
//---------------------------------------------------------------------------
#endif
