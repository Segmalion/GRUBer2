//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.Hash.hpp>
#include <thread> // Required for std::this_thread::sleep_for
#include <chrono> // Required for std::chrono::seconds
#include <filesystem>
#include <atomic>
#include <System.DateUtils.hpp>
#pragma hdrstop

#include "MainForm.h"
#include "ComentForm.h"
#include "StructuresForm.h"
#include "StructurePickForm.h"
#include "DialogDirExist.h"
#include "About.h"
#include "ClearTemp.h"
#include "FormSerial.h"
#include "InstallSoft.h"
#include "Users.h"
#include "FormQuarantine.h"

#include "Arm.h"
#include "Config.h"
#include "Dir.h"

#include "RunApp.h"
#include "Help.h"
#include "Text.h"
#include "Fille.h"
#include "Eset.h"

#include "Th_Gruber.h"
#include "CrashHandler.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
//---------------------------------------------------------------------------

//обявление переменных типа структуры
Config curConfig;
Arm curPC;
Dir curDir;
//обявление переменных
UnicodeString cmdEXE, curentDate;
// Флаги нижче читаються/пишуться як з головного потоку, так і з фонового
// (Th_Gruber/Th_ClearFile) без Synchronize - std::atomic<bool> замість bool
// прибирає data race на цих прапорцях (пор. з compute/apply-розділенням
// для доступу до VCL, описаним у CLAUDE.md).
std::atomic<bool> th_Gruber_run{false}, th_ClearFile_run{false};
bool th_EsetUpdate_run=0; // наразі ніде більше не використовується
std::atomic<bool> th_Gruber_runMini{false}, th_Gruber_runUSB{false};
std::atomic<bool> stopBool{false}, passBool{false};
bool dirGrubRewrite; // пишеться в Synchronize(), уже синхронізовано ним
bool gruberStart=0;  // читається/пишеться лише з головного потоку
std::atomic<bool> checkDirExist{false};
std::vector<UnicodeString> vStrPartition;
std::atomic<bool> grubActive{false};
extern std::vector<UnicodeString> blockProgrammsNames;
struct defection {
	bool user;
	bool soft;
	bool eset;
	std::vector<UnicodeString> quarantineDirs; // папки карантину ESET, де знайдено файли
	std::vector<User> users; // повний список користувачів для таблиці Grid_Users (потрібен у Grid_UsersDrawCell)
} curDefection;
// CheckBox_installAvpz* - "тільки читання": OnClick відкочує ручні кліки
// користувача (див. CheckBox_installAvpzESETClick), але сам відкат теж
// відбувається через Checked, тому програмне оновлення стану мусить
// проходити через цей прапорець, інакше OnClick від власного присвоєння
// відкотить щойно встановлене значення назад.
static bool avpzCheckBoxProgrammaticSet = false;
static void setReadOnlyCheckBox(TCheckBox *cb, bool value) {
	avpzCheckBoxProgrammaticSet = true;
	cb->Checked = value;
	avpzCheckBoxProgrammaticSet = false;
}
//---------------------------------------------------------------------------
extern const UnicodeString versionApp = GetFullAppVersion();
//---------------------------------------------------------------------------
std::vector<UnicodeString> fileInfoGrub() {
	std::vector<UnicodeString> vStr;
	// раздел версии файла
	for(auto str : curPC.mStrIniVersionNumber()) vStr.push_back(str);
	// раздел даты и пользователя
	for(auto str : curPC.mStrLastGrub()) vStr.push_back(str);
	// раздел номеров ПК (структур)
	for(auto str : curPC.mStrStructures()) vStr.push_back(str);
	// раздел поточної обраної структури
	for(auto str : curPC.mStrCurStructure()) vStr.push_back(str);
	// раздел серийников
	for(auto str : curPC.mStrSerial()) vStr.push_back(str);
	// раздел об АРМ-1
	for(auto str : curPC.mStrInfoArm()) vStr.push_back(str);
	// раздел об АРМ-2
	for(auto str : curPC.mStrInfoArmGrub()) vStr.push_back(str);
	// раздел об ESET
	for(auto str : curPC.mStrInfoArmEset()) vStr.push_back(str);
	// раздел о сетевом соединении
	for(auto str : curPC.mStrInfoArmNet()) vStr.push_back(str);
	// раздел коментария
	vStr.push_back("[comment]");
	for (auto str : curPC.getComent()) {
		vStr.push_back(str);
	}
	vStr.push_back("#stop");
	return vStr;
}
void changeEditDirColor() {
	if(DirectoryExists(curDir.get_grubPath())) {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x006E00;
		Form1->EditDirGrubName->Color = (TColor) 0xEAFFEA;
		if (!grubActive) Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer вже зібрано!";
	} else {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x00006E;
		Form1->EditDirGrubName->Color = (TColor) 0xEAEAFF;
		Form1->StatusBar1->Panels->Items[0]->Text = " GRUBer не зібрано:(";
	}
	Form1->BtnGruberDirOpen->Enabled = DirectoryExists(curDir.get_grubPath());
}
// Оновлює ShowNetIP/ShowNetMAC/ShowNetStatus відповідно до адаптера,
// обраного зараз в ShowNetName (індекс у списку відповідає curPC.get_netAdapters()).
void updateNetAdapterFields() {
	std::vector<NetAdapterInfo> adapters = curPC.get_netAdapters();
	int idx = Form1->ShowNetName->ItemIndex;
	if (idx < 0 || idx >= (int)adapters.size()) {
		Form1->ShowNetIP->Text = "";
		Form1->ShowNetMAC->Text = "";
		Form1->ShowNetStatus->Text = "";
		return;
	}
	NetAdapterInfo &a = adapters[idx];
	Form1->ShowNetIP->Text = a.ip;
	Form1->ShowNetMAC->Text = a.mac;
	if (a.active) {
		Form1->ShowNetStatus->Text = "Активне";
	} else if (a.lastActive == TDateTime(0.0)) {
		Form1->ShowNetStatus->Text = "Неактивне";
	} else {
		Form1->ShowNetStatus->Text = "Неактивне (з " + a.lastActive.FormatString("dd.MM.yy HH:mm") + ")";
	}
}
void __fastcall TForm1::ShowNetNameChange(TObject *Sender)
{
	updateNetAdapterFields();
}
// Grid_Users малюється вручну (DefaultDrawing = False у Grid_UsersDrawCell),
// тож при кастомній відмальовці TCustomGrid не завжди сам перераховує
// Font/DefaultRowHeight при зміні DPI монітора - робимо це явно. Замість
// хардкоджених дизайнерських значень (які "розсинхронізувались" би з .dfm при
// першому ж пересохраненні форми в IDE на іншому DPI) один раз запам'ятовуємо
// поточні (вже коректні на старті) Font.Height/DefaultRowHeight разом з PPI -
// той самий підхід, що і для GridPanel нижче.
static int gGridUsersBaselineFontHeight = 0;
static int gGridUsersBaselineRowHeight = 0;
static int gGridUsersBaselinePPI = 0;
void captureGridUsersDpiBaseline() {
	gGridUsersBaselineFontHeight = Form1->Grid_Users->Font->Height;
	gGridUsersBaselineRowHeight = Form1->Grid_Users->DefaultRowHeight;
	gGridUsersBaselinePPI = Form1->PixelsPerInch;
}
void applyGridUsersDpiScale() {
	if (gGridUsersBaselinePPI == 0) return;
	int ppi = Form1->PixelsPerInch;
	Form1->Grid_Users->Font->Height = MulDiv(gGridUsersBaselineFontHeight, ppi, gGridUsersBaselinePPI);
	Form1->Grid_Users->DefaultRowHeight = MulDiv(gGridUsersBaselineRowHeight, ppi, gGridUsersBaselinePPI);
	Form1->Grid_Users->Invalidate();
}
// Форма майже суцільно зібрана з вкладених TGridPanel з рядками/колонками
// SizeStyle = ssAbsolute (фіксовані пікселі при дизайнерському PPI). У
// TCustomGridPanel є свій ChangeScale, але на практиці Value для ssAbsolute
// не завжди коректно перераховується при зміні DPI монітора чи масштабу
// екрана "на льоту" - через це ламається розмітка (напр. GridPanel_forButGrub).
// Замість дизайнерських значень (яких для ~15 GridPanel по всій формі довелось
// би витягувати з .dfm) один раз запам'ятовуємо поточні (вже коректні на
// старті) Value та PPI, а при зміні DPI перераховуємо відносно цієї точки.
struct AbsoluteCellBaseline {
	TCellItem *item;
	double baseValue;
};
static std::vector<AbsoluteCellBaseline> gGridPanelBaselines;
static int gGridPanelBaselinePPI = 0;
static void collectGridPanelAbsoluteCells(TControl *control) {
	TGridPanel *panel = dynamic_cast<TGridPanel*>(control);
	if (panel) {
		for (int i = 0; i < panel->RowCollection->Count; i++) {
			TCellItem *item = (*panel->RowCollection)[i];
			if (item->SizeStyle == TSizeStyle::ssAbsolute)
				gGridPanelBaselines.push_back({item, item->Value});
		}
		for (int i = 0; i < panel->ColumnCollection->Count; i++) {
			TCellItem *item = (*panel->ColumnCollection)[i];
			if (item->SizeStyle == TSizeStyle::ssAbsolute)
				gGridPanelBaselines.push_back({item, item->Value});
		}
	}
	TWinControl *winControl = dynamic_cast<TWinControl*>(control);
	if (winControl) {
		for (int i = 0; i < winControl->ControlCount; i++)
			collectGridPanelAbsoluteCells(winControl->Controls[i]);
	}
}
void captureGridPanelDpiBaselines() {
	gGridPanelBaselines.clear();
	collectGridPanelAbsoluteCells(Form1);
	gGridPanelBaselinePPI = Form1->PixelsPerInch;
}
void rescaleGridPanelsForDpi() {
	if (gGridPanelBaselinePPI == 0) return;
	int ppi = Form1->PixelsPerInch;
	for (auto &b: gGridPanelBaselines) b.item->Value = b.baseValue * ppi / gGridPanelBaselinePPI;
}
void __fastcall TForm1::Form1AfterMonitorDpiChanged(TObject *Sender, int OldDPI, int NewDPI)
{
	rescaleGridPanelsForDpi();
	applyGridUsersDpiScale();
}
// Ловить винятки, що виникають під час обробки повідомлень у Application->Run()
// (наприклад, у обробнику кліку кнопки). Пише в crash.log, тоді показує
// стандартний діалог VCL - для користувача поведінка не змінюється, але тепер
// причина падіння лишається в файлі, а не тільки на екрані, що зникає одразу.
void __fastcall TForm1::AppExceptionHandler(TObject *Sender, Exception *E)
{
	LogCrash("Application", E->ClassName() + ": " + E->Message);
	Application->ShowException(E);
}
void RestartApplicationRunas()
{
	fs::path p_app;
	if (x64_app() == true) p_app = fs::current_path() / "GRUBer.exe";
	else p_app = fs::current_path() / "GRUBer_x32.exe";
	if(exists(p_app)) {
		ShellExecuteW(NULL, L"runas", p_app.c_str(), NULL, NULL, SW_SHOWDEFAULT);
		exit(1);
	} else printLogDebug("Не вдалося перезапустити ГРАБер з правами адміна :(");
}
// ---------------------------------------------------------------------------
// "Тяжёлые" части - без обращения к Form1/VCL. Можно безопасно вызывать из
// фонового потока (Th_Gruber), результат затем маршалится в главный поток.
// ---------------------------------------------------------------------------
SoftDefectionResult computeSoftDefection() {
	SoftDefectionResult res;
	curPC.read_soft();
	std::vector<program> blockedInstalledSoft = curPC.get_softBlock();
	if (blockedInstalledSoft.size() == 0) {
		res.bad = false;
	} else {
		for(auto soft: blockedInstalledSoft) sortToVector(res.lines, soft.name);
		res.bad = true;
	}
	for (auto soft: curPC.get_softInstall()) {
		if (compareInSring(soft.name, "ESET Endpoint Security")) res.esetInstalled = true;
		if (compareInSring(soft.name, "ESET Rogue Detection Sensor")) res.rdSensorInstalled = true;
		if (compareInSring(soft.name, "Trellix Endpoint Security (HX) Agent")) res.trellixInstalled = true;
	}
	return res;
}
UsersDefectionResult computeUsersDefection() {
	UsersDefectionResult res;
    curPC.read_user();
	std::vector<User> usersList = curPC.get_users();
	if (usersList.size() == 0) {
		res.bad = false; // curDefection.user не трогаем - как и в исходном коде
	} else {
		short admin_t = 0, user_t = 0, guest_t = 0;
		for(auto user: usersList) {
			if (user.priv == "ADMIN") admin_t++;
			if (user.priv == "USER") user_t++;
			if (user.priv == "GUEST") guest_t++;
		}
		res.users = usersList;
		if (curPC.getCategoryName() == "Особистий") {
			res.bad = false;
		} else {
			if (admin_t == 1 && curPC.getClassName() != "ЛООК") {
				if ((user_t ) > 0 ) {
					res.bad = false;
				} else res.bad = true;
			} else if (admin_t == 2 && curPC.getClassName() == "ЛООК") {
				if ((user_t) > 0 ) {
					res.bad = false;
				} else res.bad = true;
			} else res.bad = true;
		}
	}
	return res;
}
EsetDefectionResult computeEsetDefection() {
	EsetDefectionResult res;
	UnicodeString dirSysQuarantine  = "C:\\Windows\\System32\\config\\systemprofile\\AppData\\Local\\ESET\\ESET Security\\Quarantine\\";
	UnicodeString dirUserQuarantine = "AppData\\Local\\ESET\\ESET Security\\Quarantine\\";
	patchList sysList, userList;
    // --- готовим список пользовательских папок (userDirList)---
	std::vector<UnicodeString> userListBad { //запрещеные пользователи
		"All Users",
		"Default",
		"Default User",
		"Public"
	};
	std::vector<UnicodeString> userDirList; //создаем вектор с папками пользователей
	// процедура поиска папок пользователей
	UnicodeString dirUser = "C:\\Users";
	TSearchRec srUser;
	if (!FindFirst(dirUser + "\\*.*", faAnyFile, srUser))
		do {
			if (!(srUser.Name == "." || srUser.Name == ".." || srUser.Name == "INFO.NQI")) { // это не трогаем
				if ((srUser.Attr & faDirectory) != 0) {
					if (!compareVectorAndString(srUser.Name, userListBad)) {
						userDirList.push_back(dirUser + "\\" + srUser.Name);
					}
				}
			}
		} while (!FindNext(srUser)); // ищем пока не найдем все
	FindClose(srUser);
	// --- готовим список всех файлов во временых папках (самая долгая часть - обход диска) ---
	// папка системного карантина
	patchList temp = scanDirToFille(dirSysQuarantine);
	sysList.list.insert(sysList.list.end(), temp.list.begin(), temp.list.end());
	sysList.countDir += temp.countDir ;
	sysList.countFille += temp.countFille ;
	sysList.size += temp.size;
	// папки карантина пользователей
	for (auto userDir: userDirList) {
		UnicodeString qDir = userDir + "\\" + dirUserQuarantine;
		patchList temp = scanDirToFille(qDir);
		userList.list.insert(userList.list.end(), temp.list.begin(), temp.list.end());
		userList.countDir += temp.countDir;
		userList.countFille += temp.countFille;
		userList.size += temp.size;
		int countThisUserFille = 0;
		for (auto file: temp.list) {
			if (!(compareInSring(file.str, "INFO.NQI") || file.dir)) countThisUserFille ++;
		}
		if (countThisUserFille / 3 > 0) res.quarantineDirs.push_back(qDir);
	}
	// подщет файлов в карантине
	int countSysQuarantineFille = 0;
	int countUserQuarantineFille = 0;
	for (auto file: sysList.list) {
		if (!(compareInSring(file.str, "INFO.NQI") || file.dir)) countSysQuarantineFille ++;
	}
	for (auto file: userList.list) {
		if (!(compareInSring(file.str, "INFO.NQI") || file.dir)) countUserQuarantineFille ++;
	}
	res.countSys = countSysQuarantineFille / 3;
	res.countUser = countUserQuarantineFille / 3;
	res.countTotal = res.countSys + res.countUser;
	res.bad = res.countTotal > 0;
	if (res.countSys > 0) res.quarantineDirs.insert(res.quarantineDirs.begin(), dirSysQuarantine);
	return res;
}
DefectionResult computeDefection() {
	DefectionResult res;
	res.soft = computeSoftDefection();
	res.users = computeUsersDefection();
	res.eset = computeEsetDefection();
	return res;
}
// ---------------------------------------------------------------------------
// "Лёгкие" части - только запись в Form1, вызывать исключительно из главного
// потока (внутри Synchronize, если исходный вызов идёт из Th_Gruber).
// ---------------------------------------------------------------------------
void applySoftDefection(const SoftDefectionResult &r) {
	Form1->Memo1->Clear();
	if (r.lines.empty()) Form1->Memo1->Lines->Add("Не знайдено!");
	else for(auto str: r.lines) Form1->Memo1->Lines->Add(str);
	curDefection.soft = r.bad;
	setReadOnlyCheckBox(Form1->CheckBox_installAvpzESET, r.esetInstalled);
	setReadOnlyCheckBox(Form1->CheckBox_installAvpzRDsensor, r.rdSensorInstalled);
	setReadOnlyCheckBox(Form1->CheckBox_installAvpzTRELIX, r.trellixInstalled);
}
void applyUsersDefection(const UsersDefectionResult &r) {
	TStringGrid *grid = Form1->Grid_Users;
	curDefection.users = r.users; // потрібен у Grid_UsersDrawCell для підсвітки старого пароля
	if (r.users.empty()) {
		grid->RowCount = 2;
		grid->Rows[1]->Clear();
		grid->Cells[1][1] = "Нема юзерів... О_о";
	} else {
		grid->RowCount = (int)r.users.size() + 1;
		int row = 1;
		for (auto &user: r.users) {
			UnicodeString priv = "Юзер";
			if (user.priv == "ADMIN") priv = "Адмін";
			else if (user.priv == "GUEST") priv = "Гість";
			grid->Cells[0][row] = priv;
			grid->Cells[1][row] = user.name;
			grid->Cells[2][row] = user.fullName;
			grid->Cells[3][row] = UnicodeString(user.password_age);
			if (user.last_logon == 0) {
				grid->Cells[4][row] = "ніколи";
			} else {
				TDateTime lastLogonDate = System::Dateutils::UnixToDateTime(user.last_logon, false);
				grid->Cells[4][row] = lastLogonDate.FormatString("dd.MM.yy HH:mm");
			}
			grid->Cells[5][row] = user.accountType;
			row++;
		}
		curDefection.user = r.bad;
	}
}
// === підсвітка рядків таблиці юзерів: старий пароль (>42 днів) у не-адмінів - блідо-оранжевим
void __fastcall TForm1::Grid_UsersDrawCell(TObject *Sender, int ACol, int ARow, const TRect &Rect, TGridDrawState State)
{
	TStringGrid *grid = (TStringGrid *)Sender;
	bool warnAge = false;
	if (ARow > 0 && ACol == 3) {
		size_t dataIdx = (size_t)(ARow - 1);
		if (dataIdx < curDefection.users.size()) {
			const User &u = curDefection.users[dataIdx];
			warnAge = u.password_age > 42 && u.priv != "ADMIN";
		}
	}
	grid->Canvas->Font->Style = TFontStyles(); // Canvas спільний для всіх клітинок - стиль треба скидати щоразу
	if (State.Contains(gdSelected)) {
		grid->Canvas->Brush->Color = clHighlight;
		grid->Canvas->Font->Color = clHighlightText;
	} else if (ARow == 0) {
		grid->Canvas->Brush->Color = clBtnFace;
		grid->Canvas->Font->Color = clWindowText;
	} else if (warnAge) {
		grid->Canvas->Brush->Color = (TColor)0x00B2E0FF; // блідо-оранжевий
		grid->Canvas->Font->Color  = (TColor)0x00334065; // темно-коричневий
	} else {
		grid->Canvas->Brush->Color = clWindow;
		grid->Canvas->Font->Color = clWindowText;
	}
	grid->Canvas->FillRect(Rect);
	UnicodeString text = grid->Cells[ACol][ARow];
	int textTop = Rect.Top + (Rect.Height() - grid->Canvas->TextHeight(text)) / 2;
	grid->Canvas->TextOut(Rect.Left + 4, textTop, text);
}
void applyEsetDefection(const EsetDefectionResult &r) {
	if (r.countTotal > 0) {
		Form1->Show_ESETQuarantine->Text = UnicodeString(r.countTotal);
		UnicodeString str = "В системі " + UnicodeString(r.countSys)
			+ ", у користувачів " + UnicodeString(r.countUser) + "...";
		Form1->Show_ESETQuarantine->Hint = str;
	} else {
		Form1->Show_ESETQuarantine->Text = "0";
		Form1->Show_ESETQuarantine->Hint = "Карантин порожній!";
	}
	curDefection.eset = r.bad;
	curDefection.quarantineDirs = r.quarantineDirs;
	Form1->Button_OpenQuarantine->Enabled = !r.quarantineDirs.empty();
}
void applyDefectionLabels(const DefectionResult &r) {
	applySoftDefection(r.soft);
	applyUsersDefection(r.users);
	applyEsetDefection(r.eset);
	Form1->PageControl_InfoTabs->Pages[1]->Caption = u"Перевірки"; // \uE10A(B) - все норм
	if (curDefection.soft || curDefection.user || curDefection.eset) {
//		short i = curDefection.soft + curDefection.user + curDefection.eset;
		Form1->PageControl_InfoTabs->Pages[1]->Caption = u"\uE10AПеревірки\uE10A"; // \uE10A(B) - все норм
	}
	if (curDefection.soft) {
		Form1->Label_DefectionSoft->Font->Color = (TColor)clRed;
		Form1->Label_DefectionSoft->Font->Style = TFontStyles() << fsBold;
	} else {
		Form1->Label_DefectionSoft->Font->Color = (TColor)clWindowText;
		Form1->Label_DefectionSoft->Font->Style = TFontStyles() >> fsBold;
	}
	if (curDefection.user) {
		Form1->Label_DefectionUser->Font->Color = (TColor)clRed;
		Form1->Label_DefectionUser->Font->Style = TFontStyles() << fsBold;
	}else {
		Form1->Label_DefectionUser->Font->Color = (TColor)clWindowText;
		Form1->Label_DefectionUser->Font->Style = TFontStyles() >> fsBold;
	}
	if (curDefection.eset) {
		Form1->Label_checkQuarantineEset_1->Font->Color = (TColor)clRed;
		Form1->Label_checkQuarantineEset_1->Font->Style = TFontStyles() << fsBold;
	}else {
		Form1->Label_checkQuarantineEset_1->Font->Color = (TColor)clWindowText;
		Form1->Label_checkQuarantineEset_1->Font->Style = TFontStyles() >> fsBold;
	}
}
// ---------------------------------------------------------------------------
// Обёртки "compute+apply вместе" - оставлены для существующих мест вызова
// из главного потока (конструктор формы, обработчик кнопки). Никого не ломают.
// ---------------------------------------------------------------------------
void showSoft() {
	applySoftDefection(computeSoftDefection());
}
void showUsers() {
	applyUsersDefection(computeUsersDefection());
}
void checkEsetQuarantine() {
	applyEsetDefection(computeEsetDefection());
}
void checkDefection() {
	applyDefectionLabels(computeDefection());
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Randomize(); // для generateStructureId()
	PageControl_SetInfo->TabIndex = 0;
	PageControl_InfoTabs->TabIndex = 0;
	// === заголовки таблиці юзерів (Grid_Users)
	Grid_Users->Cells[0][0] = "Права";
	Grid_Users->Cells[1][0] = "Логін";
	Grid_Users->Cells[2][0] = "ПІБ";
	Grid_Users->Cells[3][0] = "Вік пароля";
	Grid_Users->Cells[4][0] = "Дата входу";
	Grid_Users->Cells[5][0] = "Тип";
	// підв'язано кодом, а не через .dfm, - див. коментар біля оголошення в MainForm.h
	Grid_Users->OnDrawCell = Grid_UsersDrawCell;
	OnAfterMonitorDpiChanged = Form1AfterMonitorDpiChanged;
	captureGridUsersDpiBaseline();
	applyGridUsersDpiScale();
	fs::path p_curDir = fs::current_path();
	// === запуск правильной разрядности
	if (x64_sys() == true && x64_app() == false) {
		fs::path p_app_x64 = p_curDir / "GRUBer.exe";
		if(exists(p_app_x64)) {
			ShellExecuteW(NULL, L"open", p_app_x64.c_str(), NULL, NULL, SW_SHOWDEFAULT);
			exit(1);
		}
	}
}
//---------------------------------------------------------------------------
// Виконується після того, як усі форми застосунку вже створені
// (Application->CreateForm у GRUBer.cpp) - на відміну від конструктора,
// тут безпечно звертатися до інших форм (FormStructurePick), бо в
// конструкторі Form1 (перша форма, що створюється) вони ще не існують.
void __fastcall TForm1::FormShow(TObject *Sender)
{
	if (gruberStart) return; // весь блок нижче - одноразова ініціалізація при старті
	fs::path p_configIni = fs::current_path() / "GRUBer.ini";
    // === нові структури, знайдені на ПК (запит "додати структуру?" - до
	// заповнення комбобоксів, щоб нова структура одразу в них потрапила)
	{
		std::vector<StructurePcData> unknown = findUnknownStructures(curPC, curConfig);
		bool configChanged = false;
		for (auto &u : unknown) {
			UnicodeString text = L"На цьому ПК знайдено невідому структуру \"" + u.name +
				L"\". Додати її до списку структур програми?";
			if (Application->MessageBox(text.c_str(), L"Невідома структура", MB_YESNO) == IDYES) {
				StructureDef def;
				def.id = u.id;
				def.name = u.name;
				def.partition = vStrGenFromStr(u.partition);
				auto structs = curConfig.get_structures();
				structs.push_back(def);
				curConfig.set_structures(structs);
				configChanged = true;
			}
		}
		if (configChanged) curConfig.saveFileIni();
	}
    // === выводим настройки & сохраненую инфу об АРМ
	setConfigToForm(curConfig);
	setInfoArmToForm(curPC);
	printLogDebug("{SYS-x64} = " + UnicodeString(x64_sys()));
	printLogDebug("{APP-x64} = " + UnicodeString(x64_app()));
	// === проверка на необходимые файлы и папки
	if(exists(p_configIni)) printLogDebug("Config fille OK");
	else {
		UnicodeString text = "Немає файла налаштувань...";
		UnicodeString formCaption = "Де файл?!";
		if(Application->MessageBox( text.c_str(), formCaption.c_str(), MB_OK) == IDOK) {
			exit(0);
		}
	}
	/* === проверка прав админа === */
	UnicodeString admMode;
	if(IsAdminMode()) {
		printLogDebug("Запущено з правами Адміністратора!");
		Button_RestartAssAdmin->Enabled = false;
		BtnClearPC->Enabled = true;
		admMode = "AdminMode";
	} else {
		printLogDebug("Запущено без прав Адміністратора!");
		int number = Form1->Edit_NumberARM->Value;
		UnicodeString text = "Перезапустити GRUBer з правами Адміністратора?\n( ПК: "
			+ UnicodeString(number)
			+ ", Відділ.: " + UnicodeString(curPC.getPartition()) + " )";
		UnicodeString formCaption = "Нема прав Адміна.. :'(";
		if(Application->MessageBox( text.c_str(), formCaption.c_str(), MB_YESNO) == IDYES) {
				RestartApplicationRunas();
		}
		admMode = "UserMode";
	}
    // === запит на перезбереження GRUBer.ini у новому форматі, якщо файл ще
	// застарілої версії (ini_version=0/відсутній) - навмисно після запиту на
	// перезапуск від адміна, а не до нього
	if (curConfig.get_iniVersion() == 0) {
		UnicodeString text = L"Файл налаштувань (GRUBer.ini) збережено застарілим форматом.\n"
			L"Перезберегти його у новому форматі?";
		if (Application->MessageBox(text.c_str(), L"Застарілий формат налаштувань", MB_YESNO) == IDYES) {
			curConfig.saveFileIni();
		}
	}
    // === міграція старих даних структур (запит - до якої структури віднести
	// відділ/місце/телефон з попередньої версії) - навмисно після запиту на
	// перезапуск від адміна, а не до нього
	if (curPC.needsLegacyMigrationPrompt()) {
		UnicodeString pickedId = FormStructurePick->ShowPick(
			L"Знайдено застарілі дані (відділ/місце/телефон) з попередньої версії. "
			L"До якої структури їх віднести?");
		UnicodeString pickedName;
		for (auto &s : curConfig.get_structures()) if (s.id == pickedId) { pickedName = s.name; break; }
		if (!pickedId.IsEmpty()) curPC.applyPendingLegacyMigration(pickedId, pickedName);
		else curPC.clearPendingLegacyMigration();
		infoSetToFille(curPC);
		// оновлюємо поля вкладки "Інфо" - міграція могла змінити дані
		// структури, що зараз показана в ComboBox_CurStructur
		applyCurStructureSelectionToForm(getCurStructureId());
	}
	/* === наполняем форму === */
	printLog(">>", "Запушенно GRUBer v." + versionApp);
	printLog(">>", "Останій граб: " + curPC.lastGrub());
	// --- проверка нарушений
	checkDefection();
	// --- заполняем строку с именем папки граба
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
	if (DirectoryExists(curDir.get_grubPath())) {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x006E00;
		Form1->EditDirGrubName->Color = (TColor) 0xEAFFEA;
	} else {
		Form1->EditDirGrubName->Font->Color = (TColor) 0x00006E;
		Form1->EditDirGrubName->Color = (TColor) 0xEAEAFF;
	}
	// --- статус бар
	if (x64_app()) StatusBar1->Panels->Items[2]->Text = "v." + versionApp + " (x64_" + admMode + ") ";
	else StatusBar1->Panels->Items[2]->Text = "v." + versionApp + " (x32_" + admMode + ") ";
	gruberStart = 1;
	captureGridPanelDpiBaselines();
}
//---------------------------------------------------------------------------
/* КНОПКИ */
// === запуск Граба
void __fastcall TForm1::BtnGruberRunClick(TObject *Sender)
{
	if (th_Gruber_run == false) {
		checkDirExist = true;
		th_Gruber_runMini = false; th_Gruber_runUSB=false;
		Th_Gruber *Thr = new Th_Gruber(true);
		Thr->Resume();
	}
}
void __fastcall TForm1::Gruber_MiniClick(TObject *Sender)
{
	//запускаем граб
	if (th_Gruber_run == false) {
		checkDirExist = false;
		th_Gruber_runMini = true; th_Gruber_runUSB=false;
		Th_Gruber *Thr = new Th_Gruber(true);
		Thr->Resume();
	}
}
void __fastcall TForm1::Gruber_USBClick(TObject *Sender)
{
	//запускаем граб
	if (th_Gruber_run == false) {
		checkDirExist = false;
		th_Gruber_runMini = false; th_Gruber_runUSB=true;
		Th_Gruber *Thr = new Th_Gruber(true);
		Thr->Resume();
	}
}
// === открыть редактор структур
void __fastcall TForm1::BtnEditStructuresClick(TObject *Sender)
{
	FormStructures->loadStructures();
	FormStructures->ShowModal();
}
// === открыть папку Граба
void __fastcall TForm1::BtnGruberDirOpenClick(TObject *Sender)
{
	ShellExecuteW(NULL, L"open", curDir.get_grubPath().c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// === открыть папку логов ESET Management Agent
void __fastcall TForm1::Button_EsetLogsDirClick(TObject *Sender)
{
	ShellExecuteW(NULL, L"open", getEsetLogsDir().c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// === показати вміст карантину ESET у власному вікні GRUBer.
// Відкрити теку карантину в Провіднику виявилося неможливим (профіль SYSTEM,
// і навіть штатне "Продовжити" в Провіднику відмовляє - див. історію вище в
// git log цього файлу) - тому замість Провідника показуємо список файлів
// напряму, тим самим FindFirstFile/scanDirToFille, яким GRUBer і так читає цю
// теку для підрахунку кількості (computeEsetDefection) без жодних проблем.
void __fastcall TForm1::Button_OpenQuarantineClick(TObject *Sender)
{
	FormQuarantine->loadDirs(curDefection.quarantineDirs);
	FormQuarantine->ShowModal();
	checkEsetQuarantine(); // оновити лічильники/кнопку на головній формі, якщо щось видалили
}
// === остановка Граба
// --- полная
void __fastcall TForm1::BtnGruberStopClick(TObject *Sender)
{
	stopBool = true;
}
// --- частичная
void __fastcall TForm1::РassClick(TObject *Sender)
{
	passBool = true;
}
// === сохранение настроек
void __fastcall TForm1::BtnSaveSetteingsClick(TObject *Sender)
{
	curConfig.saveFileIni();
}
// === запуск парсера
void __fastcall TForm1::BtnDevListerOpenClick(TObject *Sender)
{
	UnicodeString setApp = GetCurrentDir() + "\\DeviceLister.exe";
	short t_cat;
	if (curPC.getCategoryID() == 0) t_cat = 0;
	if (curPC.getCategoryID() >= 1 && curPC.getCategoryID() <= 3) t_cat = 1;
	if (curPC.getCategoryID() == 4) t_cat = 2;
	if (curPC.getCategoryID() == 5) t_cat = 3;
	if (curPC.getCategoryID() == 6) t_cat = 4;
	UnicodeString setArg = "-cat " + String(t_cat);
	ShellExecuteW(NULL, L"open", setApp.c_str(), setArg.c_str(), NULL, SW_SHOWDEFAULT);
}
// === провека лицензий
void __fastcall TForm1::BtnLicenseClick(TObject *Sender)
{
	UnicodeString setApp = curDir.get_toolPath() + "\\CheckActivationStatus\\CheckActivationStatus.exe";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// === общее инфо
void __fastcall TForm1::BtnInfoClick(TObject *Sender)
{
	UnicodeString setApp = curDir.get_toolPath() + "\\scripts\\info_ps1\\Run.bat";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// === about form
void __fastcall TForm1::BtnAboutGruberClick(TObject *Sender)
{
	FormAbout->Position = (TPosition)7;
	FormAbout->ShowModal();
}
// === очистка временых файлов
void __fastcall TForm1::BtnClearPCClick(TObject *Sender)
{
	FormClearTempDir->Position = (TPosition)7;
	FormClearTempDir->ShowModal();
}
// === перезапуск от админа
void __fastcall TForm1::Button_RestartAssAdminClick(TObject *Sender)
{
	RestartApplicationRunas();
}
//---------------------------------------------------------------------------
/* Обновление ESET */
void __fastcall TForm1::BtnEditEsetMirrorDirClick(TObject *Sender)
{
	DirOpenEsetMirror->DefaultFolder = EditEsetMirrorDir->Text;
	DirOpenEsetMirror->Execute();
}
void __fastcall TForm1::DirOpenEsetMirrorFileOkClick(TObject *Sender, bool &CanClose)
{
	EditEsetMirrorDir->Text = DirOpenEsetMirror->FileName;
}
void __fastcall TForm1::CheckBox_ShowEsetUpdateClick(TObject *Sender)
{
	curConfig.setShowEsetUpd(CheckBox_ShowEsetUpdate->Checked);
}
void __fastcall TForm1::BtnEsetUpdateClick(TObject *Sender)
{
	bool oldUPDarch = 0; // 0-old 1-new
	//UnicodeString archUpd;
	const fs::path curDirectory = fs::current_path();
	const fs::path updArhOld = curDirectory / L"update.7z";
	const fs::path updArhZIPx32 =  curDirectory / L"update_x32.zip";
	const fs::path updArhZIPx64 =  curDirectory / L"update_x64.zip";
	const fs::path updArhZSTDx32 = curDirectory / L"update_x32.tar.zstd";
	const fs::path updArhZSTDx64 = curDirectory / L"update_x64.tar.zstd";
	const fs::path esetUpdDir = curPC.getEsetDir().c_str();
	fs::path updArhive;
	bool zstd = false;

	if (fs::exists(updArhZSTDx32) || fs::exists(updArhZSTDx64)) {
		if (x64_sys()) updArhive = updArhZSTDx64;
		else updArhive = updArhZSTDx32;
		zstd = true;
	} else if (fs::exists(updArhZIPx32) || fs::exists(updArhZIPx64)) {
		if (x64_sys()) updArhive = updArhZIPx64;
		else updArhive = updArhZIPx32;
	} else if (fs::exists(updArhOld)) {
		updArhive = updArhOld;
	} else {
		printLog("!!", "ESET-Update: Немає архіву з базами! " + UnicodeString(curDirectory.c_str()));
		return;
    }
    if (!fs::exists(updArhive)) {
		printLog("!!", "ESET-Update: Немає архіву з базами! " + UnicodeString(curDirectory.c_str()));
		return;
	}
	printLog(">>", "ESET-Update: Оновленя бази Eset...");
	BtnEsetUpdate->Enabled = false;
	StatusBar1->Panels->Items[1]->Text = " Оновленя бази Eset...";
	// теку дзеркала могли раніше створити під іншим рівнем прав (адмін/юзер) -
	// перевіряємо доступ ДО розпакування, інакше 7-Zip впирається в
	// ACCESS_DENIED і зависає на власному діалозі помилки (RunApp чекає завершення
	// процесу без таймауту)
	UnicodeString esetUpdDirStr = esetUpdDir.wstring().c_str();
	ensureDirWithAccess(esetUpdDirStr);
	if (!warnIfNoAccess(esetUpdDirStr)) {
		BtnEsetUpdate->Enabled = true;
		StatusBar1->Panels->Items[1]->Text = " Немає доступу до теки ESET mirror!";
		return;
	}
	if (fs::exists(esetUpdDir / L"dll\\update.ver"))
		if(fs::remove_all(esetUpdDir)) ensureDirWithAccess(esetUpdDirStr);
	//запуск обновления
	UnicodeString app32 = curDir.get_toolPath() + "\\7zip\\32\\7za.exe";
	UnicodeString app64 = curDir.get_toolPath() + "\\7zip\\64\\7za.exe";
	UnicodeString updArh = updArhive.wstring().c_str();
	UnicodeString updDir = esetUpdDir.wstring().c_str();
	UnicodeString arg = "x -y \"" + updArh + "\" -o\"" + updDir + "\"";
	if (curConfig.getShowEsetUpd()) app32 = curDir.get_toolPath() + "\\7zip\\32\\7zG.exe";
	if (curConfig.getShowEsetUpd()) app64 = curDir.get_toolPath() + "\\7zip\\64\\7zG.exe";
	RunApp esetBaseUnpack { app32, app64, arg };
	esetBaseUnpack.run(!curConfig.getShowEsetUpd());
	if(zstd) {
		fs::path tar = esetUpdDir / updArhive.filename().replace_extension("");
		updArh = tar.wstring().c_str();
		arg = "x -y \"" + updArh + "\" -o\"" + updDir + "\"";
		//printLog("**", "{ESET-arg}=" + arg);
		RunApp esetBaseTarUnpack { app32, app64, arg };
		esetBaseTarUnpack.run(!curConfig.getShowEsetUpd());
		fs::remove(tar);
	}
	//------
	if (esetBaseUnpack.checkErr()){
		//ошибочка вышла...
		printLog("!!", "ESET-Update: Щось пішло НЕ так...");
		BtnEsetUpdate->Enabled = true;
		return;
	}
	printLog("OK", "ESET-Update: Бази оновленно!");
    BtnEsetUpdate->Enabled = true;
	StatusBar1->Panels->Items[1]->Text = " Бази оновленно!";
	if (FileExists("c:\\Program Files\\ESET\\ESET Security\\ermm.exe")) {
		RunApp esetBaseUpdate {"c:\\Program Files\\ESET\\ESET Security\\ermm.exe",
			NULL, "start update"};
		esetBaseUpdate.run();
	}
}
//---------------------------------------------------------------------------
/* Изменение полей */
UnicodeString __fastcall TForm1::getCurStructureId()
{
	int i = ComboBox_CurStructur->ItemIndex;
	if (i < 0 || i >= (int)curStructureComboIds.size()) return "";
	return curStructureComboIds[i];
}
void __fastcall TForm1::Edit_NumberARMChange(TObject *Sender)
{
	UnicodeString id = getCurStructureId();
	if (!id.IsEmpty())
		curPC.setStructureNumber(id, ComboBox_CurStructur->Text, Edit_NumberARM->Value);
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
}
void __fastcall TForm1::EditPartitionChange(TObject *Sender)
{
	// "Без відділу" - лише UI-заглушка за замовчуванням, у файли пишемо
	// порожнє значення замість неї
	UnicodeString saveVal = (EditPartition->Text == "Без відділу") ? UnicodeString("") : EditPartition->Text;
	curPC.setPartition(saveVal); // плоске дзеркало - для dirGrubName() та підказки про права адміна
	UnicodeString id = getCurStructureId();
	if (!id.IsEmpty())
		curPC.setStructurePartition(id, ComboBox_CurStructur->Text, saveVal);
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
	bool knownPartition = EditPartition->Items->IndexOf(EditPartition->Text) >= 0;
	EditPartition->Color = knownPartition ? clWindow : (TColor)0x00D0D0FF; // блідо-червоний, якщо значення не обране зі списку
}
void __fastcall TForm1::EditArmClassChange(TObject *Sender)
{
	curPC.setClass(EditArmClass->Text, EditArmClass->ItemIndex);
    checkDefection();
}
void __fastcall TForm1::EditCategoryChange(TObject *Sender)
{
	short indx = EditCategory->ItemIndex;
	curPC.setCategory(EditCategory->Items->Strings[indx], indx);
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
	curPC.setClass(EditArmClass->Text, EditArmClass->ItemIndex);
    checkDefection();
}
void __fastcall TForm1::EditResponChange(TObject *Sender)
{
	curPC.setRespon(EditRespon->Text);
}
void __fastcall TForm1::EditPurposeChange(TObject *Sender)
{
	curPC.setPurpose(EditPurpose->Text);
}
void __fastcall TForm1::Edit_PlaceChange(TObject *Sender) // <===
{
	curPC.setPlace(Edit_Place->Text); // плоске дзеркало
	UnicodeString id = getCurStructureId();
	if (!id.IsEmpty())
		curPC.setStructurePlace(id, ComboBox_CurStructur->Text, Edit_Place->Text);
}
void __fastcall TForm1::Edit_PhoneChange(TObject *Sender) // <===
{
	curPC.setPhone(Edit_Phone->Text); // плоске дзеркало
	UnicodeString id = getCurStructureId();
	if (!id.IsEmpty())
		curPC.setStructurePhone(id, ComboBox_CurStructur->Text, Edit_Phone->Text);
}
void __fastcall TForm1::EditLicWinChange(TObject *Sender)
{
	curPC.setLicWindows(EditLicWin->Text, EditLicWin->ItemIndex);
}
void __fastcall TForm1::EditLicOfficeChange(TObject *Sender)
{
	curPC.setLicOffice(EditLicOffice->Text, EditLicOffice->ItemIndex);
}
void __fastcall TForm1::EditComentChange(TObject *Sender)
{
	std::vector<UnicodeString> vStr;
	for (auto i : Form1->EditComent->Lines) {
		vStr.push_back(i);
	}
	curPC.setComent(vStr);
}
void __fastcall TForm1::EditComentDblClick(TObject *Sender)
{
	FormComent->EditComent->Lines = Form1->EditComent->Lines;
	FormComent->ShowModal();
}
void __fastcall TForm1::EditDirGrubNameChange(TObject *Sender)
{
	UnicodeString dirGrub = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
	UnicodeString dirEdit = EditDirGrubName->Text;
	if (dirGrub != dirEdit) curDir.set_grubPath(dirEdit);
	else curDir.set_grubPath(dirGrub);
	changeEditDirColor(); //смена заливки поля "папки граба" и активация кнопок
}
void __fastcall TForm1::EditGrubUserChange(TObject *Sender)
{
	curConfig.setUser(Form1->EditGrubUser->Text);
}
void __fastcall TForm1::EditEsetMirrorDirChange(TObject *Sender)
{
	curPC.setEsetDir(Form1->EditEsetMirrorDir->Text);
	if(gruberStart) infoSetToFille(curPC);
}
/* Изменение полей на GRUBer+*/
void __fastcall TForm1::Edit_InNumberARMChange(TObject *Sender)
{
	curPC.setInNumberARM(Edit_InNumberARM->Text);
}
void __fastcall TForm1::Edit_InNumberHDDChange(TObject *Sender)
{
	curPC.setInNumberHDD(Edit_InNumberHDD->Text);
}
void __fastcall TForm1::Edit_InNumberDeclrChange(TObject *Sender)
{
	curPC.setInNumberDeclr(Edit_InNumberDeclr->Text);
}
void __fastcall TForm1::Edit_InNumberFormulyarChange(TObject *Sender)
{
	curPC.setInNumberFormulyar(Edit_InNumberFormulyar->Text);
}
void __fastcall TForm1::Edit_InNumberWorkChange(TObject *Sender)
{
	curPC.setInNumberWork(Edit_InNumberWork->Text);
}
void __fastcall TForm1::Edit_InNumberPersonChange(TObject *Sender)
{
	curPC.setInNumberPerson(Edit_InNumberPerson->Text);
}
void __fastcall TForm1::Edit_InResponChange(TObject *Sender) // <===
{
	curPC.setInRespon(Edit_InRespon->Text);
}
void __fastcall TForm1::Edit_InAdminBPChange(TObject *Sender) // <===
{
	curPC.setInAdminBP(Edit_InAdminBP->Text);
}
// -----
void __fastcall TForm1::ComboBox_PoliticInstallChange(TObject *Sender)
{
	curPC.set_lgpo(ComboBox_PoliticInstall->Text);
}
void __fastcall TForm1::ComboBox_ContrUSBChange(TObject *Sender)
{
	curPC.set_controlUSB(ComboBox_ContrUSB->Text);
}
void __fastcall TForm1::ComboBox_MultiUSERSChange(TObject *Sender)
{
	curPC.set_multiUser(ComboBox_MultiUSERS->Text);
}
// -----
void __fastcall TForm1::ShowSerialGenarateDblClick(TObject *Sender)
{
	Form_Serial->Edit1->Text = curPC.getSerialMain();
	Form_Serial->Edit2->Text = curPC.getUUID();
	Form_Serial->Edit3->Text = curPC.getSerial_mrb();
	Form_Serial->Edit4->Text = curPC.getCPUID();
	// генерация уникального серийника
	Form_Serial->Edit5->Text = curPC.getUnSerial();
	//Form_Serial->Edit5->Text = "test";
	// открытие окна с серийниками
	Form_Serial->Position = (TPosition)7;
	Form_Serial->ShowModal();
}
//---------------------------------------------------------------------------
/* Чекбоксы в настройках */
void __fastcall TForm1::CheckBoxDebugClick(TObject *Sender)
{
	curConfig.setDebug(CheckBoxDebug->Checked);
}
void __fastcall TForm1::CheckBox_TempDirClick(TObject *Sender)
{
	curConfig.setTempDir(CheckBox_TempDir->Checked);
}
void __fastcall TForm1::CheckBoxAuditClick(TObject *Sender)
{
	// 0 - off, 1 - full, 2 - mini
	curConfig.setAudit(CheckBoxAudit->State);
}
void __fastcall TForm1::CheckBoxEsetLogClick(TObject *Sender)
{
	// 0 - off, 1 - full, 2 - mini
	curConfig.setEsetLog(CheckBoxEsetLog->State);
}
void __fastcall TForm1::CheckBoxOldGrubClick(TObject *Sender)
{
	// 0 - off, 1 - full, 2 - mini
	curConfig.setOldGrub(CheckBoxOldGrub->State);
	if (CheckBoxOldGrub->State!=2) {
		if (curConfig.getOldGrub()==0) {
			if (ComentTxt->Checked) {ComentTxt->Checked = 0; curConfig.setOldGrubComent(ComentTxt->Checked);}
			if (InfoTxt->Checked) {InfoTxt->Checked = 0; curConfig.setOldGrubInfo(InfoTxt->Checked);}
			if (NetTxt->Checked) {NetTxt->Checked = 0; curConfig.setOldGrubNet(NetTxt->Checked);}
			if (UsbTxt->Checked) {UsbTxt->Checked = 0; curConfig.setOldGrubUsb(UsbTxt->Checked);}
		}
		if (curConfig.getOldGrub()==1) {
			if (!ComentTxt->Checked) {ComentTxt->Checked = 1; curConfig.setOldGrubComent(ComentTxt->Checked);}
			if (!InfoTxt->Checked) {InfoTxt->Checked = 1; curConfig.setOldGrubInfo(InfoTxt->Checked);}
			if (!NetTxt->Checked) {NetTxt->Checked = 1; curConfig.setOldGrubNet(NetTxt->Checked);}
			if (!UsbTxt->Checked) {UsbTxt->Checked = 1; curConfig.setOldGrubUsb(UsbTxt->Checked);}
		}
	}
}
void __fastcall TForm1::ComentTxtClick(TObject *Sender)
{
	ComentTxt->Checked = !ComentTxt->Checked;
	curConfig.setOldGrubComent(ComentTxt->Checked);
	CheckBoxOldGrub->State = (TCheckBoxState)curConfig.checkOldGrubState();
}
void __fastcall TForm1::InfoTxtClick(TObject *Sender)
{
	InfoTxt->Checked = !InfoTxt->Checked;
	curConfig.setOldGrubInfo(InfoTxt->Checked);
	CheckBoxOldGrub->State = (TCheckBoxState)curConfig.checkOldGrubState();
}
void __fastcall TForm1::NetTxtClick(TObject *Sender)
{
	NetTxt->Checked = !NetTxt->Checked;
	curConfig.setOldGrubNet(NetTxt->Checked);
	CheckBoxOldGrub->State = (TCheckBoxState)curConfig.checkOldGrubState();
}
void __fastcall TForm1::UsbTxtClick(TObject *Sender)
{
	UsbTxt->Checked = !UsbTxt->Checked;
	curConfig.setOldGrubUsb(UsbTxt->Checked);
	CheckBoxOldGrub->State = (TCheckBoxState)curConfig.checkOldGrubState();
}
void __fastcall TForm1::CheckBoxNewGrubClick(TObject *Sender)
{
	curConfig.setNewGrub(CheckBoxNewGrub->Checked);
}
void __fastcall TForm1::CheckBoxLicenseClick(TObject *Sender)
{
	curConfig.setLicense(CheckBoxLicense->Checked);
}
void __fastcall TForm1::CheckBoxEsetAutoUpdateClick(TObject *Sender)
{
	bool i = Form1->CheckBoxEsetAutoUpdate->Checked;
	if(Form1->CheckBoxEsetAutoUpdate->Checked)
		StatusBar1->Panels->Items[1]->Text = " ESET оновлюеться самостійно";
	else StatusBar1->Panels->Items[1]->Text = " Бази не оновлювалися";
	Form1->EditEsetMirrorDir->Enabled = !i;
	Form1->BtnEditEsetMirrorDir->Enabled = !i;
	Form1->BtnEsetUpdate->Enabled = !i;
	curPC.setEsetAutoUpdate(i);
	if(gruberStart) infoSetToFille(curPC);
}
void __fastcall TForm1::ComboBox_DefStructurChange(TObject *Sender)
{
	int i = ComboBox_DefStructur->ItemIndex;
	if (i < 0 || i >= (int)defStructureComboIds.size()) return;
	// не перемикає ComboBox_CurStructur/поля вкладки "Інфо" - нова структура за
	// замовчуванням застосується лише при наступному запуску програми
	curConfig.set_defaultStructureId(defStructureComboIds[i]);
}
void __fastcall TForm1::ComboBox_CurStructurChange(TObject *Sender)
{
	applyCurStructureSelectionToForm(getCurStructureId());
}
//---------------------------------------------------------------------------
/* Запуск ПО */
// INFO
void __fastcall TForm1::BtnApp_HWiNFOClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64_sys()) setApp = curDir.get_toolPath() + "\\HWiNFO\\HWiNFO64.exe";
	else setApp = curDir.get_toolPath() + "\\HWiNFO\\HWiNFO32.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_CPUZClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64_sys()) setApp = curDir.get_toolPath() + "\\CPU-Z\\cpuz_x64.exe";
	else setApp = curDir.get_toolPath() + "\\CPU-Z\\cpuz_x32.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_GPUZClick(TObject *Sender)
{
	LPCWSTR oper = L"open";
	UnicodeString setApp = curDir.get_toolPath() + "\\GPU-Z\\GPU-Z.2.60.0.exe";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_procexpClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64_sys()) setApp = curDir.get_toolPath() + "\\SysinternalsSuite\\procexp64.exe";
	else setApp = curDir.get_toolPath() + "\\SysinternalsSuite\\procexp.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_autorunsClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64_sys()) setApp = curDir.get_toolPath() + "\\SysinternalsSuite\\Autoruns64.exe";
	else setApp = curDir.get_toolPath() + "\\SysinternalsSuite\\Autoruns.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_tcpviewClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64_sys()) setApp = curDir.get_toolPath() + "\\SysinternalsSuite\\tcpview64.exe";
	else setApp = curDir.get_toolPath() + "\\SysinternalsSuite\\tcpview.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// File system
void __fastcall TForm1::BtnApp_TotalClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64_sys()) setApp = curDir.get_toolPath() + "\\totalcmd\\TOTALCMD64.EXE";
	else setApp = curDir.get_toolPath() + "\\totalcmd\\TOTALCMD.EXE";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_EverythingClick(TObject *Sender)
{
	UnicodeString setApp = curDir.get_toolPath() + "\\Everything\\Everything.exe";
	ShellExecuteW(NULL, L"open", setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
//
void __fastcall TForm1::BtnApp_UscDevUClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64_sys()) setApp = curDir.get_toolPath() + "\\USBDeview\\USBDeview_x64.exe";
	else setApp = curDir.get_toolPath() + "\\USBDeview\\USBDeview_x32.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_DeviceCleanupClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64_sys()) setApp = curDir.get_toolPath() + "\\DeviceCleanup\\x64\\DeviceCleanup.exe";
	else setApp = curDir.get_toolPath() + "\\DeviceCleanup\\Win32\\DeviceCleanup.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::BtnApp_UsbTreeViewClick(TObject *Sender)
{
	UnicodeString setApp;
	LPCWSTR oper = L"open";
	if (x64_sys()) setApp = curDir.get_toolPath() + "\\UsbTreeView\\x64\\UsbTreeView.exe";
	else setApp = curDir.get_toolPath() + "\\UsbTreeView\\UsbTreeView.exe";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
// --- запуск консоли
void __fastcall TForm1::BtnKiberConsolOpenClick(TObject *Sender)
{
    LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = curDir.get_toolPath() + "\\KiberConsole.msc";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_ControlPanelClick(TObject *Sender)
{
	LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "control.exe";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_setingsPCClick(TObject *Sender)
{
    LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "sysdm.cpl";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_msconfigClick(TObject *Sender)
{
    LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "msconfig.exe";
	ShellExecuteW(NULL, oper, setApp.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_CrashMonitorClick(TObject *Sender)
{
	LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "perfmon.exe";
	UnicodeString setArg = "/rel";
	ShellExecuteW(NULL, oper, setApp.c_str(), setArg.c_str(), NULL, SW_SHOWDEFAULT);
}
void __fastcall TForm1::Button_ResMonClick(TObject *Sender)
{
    LPCWSTR oper = L"open";
	if(CheckBox_RunAs->Checked) oper = L"runas";
	UnicodeString setApp = "resmon.exe";
	UnicodeString setArg = "/rel";
	ShellExecuteW(NULL, oper, setApp.c_str(), setArg.c_str(), NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditPrefixPartitionChange(TObject *Sender)
{
	curConfig.setPrefixPartition(EditPrefixPartition->Text);
    EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
}
void __fastcall TForm1::CheckBoxPrefixPartitionClick(TObject *Sender)
{
	EditPrefixPartition->Enabled=CheckBoxPrefixPartition->State;
	curConfig.setEnablePrefixPartition(CheckBoxPrefixPartition->State);
	EditDirGrubName->Text = curPC.dirGrubName(curConfig.getPrefixPartition(), curConfig.getEnablePrefixPartition());
}
//---------------------------------------------------------------------------
/* перезапуск проверки нарушений на ПК */
void __fastcall TForm1::Button_CheckDefectionClick(TObject *Sender)
{
	checkDefection();
}//--------------------------------------------------------------------------

void __fastcall TForm1::CheckListBox_SPZClickCheck(TObject *Sender)
{
	std::vector<UnicodeString> tm_vStr;
	for (int i = 0; i < Form1->CheckListBox_SPZ->Items->Count; i++)
		if(Form1->CheckListBox_SPZ->Checked[i])
			tm_vStr.push_back(Form1->CheckListBox_SPZ->Items->Strings[i]);
	curPC.set_spzInstal(tm_vStr);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox_installAvpzESETClick(TObject *Sender)
{
	// avpzCheckBoxProgrammaticSet - зараз йде програмне оновлення (setReadOnlyCheckBox),
	// відкат не потрібен. Інакше - TCheckBox::Checked сам генерує повторний
	// OnClick, тому без цього прапорця відкат нижче зациклюється в
	// нескінченну рекурсію (Stack Overflow).
	if (avpzCheckBoxProgrammaticSet) return;
	avpzCheckBoxProgrammaticSet = true;
	((TCheckBox*)Sender)->Checked = !((TCheckBox*)Sender)->Checked;
	avpzCheckBoxProgrammaticSet = false;
}
//---------------------------------------------------------------------------

