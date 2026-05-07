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
	UnicodeString logTime = myTimeTemp->FormatString("hh:mm:ss");
	str = "[" + logTime + "]" + str;
	Form1->RichEdit_LOG->Lines->Add(str);
	// Form1->RichEdit_LOG->SelAttributes->Color = clDefault;
    /*
    //длина поточ.строки
	int iStr = Form1->RichEdit_LOG->Lines->Count;
	int startPos = 0, stopPos = 0;
	//id начала строки и конца
	int strStart = Form1->RichEdit_LOG->Perform(EM_LINEINDEX, iStr-1, 0);
	int strStop  = Form1->RichEdit_LOG->Lines->Strings[iStr-1].Length();
	//выделение символов строки
	Form1->RichEdit_LOG->SelStart = strStart + startPos;
	Form1->RichEdit_LOG->SelLength = strStop - (startPos + stopPos);
	//задание цвета
	Form1->RichEdit_LOG->SelAttributes->Color = (TColor) 0x008080F0;
	*/
}
void printLogDebug(UnicodeString str)
{
	if (Form1->CheckBoxDebug->Checked == false) return;
	else printLog("[DEBUG]" + str);
}
void printLog(UnicodeString info, UnicodeString str)
{
//	int i = Form1->RichEdit_LOG->Lines->Count;
//	Form1->RichEdit_LOG->SelStart = Form1->RichEdit_LOG->Perform(EM_LINEINDEX, i, 0);
//	Form1->RichEdit_LOG->SelLength = Form1->RichEdit_LOG->Lines->Strings[i].Length();
//	if (info == "OK") Form1->RichEdit_LOG->SelAttributes->Color = clGreen;
//	if (info == ">>") Form1->RichEdit_LOG->SelAttributes->Color = (TColor) 0x00FF901E;
//	if (info == "!!") Form1->RichEdit_LOG->SelAttributes->Color = (TColor) 0x00008CFF;
//	if (info == "ER") Form1->RichEdit_LOG->SelAttributes->Color = clRed;
	printLog("[" + info + "]" + str);
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
void setConfigToForm(Config &curConfig) {
	Form1->CheckBoxDebug->Checked = curConfig.getDebug();
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
	Form1->CheckBoxEsetLog->State = (TCheckBoxState)curConfig.getEsetLog();
	Form1->CheckBoxPrefixPartition->State = (TCheckBoxState)curConfig.getEnablePrefixPartition();
	Form1->ComboBox_forNumberARM->ItemIndex = curConfig.get_forNumberARMid();
	Form1->EditPrefixPartition->Text = curConfig.getPrefixPartition();
	for(auto i : curConfig.getPartition()) Form1->EditPartition->Items->Add(i);
	for(auto i : curConfig.get_lgpo()) if(!i.IsEmpty()) Form1->ComboBox_PoliticInstall->Items->Add(i); //<--
	for(auto i : curConfig.get_usb())  if(!i.IsEmpty()) Form1->ComboBox_ContrUSB->Items->Add(i); //<--
	for(auto i : curConfig.get_user()) if(!i.IsEmpty()) Form1->ComboBox_MultiUSERS->Items->Add(i); //<--
	for(auto i : curConfig.get_spz()) if(!i.IsEmpty()) Form1->CheckListBox_SPZ->Items->Add(i); //<--
}
void setInfoArmToForm(Arm &curPC) {
	if (curPC.get_useForNumberARMid() != 0)
		Form1->ComboBox_forNumberARM->ItemIndex = curPC.get_useForNumberARMid();
	if (Form1->ComboBox_forNumberARM->ItemIndex == 0) {
		Form1->Edit_NumberARM->Value = 0;
		Form1->Edit_NumberARM->Enabled = false;
	}
	if (Form1->ComboBox_forNumberARM->ItemIndex == 1) {
		Form1->Edit_NumberARM->Value = curPC.getNumber_UVs();
		Form1->Edit_NumberARM->Enabled = true;
	}
	if (Form1->ComboBox_forNumberARM->ItemIndex == 2) {
		Form1->Edit_NumberARM->Value = curPC.getNumber_UVs_logist();
		Form1->Edit_NumberARM->Enabled = true;
	}
	if (Form1->ComboBox_forNumberARM->ItemIndex == 3) {
		Form1->Edit_NumberARM->Value = curPC.getNumber_OK();
		Form1->Edit_NumberARM->Enabled = true;
	}
	if (Form1->ComboBox_forNumberARM->ItemIndex == 4) {
		Form1->Edit_NumberARM->Value = curPC.getNumber_OK_logist();
		Form1->Edit_NumberARM->Enabled = true;
	}
	Form1->EditPartition->Text = curPC.getPartition();
	//---
	if (!curPC.get_lgpo().IsEmpty())
		Form1->ComboBox_PoliticInstall->Text = curPC.get_lgpo();  //<--
	if (!curPC.get_controlUSB().IsEmpty())
		Form1->ComboBox_ContrUSB->Text  = curPC.get_controlUSB(); //<--
	if (!curPC.get_multiUser().IsEmpty())
		Form1->ComboBox_MultiUSERS->Text = curPC.get_multiUser(); //<--
	std::vector<UnicodeString> tp_vStr = curPC.get_spzInstal();
	for (int i = 0; i < tp_vStr.size(); i++) {
		if (Form1->CheckListBox_SPZ->Items->Count !=0) {
			for (int j = 0; j < Form1->CheckListBox_SPZ->Items->Count; j++) {
				if (tp_vStr[i] == Form1->CheckListBox_SPZ->Items->Strings[j]) {
					//printLogDebug("CHECK = " + UnicodeString(j));
					Form1->CheckListBox_SPZ->Checked[j] = true;
				}
			}
		}
	}
	//---
	Form1->EditArmClass->ItemIndex = curPC.getClassID();
	Form1->EditCategory->ItemIndex = curPC.getCategoryID();
	Form1->EditLicWin->Text    = curPC.getLicWindowsName();
	Form1->EditLicOffice->Text = curPC.getLicOfficeName();
	Form1->EditRespon->Text    = curPC.getRespon();
	Form1->EditPurpose->Text   = curPC.getPurpose();
	Form1->Edit_Place->Text   = curPC.getPlace();
	Form1->Edit_Phone->Text   = curPC.getPhone();

	Form1->Edit_InNumberARM->Text = curPC.getInNumberARM();
	Form1->Edit_InNumberHDD->Text = curPC.getInNumberHDD();
	Form1->Edit_InNumberDeclr->Text = curPC.getInNumberDeclr();
	Form1->Edit_InNumberFormulyar->Text = curPC.getInNumberFormulyar();
	Form1->Edit_InNumberWork->Text = curPC.getInNumberWork();
	Form1->Edit_InNumberPerson->Text = curPC.getInNumberPerson();
	Form1->Edit_InRespon->Text = curPC.getInRespon();
	Form1->Edit_InAdminBP->Text = curPC.getInAdminBP();

	Form1->EditComent->Clear();
	for (auto str : curPC.getComent()) {
		Form1->EditComent->Lines->Add(str);
	}
	Form1->CheckBoxEsetAutoUpdate->Checked = curPC.getEsetAutoUpdate();
	if (curPC.getEsetAutoUpdate())
		Form1->StatusBar1->Panels->Items[1]->Text = " ESET оновлюеться самостійно";
	else Form1->StatusBar1->Panels->Items[1]->Text = " Бази не оновлювалися";
	Form1->EditEsetMirrorDir->Text = curPC.getEsetDir();

	Form1->LabEdit_NumUVs->Text = curPC.getNumber_UVs();
	Form1->LabEdit_NumUVsO->Text = curPC.getNumber_UVs_logist();
	Form1->LabEdit_NumOK->Text = curPC.getNumber_OK();
	Form1->LabEdit_NumOKO->Text = curPC.getNumber_OK_logist();

    Form1->ShowName->Text = curPC.getDesktopName();
	Form1->ShowSerial->Text = curPC.getSerial();
	Form1->ShowSerialGenarate->Text = curPC.getUnSerial();
	Form1->ShowManufacturer->Text = curPC.get_manufacturer();
	Form1->ShowProductName->Text = curPC.get_productName();
	//infoSetToFille(curPC);
//...
}
bool infoSetToFille(Arm &curPC)
{
	const UnicodeString dir = "C:\\ProgramData\\GRUBer\\";
	const UnicodeString file = "gruber_info.ini";
	TStringList *infoFille = new TStringList;
	/* формирование файла */
	// раздел версии файла
	for(auto str : curPC.mStrIniVersionNumber()) infoFille->Add(str);
	// раздел даты и пользователя
	for(auto str : curPC.mStrLastGrub()) infoFille->Add(str);
	// раздел номеров ПК
	for(auto str : curPC.mStrNumberARM()) infoFille->Add(str);
	// раздел серийников
	for(auto str : curPC.mStrSerial()) infoFille->Add(str);
	// раздел об АРМ
	for(auto str : curPC.mStrInfoArmGrub()) infoFille->Add(str);
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
bool x64_sys() {
	return GetSystemWow64DirectoryW(nullptr, 0u);
}
bool x64_app() {
	if (sizeof(LPVOID) == 4) return false;
	else return true;
}

