//---------------------------------------------------------------------------

#include <System.hpp>
#include <atomic>
#include <filesystem>
#pragma hdrstop

#include "Th_EsetDownload.h"
#include "MainForm.h"

#include "Config.h"
#include "Dir.h"
#include "EsetDownload.h"

#include "Help.h"
#include "CrashHandler.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace fs = std::filesystem;

extern Config curConfig;
extern Dir curDir;
extern std::atomic<bool> th_EsetDownload_run, stopEsetDownload;

//---------------------------------------------------------------------------
void progressBarEsetGo(int percent) {
	auto setProgress = [percent]() { Form1->ProgressBar_ESET->Position = percent; };
	if (GetCurrentThreadId() == MainThreadID) setProgress();
	else TThread::Synchronize(NULL, setProgress);
}
void esetDlStatus(UnicodeString text) {
	auto setStatus = [text]() { Form1->StatusBar1->Panels->Items[1]->Text = " " + text; };
	if (GetCurrentThreadId() == MainThreadID) setStatus();
	else TThread::Synchronize(NULL, setStatus);
}
// повернути кнопки в стан спокою після завершення (успіх/помилка/скасування)
static void restoreEsetDownloadUI() {
	// [&] (не []) навмисно - captureless-лямбда розпадається у вказівник на
	// функцію, який неоднозначно конвертується одразу в обидва перевантаження
	// TThread::Synchronize (через bool і через делегат)
	auto restore = [&]() {
		Form1->BtnEsetDownload->Caption = "Завантажити базу ESET";
		Form1->BtnEsetUpdate->Enabled = !Form1->CheckBoxEsetAutoUpdate->Checked;
	};
	if (GetCurrentThreadId() == MainThreadID) restore();
	else TThread::Synchronize(NULL, restore);
}
//---------------------------------------------------------------------------
__fastcall Th_EsetDownload::Th_EsetDownload(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall Th_EsetDownload::Execute()
{
	try
	{
		ExecuteImpl();
	}
	catch (Exception &e)
	{
		LogCrash("Th_EsetDownload", e.ClassName() + ": " + e.Message);
		printLog("ER", "ESET-Download: критична помилка - " + e.Message);
		esetDlStatus("Помилка завантаження бази ESET");
		th_EsetDownload_run = false;
		restoreEsetDownloadUI();
	}
	catch (std::exception &e)
	{
		UnicodeString what = e.what();
		LogCrash("Th_EsetDownload", what);
		printLog("ER", "ESET-Download: критична помилка - " + what);
		esetDlStatus("Помилка завантаження бази ESET");
		th_EsetDownload_run = false;
		restoreEsetDownloadUI();
	}
	catch (...)
	{
		LogCrash("Th_EsetDownload", "невідомий виняток");
		printLog("ER", "ESET-Download: критична помилка (невідомий тип винятку)");
		esetDlStatus("Помилка завантаження бази ESET");
		th_EsetDownload_run = false;
		restoreEsetDownloadUI();
	}
}
//---------------------------------------------------------------------------
void __fastcall Th_EsetDownload::ExecuteImpl()
{
	FreeOnTerminate = true;
	th_EsetDownload_run = true;
	stopEsetDownload = false;

	// текст (розмір/швидкість/відсоток) вже повністю сформований у
	// EsetDownload.cpp - тут лише показуємо його як є
	EsetDlProgressCb progressCb = [](int percent, UnicodeString phase) {
		progressBarEsetGo(percent);
		esetDlStatus(phase);
	};

	fs::path tempRoot = fs::path(curDir.get_grubPathTemp().c_str()) / L"eset_download";
	std::error_code ec;
	fs::remove_all(tempRoot, ec);
	fs::create_directories(tempRoot, ec);

	fs::path fullZip = tempRoot / L"update_full.zip";
	fs::path unpackDir = tempRoot / L"unpack";
	bool zstd = (curConfig.getEsetDlArhive() == "zstd");
	// готові архіви спершу збираються у temp - тека ПО (fs::current_path())
	// не займається до самого кінця, щоб робочі update_x32/x64.* там не
	// зникали передчасно, якщо завантаження/пакування впаде або буде скасоване
	fs::path tempOutX32 = tempRoot / (zstd ? L"update_x32.tar.zstd" : L"update_x32.zip");
	fs::path tempOutX64 = tempRoot / (zstd ? L"update_x64.tar.zstd" : L"update_x64.zip");

	printLog(">>", "ESET-Download: завантаження бази ESET...");
	progressBarEsetGo(0);
	esetDlStatus("Завантаження бази ESET...");

	UnicodeString errMsg;
	bool ok = EsetDownload_DownloadFile(curConfig.getEsetDlUrl(), fullZip,
		curConfig.getEsetDlUser(), curConfig.getEsetDlPass(), curConfig.getEsetDlUpdateMs(),
		stopEsetDownload, progressCb, errMsg);

	if (!ok) {
		bool cancelled = stopEsetDownload;
		printLog(cancelled ? "!!" : "ER", "ESET-Download: " + errMsg);
		esetDlStatus(cancelled ? "Завантаження зупинено" : "Помилка завантаження");
		fs::remove_all(tempRoot, ec);
		th_EsetDownload_run = false;
		restoreEsetDownloadUI();
		return;
	}

	printLog(">>", "ESET-Download: розпакування архіву...");
	progressBarEsetGo(0);
	esetDlStatus("Розпакування архіву...");
	ok = EsetDownload_ExtractArchive(fullZip, unpackDir, stopEsetDownload, errMsg);
	if (!ok) {
		bool cancelled = stopEsetDownload;
		printLog(cancelled ? "!!" : "ER", "ESET-Download: " + errMsg);
		esetDlStatus(cancelled ? "Завантаження зупинено" : "Помилка розпакування");
		fs::remove_all(tempRoot, ec);
		th_EsetDownload_run = false;
		restoreEsetDownloadUI();
		return;
	}

	printLog(">>", "ESET-Download: сортування та пакування баз...");
	progressBarEsetGo(0);
	esetDlStatus("Пакування баз...");
	ok = EsetDownload_SortAndRepack(unpackDir, curConfig.getEsetDlArhive(), tempOutX32, tempOutX64,
		stopEsetDownload, progressCb, errMsg);
	if (!ok) {
		bool cancelled = stopEsetDownload;
		printLog(cancelled ? "!!" : "ER", "ESET-Download: " + errMsg);
		esetDlStatus(cancelled ? "Завантаження зупинено" : "Помилка пакування");
		fs::remove_all(tempRoot, ec);
		th_EsetDownload_run = false;
		restoreEsetDownloadUI();
		return;
	}

	// публікація у теку ПО - лише зараз, коли нові архіви вже готові у temp;
	// спершу копіюємо нове (з живим прогресом через CopyFileExW), і тільки
	// після успіху приберемо застарілий формат
	progressBarEsetGo(0);
	esetDlStatus("Публікація архівів...");
	fs::path poX32Zip = fs::current_path() / L"update_x32.zip";
	fs::path poX64Zip = fs::current_path() / L"update_x64.zip";
	fs::path poX32Zstd = fs::current_path() / L"update_x32.tar.zstd";
	fs::path poX64Zstd = fs::current_path() / L"update_x64.tar.zstd";
	fs::path poX32 = zstd ? poX32Zstd : poX32Zip;
	fs::path poX64 = zstd ? poX64Zstd : poX64Zip;

	bool published32 = false, published64 = false;
	UnicodeString pubErr;
	if (fs::exists(tempOutX32, ec)) {
		published32 = EsetDownload_PublishFile(tempOutX32, poX32, curConfig.getEsetDlUpdateMs(),
			stopEsetDownload, progressCb, pubErr);
		if (!published32) printLog("!!", "ESET-Download: " + pubErr);
	}
	if (!stopEsetDownload && fs::exists(tempOutX64, ec)) {
		published64 = EsetDownload_PublishFile(tempOutX64, poX64, curConfig.getEsetDlUpdateMs(),
			stopEsetDownload, progressCb, pubErr);
		if (!published64) printLog("!!", "ESET-Download: " + pubErr);
	}
	if (!published32 && !published64) {
		bool cancelled = stopEsetDownload;
		printLog(cancelled ? "!!" : "ER", "ESET-Download: не вдалось опублікувати готові архіви у теку ПО.");
		esetDlStatus(cancelled ? "Завантаження зупинено" : "Помилка публікації архівів");
		fs::remove_all(tempRoot, ec);
		th_EsetDownload_run = false;
		restoreEsetDownloadUI();
		return;
	}
	// прибираємо застарілий формат лише для тих архітектур, які реально
	// щойно оновили - робочий архів іншої архітектури (якщо не входив у цю
	// поставку) лишається недоторканим
	if (published32) fs::remove(zstd ? poX32Zip : poX32Zstd, ec);
	if (published64) fs::remove(zstd ? poX64Zip : poX64Zstd, ec);

	fs::remove_all(tempRoot, ec);
	progressBarEsetGo(100);
	esetDlStatus("Базу ESET завантажено!");
	printLog("OK", "ESET-Download: базу ESET завантажено та підготовлено!");
	th_EsetDownload_run = false;
	restoreEsetDownloadUI();
}
//---------------------------------------------------------------------------
