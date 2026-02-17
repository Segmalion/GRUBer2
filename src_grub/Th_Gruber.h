//---------------------------------------------------------------------------

#ifndef Th_GruberH
#define Th_GruberH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class Th_Gruber : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall Th_Gruber(bool CreateSuspended);
};

double progressBarStep();
void progressBarGo(int i , bool err = 0);

bool job_infoFille(UnicodeString dir);
bool job_comTxt(UnicodeString dir);
bool job_info(UnicodeString dir);
bool job_softFille(UnicodeString dir);
bool job_usb(UnicodeString dir);
bool job_net1(UnicodeString dir);
bool job_net2(UnicodeString dir);
bool job_license(UnicodeString dir);
bool job_audit(UnicodeString dir);
bool job_diskInfo(UnicodeString dir);
bool job_esetLog(UnicodeString dir);
//---------------------------------------------------------------------------
#endif
