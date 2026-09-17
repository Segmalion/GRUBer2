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
// outStatus (якщо не NULL) - сирий код WinVerifyTrust, щоб викликач міг
// розрізнити CERT_E_UNTRUSTEDROOT (кореневий сертифікат просто не довірений
// на цьому ПК - можна запропонувати встановити GreenCapsul_RootCA.cer) від
// будь-якої іншої, "справжньої" відмови підпису (підробка, підміна файлу).
bool Update_VerifyTrust(const fs::path &exePath, UnicodeString &errMsg, LONG *outStatus = NULL);

// відбиток сертифіката підписанта файлу збігається з UPDATE_SIGNER_SHA1
bool Update_VerifySigner(const fs::path &exePath, UnicodeString expectedSha1Hex, UnicodeString &errMsg);

// обидві перевірки разом - єдина точка виклику перед застосуванням оновлення.
// outUntrustedRoot (якщо не NULL) - true лише якщо причина відмови саме
// CERT_E_UNTRUSTEDROOT (див. Update_VerifyTrust вище).
bool Update_VerifyTrustedExe(const fs::path &exePath, UnicodeString &errMsg, bool *outUntrustedRoot = NULL);

// встановлює кореневий сертифікат, вшитий у сам GRUBer.exe як ресурс RCDATA
// "GREENCAPSUL_ROOTCA" (див. UpdateResources.rc), у сховище поточного
// користувача (CurrentUser\Root) - без прав адміністратора, цього досить,
// щоб WinVerifyTrust цього ж процесу почав довіряти ланцюгу. НЕ впливає на
// пінінг відбитка підписанта (UPDATE_SIGNER_SHA1, Update_VerifySigner) -
// той лишається окремим, більш суворим бар'єром і після встановлення кореня.
bool Update_InstallEmbeddedRootCert(UnicodeString &errMsg);

#endif
