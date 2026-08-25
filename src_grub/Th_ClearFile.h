//---------------------------------------------------------------------------

#ifndef Th_ClearFileH
#define Th_ClearFileH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vector>
//---------------------------------------------------------------------------
class Th_ClearFile : public TThread
{
private:
	void __fastcall ExecuteImpl();
protected:
	void __fastcall Execute();
public:
	__fastcall Th_ClearFile(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
