//---------------------------------------------------------------------------

#ifndef UpdateVerifyH
#define UpdateVerifyH

#include <filesystem>
namespace fs = std::filesystem;

//---------------------------------------------------------------------------
// Відбиток сертифіката, яким tools\build_release.ps1 підписує GRUBer.exe/
// DeviceLister.exe (signtool /fd sha256, той самий thumbprint у скрипті).
extern const UnicodeString UPDATE_SIGNER_SHA1;

// WinVerifyTrust: підпис файлу цілий і ланцюг довіри дійсний
// (WTD_REVOKE_NONE - без перевірки відкликання, техніки часто офлайн).
bool Update_VerifyTrust(const fs::path &exePath, UnicodeString &errMsg);

// відбиток сертифіката підписанта файлу збігається з UPDATE_SIGNER_SHA1
bool Update_VerifySigner(const fs::path &exePath, UnicodeString expectedSha1Hex, UnicodeString &errMsg);

// обидві перевірки разом - єдина точка виклику перед застосуванням оновлення
bool Update_VerifyTrustedExe(const fs::path &exePath, UnicodeString &errMsg);

#endif
