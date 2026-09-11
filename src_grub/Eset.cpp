//---------------------------------------------------------------------------

#pragma hdrstop

#include <memory>

#include "Eset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

UnicodeString getEsetLogsDir()
{
	return "c:\\ProgramData\\ESET\\RemoteAdministrator\\Agent\\EraAgentApplicationData\\Logs\\";
}

UnicodeString getEsetProductInstanceID()
{
	UnicodeString notFound = L"Не знайдено";
	UnicodeString filePath = getEsetLogsDir() + "trace.log";
	UnicodeString marker = "ProductInstanceID:";

	if (!FileExists(filePath)) return notFound;

	std::unique_ptr<TStringList> log(new TStringList);
	try {
		// trace.log тримається відкритим агентом ESET - читаємо з дозволом
		// на спільний доступ, інакше TStringList::LoadFromFile впаде з
		// помилкою "used by another process".
		std::unique_ptr<TFileStream> stream(new TFileStream(filePath, fmOpenRead | fmShareDenyNone));
		log->LoadFromStream(stream.get(), TEncoding::UTF8);
	} catch (const Exception &) {
		return notFound;
	}

	for (int i = 0; i < log->Count; i++) {
		UnicodeString line = log->Strings[i];
		int pos = line.Pos(marker);
		if (pos == 0) continue;
		UnicodeString rest = line.SubString(pos + marker.Length(), line.Length()).Trim();
		int spacePos = rest.Pos(" ");
		return (spacePos == 0) ? rest : rest.SubString(1, spacePos - 1);
	}
	return notFound;
}
//---------------------------------------------------------------------------
