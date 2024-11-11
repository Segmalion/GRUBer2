//---------------------------------------------------------------------------

#pragma hdrstop

#include "Arm.h"
#include "Text.h"
#include "GetSMB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

UnicodeString Arm::dirCurGrubName (UnicodeString date)
{
	UnicodeString str;
	str = "[";
	// number
	if (number == 0) {
		str = str + "--";
	} else str = str + UnicodeString(number);
	str = str + "][" + date + "]";
	// partition
	str = str + partitionName;
	// serial
	str = str + "#" + serial;
	// category
	str = str + "#" + categoryName;
	return fixDirName(str);
}
bool Arm::getInfo()
{
	// Get DesktopName
	TCHAR infoBuf[32767];
	DWORD bufCharCount = 32767;
	if( GetComputerName( infoBuf, &bufCharCount ) ) {
		desktopName = UnicodeString(infoBuf);
	} else return false;
	// Get SMB date
	GetSMB g;
	PRAW_SMBIOS_DATA dataSMB = g.GetSmbiosData();
	if (dataSMB == NULL) {
		return false;
	}
	serial = g.PrintBiosString(dataSMB, SMB_TABLE_CHASSIS, 7);
   return true;
}
