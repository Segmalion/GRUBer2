//---------------------------------------------------------------------------

#pragma hdrstop

#include <windows.h>
#include <lm.h>
#include "Users.h"

#define INFO_BUFFER_SIZE 32767
//---------------------------------------------------------------------------
#pragma package(smart_init)

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

			curUsers.push_back(tempUser);	
		}
    }
	return curUsers;
}
//---------------------------------------------------------------------------
