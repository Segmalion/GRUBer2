//---------------------------------------------------------------------------

#pragma hdrstop

#include <windows.h>
#include <memory>
#include <string>
#include <vector>
#include <System.JSON.hpp>

#include "Eset.h"
#include "Help.h"
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

static UnicodeString buildLicenseStatus(TJSONObject *result)
{
	UnicodeString state = jsonResultStr(result, "expiration_state");
	UnicodeString expDate = jsonResultStr(result, "expiration_date");
	if (state.IsEmpty() && expDate.IsEmpty()) return L"Не вдалося визначити";
	if (state == "ok") {
		return expDate.IsEmpty() ? UnicodeString(L"Активна") : (UnicodeString(L"Активна до ") + expDate);
	}
	// невідомий/проблемний стан - показати як є, разом з датою, якщо є
	UnicodeString res = state.IsEmpty() ? UnicodeString(L"Невідомий стан") : state;
	if (!expDate.IsEmpty()) res += L" (" + expDate + L")";
	return res;
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
	CreateDirectoryW(dir.c_str(), NULL); // не помилка, якщо вже існує
	return dir + L"\\gruber_eset_cfg.json";
}

static UnicodeString computeUpdateSource()
{
	UnicodeString notFound = L"Не вдалося визначити (потрібна перевірка на реальному ESET)";
	try {
		UnicodeString tmpFile = getTempEsetConfigPath();
		if (tmpFile.IsEmpty()) return notFound;
		DeleteFile(tmpFile); // прибрати залишок з попереднього запуску
		runErmm(L"get configuration --file \"" + tmpFile + L"\" --format json");
		if (!FileExists(tmpFile)) return notFound;

		UnicodeString rawText;
		try {
			std::unique_ptr<TStringList> raw(new TStringList);
			std::unique_ptr<TFileStream> stream(new TFileStream(tmpFile, fmOpenRead | fmShareDenyNone));
			raw->LoadFromStream(stream.get(), TEncoding::UTF8);
			rawText = raw->Text;
		} catch (const Exception &) {
			// файл могли не встигнути дописати/видалити - нижче трактуємо як "не знайдено"
		}
		DeleteFile(tmpFile);
		if (rawText.IsEmpty()) return notFound;

		// get configuration --format json пише СИРУ конфігурацію без звичної
		// обгортки {"id","result","error"} - одразу {"configuration":{"data":{...}}}.
		std::unique_ptr<TJSONObject> root(dynamic_cast<TJSONObject*>(TJSONObject::ParseJSONValue(rawText)));
		if (!root) return notFound;
		TJSONValue *configuration = root->Values[L"configuration"];
		if (!configuration) return notFound;

		UnicodeString url;
		bool autoselect = false;
		if (!findUpdateUrlInJson(configuration, url, autoselect)) return notFound;
		if (autoselect) {
			return url.IsEmpty() ? UnicodeString(L"Автоматичний вибір сервера ESET")
				: (UnicodeString(L"Автоматичний вибір сервера ESET (") + url + L")");
		}
		return url.IsEmpty() ? notFound : url;
	} catch (const Exception &) {
		return notFound;
	}
}

EsetInfoResult computeEsetInfo()
{
	EsetInfoResult res;
	res.esetFound = IsAdminMode() && FileExists(getErmmPath());
	if (!res.esetFound) {
		res.lastUpdateDate = L"Не знайдено";
		res.updateSource = L"Не знайдено";
		res.licenseStatus = L"Не знайдено";
		return res;
	}

	try {
		UnicodeString raw = runErmm(L"get update-status");
		std::unique_ptr<TJSONObject> root(dynamic_cast<TJSONObject*>(TJSONObject::ParseJSONValue(raw)));
		TJSONObject *result = root ? dynamic_cast<TJSONObject*>(root->Values[L"result"]) : nullptr;
		UnicodeString dt = jsonResultStr(result, L"last_successful_update_time");
		if (dt.IsEmpty()) dt = jsonResultStr(result, L"last_update_time");
		res.lastUpdateDate = dt.IsEmpty() ? UnicodeString(L"Не вдалося визначити") : formatErmmDate(dt);
	} catch (const Exception &) {
		res.lastUpdateDate = L"Не вдалося визначити";
	}

	try {
		UnicodeString raw = runErmm(L"get license-info");
		std::unique_ptr<TJSONObject> root(dynamic_cast<TJSONObject*>(TJSONObject::ParseJSONValue(raw)));
		TJSONObject *result = root ? dynamic_cast<TJSONObject*>(root->Values[L"result"]) : nullptr;
		res.licenseStatus = buildLicenseStatus(result);
	} catch (const Exception &) {
		res.licenseStatus = L"Не вдалося визначити";
	}

	res.updateSource = computeUpdateSource();

	return res;
}

UnicodeString getEsetLogsDir()
{
	return "c:\\ProgramData\\ESET\\RemoteAdministrator\\Agent\\EraAgentApplicationData\\Logs\\";
}

UnicodeString getEsetProductInstanceID()
{
	UnicodeString notFound = L"Не знайдено";
	UnicodeString filePath = getEsetLogsDir() + "trace.log";
	UnicodeString marker = "ProductInstanceID:";

	if (!FileExists(filePath)) return notFound;

	std::unique_ptr<TStringList> log(new TStringList);
	try {
		// trace.log тримається відкритим агентом ESET - читаємо з дозволом
		// на спільний доступ, інакше TStringList::LoadFromFile впаде з
		// помилкою "used by another process".
		std::unique_ptr<TFileStream> stream(new TFileStream(filePath, fmOpenRead | fmShareDenyNone));
		log->LoadFromStream(stream.get(), TEncoding::UTF8);
	} catch (const Exception &) {
		return notFound;
	}

	for (int i = 0; i < log->Count; i++) {
		UnicodeString line = log->Strings[i];
		int pos = line.Pos(marker);
		if (pos == 0) continue;
		UnicodeString rest = line.SubString(pos + marker.Length(), line.Length()).Trim();
		int spacePos = rest.Pos(" ");
		return (spacePos == 0) ? rest : rest.SubString(1, spacePos - 1);
	}
	return notFound;
}
//---------------------------------------------------------------------------
