//---------------------------------------------------------------------------
#pragma hdrstop

#include <memory>

#include "Help.h"
#include "Text.h"
#include "Fille.h"
#include "MainForm.h"
#include "Eset.h"
#include "GitVersion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
extern UnicodeString cmdEXE;
extern Config curConfig;
extern Arm curPC;
//---------------------------------------------------------------------------
/* Вывод логов */
// ВАЖНО: printLog/printLogDebug могут вызываться как из главного потока (UI),
// так и из фонового потока Th_Gruber. Прямая работа с VCL-компонентами
// (Form1->RichEdit_LOG, Form1->CheckBoxDebug) из не-главного потока запрещена
// правилами VCL и может приводить к падениям/повреждению UI. Поэтому весь
// доступ к элементам формы промаркирован через TThread::Synchronize, если
// вызов происходит не из главного потока. Если же вызов уже идёт из
// главного потока (обычный UI-обработчик) - лишний Synchronize не делается,
// компонент обновляется напрямую.
void printLog(UnicodeString str)
{
	UnicodeString logTime = TDateTime(Now()).FormatString("hh:mm:ss");
	UnicodeString line = "[" + logTime + "]" + str;
	auto addLine = [line]() {
		Form1->RichEdit_LOG->Lines->Add(line);
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
	};
	if (GetCurrentThreadId() == MainThreadID) addLine();
	else TThread::Synchronize(NULL, addLine);
}
void printLogDebug(UnicodeString str)
{
	bool debugOn = false;
	auto readDebug = [&debugOn]() { debugOn = Form1->CheckBoxDebug->Checked; };
	if (GetCurrentThreadId() == MainThreadID) readDebug();
	else TThread::Synchronize(NULL, readDebug);
	if (!debugOn) return;
	printLog("[DEBUG]" + str);
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
/* Перевірка доступу на запис перед роботою з текою + попередження.
   ТІЛЬКИ головний потік - звертається до Application->MessageBox і може
   викликати RestartApplicationRunas() (перезапуск процесу). */
bool warnIfNoAccess(UnicodeString path)
{
	if (hasWriteAccess(path)) return true;
	if (IsAdminMode()) {
		// вже під адміном, а прав нема - icacls у ensureDirWithAccess() чомусь
		// не спрацював (напр. тека на диску лише для читання)
		UnicodeString text = "Немає доступу на запис до теки:\n" + path;
		UnicodeString formCaption = "Помилка доступу";
		Application->MessageBox(text.c_str(), formCaption.c_str(), MB_OK);
		return false;
	}
	UnicodeString text = "Немає прав на запис у теку:\n" + path +
		"\nПерезапустити GRUBer з правами Адміністратора, щоб виправити права?";
	UnicodeString formCaption = "Немає доступу до теки";
	if (Application->MessageBox(text.c_str(), formCaption.c_str(), MB_YESNO) == IDYES) {
		RestartApplicationRunas(); // exit(1), не повертається
	}
	return false;
}
//---------------------------------------------------------------------------
UnicodeString GetAppVersion()
{
    // Получаем полный путь к нашему запущенному .exe файлу
    UnicodeString exeName = Application->ExeName;
    DWORD dummy = 0;

    // Узнаем размер данных о версии
    DWORD size = GetFileVersionInfoSize(exeName.c_str(), &dummy);
	if (size == 0) return L"1.0.0.1"; // Если версия не задана в настройках

    // Выделяем память под данные (используем вектор для автоматической очистки памяти)
    std::vector<BYTE> buffer(size);

    // Считываем блок информации о версии
    if (!GetFileVersionInfo(exeName.c_str(), 0, size, buffer.data())) {
        return L"1.0.0.2";
    }

    VS_FIXEDFILEINFO* fileInfo = nullptr;
    UINT fileInfoSize = 0;

    // Извлекаем фиксированную структуру с номерами
    if (VerQueryValue(buffer.data(), L"\\", (LPVOID*)&fileInfo, &fileInfoSize) && fileInfoSize > 0)
    {
        // Вытаскиваем мажорную, минорную версию, релиз и билд
        int major = HIWORD(fileInfo->dwFileVersionMS);
        int minor = LOWORD(fileInfo->dwFileVersionMS);
        int release = HIWORD(fileInfo->dwFileVersionLS);
        int build = LOWORD(fileInfo->dwFileVersionLS);

        // Формируем красивую строку
        return UnicodeString().sprintf(L"%d.%d.%d.%d", major, minor, release, build);
    }

    return L"Неизвестно";
}
//---------------------------------------------------------------------------
// Версія + git-хеш комміту, з якого зібраний .exe (GIT_COMMIT_HASH/GIT_DIRTY
// підставляються tools\gen_gitversion.bat перед компіляцією, Pre-Build Event).
UnicodeString GetFullAppVersion()
{
    UnicodeString dirty = GIT_DIRTY ? L"-dirty" : L"";
    return GetAppVersion() + L" (" + UnicodeString(GIT_COMMIT_HASH) + dirty + L")";
}
//---------------------------------------------------------------------------
void setConfigToForm(Config &curConfig) {
	Form1->CheckBoxDebug->Checked = curConfig.getDebug();
	Form1->CheckBox_ShowEsetUpdate->Checked = curConfig.getShowEsetUpd();
	Form1->CheckBox_TempDir->Checked = curConfig.getTempDir();
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
	Form1->EditPrefixPartition->Text = curConfig.getPrefixPartition();
	for(auto i : curConfig.get_lgpo()) if(!i.IsEmpty()) Form1->ComboBox_PoliticInstall->Items->Add(i); //<--
	for(auto i : curConfig.get_usb())  if(!i.IsEmpty()) Form1->ComboBox_ContrUSB->Items->Add(i); //<--
	for(auto i : curConfig.get_user()) if(!i.IsEmpty()) Form1->ComboBox_MultiUSERS->Items->Add(i); //<--
	for(auto i : curConfig.get_spz()) if(!i.IsEmpty()) Form1->CheckListBox_SPZ->Items->Add(i); //<--
	populateStructureCombos(curConfig);
}
//---------------------------------------------------------------------------
// перезаповнює обидва комбобокси структур зі списку Config, зберігаючи поточний
// вибір ComboBox_CurStructur за id, якщо така структура ще існує, інакше -
// на defaultStructureId
void populateStructureCombos(Config &curConfig) {
	UnicodeString keepId = Form1->getCurStructureId();
	std::vector<StructureDef> structs = curConfig.get_structures();

	Form1->ComboBox_CurStructur->Items->Clear();
	Form1->curStructureComboIds.clear();
	Form1->ComboBox_DefStructur->Items->Clear();
	Form1->defStructureComboIds.clear();
	for (auto &s : structs) {
		Form1->ComboBox_CurStructur->Items->Add(s.name);
		Form1->curStructureComboIds.push_back(s.id);
		Form1->ComboBox_DefStructur->Items->Add(s.name);
		Form1->defStructureComboIds.push_back(s.id);
	}

	// keepId порожній при першому заповненні (ще не було вибору) або структура
	// з таким id зникла (видалена в StructuresForm) - в обох випадках обираємо
	// структуру за замовчуванням, а не перший пункт списку
	int curIdx = -1;
	for (size_t i = 0; i < Form1->curStructureComboIds.size(); i++)
		if (Form1->curStructureComboIds[i] == keepId) { curIdx = (int)i; break; }
	if (curIdx < 0) {
		UnicodeString defId = curConfig.get_defaultStructureId();
		for (size_t i = 0; i < Form1->curStructureComboIds.size(); i++)
			if (Form1->curStructureComboIds[i] == defId) { curIdx = (int)i; break; }
	}
	if (curIdx < 0) curIdx = 0;
	if (Form1->ComboBox_CurStructur->Items->Count > 0) Form1->ComboBox_CurStructur->ItemIndex = curIdx;

	UnicodeString defId = curConfig.get_defaultStructureId();
	int defIdx = 0;
	for (size_t i = 0; i < Form1->defStructureComboIds.size(); i++)
		if (Form1->defStructureComboIds[i] == defId) { defIdx = (int)i; break; }
	if (Form1->ComboBox_DefStructur->Items->Count > 0) Form1->ComboBox_DefStructur->ItemIndex = defIdx;
}
//---------------------------------------------------------------------------
// підвантажує обрану структуру (за id) в поля Edit_NumberARM/EditPartition/
// Edit_Place/Edit_Phone - спільна логіка для setInfoArmToForm та зміни
// ComboBox_CurStructur
void applyCurStructureSelectionToForm(UnicodeString id) {
	if (id.IsEmpty()) return;
	// синхронізуємо ComboBox_CurStructur з id, який завантажуємо - інакше
	// EditPartitionChange/Edit_NumberARMChange/Edit_PlaceChange/Edit_PhoneChange
	// (що спрацьовують нижче) збережуть щойно завантажені дані під ІНШИМ id,
	// узятим із застарілого поточного вибору комбобокса (пряме присвоєння
	// ItemIndex, на відміну від вибору користувачем, не викликає OnChange)
	for (size_t i = 0; i < Form1->curStructureComboIds.size(); i++)
		if (Form1->curStructureComboIds[i] == id) { Form1->ComboBox_CurStructur->ItemIndex = (int)i; break; }
	curPC.setCurStructureSelection(id, Form1->ComboBox_CurStructur->Text);
	StructurePcData data = curPC.getStructure(id);
	Form1->Edit_NumberARM->Value = data.number;
	Form1->Edit_NumberARM->Enabled = true;
	Form1->EditPartition->Items->Clear();
	// "Без відділу" - завжди перший пункт, для будь-якої структури (навіть
	// порожньої), але це лише UI-заглушка: у списку відділів структури
	// (StructuresForm/Config) її нема і не повинно бути
	Form1->EditPartition->Items->Add("Без відділу");
	for (auto &d : curConfig.get_structures())
		if (d.id == id) for (auto &p : d.partition) Form1->EditPartition->Items->Add(p);
	Form1->EditPartition->Text = data.partition.IsEmpty() ? UnicodeString("Без відділу") : data.partition;
	// пряме присвоєння ->Text не викликає OnChange, тож підсвітку "нема у списку"
	// доводиться запускати вручну
	Form1->EditPartitionChange(Form1->EditPartition);
	Form1->Edit_Place->Text = data.place;
	Form1->Edit_PlaceChange(Form1->Edit_Place);
	Form1->Edit_Phone->Text = data.phone;
	Form1->Edit_PhoneChange(Form1->Edit_Phone);
}
//---------------------------------------------------------------------------
// структури, знайдені в gruber_info.ini цього ПК, яких немає серед структур,
// відомих програмі (GRUBer.ini) - кандидати на запит "додати цю структуру?"
std::vector<StructurePcData> findUnknownStructures(Arm &curPC, Config &curConfig) {
	std::vector<StructurePcData> unknown;
	std::vector<StructureDef> known = curConfig.get_structures();
	for (auto &s : curPC.get_structures()) {
		bool found = false;
		for (auto &k : known) if (k.id == s.id) { found = true; break; }
		if (!found) unknown.push_back(s);
	}
	return unknown;
}
void setInfoArmToForm(Arm &curPC) {
	applyCurStructureSelectionToForm(curConfig.get_defaultStructureId());
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
	Form1->EditArmClass->ItemIndex = Form1->EditArmClass->Items->IndexOf(curPC.getClassName());
	Form1->EditCategory->ItemIndex = Form1->EditCategory->Items->IndexOf(curPC.getCategoryName());
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

    Form1->ShowName->Text = curPC.getDesktopName();
	Form1->ShowSerial->Text = curPC.getSerial();
	Form1->ShowSerialGenarate->Text = curPC.getUnSerial();
	Form1->ShowManufacturer->Text = curPC.get_manufacturer();
	Form1->ShowProductName->Text = curPC.get_productName();

	Form1->ShowNetName->Items->Clear();
	for (auto &a : curPC.get_netAdapters()) Form1->ShowNetName->Items->Add(a.name);
	if (Form1->ShowNetName->Items->Count > 0) Form1->ShowNetName->ItemIndex = 0;
	updateNetAdapterFields();

	Form1->ShowEsetID->Text = getEsetProductInstanceID();
	Form1->Button_EsetLogsDir->Enabled = DirectoryExists(getEsetLogsDir());
	//infoSetToFille(curPC);
//...
}
bool infoSetToFille(Arm &curPC)
{
	const UnicodeString dir = "C:\\ProgramData\\GRUBer\\";
	const UnicodeString file = "gruber_info.ini";
	std::unique_ptr<TStringList> infoFille(new TStringList);
	/* формирование файла */
	// раздел версии файла
	for(auto str : curPC.mStrIniVersionNumber()) infoFille->Add(str);
	// раздел даты и пользователя
	for(auto str : curPC.mStrLastGrub()) infoFille->Add(str);
	// раздел номеров ПК (структур)
	for(auto str : curPC.mStrStructures()) infoFille->Add(str);
	// раздел поточної обраної структури
	for(auto str : curPC.mStrCurStructure()) infoFille->Add(str);
	// раздел серийников
	for(auto str : curPC.mStrSerial()) infoFille->Add(str);
	// раздел об АРМ
	for(auto str : curPC.mStrInfoArmGrub()) infoFille->Add(str);
	// раздел об ESET
	for(auto str : curPC.mStrInfoArmEset()) infoFille->Add(str);
	// раздел о сетевом соединении
	for(auto str : curPC.mStrInfoArmNet()) infoFille->Add(str);
	// раздел коментария
   infoFille->Add("[comment]");
	for (auto i : curPC.getComent()) {
		infoFille->Add(i);
	}
	infoFille->Add("#stop");
	/* конец формирования файла */
	// права на саму теку (не лише на файл) - щоб TempGRUB та інший вміст
	// C:\ProgramData\GRUBer\, який з'явиться пізніше, успадкував доступ на запис
	if (!DirectoryExists(dir)) ensureDirWithAccess(dir);
	else cacls(dir);
	infoFille->SaveToFile(dir + file, TEncoding::UTF8); // запись в файл
	cacls(dir + file); // права на сам файл
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

