//---------------------------------------------------------------------------

#pragma hdrstop

#include "UpdateVerify.h"

#include <vector>
#include <wintrust.h>
#include <softpub.h>
#include <wincrypt.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment(lib, "wintrust.lib")
#pragma comment(lib, "crypt32.lib")

// той самий сертифікат, яким tools\build_release.ps1 підписує обидва exe
// (signtool /fd sha256, thumbprint константа там само)
const UnicodeString UPDATE_SIGNER_SHA1 = L"B4D511E8418E0957521FE045EAAB39BA72B70F18";
//---------------------------------------------------------------------------
static UnicodeString hexEncode(const BYTE *data, DWORD len)
{
	UnicodeString out;
	out.SetLength(len * 2);
	static const wchar_t hexDigits[] = L"0123456789ABCDEF";
	for (DWORD i = 0; i < len; i++) {
		out[(int)(i * 2 + 1)] = hexDigits[(data[i] >> 4) & 0xF];
		out[(int)(i * 2 + 2)] = hexDigits[data[i] & 0xF];
	}
	return out;
}
static UnicodeString stripSpaces(UnicodeString s)
{
	UnicodeString out;
	for (int i = 1; i <= s.Length(); i++) if (s[i] != L' ') out += s[i];
	return out;
}
//---------------------------------------------------------------------------
bool Update_VerifyTrust(const fs::path &exePath, UnicodeString &errMsg)
{
	WINTRUST_FILE_INFO fileInfo = {0};
	fileInfo.cbStruct = sizeof(fileInfo);
	fileInfo.pcwszFilePath = exePath.c_str();

	WINTRUST_DATA winTrustData = {0};
	winTrustData.cbStruct = sizeof(winTrustData);
	winTrustData.dwUIChoice = WTD_UI_NONE;
	// без перевірки відкликання - техніки на виїзді часто без інтернету, а
	// підпис із таймстампом лишається валідним незалежно від CRL/OCSP
	winTrustData.fdwRevocationChecks = WTD_REVOKE_NONE;
	winTrustData.dwUnionChoice = WTD_CHOICE_FILE;
	winTrustData.pFile = &fileInfo;
	winTrustData.dwStateAction = WTD_STATEACTION_VERIFY;
	winTrustData.dwProvFlags = WTD_SAFER_FLAG;

	GUID action = WINTRUST_ACTION_GENERIC_VERIFY_V2;
	LONG status = WinVerifyTrust(NULL, &action, &winTrustData);

	winTrustData.dwStateAction = WTD_STATEACTION_CLOSE;
	WinVerifyTrust(NULL, &action, &winTrustData);

	if (status != ERROR_SUCCESS) {
		errMsg = L"Підпис файлу недійсний або відсутній (код " + UnicodeString((int)status) + L").";
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
// Дістає сертифікат підписанта embedded PKCS#7-підпису файлу.
// Стандартний прийом (MS-приклад "Get information from an Authenticode
// signed file"): CryptQueryObject -> розмір CMSG_SIGNER_INFO_PARAM ->
// CryptMsgGetParam -> CertFindCertificateInStore за Issuer+SerialNumber
// з отриманого CMSG_SIGNER_INFO.
static bool getSignerCertContext(const fs::path &exePath, PCCERT_CONTEXT &outCert, UnicodeString &errMsg)
{
	outCert = NULL;
	HCERTSTORE hStore = NULL;
	HCRYPTMSG hMsg = NULL;
	DWORD dwEncoding = 0, dwContentType = 0, dwFormatType = 0;

	BOOL ok = CryptQueryObject(CERT_QUERY_OBJECT_FILE, exePath.c_str(),
		CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED, CERT_QUERY_FORMAT_FLAG_BINARY,
		0, &dwEncoding, &dwContentType, &dwFormatType, &hStore, &hMsg, NULL);
	if (!ok) { errMsg = L"Файл не містить вбудованого підпису."; return false; }

	DWORD signerInfoSize = 0;
	ok = CryptMsgGetParam(hMsg, CMSG_SIGNER_INFO_PARAM, 0, NULL, &signerInfoSize);
	if (!ok || signerInfoSize == 0) {
		errMsg = L"Не вдалось прочитати інформацію підписанта.";
		CryptMsgClose(hMsg); CertCloseStore(hStore, 0);
		return false;
	}
	std::vector<BYTE> signerInfoBuf(signerInfoSize);
	PCMSG_SIGNER_INFO signerInfo = (PCMSG_SIGNER_INFO)signerInfoBuf.data();
	ok = CryptMsgGetParam(hMsg, CMSG_SIGNER_INFO_PARAM, 0, signerInfo, &signerInfoSize);
	if (!ok) {
		errMsg = L"Не вдалось прочитати CMSG_SIGNER_INFO.";
		CryptMsgClose(hMsg); CertCloseStore(hStore, 0);
		return false;
	}

	CERT_INFO certInfo = {0};
	certInfo.Issuer = signerInfo->Issuer;
	certInfo.SerialNumber = signerInfo->SerialNumber;
	PCCERT_CONTEXT cert = CertFindCertificateInStore(hStore, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
		0, CERT_FIND_SUBJECT_CERT, (PVOID)&certInfo, NULL);

	CryptMsgClose(hMsg);
	CertCloseStore(hStore, 0);

	if (!cert) { errMsg = L"Сертифікат підписанта не знайдено у файлі."; return false; }
	outCert = cert;
	return true;
}
//---------------------------------------------------------------------------
bool Update_VerifySigner(const fs::path &exePath, UnicodeString expectedSha1Hex, UnicodeString &errMsg)
{
	PCCERT_CONTEXT cert = NULL;
	if (!getSignerCertContext(exePath, cert, errMsg)) return false;

	BYTE hash[20]; DWORD hashLen = sizeof(hash);
	bool gotHash = CertGetCertificateContextProperty(cert, CERT_SHA1_HASH_PROP_ID, hash, &hashLen);
	UnicodeString actual = gotHash ? hexEncode(hash, hashLen) : UnicodeString();
	CertFreeCertificateContext(cert);

	if (!gotHash) { errMsg = L"Не вдалось обчислити відбиток сертифіката."; return false; }

	UnicodeString expected = stripSpaces(expectedSha1Hex).UpperCase();
	if (actual.UpperCase() != expected) {
		errMsg = L"Файл підписано НЕ тим сертифікатом, що очікувався (відбиток " + actual + L").";
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool Update_VerifyTrustedExe(const fs::path &exePath, UnicodeString &errMsg)
{
	if (!Update_VerifyTrust(exePath, errMsg)) return false;
	if (!Update_VerifySigner(exePath, UPDATE_SIGNER_SHA1, errMsg)) return false;
	return true;
}
//---------------------------------------------------------------------------
