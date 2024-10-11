//---------------------------------------------------------------------------

#pragma hdrstop

#include "MainForm.h"
#include "HelpTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern edit ed;
extern config cfg;
extern bool stopBool;
//---------------------------------------------------------------------------
/* Запуск внешнего ПО с ожиданием (путь , аргументы, статус окна) */
struct eC app(UnicodeString Tool, UnicodeString ToolArg, int i)
{
   HINSTANCE errRun;
	DWORD exitCode = 0;
   eC retCode;
	SHELLEXECUTEINFOW ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = Tool.c_str();
	ShExecInfo.lpParameters = ToolArg.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = i;
	ShExecInfo.hInstApp = errRun;
	ShellExecuteExW(&ShExecInfo);
//	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
   HANDLE hHandles[] = { ShExecInfo.hProcess };
   MSG msg;
	while(1) {
		DWORD dwRet = ::MsgWaitForMultipleObjects(1, hHandles, FALSE, INFINITE, QS_ALLINPUT);
		if(dwRet == WAIT_OBJECT_0) {
			break;
      }
		else
			if(dwRet == WAIT_OBJECT_0 + 1){
				// There is a window message available. Dispatch it.
				while(PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				if (stopBool) {
					TerminateProcess(ShExecInfo.hProcess, 1);
				}
			} else break;
	}
	//тут проверка на запуск програмы
	ULONG_PTR errU = reinterpret_cast<ULONG_PTR>(errRun);
	if (errU>32) retCode.run = 1;      //good
		else retCode.run = 0;           //error
	//тут результат выполнения ПО
	GetExitCodeProcess(ShExecInfo.hProcess, &exitCode);
	if (exitCode==0) retCode.exit = 1; //good
		else retCode.exit = 0;          //error
	CloseHandle(ShExecInfo.hProcess);
	return retCode;
}
//---------------------------------------------------------------------------
/* Вывод логов */
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
/* Работа со строками */
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
/* Чтение файла настроек */
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
		//Параметр showLog
		fStr = findParam(ini, "[settings]", "showLog");
		if(fStr == 0 || fStr == 1) cfg.showLog = fStr.ToInt();
		//Параметр partition
		fStr = findParam(ini, "[arm]", "partition");
		if(fStr != "ERROR") cfg.partition = strParamParsing(fStr);
		//Параметр armClass
		fStr = findParam(ini, "[arm]", "armClass");
		if(fStr != "ERROR") cfg.armClass = strParamParsing(fStr);
		//Параметр category
		fStr = findParam(ini, "[arm]", "category");
		if(fStr != "ERROR") cfg.category = strParamParsing(fStr);
	} else return false;
	/* Параметр debug */
	Form1->CheckBoxDebug->Checked = cfg.debug;
	/* Параметр showLog */
	Form1->CheckBoxShowLog->Checked = cfg.showLog;
	if (cfg.showLog) Form1->Width = 1024*Form1->ScaleFactor;
	else Form1->Width = 421*Form1->ScaleFactor;
	/* Параметр partition */
	for(auto i : cfg.partition)
		Form1->EditPartition->AddItem(i, NULL);
	/* Параметр armClass */
	for(auto i : cfg.armClass)
		Form1->EditArmClass->AddItem(i, NULL);
	/* Параметр category */
	for(auto i : cfg.category)
		Form1->EditCategory->AddItem(i, NULL);
	return true;
}
bool infoReadAndSet() {
	UnicodeString dir = "C:\\ProgramData\\GRUBer\\";
	if (FileExists(dir + "gruber_info.dat")) {
		TStringList *infoDatIm = new TStringList;
		infoDatIm->LoadFromFile(dir + "info_001.dat", TEncoding::UTF8);

   }
	if (FileExists(dir + "info_001.dat")) {
		TStringList *infoDatIm = new TStringList;
		infoDatIm->LoadFromFile(dir + "info_001.dat", TEncoding::UTF8);
		Form1->EditNumber->Text = infoDatIm->Strings[1];
		Form1->EditPartition->Text = infoDatIm->Strings[2];
		Form1->EditCategory->ItemIndex = StrToInt(infoDatIm->Strings[3]);
		Form1->EditComent->Text = infoDatIm->Strings[4];
		Form1->EditRespon->Text = infoDatIm->Strings[5];
		/* if(infoDatIm->Count==7) {
			if (infoDatIm->Strings[6]=="auto") Form1->CheckBoxEsetUpdate->Checked=true;
			else {
				Form1->CheckBoxEsetUpdate->Checked=false;
				Form1->EditDirEsetUpdateConf->Text = infoDatIm->Strings[6];
			}
		} */
		printLog("Останній запуск GRUBer " + infoDatIm->Strings[0]);
	}
	if (FileExists(dir + "info.dat") && !FileExists(dir + "info_001.dat")) {
		TStringList *infoDatIm = new TStringList;
		infoDatIm->LoadFromFile(dir + "info.dat", TEncoding::UTF8);
		Form1->EditNumber->Text = infoDatIm->Strings[0]; 		//NumberPC->Text
		Form1->EditPartition->Text = infoDatIm->Strings[1];	//ComboBoxDep->Text
		Form1->EditCategory->ItemIndex = StrToInt(infoDatIm->Strings[2]); //ComboBoxCat->ItemIndex
		Form1->EditComent->Text = infoDatIm->Strings[3]; 		//EditCom->Text
		printLog("Останній запуск GRUBer " + infoDatIm->Strings[4]);
	}
	return true;
}
//---------------------------------------------------------------------------


