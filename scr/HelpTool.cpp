//---------------------------------------------------------------------------

#pragma hdrstop

#include "MainForm.h"
#include "HelpTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern edit ed;
extern config cfg;
//---------------------------------------------------------------------------
void printLog(UnicodeString str)
{
	TDateTime* myTimeTemp = new TDateTime(Now());
	UnicodeString logTime = myTimeTemp->FormatString("hh:nn:ss");
	str = "[" + logTime + "] " + str;
	Form1->MemoLOG->Lines->Add(str);
}
void printLogDebug(UnicodeString str)
{
	if (cfg.debug == 0) return;
	str = "[DEBUG]" + str;
	printLog(str);
}
//---------------------------------------------------------------------------
bool isBeginUStr(UnicodeString strOR, UnicodeString srtF) {
	bool is = false;
	UnicodeString strORsh = strOR.SubString(0, srtF.Length());
	if (strORsh == srtF) is = true;
	return is;
}
std::vector<UnicodeString> strParamParsing (UnicodeString str) {
	std::vector<UnicodeString> fStr;
	while (str.Pos(",") != 0) {
		fStr.push_back(str.SubString(1, str.Pos(",")-1));
		str = str.SubString(str.Pos(",")+2, str.Length());
	}
	fStr.push_back(str);
	return fStr;
}
//---------------------------------------------------------------------------
bool paramReadAndSet() {
	UnicodeString iniFile = GetCurrentDir() + "\\GRUBer.ini";
	if (FileExists(iniFile)) {
		UnicodeString fStr;
		TStringList *ini = new TStringList;
		ini->LoadFromFile(iniFile, TEncoding::UTF8);
		int i = ini->Count;
		//Параметр debug
		fStr = findParam(ini, "[settings]", "debug");
		if(fStr == 0 || fStr == 1) cfg.debug = fStr.ToInt();
		//Параметр partition
		fStr = findParam(ini, "[arm]", "partition");
		if(fStr != "ERROR") cfg.partition = strParamParsing(fStr);
		//Параметр armClass
		fStr = findParam(ini, "[arm]", "armClass");
		if(fStr != "ERROR") cfg.armClass = strParamParsing(fStr);
		//Параметр category
		fStr = findParam(ini, "[arm]", "category");
		if(fStr != "ERROR") cfg.category = strParamParsing(fStr);
	} else return 0;
	Form1->CheckBoxDebug->Checked = cfg.debug;
	for(auto i : cfg.partition)
		Form1->EditPartition->AddItem(i, NULL);
	for(auto i : cfg.armClass)
		Form1->EditArmClass->AddItem(i, NULL);
	for(auto i : cfg.category)
		Form1->EditCategory->AddItem(i, NULL);
   return 1;
}
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm)
{
	UnicodeString find, str;
	bool findCat = false;
	for (int i = 0; i < ini->Count; i++) {
		str = ini->Strings[i];
		//printLog(str);
		if (findCat == false && str == cat) {
			findCat = true;
			continue;
		}
		if (findCat == true && isBeginUStr(str, "[")) {
			break;
		}
		if (findCat == true && isBeginUStr(str, prm)) {
			find = str.SubString(prm.Length()+2,str.Length());
			return find;
		}
	}
	return "ERROR";
}
//---------------------------------------------------------------------------


