//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

// Подключаем заголовочные файлы нашей логики
#include "MainDevLister.h"
//---------------------------------------------------------------------------
USEFORM("MainDevLister.cpp", Form1);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        // 1. Проверяем аргументы командной строки ДО инициализации VCL
		// Нам нужно как минимум 2 аргумента: "-silent" и "путь к файлу"
		bool silent = false;
		UnicodeString outputPath;
		short t_cat = 0;
		if (ParamCount() > 0)
		{
			for (int i=1;i<=ParamCount();i++) {
				if (ParamStr(i).LowerCase() == L"-silent") {
					outputPath = ParamStr(i+1);
					silent = true;
				}
				if (ParamStr(i).LowerCase() == L"-cat") {
					t_cat = ParamStr(i+1).ToIntDef(0);
					if (t_cat > 4 || t_cat < 0) t_cat = 0;
					indefPC.catPC = t_cat;
				}
			}
			if (silent) {
				// Выполняем сбор информации о ПК (у вас в коде это глобальные функции)
				getInfoPC();

				// Сканируем устройства системы (возвращает std::vector<deviceInfo>)
				std::vector<deviceInfo> devices = scanDevices();

				// Проверяем статус по вашей базе/файлам (у вас в коде checkRegDevice)
				// Если для работы checkRegDevice() обязательно нужно подключение к БД,
				// можно быстро создать временный объект TForm1 без его показа:
				// std::unique_ptr<TForm1> silentForm(new TForm1(nullptr));
				// silentForm->createDB();
				// silentForm->vectorToBD(devices);

				checkRegDevice(devices);

				// Вызываем вашу готовую функцию сохранения в JSON
				// (Она объявлена у вас в MainDevLister.h)
				if (SaveDataToJSON(outputPath, indefPC, devices))
				{
					// Успешно сохранено, выходим из программы с кодом 0
					return 0;
				}
				else
				{
					// Ошибка сохранения, выходим с кодом ошибки
					return 1;
				}
			}
		}

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
