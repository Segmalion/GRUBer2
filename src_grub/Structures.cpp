//---------------------------------------------------------------------------
#pragma hdrstop

#include "Structures.h"
#include "Text.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const UnicodeString STRUCT_ID_UVS          = "default-uvs-pivden";
const UnicodeString STRUCT_ID_UVS_LOGIST   = "default-uvs-pivden-logist";
const UnicodeString STRUCT_ID_OK           = "default-ok-pivden";
const UnicodeString STRUCT_ID_OK_LOGIST    = "default-ok-pivden-logist";
//---------------------------------------------------------------------------
std::vector<StructureDef> defaultStructures() {
	std::vector<StructureDef> vStruct;
	StructureDef s;

	s = StructureDef();
	s.id = STRUCT_ID_UVS;
	s.name = "УВ(с) \"Південь\"";
	s.partition = vStrGenFromStr(
		"G-1 (Персонал); G-2 (Розвідка); G-3 ВіАЗ; G-3 ВН; G-3 ВН \"Запоріжжя\"; "
		"G-3 ВН \"Одеса\"; G-3 ВН \"Херсон\"; G-3 ГУО; G-3 Нач. ВН; G-3 Нач. ЦОУ; "
		"G-3 ПОЧ; G-3 СОЧ; G-3 СЧЗ; G-4 (Логістика); G-5 (Планування); G-6 (Звязок); "
		"G-6 (КіберБезпека); G-7 (Підготовка); G-8 (Фін.відділ); G-9 (ЦВС); "
		"G-E (КАРТОГРАФ); G-Е (СилПідтр); Адмін.Вд.; АТЦ СБУ; БПC; БПЛА; ВППП; "
		"ГрБВС (Охорона); ГрВАС (Дзвін); ГрВК; ГрСС; ІВФ - АА; ІВФ - ВМС; ІВФ - ВСП; "
		"ІВФ - ДПСУ; ІВФ - ДСНС; ІВФ - ДССТ; ІВФ - НГУ; ІВФ - НПУ; ІВФ - ТРО; ІТВ; "
		"СВК (Капелан); КДБ; КОКОН; МВС; Мед.Зб.; ОЗБРОЕНЯ; ОКІ; ПвК; ПУСЗ; РЕБ; ССО; "
		"ТИЛ; ФЕПС; ЦК; ЦЛЗ; ЦОВгП; ЦОВгП-ВТ (Таргетинг); ЦОДТ та ЗІ; ЦППО; "
		"ЦППО (РІВ); Юр.Вд.");
	vStruct.push_back(s);

	s = StructureDef();
	s.id = STRUCT_ID_UVS_LOGIST;
	s.name = "УВ(с) \"Південь\" - Логістика";
	s.partition = vStrGenFromStr("Логістика");
	vStruct.push_back(s);

	s = StructureDef();
	s.id = STRUCT_ID_OK;
	s.name = "ОК \"Південь\"";
	s.partition = vStrGenFromStr(
		"G-1 (5-відділ); G-1 (вКОС); G-1 (вКРтСС); G-1 (Діловод); G-1 (Моб.відділ); "
		"G-1 (Моніторинг); G-1 (Оберіг); G-1 (ОШВ); G-1 (УБД); G-2 (Розвідка); "
		"G-3 (Ком.Цнт.); G-4 (Логістика - ОК); G-4 (Логістика - Штаб); "
		"G-5 (Планування); G-6 (Звязок); G-6 (СЗІвАС); G-6 (Управління Зв'язку); "
		"G-7 (Підготовка - ОК); G-7 (Підготовка - Штаб); G-8 (Планування ОР); "
		"G-E (Підтримка); Адмін.Вд.; БВС (Охорона); БпС (БезпілотніСист); "
		"Від.ВСІ(А)С; гр.Контр; гр.СС; ІТВ (Вітязь-2); ІТВ (Вітязь-3); Капелан; "
		"Кокон; МВС; Мед.заб.; ППО; ППП; ПУСЗ; РВІА; РЕБ; Так.Мед.; Фін.Від.; ЦВС; "
		"ЦК; цОДТ; Юр.Від.");
	vStruct.push_back(s);

	s = StructureDef();
	s.id = STRUCT_ID_OK_LOGIST;
	s.name = "ОК \"Південь\" - Логістика";
	s.partition = vStrGenFromStr("Логістика");
	vStruct.push_back(s);

	return vStruct;
}
//---------------------------------------------------------------------------
UnicodeString generateStructureId() {
	UnicodeString seed = FormatDateTime("yyyymmddhhnnsszzz", Now()) + IntToStr(Random(MAXINT));
	return GetFastHash_CRC32(seed).LowerCase();
}
//---------------------------------------------------------------------------
