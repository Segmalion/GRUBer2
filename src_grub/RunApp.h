//---------------------------------------------------------------------------

#ifndef RunAppH
#define RunAppH

#include <atomic>
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
	// додатковий прапорець скасування, окрім глобальних stopBool/passBool
	// (напр. кнопка "Зупинити завантаження" ESET не повинна зупиняти Граб і навпаки)
	std::atomic<bool> *externalStop = nullptr;
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
	//сеттер
	void set_dir(UnicodeString d);
	void set_externalStop(std::atomic<bool> *flag);
};

#endif
