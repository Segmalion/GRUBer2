//---------------------------------------------------------------------------

#include <System.hpp>
#include <atomic>
#include <filesystem>
#pragma hdrstop

#include "Th_UpdateCheck.h"
#include "MainForm.h"

#include "Config.h"
#include "UpdateCheck.h"
#include "UpdateVerify.h"
#include "UpdateInstall.h"
#include "GitVersion.h"
#include "Help.h" // printLog - той самий видимий лог, що й у "Лог Граба"

#include "CrashHandler.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace fs = std::filesystem;

extern Config curConfig;
extern std::atomic<bool> th_UpdateCheck_run, stopUpdate;
extern std::atomic<bool> grubActive, th_Gruber_run, th_EsetDownload_run;
//---------------------------------------------------------------------------
// прогрес завантаження оновлення - на ProgressBar_Grub (головна вкладка), а
// не на ProgressBar_ESET, щоб не виглядало так, ніби йде завантаження бази
// ESET. Безпечно ділити бар з Th_Gruber - вище вже перевірено, що граб
// зараз не активний (grubActive/th_Gruber_run), перш ніж починати завантаження.
static void updateProgressGo(int percent) {
	auto setProgress = [percent]() { Form1->ProgressBar_Grub->Position = percent; };
	if (GetCurrentThreadId() == MainThreadID) setProgress();
	else TThread::Synchronize(NULL, setProgress);
}
static void updateStatusText(UnicodeString text) {
	auto setStatus = [text]() { Form1->StatusBar1->Panels->Items[1]->Text = " " + text; };
	if (GetCurrentThreadId() == MainThreadID) setStatus();
	else TThread::Synchronize(NULL, setStatus);
}
//---------------------------------------------------------------------------
__fastcall Th_UpdateCheck::Th_UpdateCheck(bool CreateSuspended, bool silentMode)
	: TThread(CreateSuspended), silent(silentMode)
{
}
//---------------------------------------------------------------------------
void __fastcall Th_UpdateCheck::Execute()
{
	try
	{
		ExecuteImpl();
	}
	catch (Exception &e)
	{
		LogCrash("Th_UpdateCheck", e.ClassName() + ": " + e.Message);
		Update_Log(L"Перевірка оновлень: критична помилка - " + e.Message);
		th_UpdateCheck_run = false;
	}
	catch (std::exception &e)
	{
		UnicodeString what = e.what();
		LogCrash("Th_UpdateCheck", what);
		Update_Log(L"Перевірка оновлень: критична помилка - " + what);
		th_UpdateCheck_run = false;
	}
	catch (...)
	{
		LogCrash("Th_UpdateCheck", L"невідомий виняток");
		Update_Log(L"Перевірка оновлень: критична помилка (невідомий тип винятку)");
		th_UpdateCheck_run = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Th_UpdateCheck::ExecuteImpl()
{
	FreeOnTerminate = true;
	th_UpdateCheck_run = true;
	stopUpdate = false;

	printLog(">>", L"Перевірка оновлень GRUBer/DeviceLister...");

	Update_CleanStaleStaging(UnicodeString(GIT_COMMIT_HASH));

	UpdateRelease rel;
	UnicodeString errMsg;
	bool fetchOk = Update_FetchLatestRelease(rel, errMsg);
	bool hardError = !errMsg.IsEmpty();

	// час перевірки фіксуємо завжди, окрім справжньої мережевої помилки -
	// щоб тимчасова недоступність мережі не відкладала повторну спробу на
	// повний intervalHours (curConfig - не потокобезпечний, тому тільки
	// через Synchronize, за правилом compute/apply з CLAUDE.md)
	if (!hardError) {
		// формат навмисно збігається з ShortDateFormat/ShortTimeFormat, які
		// задає StrToDateTimeSafe() (Text.cpp) - інакше зворотний парсинг у
		// shouldRunStartupUpdateCheck() (MainForm.cpp) поверне 0/дефолт
		UnicodeString nowStr = TDateTime(Now()).FormatString(L"dd.MM.yy hh:mm");
		TThread::Synchronize(NULL, [nowStr]() {
			curConfig.setUpdLastCheckUtc(nowStr);
			curConfig.saveFileIni();
		});
	}

	if (hardError) {
		printLog("ER", L"Перевірка оновлень: мережева помилка - " + errMsg);
		Update_Log(L"Перевірка оновлень: мережева помилка - " + errMsg);
		if (!silent) {
			TThread::Synchronize(NULL, [errMsg]() {
				Application->MessageBox((L"Не вдалося перевірити оновлення:\n" + errMsg).c_str(),
					L"Перевірка оновлень", MB_OK | MB_ICONERROR);
			});
		}
		th_UpdateCheck_run = false;
		return;
	}

	if (!fetchOk || !rel.valid) {
		printLog("!!", L"Перевірка оновлень: релізів не знайдено, або перевірку не налаштовано.");
		if (!silent) {
			TThread::Synchronize(NULL, [&]() {
				Application->MessageBox(L"Оновлень не знайдено (немає релізів, або перевірку не налаштовано).",
					L"Перевірка оновлень", MB_OK);
			});
		}
		th_UpdateCheck_run = false;
		return;
	}

	UnicodeString skipTag;
	TThread::Synchronize(NULL, [&skipTag]() { skipTag = curConfig.getUpdSkipTag(); });

	if (!Update_IsNewer(rel, skipTag)) {
		printLog("OK", L"Перевірка оновлень: у вас найновіша версія (" + UnicodeString(GIT_COMMIT_HASH) + L").");
		if (!silent) {
			TThread::Synchronize(NULL, [&]() {
				Application->MessageBox(L"У вас найновіша версія GRUBer/DeviceLister.",
					L"Перевірка оновлень", MB_OK);
			});
		}
		th_UpdateCheck_run = false;
		return;
	}

	// не заважаємо активному грабу чи завантаженню бази ESET - спробуємо
	// знову наступного разу (наступний запуск/ручна перевірка)
	if (grubActive || th_Gruber_run || th_EsetDownload_run) {
		printLog("!!", L"Перевірка оновлень: знайдено " + rel.tagName + L", але GRUBer зараз зайнятий - відкладено.");
		Update_Log(L"Перевірка оновлень: знайдено " + rel.tagName + L", але GRUBer зараз зайнятий - відкладено.");
		th_UpdateCheck_run = false;
		return;
	}

	printLog(">>", L"Перевірка оновлень: знайдено нову версію " + rel.tagName + L" (" + rel.name + L").");

	int mbResult = IDNO;
	TThread::Synchronize(NULL, [&mbResult, rel]() {
		UnicodeString text = L"Знайдено нову версію GRUBer/DeviceLister:\n" + rel.name;

		// release notes (--notes тексту з /release-build), якщо є - обрізаємо
		// задовге тіло, щоб MessageBox лишався читабельним
		UnicodeString notes = rel.body.Trim();
		const int maxNotesLen = 1000;
		if (notes.Length() > maxNotesLen) notes = notes.SubString(1, maxNotesLen) + L"...";
		if (!notes.IsEmpty()) text += L"\n\nЩо нового:\n" + notes;

		text += L"\n\nОновити зараз? Програма закриється і перезапуститься.\n\n"
			L"\"Скасувати\" - не пропонувати цю версію знову.";
		mbResult = Application->MessageBox(text.c_str(), L"Доступне оновлення GRUBer", MB_YESNOCANCEL | MB_ICONQUESTION);
	});

	if (mbResult == IDCANCEL) {
		printLog("!!", L"Перевірка оновлень: версію " + rel.tagName + L" відхилено, більше не пропонувати.");
		TThread::Synchronize(NULL, [rel]() {
			curConfig.setUpdSkipTag(rel.tagName);
			curConfig.saveFileIni();
		});
		th_UpdateCheck_run = false;
		return;
	}
	if (mbResult != IDYES) {
		printLog("!!", L"Перевірка оновлень: оновлення відкладено користувачем.");
		th_UpdateCheck_run = false;
		return;
	}

	UpdateAsset gruberAsset, dlAsset;
	if (!Update_FindAsset(rel, L"GRUBer.exe", gruberAsset) || !Update_FindAsset(rel, L"DeviceLister.exe", dlAsset)) {
		printLog("ER", L"Перевірка оновлень: у релізі " + rel.tagName + L" немає обох потрібних файлів.");
		Update_Log(L"Перевірка оновлень: у релізі " + rel.tagName + L" немає обох потрібних файлів.");
		TThread::Synchronize(NULL, [&]() {
			Application->MessageBox(L"Реліз не містить обох потрібних файлів (GRUBer.exe/DeviceLister.exe).",
				L"Помилка оновлення", MB_OK | MB_ICONERROR);
		});
		th_UpdateCheck_run = false;
		return;
	}

	fs::path stageDir = Update_StagingDir(rel.tagName);
	fs::path gruberStaged = stageDir / L"GRUBer.exe";
	fs::path dlStaged = stageDir / L"DeviceLister.exe";

	EsetDlProgressCb progressCb = [](int percent, UnicodeString phase) {
		updateProgressGo(percent);
		updateStatusText(phase);
	};

	UnicodeString dlErr;
	updateStatusText(L"Завантаження GRUBer.exe...");
	bool ok = Update_DownloadAsset(gruberAsset, gruberStaged, 150, stopUpdate, progressCb, dlErr);
	if (ok) {
		updateStatusText(L"Завантаження DeviceLister.exe...");
		ok = Update_DownloadAsset(dlAsset, dlStaged, 150, stopUpdate, progressCb, dlErr);
	}
	if (!ok) {
		bool cancelled = stopUpdate;
		printLog(cancelled ? "!!" : "ER", cancelled ? L"Перевірка оновлень: завантаження скасовано користувачем."
			: L"Перевірка оновлень: завантаження не вдалося - " + dlErr);
		Update_Log(cancelled ? L"Перевірка оновлень: завантаження скасовано користувачем."
			: L"Перевірка оновлень: завантаження не вдалося - " + dlErr);
		if (!cancelled) {
			TThread::Synchronize(NULL, [dlErr]() {
				Application->MessageBox((L"Не вдалося завантажити оновлення:\n" + dlErr).c_str(),
					L"Помилка оновлення", MB_OK | MB_ICONERROR);
			});
		}
		std::error_code ec; fs::remove_all(stageDir, ec);
		th_UpdateCheck_run = false;
		return;
	}

	updateStatusText(L"Перевірка підпису оновлення...");
	UnicodeString verifyErr;
	bool untrustedRoot = false;
	bool verified = Update_VerifyTrustedExe(gruberStaged, verifyErr, &untrustedRoot);
	if (verified) {
		bool untrustedRoot2 = false;
		verified = Update_VerifyTrustedExe(dlStaged, verifyErr, &untrustedRoot2);
		if (!verified) untrustedRoot = untrustedRoot2;
	}

	// CERT_E_UNTRUSTEDROOT (а не будь-яка інша відмова підпису!) означає, що
	// сам підпис коректний, просто кореневий сертифікат видавця не довірений
	// на цьому конкретному ПК - типова ситуація для внутрішнього CA. Пінінг
	// відбитка підписанта (Update_VerifySigner/UPDATE_SIGNER_SHA1) лишається
	// в силі й після встановлення кореня - зловмисник з чужим коренем усе
	// одно не підбере той самий SHA1, тож ризик тут не зростає.
	if (!verified && untrustedRoot) {
		printLog("!!", L"Перевірка оновлень: кореневий сертифікат не довірений, пропоную встановити вбудований.");
		int mbCert = IDNO;
		TThread::Synchronize(NULL, [&mbCert]() {
			UnicodeString text = L"Оновлення підписано коректно, але кореневий сертифікат видавця "
				L"не довірений на цьому ПК.\n\nВстановити кореневий сертифікат у сховище цього "
				L"комп'ютера зараз?";
			mbCert = Application->MessageBox(text.c_str(), L"Кореневий сертифікат не довірений",
				MB_YESNO | MB_ICONWARNING);
		});
		if (mbCert == IDYES) {
			UnicodeString certErr;
			if (Update_InstallEmbeddedRootCert(certErr)) {
				printLog("OK", L"Перевірка оновлень: кореневий сертифікат встановлено, повторна перевірка підпису...");
				Update_Log(L"Перевірка оновлень: кореневий сертифікат встановлено.");
				UnicodeString retryErr;
				verified = Update_VerifyTrustedExe(gruberStaged, retryErr) &&
						   Update_VerifyTrustedExe(dlStaged, retryErr);
				if (!verified) verifyErr = retryErr;
			} else {
				printLog("ER", L"Перевірка оновлень: не вдалось встановити кореневий сертифікат - " + certErr);
				Update_Log(L"Перевірка оновлень: не вдалось встановити кореневий сертифікат - " + certErr);
			}
		}
	}

	if (!verified) {
		printLog("ER", L"Перевірка оновлень: ВІДХИЛЕНО - недійсний підпис (" + verifyErr + L").");
		Update_Log(L"Перевірка оновлень: ВІДХИЛЕНО - недійсний підпис (" + verifyErr + L").");
		std::error_code ec; fs::remove_all(stageDir, ec);
		TThread::Synchronize(NULL, [verifyErr]() {
			Application->MessageBox((L"Оновлення відхилено: недійсний цифровий підпис файлу.\n" + verifyErr).c_str(),
				L"Оновлення відхилено", MB_OK | MB_ICONERROR);
		});
		th_UpdateCheck_run = false;
		return;
	}

	fs::path installDir = fs::current_path();
	fs::path cmdPath;
	UnicodeString helperErr;
	if (!Update_WriteHelperCmd(stageDir, cmdPath, helperErr)) {
		printLog("ER", L"Перевірка оновлень: не вдалось згенерувати встановлювач - " + helperErr);
		Update_Log(L"Перевірка оновлень: не вдалось згенерувати встановлювач - " + helperErr);
		TThread::Synchronize(NULL, [helperErr]() {
			Application->MessageBox(helperErr.c_str(), L"Помилка оновлення", MB_OK | MB_ICONERROR);
		});
		th_UpdateCheck_run = false;
		return;
	}

	bool needElevation = !Update_InstallDirWritable(installDir);
	UnicodeString launchErr;
	if (!Update_LaunchHelper(cmdPath, installDir, GetCurrentProcessId(), needElevation, launchErr)) {
		printLog("ER", L"Перевірка оновлень: не вдалось запустити встановлювач - " + launchErr);
		Update_Log(L"Перевірка оновлень: не вдалось запустити встановлювач - " + launchErr);
		TThread::Synchronize(NULL, [launchErr]() {
			Application->MessageBox(launchErr.c_str(), L"Помилка оновлення", MB_OK | MB_ICONERROR);
		});
		th_UpdateCheck_run = false;
		return;
	}

	printLog("OK", L"Перевірка оновлень: оновлення " + rel.tagName + L" застосовується, закриваю GRUBer.");
	Update_Log(L"Перевірка оновлень: оновлення " + rel.tagName + L" застосовується, закриваю GRUBer.");
	th_UpdateCheck_run = false;
	TThread::Synchronize(NULL, [&]() { Application->Terminate(); });
}
//---------------------------------------------------------------------------
