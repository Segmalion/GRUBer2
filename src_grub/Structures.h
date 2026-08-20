//---------------------------------------------------------------------------
#ifndef StructuresH
#define StructuresH

#include <vector>
//---------------------------------------------------------------------------
// Визначення структури (глобальне, зберігається в GRUBer.ini через Config)
struct StructureDef {
	UnicodeString id;
	UnicodeString name;
	std::vector<UnicodeString> partition; // список відділів за замовчуванням
};
// Дані структури для конкретного ПК (зберігаються в gruber_info.ini через Arm)
struct StructurePcData {
	UnicodeString id;
	UnicodeString name; // дублюється для читабельності gruber_info.ini
	int number = 0;
	UnicodeString partition, place, phone;
};
//---------------------------------------------------------------------------
// фіксовані ід. 4-х вбудованих структур - однакові на будь-якій інсталяції
// GRUBer, щоб міграція зі старого формату та подальша агрегація файлів з
// різних ПК були детермінованими
extern const UnicodeString STRUCT_ID_UVS;
extern const UnicodeString STRUCT_ID_UVS_LOGIST;
extern const UnicodeString STRUCT_ID_OK;
extern const UnicodeString STRUCT_ID_OK_LOGIST;
//---------------------------------------------------------------------------
std::vector<StructureDef> defaultStructures();
UnicodeString generateStructureId();
#endif
