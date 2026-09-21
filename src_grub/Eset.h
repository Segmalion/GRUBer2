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
// Живий стан встановленого ESET Endpoint Security, читається через ermm.exe.
struct EsetInfoResult {
	bool esetFound = false;       // ermm.exe знайдено і викликано з правами адміна
	UnicodeString lastUpdateDate; // дата останнього успішного оновлення баз
	UnicodeString updateSource;   // сервер/шлях, звідки ESET тягне бази (best-effort)
	UnicodeString licenseStatus;  // статус ліцензії
};
// Без VCL - безпечно викликати з фонового потоку.
EsetInfoResult computeEsetInfo();
//---------------------------------------------------------------------------
#endif
