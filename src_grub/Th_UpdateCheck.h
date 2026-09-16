//---------------------------------------------------------------------------

#ifndef Th_UpdateCheckH
#define Th_UpdateCheckH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class Th_UpdateCheck : public TThread
{
private:
	bool silent; // true = тиха автоперевірка при старті, false = ручна (About)
	void __fastcall ExecuteImpl();
protected:
	void __fastcall Execute();
public:
	__fastcall Th_UpdateCheck(bool CreateSuspended, bool silentMode);
};
//---------------------------------------------------------------------------
#endif
