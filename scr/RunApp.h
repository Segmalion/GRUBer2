//---------------------------------------------------------------------------

#ifndef RunAppH
#define RunAppH
//---------------------------------------------------------------------------
class RunApp {
private:
    UnicodeString app;
	UnicodeString app32;
	UnicodeString app64;
	UnicodeString arg;
	UnicodeString dir;
	bool runas;
	bool hide;
	struct eC {
		bool run;  // результат запуска
		short exit; // результат выполнения
		// 0 - без ошибки, 1 - с ошибкой, -1 - ручная остановка
		UnicodeString runCode;
		UnicodeString exitCode;
	} error;
	bool check();
public:
	RunApp(UnicodeString apSx32, UnicodeString apSx64 = NULL, UnicodeString arS = NULL);
	//func
	void run (bool h = true, bool r = false);
	UnicodeString errorString();
	UnicodeString resultString();
	bool checkErr();
	// геттер

};

#endif
