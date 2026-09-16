//---------------------------------------------------------------------------

#ifndef UpdateInstallH
#define UpdateInstallH

#include <filesystem>
namespace fs = std::filesystem;

//---------------------------------------------------------------------------
// C:\ProgramData\GRUBer\update\<tag>\ - тека стейджингу для конкретного релізу
fs::path Update_StagingDir(UnicodeString tag);

// видаляє всі підтеки C:\ProgramData\GRUBer\update\*, крім keepTag
void Update_CleanStaleStaging(UnicodeString keepTag);

// пробний запис у теку встановлення - true, якщо в неї можна писати поточним
// токеном процесу без runas (див. IsAdminMode()/RunApp у Help.h/RunApp.h)
bool Update_InstallDirWritable(const fs::path &installDir);

// генерує apply_update.cmd у stageDir; outCmd - шлях до згенерованого файлу
bool Update_WriteHelperCmd(const fs::path &stageDir, fs::path &outCmd, UnicodeString &errMsg);

// ShellExecuteW(hidden, "open" або "runas" залежно від needElevation) +
// аргументи "<installDir>" <gruberPid>
bool Update_LaunchHelper(const fs::path &cmdPath, const fs::path &installDir,
	DWORD gruberPid, bool needElevation, UnicodeString &errMsg);

// дописує рядок у C:\ProgramData\GRUBer\error\update.log (проста файлова
// операція без залежності від VCL/Form1 - за зразком LogCrash() з CrashHandler.cpp)
void Update_Log(const UnicodeString &message);

#endif
