//---------------------------------------------------------------------------

#ifndef RunAppH
#define RunAppH
//---------------------------------------------------------------------------
class RunApp {
private:
	UnicodeString app;
	UnicodeString arg;
	UnicodeString dir;
	bool runas;
	bool hide;
	struct eC {
		bool run;  // результат запуска
		bool exit; // результат выполнения
		// 0 - без ошибки, 1 - с ошибкой
		UnicodeString runCode;
		UnicodeString exitCode;
	};
	bool check();
public:
	void run (bool h = true, bool r = false);
	eC error;
	void setApp(UnicodeString apS);
	void setArg(UnicodeString arS);
};

#endif
