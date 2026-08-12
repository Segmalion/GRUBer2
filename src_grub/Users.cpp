//---------------------------------------------------------------------------

#pragma hdrstop

#include <windows.h>
#include <lm.h>
#include <sddl.h>
#include <map>
#include "Users.h"

#pragma comment(lib, "advapi32.lib")

#define INFO_BUFFER_SIZE 32767
//---------------------------------------------------------------------------
#pragma package(smart_init)

// NetUserEnum (usri3_last_logon) для локальних (не доменних) облікових записів
// на звичайній робочій станції зазвичай завжди повертає 0 - Windows не веде цей
// лічильник поза доменом, навіть для активної зараз сесії. Як наближення часу
// останнього входу беремо час останньої модифікації NTUSER.DAT з профілю
// користувача.
// Шлях профілю шукаємо перебором підключів ProfileList і розпізнаванням SID
// кожного підключа через LookupAccountSidW (SID -> ім'я), а не навпаки
// (ім'я -> SID через LookupAccountNameW) - для акаунтів, прив'язаних до
// Microsoft-акаунту, зворотній резолвінг імені на SID часто не збігається з
// реальним підключем у ProfileList, а SID з реєстру завжди дійсний.
static bool findProfileImagePathByUserName(const UnicodeString &userName, UnicodeString &outPath) {
	HKEY hProfileList;
	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
			L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\ProfileList",
			0, KEY_READ, &hProfileList) != ERROR_SUCCESS)
		return false;

	bool found = false;
	for (DWORD idx = 0; !found; idx++) {
		WCHAR subKeyName[256];
		DWORD subKeyNameSize = 256;
		LONG enumRes = RegEnumKeyExW(hProfileList, idx, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL);
		if (enumRes == ERROR_NO_MORE_ITEMS) break;
		if (enumRes != ERROR_SUCCESS) continue;

		PSID sid = NULL;
		if (!ConvertStringSidToSidW(subKeyName, &sid)) continue;

		WCHAR accName[256]; DWORD accNameSize = 256;
		WCHAR domName[256]; DWORD domNameSize = 256;
		SID_NAME_USE use;
		bool resolved = LookupAccountSidW(NULL, sid, accName, &accNameSize, domName, &domNameSize, &use);
		LocalFree(sid);
		if (!resolved) continue;
		if (userName.UpperCase() != UnicodeString(accName).UpperCase()) continue;

		HKEY hSub;
		if (RegOpenKeyExW(hProfileList, subKeyName, 0, KEY_READ, &hSub) == ERROR_SUCCESS) {
			WCHAR profilePath[MAX_PATH * 2] = {0};
			DWORD pathSize = sizeof(profilePath);
			DWORD type;
			if (RegQueryValueExW(hSub, L"ProfileImagePath", NULL, &type, (LPBYTE)profilePath, &pathSize) == ERROR_SUCCESS
					&& type == REG_SZ) {
				outPath = profilePath;
				found = true;
			}
			RegCloseKey(hSub);
		}
	}
	RegCloseKey(hProfileList);
	return found;
}
static unsigned int lastLogonFromProfile(const UnicodeString &userName) {
	UnicodeString profilePath;
	if (!findProfileImagePathByUserName(userName, profilePath)) return 0;

	UnicodeString ntUserPath = profilePath + "\\NTUSER.DAT";
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesExW(ntUserPath.c_str(), GetFileExInfoStandard, &fad))
		return 0;

	ULARGE_INTEGER uli;
	uli.LowPart = fad.ftLastWriteTime.dwLowDateTime;
	uli.HighPart = fad.ftLastWriteTime.dwHighDateTime;
	// FILETIME - 100-наносекундні інтервали з 1601-01-01, переводимо в Unix-секунди (з 1970-01-01)
	const unsigned long long EPOCH_DIFF_SEC = 11644473600ULL;
	unsigned long long unixSeconds = uli.QuadPart / 10000000ULL - EPOCH_DIFF_SEC;
	return (unsigned int)unixSeconds;
}
// LookupAccountNameW/LookupAccountSidW не бачать зв'язку з Microsoft-акаунтом -
// це властивість активної сесії входу, а не запису в SAM. Сам Windows кешує цей
// зв'язок у реєстрі:
//   HKLM\SOFTWARE\Microsoft\IdentityStore\LogonCache\<ProviderGUID>\Sid2Name\<CloudSid>
//     AuthenticatingAuthority = "MicrosoftAccount"
//     DisplayName             = повне ім'я, яке Windows поставила локальному
//                                акаунту при прив'язці (= usri3_full_name)
// Це працює повністю офлайн, без зовнішніх процесів - на відміну від
// PowerShell/Get-LocalUser, який (а) блимає консольним вікном при запуску,
// (б) може бути заблокований політиками на частині ПК.
static std::map<UnicodeString, UnicodeString> loadMicrosoftAccountFullNames() {
	std::map<UnicodeString, UnicodeString> result; // fullName (UpperCase) -> AuthenticatingAuthority
	HKEY hLogonCache;
	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
			L"SOFTWARE\\Microsoft\\IdentityStore\\LogonCache",
			0, KEY_READ, &hLogonCache) != ERROR_SUCCESS)
		return result;

	for (DWORD provIdx = 0; ; provIdx++) {
		WCHAR provKeyName[256];
		DWORD provKeyNameSize = 256;
		LONG provEnumRes = RegEnumKeyExW(hLogonCache, provIdx, provKeyName, &provKeyNameSize, NULL, NULL, NULL, NULL);
		if (provEnumRes == ERROR_NO_MORE_ITEMS) break;
		if (provEnumRes != ERROR_SUCCESS) continue;

		HKEY hSid2Name;
		if (RegOpenKeyExW(hLogonCache, (UnicodeString(provKeyName) + "\\Sid2Name").c_str(), 0, KEY_READ, &hSid2Name) != ERROR_SUCCESS)
			continue;

		for (DWORD sidIdx = 0; ; sidIdx++) {
			WCHAR sidKeyName[256];
			DWORD sidKeyNameSize = 256;
			LONG sidEnumRes = RegEnumKeyExW(hSid2Name, sidIdx, sidKeyName, &sidKeyNameSize, NULL, NULL, NULL, NULL);
			if (sidEnumRes == ERROR_NO_MORE_ITEMS) break;
			if (sidEnumRes != ERROR_SUCCESS) continue;

			HKEY hEntry;
			if (RegOpenKeyExW(hSid2Name, sidKeyName, 0, KEY_READ, &hEntry) != ERROR_SUCCESS) continue;

			WCHAR authBuf[128] = {0}; DWORD authSize = sizeof(authBuf);
			WCHAR nameBuf[256] = {0}; DWORD nameSize = sizeof(nameBuf);
			DWORD type;
			bool hasAuth = RegQueryValueExW(hEntry, L"AuthenticatingAuthority", NULL, &type, (LPBYTE)authBuf, &authSize) == ERROR_SUCCESS;
			bool hasName = RegQueryValueExW(hEntry, L"DisplayName", NULL, &type, (LPBYTE)nameBuf, &nameSize) == ERROR_SUCCESS;
			RegCloseKey(hEntry);
			if (hasAuth && hasName) {
				UnicodeString displayName = UnicodeString(nameBuf).Trim().UpperCase();
				if (!displayName.IsEmpty()) result[displayName] = UnicodeString(authBuf);
			}
		}
		RegCloseKey(hSid2Name);
	}
	RegCloseKey(hLogonCache);
	return result;
}
static UnicodeString getAccountType(const UnicodeString &fullName, const std::map<UnicodeString, UnicodeString> &msaFullNames) {
	UnicodeString key = fullName.Trim().UpperCase();
	if (key.IsEmpty()) return "Локальна";
	auto it = msaFullNames.find(key);
	if (it != msaFullNames.end() && it->second.UpperCase() == "MICROSOFTACCOUNT") return "Microsoft";
	return "Локальна";
}
//---------------------------------------------------------------------------
std::vector<User> currentUsers() {
	std::vector<User> curUsers;

	std::vector<LPUSER_INFO_3> list;
	LPUSER_INFO_3 pBuf = NULL;
	LPUSER_INFO_3 pTmpBuf;
	DWORD dwLevel = 3;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	NET_API_STATUS nStatus;
	LPTSTR pszServerName = NULL;
	WCHAR infoBuf[INFO_BUFFER_SIZE];
	DWORD bufCharCount = INFO_BUFFER_SIZE;
	do {
		nStatus = NetUserEnum((LPCWSTR)pszServerName, dwLevel,
			FILTER_NORMAL_ACCOUNT, // global users
			(LPBYTE*)&pBuf, dwPrefMaxLen, &dwEntriesRead, &dwTotalEntries,
			&dwResumeHandle);
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)) {
			if ((pTmpBuf = pBuf) != NULL) {
				for (i = 0; (i < dwEntriesRead); i++) {
					assert(pTmpBuf != NULL);
					if (pTmpBuf == NULL) break;
					list.push_back(pTmpBuf);
					pTmpBuf++;
				}
            }
		}
	}
	while (nStatus == ERROR_MORE_DATA);

	std::map<UnicodeString, UnicodeString> msaFullNames = loadMicrosoftAccountFullNames();
	for (auto user: list) {
		if (!(user->usri3_flags & UF_ACCOUNTDISABLE)) {
			User tempUser;
			/*
			UnicodeString name;
			UnicodeString fullName;
			unsigned int password_age;  // насколько стар пароль
			UnicodeString priv; 		// привилегии - GUEST, USER, ADMIN
			bool flags_ACCOUNTDISABLE, flags_LOCKOUT, flags_DONT_EXPIRE_PASSWD, flags_PASSWORD_EXPIRED;
			unsigned int password_expired;      // время с устаревания пароля
			unsigned int logon_bad, logon_good; // кол-во входа в систему
			*/
			tempUser.name = user->usri3_name;
			tempUser.fullName = user->usri3_full_name;
			tempUser.password_age = user->usri3_password_age/60/60/24;

			if(user->usri3_priv & USER_PRIV_GUEST) tempUser.priv = "GUEST";
			if(user->usri3_priv & USER_PRIV_USER)  tempUser.priv = "USER";
			if(user->usri3_priv & USER_PRIV_ADMIN) tempUser.priv = "ADMIN";

			if(user->usri3_flags & UF_ACCOUNTDISABLE) tempUser.flags_ACCOUNTDISABLE = true;
			else tempUser.flags_ACCOUNTDISABLE = false;
			if(user->usri3_flags & UF_LOCKOUT) tempUser.flags_LOCKOUT = true;
			else tempUser.flags_LOCKOUT = false;
			if(user->usri3_flags & UF_DONT_EXPIRE_PASSWD) tempUser.flags_DONT_EXPIRE_PASSWD = true;
			else tempUser.flags_DONT_EXPIRE_PASSWD = false;
			if(user->usri3_flags & UF_PASSWORD_EXPIRED) tempUser.flags_PASSWORD_EXPIRED = true;
			else tempUser.flags_PASSWORD_EXPIRED = false;

			tempUser.password_expired = user->usri3_password_age;

			tempUser.logon_bad = user->usri3_bad_pw_count;
			tempUser.logon_good = user->usri3_num_logons;
			tempUser.last_logon = user->usri3_last_logon;
			if (tempUser.last_logon == 0) tempUser.last_logon = lastLogonFromProfile(tempUser.name);
			tempUser.accountType = getAccountType(tempUser.fullName, msaFullNames);

			curUsers.push_back(tempUser);	
		}
    }
	return curUsers;
}
//---------------------------------------------------------------------------
