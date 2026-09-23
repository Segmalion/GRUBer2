//---------------------------------------------------------------------------

#ifndef EsetH
#define EsetH

//---------------------------------------------------------------------------
// Каталог логів ESET Management Agent (містить trace.log).
UnicodeString getEsetLogsDir();
//---------------------------------------------------------------------------
// Живий стан встановленого ESET Endpoint Security, читається через ermm.exe.
// has* показує, чи вдалось отримати саме ЦЕЙ блок даних щойно - виклик має
// займати кеш (Arm::eset) лише коли відповідний has*==true, і лишати старе
// значення без змін інакше (ermm тимчасово недоступний/без прав адміна тощо).
struct EsetInfoResult {
	bool esetFound = false; // ermm.exe взагалі знайдено на диску

	bool hasUpdateDate = false;
	UnicodeString lastUpdateDate; // дата останнього успішного оновлення баз

	bool hasUpdateSource = false;
	bool autoUpdate = true;      // true = мережеве/авто джерело, false = локальна тека
	UnicodeString dirMirror;     // локальний шлях (лише коли autoUpdate=false)
	UnicodeString updateSourceFailReason; // причина, заповнена лише коли hasUpdateSource=false

	bool hasLicenseStatus = false;
	bool licenseActive = false; // true - ліцензія активна
	TDateTime licenseDate;      // дата закінчення ліцензії
	UnicodeString licenseKey;   // ключ ліцензії (public_id)

	bool hasProductID = false;
	UnicodeString productID; // ProductInstanceID з trace.log (поточного або архівного)
};
// Без VCL - безпечно викликати з фонового потоку.
EsetInfoResult computeEsetInfo();
//---------------------------------------------------------------------------
#endif
