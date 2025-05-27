//---------------------------------------------------------------------------
#pragma hdrstop

#include "Help.h"
#include "Text.h"
#include "Fille.h"
#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
extern UnicodeString cmdEXE;
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
/* Проверка прав админа */
bool IsAdminMode() {
	 bool fRet = false;
	 HANDLE hToken = NULL;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
		  TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
		  if( GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize ) ) {
            fRet = Elevation.TokenIsElevated;
		  }
    }
    if( hToken ) {
        CloseHandle( hToken );
	 }
	 return fRet;
}
//---------------------------------------------------------------------------
void setInfoArmToForm(Arm &curPC) {
	Form1->EditNumber->Value   = curPC.getNumber();
	Form1->EditPartition->Text = curPC.getPartition();
	Form1->EditArmClass->ItemIndex = curPC.getClassID();
	Form1->EditCategory->ItemIndex = curPC.getCategoryID();
	Form1->EditLicWin->ItemIndex    = curPC.getLicWindowsID();
	Form1->EditLicOffice->ItemIndex = curPC.getLicOfficeID();
	Form1->EditArmClass->Text  = curPC.getClassName();
	Form1->EditCategory->Text  = curPC.getCategoryName();
	Form1->EditLicWin->Text    = curPC.getLicWindowsName();
	Form1->EditLicOffice->Text = curPC.getLicOfficeName();
	Form1->EditRespon->Text    = curPC.getRespon();
	Form1->EditPurpose->Text   = curPC.getPurpose();

	Form1->Edit_InNumberARM->Text = curPC.getInNumberARM();
	Form1->Edit_InNumberHDD->Text = curPC.getInNumberHDD();
	Form1->Edit_InNumberDeclr->Text = curPC.getInNumberDeclr();
	Form1->Edit_InNumberFormulyar->Text = curPC.getInNumberFormulyar();
	Form1->Edit_InNumberWork->Text = curPC.getInNumberWork();
	Form1->Edit_InNumberPerson->Text = curPC.getInNumberPerson();
	Form1->Edit_ComPoliticInstall->Text = curPC.getComPoliticInstall();
	Form1->Edit_ComContrUSB->Text = curPC.getComContrUSB();
	Form1->Edit_ComMultiUSERS->Text = curPC.getComMultiUSERS();
	Form1->CheckBox_PoliticInstall->Checked = curPC.getPoliticInstall();
	Form1->CheckBox_ContrUSB->Checked = curPC.getContrUSB();
	Form1->CheckBox_MultiUSERS->Checked = curPC.getMultiUSERS();
	//Form1->Edit_ComPoliticInstall->Enabled = curPC.getPoliticInstall();
	//Form1->Edit_ComContrUSB->Enabled = curPC.getContrUSB();
	//Form1->Edit_ComMultiUSERS->Enabled = curPC.getMultiUSERS();

	Form1->EditComent->Clear();
	for (auto str : curPC.getComent()) {
		Form1->EditComent->Lines->Add(str);
	}
	Form1->CheckBoxEsetAutoUpdate->Checked = curPC.getEsetAutoUpdate();
	if (curPC.getEsetAutoUpdate())
		Form1->StatusBar1->Panels->Items[1]->Text = " ESET оновлюеться самостійно";
	else Form1->StatusBar1->Panels->Items[1]->Text = " Бази не оновлювалися";
	Form1->EditEsetMirrorDir->Text = curPC.getEsetDir();
	//infoSetToFille(curPC);
//...
}
void setConfigToForm(Config &curConfig) {
	Form1->CheckBoxDebug->Checked = curConfig.getDebug();
	Form1->CheckBoxShowLog->Checked = curConfig.getShowLog();
    Form1->CheckBox_ShowEsetUpdate->Checked = curConfig.getShowEsetUpd();
	Form1->EditGrubUser->Text = curConfig.getUser();
	Form1->CheckBoxOldGrub->State = (TCheckBoxState)curConfig.getOldGrub();
	Form1->ComentTxt->Checked = curConfig.getOldGrubComent();
	Form1->InfoTxt->Checked = curConfig.getOldGrubInfo();
	Form1->NetTxt->Checked = curConfig.getOldGrubNet();
	Form1->UsbTxt->Checked = curConfig.getOldGrubUsb();
	Form1->CheckBoxNewGrub->Checked = curConfig.getNewGrub();
	Form1->CheckBoxLicense->Checked = curConfig.getLicense();
	Form1->CheckBoxAudit->State = (TCheckBoxState)curConfig.getAudit();
	//if (curConfig.getAudit() == 0) Form1->CheckBoxAudit->State = cbUnchecked;
	//if (curConfig.getAudit() == 2) Form1->CheckBoxAudit->State = cbGrayed;
	//if (curConfig.getAudit() == 1) Form1->CheckBoxAudit->State = cbChecked;
	Form1->CheckBoxEsetLog->State = (TCheckBoxState)curConfig.getEsetLog();
	//if (curConfig.getEsetLog() == 0) Form1->CheckBoxEsetLog->State = cbUnchecked;
	//if (curConfig.getEsetLog() == 2) Form1->CheckBoxEsetLog->State = cbGrayed;
	//if (curConfig.getEsetLog() == 1) Form1->CheckBoxEsetLog->State = cbChecked;
	//Form1->CheckBoxEsetLog->State = curConfig.getEsetLog();
	for(auto i : curConfig.getPartition()) Form1->EditPartition->Items->Add(i);
	for(auto i : curConfig.getArmClass()) Form1->EditArmClass->Items->Add(i);
	for(auto i : curConfig.getCategory()) Form1->EditCategory->Items->Add(i);
	Form1->CheckBoxPrefixPartition->State = (TCheckBoxState)curConfig.getEnablePrefixPartition();
    Form1->EditPrefixPartition->Text = curConfig.getPrefixPartition();

}
bool infoSetToFille(Arm &curPC)
{
	const UnicodeString dir = "C:\\ProgramData\\GRUBer\\";
	const UnicodeString file = "gruber_info.ini";
	TStringList *infoFille = new TStringList;
	/* формирование файла */
	// раздел даты и пользователя
	for(auto str : curPC.mStrLastGrub()) infoFille->Add(str);
	// раздел об АРМ
	for(auto str : curPC.mStrInfoArmGrubFull()) infoFille->Add(str);
	// раздел об ESET
	for(auto str : curPC.mStrInfoArmEset()) infoFille->Add(str);
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
bool compareVectorAndString(UnicodeString str, std::vector<UnicodeString> vct) {
	for(auto &a: vct) {
		if (str == a) return true;
	}
	return false;
}
//---------------------------------------------------------------------------


