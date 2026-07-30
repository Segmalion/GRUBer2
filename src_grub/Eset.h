//---------------------------------------------------------------------------

#ifndef EsetH
#define EsetH

//---------------------------------------------------------------------------
// Каталог логів ESET Management Agent (містить trace.log).
UnicodeString getEsetLogsDir();
// Читає ProductInstanceID (ESET ID) з trace.log ESET Management Agent.
// Повертає "Не знайдено", якщо файл або відповідний рядок відсутні.
UnicodeString getEsetProductInstanceID();
//---------------------------------------------------------------------------
#endif
