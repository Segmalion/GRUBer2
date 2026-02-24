//---------------------------------------------------------------------------

#pragma hdrstop

#include <windows.h>
#include "InstallSoft.h"
#include "Help.h"
#include "Text.h"

#include "Config.h"

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

#pragma package(smart_init)
//---------------------------------------------------------------------------
extern Config curConfig;
std::vector<UnicodeString> blockProgrammsNames;
std::vector<UnicodeString> UnBlockProgrammsNames;
//---------------------------------------------------------------------------
std::vector<program> read_hKey(HKEY hKey, UnicodeString typeProg) {
	std::vector<program> tempListSoft;

	wchar_t    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string
	wchar_t    achClass[MAX_PATH] = L"";  // buffer for class name
	DWORD    cchClassName = MAX_PATH;  // size of class string
	DWORD    cSubKeys=0;               // number of subkeys
	DWORD    cbMaxSubKey;              // longest subkey size
	DWORD    cchMaxClass;              // longest class string
	DWORD    cValues;              // number of values for key
	DWORD    cchMaxValue;          // longest value name
	DWORD    cbMaxValueData;       // longest value data
	DWORD    cbSecurityDescriptor; // size of security descriptor
	FILETIME ftLastWriteTime;      // last write time

    DWORD type;
	DWORD cdata;
    HKEY hSubkey;
	DWORD i, retCode;

	wchar_t  achValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;

	// Get the class name and the value count.
	retCode = RegQueryInfoKey(
		hKey,                    // key handle
		achClass,                // buffer for class name
		&cchClassName,           // size of class string
		NULL,                    // reserved
		&cSubKeys,               // number of subkeys
		&cbMaxSubKey,            // longest subkey size
		&cchMaxClass,            // longest class string
		&cValues,                // number of values for this key
		&cchMaxValue,            // longest value name
		&cbMaxValueData,         // longest value data
        &cbSecurityDescriptor,   // security descriptor
		&ftLastWriteTime);       // last write time

    // Enumerate the subkeys
	if (cSubKeys == 0) {
//		printLogDebug("Error: no subkeys!");
//		printLogDebug("{achKey}: " + UnicodeString(achKey));
//		wprintf(L"Error: no subkeys!\n",achKey);
	}
	else {
		for (i=0; i<cSubKeys; i++)
        {
			program soft;
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
					 achKey,
                     &cbName,
					 NULL,
					 NULL,
					 NULL,
					 &ftLastWriteTime);
			if (retCode != ERROR_SUCCESS) continue;
			else {
//				printLogDebug("RegEnumKeyEx SUCCESS");
//				printLogDebug("{achKey}: " + UnicodeString(achKey));
            }
			retCode =   RegOpenKey(hKey,achKey,&hSubkey);

			if(retCode != ERROR_SUCCESS){
//					wprintf(L"%s: RegOpenKey failed\n",achKey);
//					printLogDebug("RegOpenKey failed!");
//					printLogDebug("{achKey}: " + UnicodeString(achKey));
					continue;
			}

			soft.type = typeProg;
			WCHAR buffer[256];

			cdata = sizeof(buffer);
			retCode = RegQueryValueEx(hSubkey,L"DisplayName",NULL,&type,(LPBYTE)buffer,&cdata);
			if(retCode == ERROR_SUCCESS){
					soft.name = buffer;
					//soft.name = soft.name + " {" + UnicodeString(achKey) + "}";
			}

			cdata = sizeof(buffer);
			retCode = RegQueryValueEx(hSubkey,L"DisplayVersion",NULL,&type,(LPBYTE)buffer,&cdata);
			if(retCode == ERROR_SUCCESS){
					soft.version = buffer;
			}

			cdata = sizeof(buffer);
			retCode = RegQueryValueEx(hSubkey,L"Publisher",NULL,&type,(LPBYTE)buffer,&cdata);
			if(retCode == ERROR_SUCCESS){
					soft.publisher = buffer;
			}
			if (!soft.name.IsEmpty()) { // Добавляем, только если есть название
				tempListSoft.push_back(soft);
			} //else printLogDebug("NAME IsEmpty!");
			RegCloseKey(hSubkey);
		}
	}
	return tempListSoft;
}
//---------------------------------------------------------------------------
std::vector<program> installSoft() {
	std::vector<program> listSoft;
	std::vector<program> sort_listSoft;
	blockProgrammsNames = curConfig.get_softBlackList();
	UnBlockProgrammsNames = curConfig.get_softWriteList();

	HKEY hKey;

	LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
								L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
								0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS) {
		return listSoft;
	} else {
		std::vector<program> GlobalListSoft = read_hKey(hKey, "Global");
		listSoft.insert(listSoft.end(), GlobalListSoft.begin(), GlobalListSoft.end());
	}
	RegCloseKey(hKey);

	lResult = RegOpenKeyEx(HKEY_CURRENT_USER,
								L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
								0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS) {
		return listSoft;
	} else {
		std::vector<program> GlobalListSoft = read_hKey(hKey, "CurentUser");
		listSoft.insert(listSoft.end(), GlobalListSoft.begin(), GlobalListSoft.end());
	}
	RegCloseKey(hKey);

	if (x64()) {
		LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
									L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
									0, KEY_READ, &hKey);
		if (lResult != ERROR_SUCCESS) {
			return listSoft;
		} else {
			std::vector<program> GlobalListSoft = read_hKey(hKey, "Global(x32)");
			listSoft.insert(listSoft.end(), GlobalListSoft.begin(), GlobalListSoft.end());
		}
		RegCloseKey(hKey);

		lResult = RegOpenKeyEx(HKEY_CURRENT_USER,
									L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
									0, KEY_READ, &hKey);
		if (lResult != ERROR_SUCCESS) {
			return listSoft;
		} else {
			std::vector<program> GlobalListSoft = read_hKey(hKey, "CurentUser(x32)");
			listSoft.insert(listSoft.end(), GlobalListSoft.begin(), GlobalListSoft.end());
		}
		RegCloseKey(hKey);
	}
	return listSoft;
}
//---------------------------------------------------------------------------
std::vector<program> blockInstallSoft(std::vector<program> listSoft) {
	std::vector<program> blockListSoft;
	for (auto soft: listSoft) {
		bool UnBlock = false;
		for(auto UnBlockProgr: UnBlockProgrammsNames) {
			if (compareInSring(soft.name, UnBlockProgr)) UnBlock = true;
		}
		if (UnBlock) continue;
		for(auto blockProgr: blockProgrammsNames) {
			if (compareInSring(soft.name, blockProgr)) {
				blockListSoft.push_back(soft);
				break;
            }
		}
	}
	return blockListSoft;
}
//---------------------------------------------------------------------------
