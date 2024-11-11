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
/* Основной граб */

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
/* Сборка именни папки */

/*
UnicodeString dirCurGrubName (arm &curPC, UnicodeString date)
{
	UnicodeString str;
	str = "[";
	// number
	if (curPC.number == 0) {
		str = str + "--";
	} else str = str + UnicodeString(curPC.number);
	str = str + "][" + date + "]";
	// partition
	str = str + curPC.partitionName;
	// serial
	str = str + "#" + curPC.serial;
	// category
	str = str + "#" + curPC.categoryName;
	//curPC.dirGrubName = fixDirName(str);
	return fixDirName(str);
} */
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
/* Чтение и запись файла настроек */
UnicodeString findParam(TStringList *ini, UnicodeString cat, UnicodeString prm)
{
	UnicodeString resultStr, findStr;
	bool findCat = false;
	for (int i = 0; i < ini->Count; i++) {
		findStr = ini->Strings[i];
		//printLog(str);
		if (findCat == false && findStr == cat) {
			findCat = true;
			continue;
		}
		if (findCat == true && isBeginUStr(findStr, "[")) {
			break;
		}
		if (findCat == true && isBeginUStr(findStr, prm)) {
			resultStr = findStr.SubString(prm.Length()+2,findStr.Length());
			return resultStr;
		}
	}
	return "ERROR";
}
std::vector<UnicodeString> findCategory(TStringList *ini, UnicodeString cat) {
	std::vector<UnicodeString> findMulStr;
	UnicodeString findStr;
	bool findCat = false;
	for (int i = 0; i < ini->Count; i++) {
		findStr = ini->Strings[i];
		if (findCat == false && findStr == cat) {
			findCat = true;
			continue;
		}
		if (findCat == true && isBeginUStr(findStr, "#stop")) {
			return findMulStr;
		}
		if (findCat == true) {
			findMulStr.push_back(findStr);
			continue;
		}
	}
	findMulStr.push_back("ERROR");
	return findMulStr;
}
//Основные функции
bool paramReadAndSet(cnfgGrub &cfg)
{
	UnicodeString iniFile = GetCurrentDir() + "\\GRUBer.ini";
	if (FileExists(iniFile)) {
		UnicodeString findStr;
		TStringList *ini = new TStringList;
		ini->LoadFromFile(iniFile, TEncoding::UTF8);
		int i = ini->Count;
		//Параметр debug
		findStr = findParam(ini, "[settings]", "debug");
		if(findStr == 0 || findStr == 1) cfg.debug = findStr.ToInt();
		//Параметр showLog
		findStr = findParam(ini, "[settings]", "showLog");
		if(findStr == 0 || findStr == 1) cfg.showLog = findStr.ToInt();
		//Параметр partition
		findStr = findParam(ini, "[arm]", "partition");
		if(findStr != "ERROR") cfg.partition = strParamParsing(findStr);
		//Параметр armClass
		findStr = findParam(ini, "[arm]", "armClass");
		if(findStr != "ERROR") cfg.armClass = strParamParsing(findStr);
		//Параметр category
		findStr = findParam(ini, "[arm]", "category");
		if(findStr != "ERROR") cfg.category = strParamParsing(findStr);
		//Параметр user
		findStr = findParam(ini, "[settings]", "user");
		if(findStr != "ERROR") cfg.grubUser = findStr;
	} else return false;
	/* Параметр debug */
	Form1->CheckBoxDebug->Checked = cfg.debug;
	/* Параметр showLog */
	Form1->CheckBoxShowLog->Checked = cfg.showLog;
	if (cfg.showLog) Form1->Width = 1024*Form1->ScaleFactor;
	else Form1->Width = 421*Form1->ScaleFactor;
	/* Параметр partition */
	for(auto i : cfg.partition) Form1->EditPartition->Items->Add(i);
	/* Параметр armClass */
	for(auto i : cfg.armClass) Form1->EditArmClass->Items->Add(i);
	/* Параметр category */
	for(auto i : cfg.category) Form1->EditCategory->Items->Add(i);
	/* Параметр user */
	Form1->EditGrubUser->Text = cfg.grubUser;
	return true;
}
bool infoReadAndSet(Arm &curPC)
{
	UnicodeString dir = "C:\\ProgramData\\GRUBer\\";
	if (FileExists(dir + "gruber_info.ini")) {
		UnicodeString findStr;
		TStringList *infoDatIm = new TStringList;
		infoDatIm->LoadFromFile(dir + "gruber_info.ini", TEncoding::UTF8);
		// 1 - номер АРМ
		findStr = findParam(infoDatIm, "[infoARM]", "number");
		Form1->EditNumber->Value = findStr.ToInt();
		curPC.number = findStr.ToInt();
		// 2 - отдел
		findStr = findParam(infoDatIm, "[infoARM]", "partition");
		Form1->EditPartition->Text = findStr;
		curPC.partitionName = findStr;
		// 3 - клас АРМ
		findStr = findParam(infoDatIm, "[infoARM]", "armClassID");
		Form1->EditArmClass->ItemIndex = findStr.ToInt();
		curPC.armClassId = findStr.ToInt();
		curPC.armClassName = findParam(infoDatIm, "[infoARM]", "armClassName");
		// 4 - категория АРМ
		findStr = findParam(infoDatIm, "[infoARM]", "categoryID");
		Form1->EditCategory->ItemIndex = findStr.ToInt();
		curPC.categoryId = findStr.ToInt();
		curPC.categoryName = findParam(infoDatIm, "[infoARM]", "categoryName");
		// 5 - лицензия ОС
		findStr = findParam(infoDatIm, "[infoARM]", "licenseWindowsID");
		Form1->EditLicWin->ItemIndex = findStr.ToInt();
		curPC.licWindowsId = findStr.ToInt();
		curPC.licWindowsName = findParam(infoDatIm, "[infoARM]", "licenseWindowsName");
		// 6 - лицензия оффиса
		findStr = findParam(infoDatIm, "[infoARM]", "licenseOfficeID");
		Form1->EditLicOffice->ItemIndex = findStr.ToInt();
		curPC.licOfficeId = findStr.ToInt();
		curPC.licOfficeName = findParam(infoDatIm, "[infoARM]", "licenseOfficeName");
		// 7 - ответственый
		findStr = findParam(infoDatIm, "[infoARM]", "respon");
		Form1->EditRespon->Text = findStr;
		curPC.respon = findStr;
		// 8 - коментарий
		Form1->EditComent->Clear();
		for (auto i : findCategory(infoDatIm, "[comment]")) {
			Form1->EditComent->Lines->Add(i);
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
bool infoSetToFille(const infoEset &cfgEset, const histGrub &lastGrub, const Arm &curPC)
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
	infoFille->Add("[infoARM]");
	infoFille->Add("number=" + UnicodeString(curPC.number));
	infoFille->Add("partition=" + curPC.partitionName);
	infoFille->Add("armClassID=" + UnicodeString(curPC.armClassId));
	infoFille->Add("armClasName=" + curPC.armClassName);
	infoFille->Add("categoryID=" + UnicodeString(curPC.categoryId));
	infoFille->Add("categoryName=" + curPC.categoryName);
	infoFille->Add("licenseWindowsID=" + UnicodeString(curPC.licWindowsId));
	infoFille->Add("licenseWindowsName=" + curPC.licWindowsName);
	infoFille->Add("licenseOfficeID=" + UnicodeString(curPC.licOfficeId));
	infoFille->Add("licenseOfficeName=" + curPC.licOfficeName);
	infoFille->Add("respon=" + curPC.respon);
	// раздел об ESET
	infoFille->Add("[infoESET]");
	infoFille->Add("dirMirror=" + cfgEset.dirMirror);
	infoFille->Add("autoUpdate=" + UnicodeString(cfgEset.autoUpdate));
	infoFille->Add("lastUpdateDate=" + cfgEset.lastUpdateDate);
	infoFille->Add("lastUpdateUser=" + cfgEset.lastUpdateUser);
	infoFille->Add("lastUpdateArchive=" + cfgEset.lastUpdateArchive);
	// раздел коментария
	infoFille->Add("[comment]");
	for (auto i : curPC.coment) {
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


