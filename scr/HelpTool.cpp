//---------------------------------------------------------------------------

#pragma hdrstop

#include "MainForm.h"
#include "HelpTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern bool chDeb;

void printLog(UnicodeString str)
{
	TDateTime* myTimeTemp = new TDateTime(Now());
	UnicodeString logTime = myTimeTemp->FormatString("hh:nn:ss");
	str = "[" + logTime + "] " + str;
	Form1->MemoLOG->Lines->Add(str);
}
void printLogDebug(UnicodeString str)
{
	if(chDeb == 0) return;
	TDateTime* myTimeTemp = new TDateTime(Now());
	UnicodeString logTime = myTimeTemp->FormatString("hh:nn:ss");
	str = "[" + logTime + "] [DEBUG]" + str;
	Form1->MemoLOG->Lines->Add(str);
}
