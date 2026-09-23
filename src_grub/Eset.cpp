//---------------------------------------------------------------------------

#pragma hdrstop

#include <windows.h>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <System.JSON.hpp>
#include <System.DateUtils.hpp>
#include <System.ZLib.hpp>

#include "Eset.h"
#include "Help.h"
#include "Fille.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static UnicodeString getErmmPath()
{
	// той самий шлях, що вже використовується для "start update" у BtnEsetUpdateClick
	return "c:\\Program Files\\ESET\\ESET Security\\ermm.exe";
}

// Запускає ermm.exe з заданими аргументами і повертає його stdout (UTF-8).
// Повертає порожній рядок при будь-якій помилці запуску/таймауті.
static UnicodeString runErmm(const UnicodeString &args, DWORD timeoutMs = 10000)
{
	UnicodeString ermmPath = getErmmPath();
	if (!FileExists(ermmPath)) return UnicodeString();

	SECURITY_ATTRIBUTES sa = {0};
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;

	HANDLE hReadPipe = NULL, hWritePipe = NULL;
	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) return UnicodeString();
	SetHandleInformation(hReadPipe, HANDLE_FLAG_INHERIT, 0); // читаючий кінець - лише для батька

	STARTUPINFOW si = {0};
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.hStdOutput = hWritePipe;
	si.hStdError = hWritePipe;

	PROCESS_INFORMATION pi = {0};
	UnicodeString cmdLine = "\"" + ermmPath + "\" " + args;
	std::vector<wchar_t> cmdBuf(cmdLine.c_str(), cmdLine.c_str() + cmdLine.Length() + 1);

	BOOL ok = CreateProcessW(NULL, cmdBuf.data(), NULL, NULL, TRUE,
		CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	CloseHandle(hWritePipe); // батько більше нічого не пише в pipe
	if (!ok) {
		CloseHandle(hReadPipe);
		return UnicodeString();
	}

	DWORD waitResult = WaitForSingleObject(pi.hProcess, timeoutMs);
	if (waitResult != WAIT_OBJECT_0) TerminateProcess(pi.hProcess, 1);

	std::string output;
	char buf[4096];
	DWORD avail = 0;
	while (PeekNamedPipe(hReadPipe, NULL, 0, NULL, &avail, NULL) && avail > 0) {
		DWORD readBytes = 0;
		if (!ReadFile(hReadPipe, buf, sizeof(buf), &readBytes, NULL) || readBytes == 0) break;
		output.append(buf, readBytes);
	}
	CloseHandle(hReadPipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	if (output.empty()) return UnicodeString();
	UTF8String utf8(output.c_str(), (int)output.length());
	return UnicodeString(utf8);
}

static UnicodeString jsonResultStr(TJSONObject *result, const UnicodeString &key)
{
	if (!result) return UnicodeString();
	TJSONValue *v = result->Values[key];
	return v ? v->Value() : UnicodeString();
}

// "YYYY-MM-DD HH-MM-SS" (формат ermm) -> "dd.MM.yyyy HH:mm"
static UnicodeString formatErmmDate(const UnicodeString &d)
{
	if (d.Length() < 16) return d; // невідомий формат - показати як є
	UnicodeString y = d.SubString(1, 4), mo = d.SubString(6, 2), da = d.SubString(9, 2);
	UnicodeString hh = d.SubString(12, 2), mi = d.SubString(15, 2);
	return da + "." + mo + "." + y + " " + hh + ":" + mi;
}

// "YYYY-MM-DD" (формат ermm) -> TDateTime; TDateTime(0.0), якщо не розпарсилось
static TDateTime parseIsoDate(const UnicodeString &d)
{
	if (d.Length() < 10) return TDateTime(0.0);
	int y = d.SubString(1, 4).ToIntDef(0);
	int m = d.SubString(6, 2).ToIntDef(0);
	int day = d.SubString(9, 2).ToIntDef(0);
	if (y == 0 || m == 0 || day == 0) return TDateTime(0.0);
	try {
		return EncodeDate((unsigned short)y, (unsigned short)m, (unsigned short)day);
	} catch (const Exception &) {
		return TDateTime(0.0);
	}
}

// Рекурсивний пошук першого об'єкта з ключем "UpdateUrl" у деревi JSON, який
// повертає "get configuration --format json" (перевірено на живому ESET
// Endpoint Security 12.1: {"configuration":{"data":{"Settings":{...
// "profile":{"profile":[{"settings":{"UPDATE_CFG":{"UpdateUrl":"...",
// "UpdateUrlAutoselect":0, ...}}}]}...}}}} - шлях до профілю в дереві може
// відрізнятись між версіями продукту/кількістю профілів, тому шукаємо не за
// фіксованим шляхом, а за іменем ключа.
static bool findUpdateUrlInJson(TJSONValue *node, UnicodeString &outUrl, bool &outAutoselect)
{
	if (!node) return false;
	if (TJSONObject *obj = dynamic_cast<TJSONObject*>(node)) {
		if (TJSONValue *urlVal = obj->Values[L"UpdateUrl"]) {
			outUrl = urlVal->Value();
			TJSONValue *autoVal = obj->Values[L"UpdateUrlAutoselect"];
			outAutoselect = autoVal && autoVal->Value() != "0";
			return true;
		}
		for (int i = 0; i < obj->Count; i++) {
			if (findUpdateUrlInJson(obj->Pairs[i]->JsonValue, outUrl, outAutoselect)) return true;
		}
	} else if (TJSONArray *arr = dynamic_cast<TJSONArray*>(node)) {
		for (int i = 0; i < arr->Count; i++) {
			if (findUpdateUrlInJson(arr->Items[i], outUrl, outAutoselect)) return true;
		}
	}
	return false;
}

// Шлях до тимчасового файлу для "get configuration --file ... --format json".
// На відміну від "get update-status"/"get license-info", ermm.exe не друкує
// конфігурацію в stdout - потрібен реальний файл на диску (підтверджено на
// живій машині: без --file/за відсутньої теки команда падає з
// "General error executing command"). Системний %TEMP% елевованого процесу
// теж підтверджено не підійшов - використовуємо власну теку GRUBer-а
// (C:\ProgramData\GRUBer, та сама, де вже лежить gruber_info.ini/логи).
static UnicodeString getTempEsetConfigPath()
{
	UnicodeString dir = L"C:\\ProgramData\\GRUBer";
	// створює теку (якщо відсутня) і одразу видає Users право на запис -
	// на відміну від голого CreateDirectoryW, щоб потім не впертись у
	// "Access is denied" при записі gruber_info.ini з-під не-адміна
	ensureDirWithAccess(dir);
	return dir + L"\\gruber_eset_cfg.json";
}

struct UpdateSourceResult {
	bool ok = false;
	bool autoUpdate = true;
	UnicodeString dirMirror;
};

// "X:\..." - локальний диск; мережевий URL/UNC-шлях/порожньо - не локальний.
static bool isLocalPath(const UnicodeString &s)
{
	return s.Length() >= 3
		&& ((s[1] >= L'A' && s[1] <= L'Z') || (s[1] >= L'a' && s[1] <= L'z'))
		&& s[2] == L':' && s[3] == L'\\';
}

static UpdateSourceResult computeUpdateSource()
{
	UpdateSourceResult res;
	try {
		UnicodeString tmpFile = getTempEsetConfigPath();
		if (tmpFile.IsEmpty()) return res;
		DeleteFile(tmpFile); // прибрати залишок з попереднього запуску
		runErmm(L"get configuration --file \"" + tmpFile + L"\" --format json");
		if (!FileExists(tmpFile)) return res;

		UnicodeString rawText;
		try {
			std::unique_ptr<TStringList> raw(new TStringList);
			std::unique_ptr<TFileStream> stream(new TFileStream(tmpFile, fmOpenRead | fmShareDenyNone));
			raw->LoadFromStream(stream.get(), TEncoding::UTF8);
			rawText = raw->Text;
		} catch (const Exception &) {
			// файл могли не встигнути дописати/видалити - нижче трактуємо як невдачу
		}
		DeleteFile(tmpFile);
		if (rawText.IsEmpty()) return res;

		// get configuration --format json пише СИРУ конфігурацію без звичної
		// обгортки {"id","result","error"} - одразу {"configuration":{"data":{...}}}.
		std::unique_ptr<TJSONObject> root(dynamic_cast<TJSONObject*>(TJSONObject::ParseJSONValue(rawText)));
		if (!root) return res;
		TJSONValue *configuration = root->Values[L"configuration"];
		if (!configuration) return res;

		UnicodeString url;
		bool autoselect = false;
		if (!findUpdateUrlInJson(configuration, url, autoselect)) return res;

		res.ok = true;
		if (autoselect || !isLocalPath(url)) {
			res.autoUpdate = true;
			res.dirMirror = UnicodeString();
		} else {
			res.autoUpdate = false;
			res.dirMirror = url;
		}
		return res;
	} catch (const Exception &) {
		return res;
	}
}

// ---------------------------------------------------------------------------
// Fallback через реєстр, коли ermm.exe недоступний/заблокований/вимкнений у
// налаштуваннях ESET. Перевірено на реальних експортах реєстру (ліцензована й
// неліцензована тестові машини, ESET Endpoint Security 12.1/13.0, 2026-09-22):
//   HKLM\SOFTWARE\ESET\ESET Security\CurrentVersion\Info
//     WebActivationState (DWORD, 0 - не активовано, інакше - активовано)
//     WebLicensePublicId (REG_SZ, ключ ліцензії формату "XXX-XXX-XXX")
//   ...\CurrentVersion\Plugins\01000400\Settings
//     LastSuccessfulUpdate / LastUpdateAttempt (DWORD, unix-час; буває REG_SZ ""
//     замість DWORD, якщо оновлення ще жодного разу не було)
//   ...\CurrentVersion\Config\plugins\01000400\profile\profile\<профіль>\
//     settings\UPDATE_CFG: UpdateUrl (REG_SZ) / UpdateUrlAutoselect (DWORD) -
//     та сама пара полів, що й у "get configuration" через ermm. ПІДТВЕРДЖЕНО
//     на реальній машині: ця підгілка може бути відсутня, НАВІТЬ КОЛИ локальне
//     дзеркало реально налаштовано (якщо шлях виставили не через штатний екран
//     налаштувань ESET) - тому відсутність гілки трактується як "не вдалося
//     визначити", а НЕ як підтверджене "мережа/авто" (інакше можна хибно
//     перекрити вже відомий правильний кешований шлях).
// Дати закінчення ліцензії в реєстрі НЕМА ЗОВСІМ - недоступна цим шляхом.
// ---------------------------------------------------------------------------

static UnicodeString esetRegBase()
{
	return L"SOFTWARE\\ESET\\ESET Security\\CurrentVersion";
}

// Відкриває SOFTWARE\ESET\ESET Security\CurrentVersion<sub> відносно
// HKEY_LOCAL_MACHINE, з фолбеком на Wow6432Node - той самий підхід, що й
// InstallSoft.cpp для інших вендорів (x64_sys() гейтить лише 32-бітну гілку).
static bool openEsetKey(const UnicodeString &sub, HKEY &outKey)
{
	UnicodeString path = esetRegBase() + sub;
	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, path.c_str(), 0, KEY_READ, &outKey) == ERROR_SUCCESS)
		return true;
	if (x64_sys()) {
		UnicodeString wowPath = L"SOFTWARE\\Wow6432Node\\ESET\\ESET Security\\CurrentVersion" + sub;
		if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, wowPath.c_str(), 0, KEY_READ, &outKey) == ERROR_SUCCESS)
			return true;
	}
	return false;
}

static bool esetRegistryFound()
{
	HKEY hKey;
	if (!openEsetKey(L"\\Info", hKey)) return false;
	RegCloseKey(hKey);
	return true;
}

// Читає рядкове значення незалежно від того, як воно фактично типізоване:
// "публічні" ключі (...\Info\WebLicensePublicId тощо) - звичайний REG_SZ, а от
// генерик-сховище налаштувань (...\Config\plugins\...) зберігає навіть рядки
// як REG_BINARY - сирі байти без типу REG_SZ (підтверджено на реальній машині:
// "UpdateUrl" мав Type=REG_BINARY у Registry Editor, і в .reg-експорті
// позначався просто "hex:...", без "hex(2):"/лапок). Тому пробуємо обидва.
static UnicodeString readRegSz(HKEY hKey, const UnicodeString &name)
{
	BYTE buf[1024];
	DWORD size = sizeof(buf);
	DWORD type = 0;
	if (RegQueryValueExW(hKey, name.c_str(), NULL, &type, buf, &size) != ERROR_SUCCESS) return UnicodeString();
	if (type == REG_SZ || type == REG_EXPAND_SZ) {
		UnicodeString s((wchar_t*)buf, size / sizeof(wchar_t));
		while (s.Length() > 0 && s[s.Length()] == L'\0') s.SetLength(s.Length() - 1);
		return s;
	}
	if (type == REG_BINARY && size > 0) {
		UTF8String utf8((char*)buf, (int)size);
		return UnicodeString(utf8);
	}
	return UnicodeString();
}

// true лише якщо значення справді REG_DWORD і не 0 ("ще не було" зберігається
// як REG_SZ "", а не DWORD 0 - підтверджено на реальному дампі).
static bool readRegDwordAsUnixTime(HKEY hKey, const UnicodeString &name, TDateTime &out)
{
	DWORD value = 0, size = sizeof(value), type = 0;
	if (RegQueryValueExW(hKey, name.c_str(), NULL, &type, (LPBYTE)&value, &size) != ERROR_SUCCESS) return false;
	if (type != REG_DWORD || value == 0) return false;
	out = System::Dateutils::UnixToDateTime(value, false);
	return true;
}

static bool registryGetUpdateDate(UnicodeString &outFormatted)
{
	HKEY hKey;
	if (!openEsetKey(L"\\Plugins\\01000400\\Settings", hKey)) return false;
	TDateTime dt;
	// саме LastUpdate (не LastSuccessfulUpdate/LastUpdateAttempt)
	bool ok = readRegDwordAsUnixTime(hKey, L"LastUpdate", dt);
	RegCloseKey(hKey);
	if (!ok) return false;
	outFormatted = dt.FormatString("dd.MM.yyyy HH:mm");
	return true;
}

static bool registryGetLicense(bool &outActive, UnicodeString &outKey)
{
	HKEY hKey;
	if (!openEsetKey(L"\\Info", hKey)) return false;
	DWORD state = 0, size = sizeof(state), type = 0;
	bool haveState = RegQueryValueExW(hKey, L"WebActivationState", NULL, &type, (LPBYTE)&state, &size) == ERROR_SUCCESS
		&& type == REG_DWORD;
	UnicodeString key = readRegSz(hKey, L"WebLicensePublicId");
	RegCloseKey(hKey);
	if (!haveState && key.IsEmpty()) return false; // взагалі нічого не знайшли
	outActive = haveState && state != 0;
	outKey = key;
	return true;
}

// Шукає UpdateUrl/UpdateUrlAutoselect під першим знайденим профілем оновлення.
// ВАЖЛИВО (уточнено на реальній машині 2026-09-22): підгілка
// Config\plugins\01000400\profile\profile НЕ завжди існує навіть коли локальне
// дзеркало реально налаштовано - вона з'являється лише якщо профіль оновлення
// хоч раз зберігали через штатний екран налаштувань ESET; якщо шлях виставили
// іншим шляхом (політикою/скриптом), цієї гілки може не бути взагалі. Тому
// відсутність підгілки трактуємо як "не вдалося визначити" (return false, кеш
// НЕ чіпаємо) - ЩО завгодно, тільки не хибний "мережа/авто", який перекриє вже
// відомий правильний шлях.
static bool registryGetUpdateSource(UnicodeString &outUrl, bool &outAutoselect)
{
	HKEY hPlugins;
	if (!openEsetKey(L"\\Config\\plugins", hPlugins)) return false;

	HKEY hProfiles;
	bool hasUpdateProfile = RegOpenKeyExW(hPlugins, L"01000400\\profile\\profile", 0, KEY_READ, &hProfiles) == ERROR_SUCCESS;
	RegCloseKey(hPlugins);
	if (!hasUpdateProfile) return false;

	bool found = false;
	for (DWORD idx = 0; !found; idx++) {
		WCHAR subKeyName[256];
		DWORD subKeyNameSize = 256;
		LONG enumRes = RegEnumKeyExW(hProfiles, idx, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL);
		if (enumRes == ERROR_NO_MORE_ITEMS) break;
		if (enumRes != ERROR_SUCCESS) continue;

		HKEY hSettings;
		UnicodeString settingsPath = UnicodeString(subKeyName) + L"\\settings\\UPDATE_CFG";
		if (RegOpenKeyExW(hProfiles, settingsPath.c_str(), 0, KEY_READ, &hSettings) == ERROR_SUCCESS) {
			UnicodeString url = readRegSz(hSettings, L"UpdateUrl");
			DWORD autosel = 0, size = sizeof(autosel), type = 0;
			RegQueryValueExW(hSettings, L"UpdateUrlAutoselect", NULL, &type, (LPBYTE)&autosel, &size);
			RegCloseKey(hSettings);
			if (!url.IsEmpty()) {
				outUrl = url;
				outAutoselect = (autosel != 0);
				found = true;
			}
		}
	}
	RegCloseKey(hProfiles);
	return found; // не знайшли жодного профілю з явним UpdateUrl - невизначено, не "мережа"
}

// ---------------------------------------------------------------------------
// ProductInstanceID (ESET ID) з логів ESET Management Agent. Читається з
// поточного trace.log, а якщо там рядка ще немає (агент довго не
// перезапускався - рядок пишеться лише при реєстрації продукту, а не на
// кожен запуск) - з архівів trace.log.<N>.gz, від найстаршого (найбільший N)
// до найновішого. Підтверджено на реальному прикладі логів: рядок
// гарантовано є в найстаршому збереженому архіві.
// ---------------------------------------------------------------------------

static bool findProductIdInStream(TStream *stream, UnicodeString &outId)
{
	UnicodeString marker = "ProductInstanceID:";
	std::unique_ptr<TStringList> log(new TStringList);
	try {
		log->LoadFromStream(stream, TEncoding::UTF8);
	} catch (const Exception &) {
		return false;
	}
	for (int i = 0; i < log->Count; i++) {
		UnicodeString line = log->Strings[i];
		int pos = line.Pos(marker);
		if (pos == 0) continue;
		UnicodeString rest = line.SubString(pos + marker.Length(), line.Length()).Trim();
		int spacePos = rest.Pos(" ");
		outId = (spacePos == 0) ? rest : rest.SubString(1, spacePos - 1);
		return true;
	}
	return false;
}

// Розпаковує .gz у пам'ять вручну, читаючи Read() по чанках у циклі - а НЕ
// через TStream::CopyFrom/LoadFromStream з розрахунком на Source.Size:
// у TZDecompressionStream Size повертає лише "скільки вже розпаковано на
// поточний момент" (0 до першого Read), а не кінцевий розмір, тож будь-який
// підхід, що спирається на Size наперед, мовчки "скопіює" 0 байт.
static bool decompressGzToMemory(const UnicodeString &path, TMemoryStream *out)
{
	try {
		// той самий дозвіл на спільний доступ, що й для trace.log - архіви
		// теж лежать в теці, яку агент ESET може продовжувати писати.
		std::unique_ptr<TFileStream> fileStream(new TFileStream(path, fmOpenRead | fmShareDenyNone));
		// windowBits = 15 + 16 - стандартний спосіб змусити zlib розпізнавати
		// gzip-контейнер (заголовок+CRC), а не голий deflate-потік.
		std::unique_ptr<TZDecompressionStream> gz(new TZDecompressionStream(fileStream.get(), 15 + 16));
		BYTE buf[65536];
		int n;
		while ((n = gz->Read(buf, (int)sizeof(buf))) > 0) {
			out->WriteBuffer(buf, n);
		}
		return true;
	} catch (const Exception &) {
		return false;
	}
}

static bool findProductIdInGz(const UnicodeString &path, UnicodeString &outId)
{
	std::unique_ptr<TMemoryStream> mem(new TMemoryStream);
	if (!decompressGzToMemory(path, mem.get())) return false;
	mem->Position = 0;
	return findProductIdInStream(mem.get(), outId);
}

// Витягує N з імені файлу "trace.log.<N>.gz"; false, якщо ім'я не
// відповідає цьому шаблону (нецифровий хвіст тощо).
static bool esetTraceArchiveIndex(const UnicodeString &fileName, int &outIndex)
{
	UnicodeString prefix = L"trace.log.";
	UnicodeString suffix = L".gz";
	if (fileName.Pos(prefix) != 1) return false;
	if (fileName.Length() <= prefix.Length() + suffix.Length()) return false;
	if (fileName.SubString(fileName.Length() - suffix.Length() + 1, suffix.Length()) != suffix) return false;
	UnicodeString numPart = fileName.SubString(prefix.Length() + 1,
		fileName.Length() - prefix.Length() - suffix.Length());
	if (numPart.IsEmpty()) return false;
	for (int i = 1; i <= numPart.Length(); i++) {
		if (numPart[i] < L'0' || numPart[i] > L'9') return false;
	}
	outIndex = numPart.ToIntDef(-1);
	return outIndex >= 0;
}

// Перелічує "trace.log.*.gz" у теці логів, пробує кожен від найстаршого
// (найбільший N) до найновішого, зупиняючись на першому влученні.
static bool findProductIdInArchives(UnicodeString &outId)
{
	UnicodeString dir = getEsetLogsDir();
	std::vector<int> indices;
	TSearchRec sr;
	if (!FindFirst(dir + "trace.log.*.gz", faAnyFile, sr)) {
		do {
			int idx;
			if (esetTraceArchiveIndex(sr.Name, idx)) indices.push_back(idx);
		} while (!FindNext(sr));
		FindClose(sr);
	}
	std::sort(indices.begin(), indices.end(), std::greater<int>());
	for (int idx : indices) {
		UnicodeString path = dir + "trace.log." + IntToStr(idx) + ".gz";
		if (findProductIdInGz(path, outId)) return true;
	}
	return false;
}

static bool computeEsetProductInstanceID(UnicodeString &outId)
{
	UnicodeString filePath = getEsetLogsDir() + "trace.log";
	if (FileExists(filePath)) {
		try {
			// trace.log тримається відкритим агентом ESET - читаємо з дозволом
			// на спільний доступ, інакше TStringList::LoadFromFile впаде з
			// помилкою "used by another process".
			std::unique_ptr<TFileStream> stream(new TFileStream(filePath, fmOpenRead | fmShareDenyNone));
			if (findProductIdInStream(stream.get(), outId)) return true;
		} catch (const Exception &) {
			// ігноруємо - спробуємо архіви
		}
	}
	return findProductIdInArchives(outId);
}

EsetInfoResult computeEsetInfo()
{
	EsetInfoResult res;
	bool ermmExists = FileExists(getErmmPath());

	// "get update-status"/"get license-info" - прості запити, працюють і без
	// прав адміністратора. Реєстровий fallback теж не потребує адмінки.
	try {
		UnicodeString raw = runErmm(L"get update-status");
		std::unique_ptr<TJSONObject> root(dynamic_cast<TJSONObject*>(TJSONObject::ParseJSONValue(raw)));
		TJSONObject *result = root ? dynamic_cast<TJSONObject*>(root->Values[L"result"]) : nullptr;
		UnicodeString dt = jsonResultStr(result, L"last_successful_update_time");
		if (dt.IsEmpty()) dt = jsonResultStr(result, L"last_update_time");
		if (!dt.IsEmpty()) {
			res.lastUpdateDate = formatErmmDate(dt);
			res.hasUpdateDate = true;
		}
	} catch (const Exception &) {}
	if (!res.hasUpdateDate) {
		UnicodeString regDate;
		if (registryGetUpdateDate(regDate)) {
			res.lastUpdateDate = regDate;
			res.hasUpdateDate = true;
		}
	}

	try {
		UnicodeString raw = runErmm(L"get license-info");
		std::unique_ptr<TJSONObject> root(dynamic_cast<TJSONObject*>(TJSONObject::ParseJSONValue(raw)));
		TJSONObject *result = root ? dynamic_cast<TJSONObject*>(root->Values[L"result"]) : nullptr;
		UnicodeString state = jsonResultStr(result, L"expiration_state");
		UnicodeString expDate = jsonResultStr(result, L"expiration_date");
		UnicodeString publicId = jsonResultStr(result, L"public_id");
		if (!state.IsEmpty() || !expDate.IsEmpty() || !publicId.IsEmpty()) {
			res.hasLicenseStatus = true;
			res.licenseActive = (state == "ok");
			res.licenseDate = parseIsoDate(expDate);
			res.licenseKey = publicId;
		}
	} catch (const Exception &) {}
	if (!res.hasLicenseStatus) {
		bool active = false;
		UnicodeString key;
		if (registryGetLicense(active, key)) {
			res.hasLicenseStatus = true;
			res.licenseActive = active;
			res.licenseKey = key;
			res.licenseDate = TDateTime(0.0); // реєстр не дає дати закінчення
		}
	}

	// "get configuration" (шлях оновлення через ermm) потребує адмінки на
	// відміну від читання HKLM\SOFTWARE - реєстровий fallback пробуємо завжди.
	if (IsAdminMode()) {
		UpdateSourceResult src = computeUpdateSource();
		if (src.ok) {
			res.hasUpdateSource = true;
			res.autoUpdate = src.autoUpdate;
			res.dirMirror = src.dirMirror;
		}
	}
	if (!res.hasUpdateSource) {
		UnicodeString url;
		bool autosel = true;
		if (registryGetUpdateSource(url, autosel)) {
			res.hasUpdateSource = true;
			res.autoUpdate = autosel || !isLocalPath(url);
			res.dirMirror = res.autoUpdate ? UnicodeString() : url;
		}
	}

	res.esetFound = ermmExists || esetRegistryFound();
	if (!res.esetFound) {
		res.updateSourceFailReason = L"Не знайдено";
	} else if (!res.hasUpdateSource) {
		res.updateSourceFailReason = L"Не вдалося визначити";
	}

	UnicodeString productId;
	if (computeEsetProductInstanceID(productId)) {
		res.hasProductID = true;
		res.productID = productId;
	}

	return res;
}

UnicodeString getEsetLogsDir()
{
	return "c:\\ProgramData\\ESET\\RemoteAdministrator\\Agent\\EraAgentApplicationData\\Logs\\";
}
//---------------------------------------------------------------------------
