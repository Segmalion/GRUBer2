//---------------------------------------------------------------------------
#pragma hdrstop

#include "Help.h"
#include "Text.h"
#include "Fille.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//обявление внешних переменных типа структуры
//extern arm curPC;
//extern config cfg;
//extern grubHistor lastGrub;
//extern configEset cfgEset;
//extern dosCom dos;
//обявление внешних переменных
extern UnicodeString cmdEXE;
extern bool stopBool;
//---------------------------------------------------------------------------
Dir::Dir() {
	progFull = GetCurrentDir();
	baseName = "base";
	dateName = "[" + curDate() + "]";
	baseFull = progFull + "\\" + baseName;
	dateFull = baseFull + "\\" + dateName;
}
void Dir::check() {
	if (!DirectoryExists(baseFull)) CreateDir(baseFull);
	if (!DirectoryExists(dateFull)) CreateDir(dateFull);
	if (!DirectoryExists(grubFull)) CreateDir(grubFull);
}
void Dir::setGrubFull (UnicodeString str) {
	grubName = str;
	grubFull = dateFull + "\\" + grubName;
}
UnicodeString Dir::getGrubFull() {
	return grubFull;
}
//---------------------------------------------------------------------------
/* Запуск внешнего ПО с ожиданием (путь , аргументы, статус окна) */
errCode app(UnicodeString Tool, UnicodeString ToolArg, int i)
{
	HINSTANCE errRun;
	DWORD exitCode = 0;
	errCode retCode;
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

//---------------------------------------------------------------------------
/* Вывод логов */
void printLog(UnicodeString str)
{
	TDateTime* myTimeTemp = new TDateTime(Now());
	UnicodeString logTime = myTimeTemp->FormatString("hh:nn:ss");
	str = "[" + logTime + "] " + str;
	Form1->MemoLOG->Lines->Add(str);
}
void printLogDebug(bool debug, UnicodeString str)
{
	if (debug == 0) return;
	str = "[DEBUG]" + str;
	printLog(str);
}
//---------------------------------------------------------------------------
// проверка и установка CMD
UnicodeString cmdCheck(void)
{
	if (fileOpen("C:\\Windows\\System32\\cmd.exe"))
		return "C:\\Windows\\System32\\cmd.exe";
	if (fileOpen("C:\\Windows\\SysWOW64\\cmd.exe"))
		return "C:\\Windows\\SysWOW64\\cmd.exe";
	return "ERROR";
}
//---------------------------------------------------------------------------
/* Чтение файла настроек */
bool paramReadAndSet(cnfgGrub &cfg)
{
	UnicodeString iniFile = GetCurrentDir() + "\\GRUBer.ini";
	if (FileExists(iniFile)) {
		UnicodeString findStr;
		TStringList *ini = new TStringList;
		ini->LoadFromFile(iniFile, TEncoding::UTF8);
		//int i = ini->Count;
		//Параметр debug
		findStr = findParam(ini, "[settings]", "debug");
		if(findStr == 0 || findStr == 1) {
			cfg.debug = findStr.ToInt();
			Form1->CheckBoxDebug->Checked = cfg.debug;
		}
		//Параметр showLog
		findStr = findParam(ini, "[settings]", "showLog");
		if(findStr == 0 || findStr == 1) {
			cfg.showLog = findStr.ToInt();
         Form1->CheckBoxShowLog->Checked = cfg.showLog;
			if (cfg.showLog) Form1->Width = 1024*Form1->ScaleFactor;
			else Form1->Width = 421*Form1->ScaleFactor;
		}
		//Параметр partition
		findStr = findParam(ini, "[arm]", "partition");
		if(findStr != "0") {
			cfg.partition = strParamParsing(findStr);
			for(auto i : cfg.partition) Form1->EditPartition->Items->Add(i);
		}
		//Параметр armClass
		findStr = findParam(ini, "[arm]", "class");
		if(findStr != "0") {
			cfg.armClass = strParamParsing(findStr);
			for(auto i : cfg.armClass) Form1->EditArmClass->Items->Add(i);
		}
		//Параметр category
		findStr = findParam(ini, "[arm]", "category");
		if(findStr != "0") {
			cfg.category = strParamParsing(findStr);
			for(auto i : cfg.category) Form1->EditCategory->Items->Add(i);
		}
		//Параметр user
		findStr = findParam(ini, "[settings]", "user");
		if(findStr != "0") {
			cfg.grubUser = findStr;
			Form1->EditGrubUser->Text = cfg.grubUser;
		}
		return true;
	} else return false;
}
/* Чтение файла с инфой по АРМу */
bool infoReadAndSet(Arm &curPC)
{
	UnicodeString dir = "C:\\ProgramData\\GRUBer\\";
	if (FileExists(dir + "gruber_info.ini")) {
		Form1->EditNumber->Value = curPC.getNumber();
		Form1->EditPartition->Text = curPC.getPartition();
		Form1->EditArmClass->Text = curPC.getClassName();
		Form1->EditArmClass->ItemIndex = curPC.getClassId();
		Form1->EditCategory->Text = curPC.getCategoryName();
		Form1->EditCategory->ItemIndex = curPC.getCategoryId();
		Form1->EditLicWin->Text = curPC.getLicWindowsName();
		Form1->EditLicWin->ItemIndex = curPC.getLicWindowsId();
		Form1->EditLicOffice->Text = curPC.getLicOfficeName();
		Form1->EditLicOffice->ItemIndex = curPC.getLicOfficeId();
		Form1->EditRespon->Text = curPC.getRespon();
		Form1->EditComent->Clear();
		for (auto str : curPC.getComent()) {
			Form1->EditComent->Lines->Add(str);
		}
		//...
		return true;
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
		return true;
	}
	if (FileExists(dir + "info.dat") && !FileExists(dir + "info_001.dat")) {
		TStringList *infoDatIm = new TStringList;
		infoDatIm->LoadFromFile(dir + "info.dat", TEncoding::UTF8);
		Form1->EditNumber->Text = infoDatIm->Strings[0]; 		//NumberPC->Text
		Form1->EditPartition->Text = infoDatIm->Strings[1];	//ComboBoxDep->Text
		Form1->EditCategory->ItemIndex = StrToInt(infoDatIm->Strings[2]); //ComboBoxCat->ItemIndex
		Form1->EditComent->Text = infoDatIm->Strings[3]; 		//EditCom->Text
		printLog("Останній запуск GRUBer " + infoDatIm->Strings[4]);
		return true;
	}
	return false;
}
/* Запись файла с инфой по АРМу */
bool infoSetToFille(infoEset &cfgEset, histGrub &lastGrub, Arm &curPC)
{
	const UnicodeString dir = "C:\\ProgramData\\GRUBer\\";
	const UnicodeString file = "gruber_info.ini";
	TStringList *infoFille = new TStringList;
	/* формирование файла */
	// раздел даты и пользователя
	infoFille->Add("[lastGrub]");
	infoFille->Add("lastGrubDate=" + lastGrub.date);
	infoFille->Add("lastGrubUser=" + lastGrub.user);
	// раздел об АРМ
	infoFille->Add("[infoGrubARM]");
	for(auto str : curPC.mStrInfoArmGrub()) infoFille->Add(str);
	// раздел об ESET
	infoFille->Add("[infoESET]");
	infoFille->Add("dirMirror=" + cfgEset.dirMirror);
	infoFille->Add("autoUpdate=" + UnicodeString(cfgEset.autoUpdate));
	infoFille->Add("lastUpdateDate=" + cfgEset.lastUpdateDate);
	infoFille->Add("lastUpdateUser=" + cfgEset.lastUpdateUser);
	infoFille->Add("lastUpdateArchive=" + cfgEset.lastUpdateArchive);
	// раздел коментария
	infoFille->Add("[comment]");
	for (auto i : curPC.getComent()) {
		infoFille->Add(i);
	}
	infoFille->Add("#stop");
	/* конец формирования файла */
	if (!DirectoryExists(dir)) CreateDir(dir); 			 // проверка наличия папки
	infoFille->SaveToFile(dir + file, TEncoding::UTF8); // запись в файл
	cacls(dir + file); // [!]изменение прав на файл -- заменить на SetSecurityІnfo!
   return true;
}
//---------------------------------------------------------------------------


