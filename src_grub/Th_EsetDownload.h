//---------------------------------------------------------------------------

#ifndef Th_EsetDownloadH
#define Th_EsetDownloadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class Th_EsetDownload : public TThread
{
private:
	void __fastcall ExecuteImpl();
protected:
	void __fastcall Execute();
public:
	__fastcall Th_EsetDownload(bool CreateSuspended);
};

void progressBarEsetGo(int percent);
void esetDlStatus(UnicodeString text);
//---------------------------------------------------------------------------
#endif
