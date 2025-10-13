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
			tempUser.name = user->usri3_name;
			tempUser.fullName = user->usri3_full_name;
			if(user->usri3_priv & USER_PRIV_ADMIN) tempUser.isAdmin = true;
			else tempUser.isAdmin = false; 
			curUsers.push_back(tempUser);	
		}
    }
	return curUsers;
}
//---------------------------------------------------------------------------
