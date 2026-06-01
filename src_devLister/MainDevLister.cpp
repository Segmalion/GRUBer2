//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <windows.h>
#include <initguid.h>
#include <devpkey.h>      // Для DEVPKEY_Device_ContainerId
#include <combaseapi.h>   // Для конвертации GUID в строку
#include <filesystem>
#include <algorithm>

#include <devquery.h>

#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

#pragma comment(lib, "cfgmgr32.lib") // <-- Добавили для работы функции статуса

#include <iostream>
#include <map>
#include <vector>

#include "MainDevLister.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#ifndef DEVPKEY_DeviceContainer_Name
DEFINE_DEVPROPKEY(DEVPKEY_DeviceContainer_Name, 0x78c34fc8, 0x104a, 0x4aca, 0x9e, 0xa4, 0x52, 0x4d, 0x52, 0x99, 0x6e, 0x57, 37);
#endif

// --- ТИПЫ ДЛЯ ДИНАМИЧЕСКОЙ ЗАГРУЗКИ DEVQUERY ---
typedef HRESULT (WINAPI *PDevGetObjectProperties)(
    DEV_OBJECT_TYPE ObjectType,
    PCWSTR pszObjectId,
    ULONG QueryFlags,
    ULONG cRequestedProperties,
    const DEVPROPCOMPKEY *pRequestedProperties,
    PULONG pcPropertyCount,
    const DEVPROPERTY **ppProperties
);

typedef VOID (WINAPI *PDevFreeObjectProperties)(
    ULONG cPropertyCount,
    const DEVPROPERTY *pProperties
);
//---------------------------------------------------------------------------
TForm1 *Form1;

short badCharSerial = 0;
short catPC = 0;
double multipler;
std::vector<deviceInfo> devicesList;
std::vector<registeredUsb> regUsbList;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	fs::path p_fileRegUsb = fs::current_path() / "registered.txt";
	regUsbList = readRegUsbFile(p_fileRegUsb);
	createDB();
    Button_DeviceUpdateCurPCClick(this);
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::RemoveDeviceFromWindows(UnicodeString instanceId)
{
    // 1. Создаем пустой набор устройств
    HDEVINFO hDevInfo = SetupDiCreateDeviceInfoList(NULL, NULL);
    if (hDevInfo == INVALID_HANDLE_VALUE) {
        printLog(L"Ошибка SetupDiCreateDeviceInfoList: " + SysErrorMessage(GetLastError()));
        return false;
    }

    // 2. Открываем (находим) конкретное устройство в системе по его Instance ID
    SP_DEVINFO_DATA devInfoData;
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    if (!SetupDiOpenDeviceInfoW(hDevInfo, instanceId.c_str(), NULL, 0, &devInfoData)) {
        printLog(L"Ошибка SetupDiOpenDeviceInfoW (Устройство не найдено в ОС): " + SysErrorMessage(GetLastError()));
        SetupDiDestroyDeviceInfoList(hDevInfo);
        return false;
    }

    // 3. Подготавливаем параметры для удаления устройства (DIF_REMOVE)
    SP_REMOVEDEVICE_PARAMS rmParams;
    rmParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
    rmParams.ClassInstallHeader.InstallFunction = DIF_REMOVE;
    rmParams.Scope = DI_REMOVEDEVICE_GLOBAL; // Удаляем глобально изо всех профилей оборудования
    rmParams.HwProfile = 0;

    // Устанавливаем параметры класса для нашего устройства
    if (!SetupDiSetClassInstallParamsW(hDevInfo, &devInfoData, &rmParams.ClassInstallHeader, sizeof(rmParams))) {
        printLog(L"Ошибка SetupDiSetClassInstallParamsW: " + SysErrorMessage(GetLastError()));
        SetupDiDestroyDeviceInfoList(hDevInfo);
        return false;
    }

    // 4. ВЫЗЫВАЕМ СИСТЕМНЫЙ ИНСТАЛЛЯТОР ДЛЯ ФИЗИЧЕСКОГО УДАЛЕНИЯ
    if (!SetupDiCallClassInstaller(DIF_REMOVE, hDevInfo, &devInfoData)) {
        DWORD err = GetLastError();
        if (err == ERROR_ACCESS_DENIED) {
            printLog(L"ОШИБКА: Отказано в доступе. Запустите программу от ИМЕНИ АДМИНИСТРАТОРА!");
        } else {
            printLog(L"Ошибка SetupDiCallClassInstaller (DIF_REMOVE): " + SysErrorMessage(err));
        }
        SetupDiDestroyDeviceInfoList(hDevInfo);
        return false;
    }

    // Освобождаем выделенную память под списки SetupAPI
    SetupDiDestroyDeviceInfoList(hDevInfo);
    return true;
}
bool __fastcall TForm1::RemoveContainerDevicesFromWindows(UnicodeString targetContainerId)
{
    // Приводим GUID к верхнему регистру для точного сравнения
    targetContainerId = targetContainerId.UpperCase().Trim();
    if (targetContainerId.IsEmpty() || targetContainerId == L"NO CONTAINER" || targetContainerId == L"GUID ERROR") {
        printLog(L"Ошибка: Некорректный Container ID для удаления.");
        return false;
    }

    // 1. Получаем список ВСЕХ устройств в системе (включая отключенные)
    HDEVINFO hDevInfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES);
    if (hDevInfo == INVALID_HANDLE_VALUE) {
        printLog(L"Ошибка SetupDiClassDevs: " + SysErrorMessage(GetLastError()));
        return false;
    }

    SP_DEVINFO_DATA devInfoData;
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    DWORD deviceIndex = 0;
    int deletedCount = 0;
    int errorCount = 0;

    // Подгружаем cfgmgr32.dll для чтения DEVPKEY_Device_ContainerId у каждого устройства
    HMODULE hCfgMgr = LoadLibraryW(L"cfgmgr32.dll");
    PDevGetObjectProperties pDevGetObjectProperties = NULL;
    PDevFreeObjectProperties pDevFreeObjectProperties = NULL;

    if (hCfgMgr) {
        pDevGetObjectProperties = (PDevGetObjectProperties)GetProcAddress(hCfgMgr, "DevGetObjectProperties");
        pDevFreeObjectProperties = (PDevFreeObjectProperties)GetProcAddress(hCfgMgr, "DevFreeObjectProperties");
    }

    if (!pDevGetObjectProperties || !pDevFreeObjectProperties) {
        printLog(L"Ошибка: Не удалось загрузить функции работы с контейнерами из cfgmgr32.dll");
        if (hCfgMgr) FreeLibrary(hCfgMgr);
        SetupDiDestroyDeviceInfoList(hDevInfo);
        return false;
    }

    // 2. Цикл перебора всех устройств компьютера
    while (SetupDiEnumDeviceInfo(hDevInfo, deviceIndex, &devInfoData))
    {
        deviceIndex++;

        // Получаем Instance ID текущего проверяемого устройства
        wchar_t instanceIdBuf[512] = L"";
        if (!SetupDiGetDeviceInstanceIdW(hDevInfo, &devInfoData, instanceIdBuf, 512, NULL)) {
            continue;
        }
        UnicodeString currentInstanceId = UnicodeString(instanceIdBuf);

        // Запрашиваем у Windows Container ID для этого Instance ID
        DEVPROPCOMPKEY reqKey[] = { { DEVPKEY_Device_ContainerId, DEVPROP_STORE_SYSTEM, NULL } };
        ULONG propCount = 0;
        const DEVPROPERTY* properties = NULL;
        UnicodeString currentContainerId = L"";

        HRESULT hr = pDevGetObjectProperties(DevObjectTypeDevice, currentInstanceId.c_str(), DevQueryFlagNone, 1, reqKey, &propCount, &properties);
        if (SUCCEEDED(hr) && propCount > 0 && properties != NULL) {
            if (properties[0].Type == 13 && properties[0].Buffer != NULL) { // 13 = DEVPROP_TYPE_GUID
                GUID containerGuid = *(GUID*)properties[0].Buffer;
                wchar_t guidStr[64] = L"";
                if (StringFromGUID2(containerGuid, guidStr, 64) > 0) {
                    currentContainerId = UnicodeString(guidStr).UpperCase().Trim();
                }
            }
            pDevFreeObjectProperties(propCount, properties);
        }

        // 3. Если Container ID совпал — удаляем это конкретное устройство из ОС Windows
        if (currentContainerId == targetContainerId)
        {
            SP_REMOVEDEVICE_PARAMS rmParams;
            rmParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
            rmParams.ClassInstallHeader.InstallFunction = DIF_REMOVE;
            rmParams.Scope = DI_REMOVEDEVICE_GLOBAL;
            rmParams.HwProfile = 0;

            if (SetupDiSetClassInstallParamsW(hDevInfo, &devInfoData, &rmParams.ClassInstallHeader, sizeof(rmParams)))
            {
                if (SetupDiCallClassInstaller(DIF_REMOVE, hDevInfo, &devInfoData)) {
                    deletedCount++;
                } else {
                    errorCount++;
                }
            } else {
                errorCount++;
            }
        }
    }

    // Освобождаем ресурсы
    FreeLibrary(hCfgMgr);
    SetupDiDestroyDeviceInfoList(hDevInfo);

    printLog(L"Удаление контейнера из ОС завершено. Удалено устройств: " + IntToStr(deletedCount) + L", ошибок: " + IntToStr(errorCount));
    return (deletedCount > 0 && errorCount == 0);
}
void __fastcall TForm1::DelDevice() {
    // 1. Проверяем, активна ли таблица и выбрана ли строка
	if (!FDQuery1->Active || FDQuery1->IsEmpty()) {
        printLog(L"Удаление невозможно: список устройств пуст.");
        return;
    }

	// 2. Вытаскиваем данные текущей строки из FDQuery1
	UnicodeString instanceId = FDQuery1->FieldByName(L"dev_instance_id")->AsString;
    UnicodeString currentStatus = FDQuery1->FieldByName(L"status")->AsString;
	UnicodeString deviceName = FDQuery1->FieldByName(L"friendly_name")->AsString;
    if (deviceName.IsEmpty()) {
		deviceName = FDQuery1->FieldByName(L"dev_desc")->AsString;
    }

    // 3. ПРОВЕРКА БЕЗОПАСНОСТИ: Запрещаем удалять подключенные устройства
    if (currentStatus == L"CONNECT") {
        MessageDlg(L"Нельзя удалить активное устройство из Windows!\n"
                   L"Сначала физически отключите его из USB-порта.",
                   mtError, TMsgDlgButtons() << mbOK, 0);
        return;
	}

    // 4. Запрашиваем подтверждение у пользователя
    UnicodeString question = L"Вы действительно хотите навсегда УДАЛИТЬ устройство из операционной системы Windows?\n\n\""
							 + deviceName + L"\"\n\n(При следующем подключении оно будет определяться как новое)";

    if (MessageDlg(question, mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) != mrYes) {
		return; // Пользователь отменил операцию
    }

	// 5. Вызываем наш системный метод удаления
	if (RemoveDeviceFromWindows(instanceId)) {
		printLog(L"Устройство успешно удалено из Windows: " + deviceName);
		Button_DeviceUpdateCurPCClick(this);
		MessageDlg(L"Устройство успешно удалено из операционной системы.", mtInformation, TMsgDlgButtons() << mbOK, 0);
    } else {
		MessageDlg(L"Не удалось удалить устройство. Проверьте логи программы и права Администратора.", mtError, TMsgDlgButtons() << mbOK, 0);
	}
}
void __fastcall TForm1::DelContainerDevice() {
    // 1. Проверяем, выбрано ли хоть что-то в гриде
    if (!FDQuery1->Active || FDQuery1->IsEmpty()) {
		printLog(L"Удаление невозможно: список пуст.");
        return;
    }

	// 2. Получаем Container ID выделенной строки
	UnicodeString containerId = FDQuery1->FieldByName(L"containerId")->AsString;
    UnicodeString containerName = FDQuery1->FieldByName(L"containerName")->AsString;

    if (containerId.IsEmpty() || containerId == L"No Container" || containerId == L"GUID Error") {
        MessageDlg(L"У выбранного устройства нет валидного Контейнера для группового удаления.", mtError, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    // 3. ПРОВЕРКА БЕЗОПАСНОСТИ: Нельзя удалять контейнер, если внутри есть хоть одно АКТИВНОЕ устройство!
    TFDQuery *FDQuery_Check = new TFDQuery(NULL);
    bool hasActiveDevices = false;
    int totalDevicesInContainer = 0;
    try {
        FDQuery_Check->Connection = FDConnection1;
        FDQuery_Check->SQL->Text = L"SELECT COUNT(*) as total, SUM(CASE WHEN status = 'CONNECT' THEN 1 ELSE 0 END) as active FROM devices WHERE containerId = :p_cid";
        FDQuery_Check->ParamByName(L"p_cid")->AsString = containerId;
        FDQuery_Check->Open();

        if (!FDQuery_Check->IsEmpty()) {
            totalDevicesInContainer = FDQuery_Check->FieldByName(L"total")->AsInteger;
            hasActiveDevices = (FDQuery_Check->FieldByName(L"active")->AsInteger > 0);
        }
    } __finally {
        delete FDQuery_Check;
    }

    if (hasActiveDevices) {
        MessageDlg(L"Невозможно удалить контейнер!\nВнутри него есть активные (подключенные) устройства.\nСначала отключите оборудование физически.",
                   mtError, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    // 4. Запрашиваем подтверждение у пользователя
	UnicodeString prompt = "Вы действительно хотите навсегда УДАЛИТЬ контейнер из Windows и программы?\n\n"
						   "Контейнер: \"" + containerName + "\"\n"
						   "GUID: " + containerId + "\n"
						   "Будет удалено связанных устройств: " + IntToStr(totalDevicesInContainer);

    if (MessageDlg(prompt, mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) != mrYes) {
        return; // Отмена
    }

    // 5. Вызываем деинсталляцию из самой Windows (Программа должна быть запущена от Админа!)
	// Метод вернет true, если успешно удалил устройства из ОС
	if (RemoveContainerDevicesFromWindows(containerId)) {
		printLog(L"Устройства успешно удалены из Windows!");
		Button_DeviceUpdateCurPCClick(this);
		MessageDlg(L"Устройство успешно удалено из операционной системы.", mtInformation, TMsgDlgButtons() << mbOK, 0);
    } else {
		MessageDlg(L"Не удалось удалить устройство. Проверьте логи программы и права Администратора.", mtError, TMsgDlgButtons() << mbOK, 0);
	}
}

void __fastcall TForm1::WndProc(Winapi::Messages::TMessage &Message)
{
    // Проверяем, пришло ли сообщение об изменении состава оборудования
    if (Message.Msg == WM_DEVICECHANGE && CheckBox_AutoUpdateDev->Checked)
    {
        // DBT_DEVNODES_CHANGED (0x0007) означает, что дерево устройств было пересчитано
        // (устройство добавлено, удалено или сменило статус)
        if (Message.WParam == 0x0007)
		{
			Timer1->Enabled = false; // Сбрасываем предыдущий дребезг
    		Timer1->Enabled = true;  // Запускаем отсчет 1000 мс заново
		}
    }

    // ОБЯЗАТЕЛЬНО передаем все остальные сообщения дальше по цепочке VCL,
    // иначе форма перестанет реагировать на мышь, клавиатуру и закрытие окна!
    TForm::WndProc(Message);
}
/* Конвертор даты */
TDateTime fileTimeToDateTime (const FILETIME &ft) {
	SYSTEMTIME stUTC, stLocal;
	// Переводим FILETIME -> SYSTEMTIME (UTC) -> Локальное время компьютера
	if (FileTimeToSystemTime(&ft, &stUTC) && SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal)) {
		try {
			// Создаем TDateTime на основе полученных системных компонентов времени
			return TDateTime(stLocal.wYear, stLocal.wMonth, stLocal.wDay,
							 stLocal.wHour, stLocal.wMinute, stLocal.wSecond, stLocal.wMilliseconds);
		} catch (...) {
			return 0; // В случае непредвиденной ошибки возвращаем пустую дату
		}
	}
	return 0; // Если Windows вернула некорректный буфер времени
};
/* Вывод логов */
void printLog(UnicodeString str)
{
	TDateTime myTimeTemp = Now();
	UnicodeString logTime = myTimeTemp.FormatString("hh:mm:ss");
	str = "[" + logTime + "]" + str;
	Form1->Memo_LOG->Lines->Add(str);
}
/* Сканер устройств */
std::vector<deviceInfo> scanDevices() {
	std::vector<deviceInfo> v_tempDevList;

	// 1. Получаем список всех присутствующих устройств
	HDEVINFO hDevInfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES);

	if (hDevInfo == INVALID_HANDLE_VALUE) {
		printLog("Failed to get devices");
		return v_tempDevList;
	}

	SP_DEVINFO_DATA devInfoData;
	devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	// 2. Перечисляем устройства
	for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData); ++i) {
		DWORD dataType;
		deviceInfo device;
		// === вспомагательная функция
		auto getProperty = [&](DWORD property) -> UnicodeString {
			wchar_t buffer[512];
			if (SetupDiGetDeviceRegistryPropertyW(hDevInfo, &devInfoData, property,
				&dataType, (PBYTE)buffer, sizeof(buffer), NULL)) {
				return UnicodeString(buffer);
			}
			return UnicodeString("");
		};

		// === заполнение структуры
		device.className = getProperty(SPDRP_CLASS);
		device.enumeratorName = getProperty(SPDRP_ENUMERATOR_NAME);
		device.friendlyName = getProperty(SPDRP_FRIENDLYNAME);
		device.devDesc = getProperty(SPDRP_DEVICEDESC);

		// - Получение Device Instance ID для извлечения серийного номера
		wchar_t instanceId[512] = L"";
		if (SetupDiGetDeviceInstanceIdW(hDevInfo, &devInfoData, instanceId, sizeof(instanceId) / sizeof(wchar_t), NULL)) {
			device.devInstanceID = UnicodeString(instanceId);

			// Ищем позицию последнего слэша '\'
			int lastSlashPos = device.devInstanceID.LastDelimiter(L"\\");
			if (lastSlashPos > 0) {
				// Вырезаем всё, что идет после последнего слэша
				UnicodeString serial = device.devInstanceID.SubString(lastSlashPos + 1, device.devInstanceID.Length() - lastSlashPos);

				// 1. ОТРЕЗАЕМ ХВОСТ ПОРТА/ИНТЕРФЕЙСА (&0, &1 и т.д.), если он есть
				int lastAmpPos = serial.LastDelimiter(L"&");
				// Проверяем, что амперсанд находится близко к концу строки (например, в пределах последних 3 символов)
				if (lastAmpPos > 0 && lastAmpPos >= (serial.Length() - 3)) {
					serial = serial.SubString(1, lastAmpPos - 1); // Отрезаем "&0"
				}

				// 2. ПРОВЕРКА НА ОСТАВШИЕСЯ АМПЕРСАНДЫ
				// Если после удаления хвоста в строке ВСЁ ЕЩЕ есть '&',
				// значит это сгенерированный Windows системный путь (типа 5&23a0781b&0), а не серийник.
				if (serial.Pos(L"&") > 0) {
					device.serialNumber = L""; // Очищаем мусор
				} else {
					device.serialNumber = serial; // Сохраняем чистый красивый серийник флешки!
				}
			} else {
				device.serialNumber = L"";
			}
		} else {
			device.serialNumber = L"";
			device.devInstanceID = L"";
		}

		// --- ПРОВЕРКА СТАТУСА
		ULONG devStatus = 0;
		ULONG devProblem = 0;
		if (CM_Get_DevNode_Status(&devStatus, &devProblem, devInfoData.DevInst, 0) == CR_SUCCESS) {
			device.status = L"CONNECT";
		} else {
			device.status = L"DISCONNECT";
		}

		// --- ПОЛУЧЕНИЕ CONTAINER ID ---
		DEVPROPTYPE propType;
		GUID containerGuid;
		DWORD requiredSize = 0;

		if (SetupDiGetDevicePropertyW(hDevInfo, &devInfoData, &DEVPKEY_Device_ContainerId,
			&propType, (PBYTE)&containerGuid, sizeof(GUID), &requiredSize, 0)) {
			wchar_t guidStr[40];
			if (StringFromGUID2(containerGuid, guidStr, 40) > 0) {
				device.containerId = UnicodeString(guidStr).Trim();
			} else {
				device.containerId = L"GUID Error";
			}
		} else {
			device.containerId = L"No Container";
		}

		// --- (Динамическая загрузка) ---
		if (device.containerId != L"No Container" && device.containerId != L"GUID Error") {
			HMODULE hDevQueryDll = LoadLibraryW(L"cfgmgr32.dll");
			if (hDevQueryDll) {
				PDevGetObjectProperties pDevGetObjectProperties = (PDevGetObjectProperties)GetProcAddress(hDevQueryDll, "DevGetObjectProperties");
				PDevFreeObjectProperties pDevFreeObjectProperties = (PDevFreeObjectProperties)GetProcAddress(hDevQueryDll, "DevFreeObjectProperties");

				if (pDevGetObjectProperties && pDevFreeObjectProperties) {
					// ===== ID контейнера =====
					DEVPROPCOMPKEY requestedProperties[] = { { DEVPKEY_DeviceContainer_Name, DEVPROP_STORE_SYSTEM, NULL } };
					ULONG propertyCount = 0;
					const DEVPROPERTY* properties = NULL;

					HRESULT hr = pDevGetObjectProperties(DevObjectTypeDeviceContainer, device.containerId.c_str(), DevQueryFlagNone, 1, requestedProperties, &propertyCount, &properties);

					if (SUCCEEDED(hr) && propertyCount > 0 && properties != NULL) {
						if (properties[0].Type == 18 && properties[0].Buffer != NULL) {
							device.containerName = UnicodeString((PCWSTR)properties[0].Buffer);
						} else {
							if (!device.friendlyName.IsEmpty()) {
								device.containerName = device.friendlyName;
							} else {
								device.containerName = device.devDesc;
							}
						}
						pDevFreeObjectProperties(propertyCount, properties);
					} else {
						device.containerName = L"Не найдено в DevQuery";
					}
					// ===== ДАТЫ =====
					// Инициализируем даты нулями (пустые значения по умолчанию)
					device.firstInstallDate = 0;
					device.installDate = 0;
					device.lastConnect = 0;
					device.lastDisconnect = 0;
					// --- ЗАПРОС ДАТЫ ПЕРВОЙ УСТАНОВКИ (First Install Date)
					DEVPROPCOMPKEY requestedDateFirstInstall[] = { { DEVPKEY_Device_FirstInstallDate, DEVPROP_STORE_SYSTEM, NULL } };
					ULONG firstInstallPropCount = 0;
					const DEVPROPERTY* firstInstallProperties = NULL;

					HRESULT hrFirstInstall = pDevGetObjectProperties(
						DevObjectTypeDevice,
						device.devInstanceID.c_str(),
						DevQueryFlagNone,
						1,
						requestedDateFirstInstall,
						&firstInstallPropCount,
						&firstInstallProperties
					);

					if (SUCCEEDED(hrFirstInstall) && firstInstallPropCount > 0 && firstInstallProperties != NULL) {
						if (firstInstallProperties[0].Type == 16 && firstInstallProperties[0].Buffer != NULL) { // 16 = DEVPROP_TYPE_FILETIME
							FILETIME ft = *(FILETIME*)firstInstallProperties[0].Buffer;
							device.firstInstallDate = fileTimeToDateTime(ft); // Наша функция конвертации
						}
						pDevFreeObjectProperties(firstInstallPropCount, firstInstallProperties);
					}
					// --- ЗАПРОС ДАТЫ ПОСЛЕДНЕЙ УСТАНОВКИ/ОБНОВЛЕНИЯ ДРАЙВЕРА (Install Date)
					DEVPROPCOMPKEY requestedDateInstall[] = { { DEVPKEY_Device_InstallDate, DEVPROP_STORE_SYSTEM, NULL } };
					ULONG installPropCount = 0;
					const DEVPROPERTY* installProperties = NULL;

					HRESULT hrInstall = pDevGetObjectProperties(
						DevObjectTypeDevice,
						device.devInstanceID.c_str(),
						DevQueryFlagNone,
						1,
						requestedDateInstall,
						&installPropCount,
						&installProperties
					);

					if (SUCCEEDED(hrInstall) && installPropCount > 0 && installProperties != NULL) {
						if (installProperties[0].Type == 16 && installProperties[0].Buffer != NULL) {
							FILETIME ft = *(FILETIME*)installProperties[0].Buffer;
							device.installDate = fileTimeToDateTime(ft); // Наша функция конвертации
						}
						pDevFreeObjectProperties(installPropCount, installProperties);
					}
					// --- ЗАПРОС ДАТЫ ПОСЛЕДНЕГО ПОДКЛЮЧЕНИЯ (Arrival Date)
					DEVPROPCOMPKEY requestedDateArrival[] = { { DEVPKEY_Device_LastArrivalDate, DEVPROP_STORE_SYSTEM, NULL } };
					ULONG arrivalPropCount = 0;
					const DEVPROPERTY* arrivalProperties = NULL;

					HRESULT hrArrival = pDevGetObjectProperties(
						DevObjectTypeDevice,
						device.devInstanceID.c_str(),
						DevQueryFlagNone,
						1,
						requestedDateArrival,
						&arrivalPropCount,
						&arrivalProperties
					);

					if (SUCCEEDED(hrArrival) && arrivalPropCount > 0 && arrivalProperties != NULL) {
						if (arrivalProperties[0].Type == 16 && arrivalProperties[0].Buffer != NULL) { // 16 = DEVPROP_TYPE_FILETIME
							FILETIME ft = *(FILETIME*)arrivalProperties[0].Buffer;
							device.lastConnect = fileTimeToDateTime(ft); // Используем наш конвертер
						}
						pDevFreeObjectProperties(arrivalPropCount, arrivalProperties);
					}
					// --- ЗАПРОС ДАТЫ ПОСЛЕДНЕГО ОТКЛЮЧЕНИЯ (Removal Date)
					DEVPROPCOMPKEY requestedDateRemoval[] = { { DEVPKEY_Device_LastRemovalDate, DEVPROP_STORE_SYSTEM, NULL } };
					ULONG removalPropCount = 0;
					const DEVPROPERTY* removalProperties = NULL;

					HRESULT hrRemoval = pDevGetObjectProperties(
						DevObjectTypeDevice,
						device.devInstanceID.c_str(),
						DevQueryFlagNone,
						1,
						requestedDateRemoval,
						&removalPropCount,
						&removalProperties
					);

					if (SUCCEEDED(hrRemoval) && removalPropCount > 0 && removalProperties != NULL) {
						if (removalProperties[0].Type == 16 && removalProperties[0].Buffer != NULL) {
							FILETIME ft = *(FILETIME*)removalProperties[0].Buffer;
							device.lastDisconnect = fileTimeToDateTime(ft); // Используем наш конвертер
						}
						pDevFreeObjectProperties(removalPropCount, removalProperties);
					}
				} else {
					device.containerName = L"Функции не найдены в DLL";
				}
				FreeLibrary(hDevQueryDll);
			} else {
				device.containerName = L"cfgmgr32.dll не найдена";
			}
		} else {
			device.containerName = L"Нет контейнера";
		}

		// ДОБАВЛЯЕМ УСТРОЙСТВО В СПИСОК (цикл for на этом заканчивается)
		v_tempDevList.push_back(device);
	}

	// 3. Освобождаем память
	SetupDiDestroyDeviceInfoList(hDevInfo);


	// =========================================================================
	// А ВОТ ТЕПЕРЬ, КОГДА СПИСОК ПОЛНОСТЬЮ СОБРАН, МЫ ДЕЛАЕМ ПОСТОБРАБОТКУ
	// =========================================================================

	// --- ПОЛУЧЕНИЕ ИМЕНИ КОМПЬЮТЕРА (один раз!) ---
	UnicodeString myComputerName = L"Этот компьютер";
	wchar_t compName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD compNameSize = sizeof(compName) / sizeof(compName[0]);
	if (GetComputerNameW(compName, &compNameSize)) {
		myComputerName = UnicodeString(compName);
	}

	// --- УНИФИКАЦИЯ ИМЕН КОНТЕЙНЕРОВ ---
	std::map<UnicodeString, UnicodeString> bestContainerNames;

	// Этап 1: Ищем самое "красивое" имя для каждого ContainerID
	for (const auto& dev : v_tempDevList) {
		if (dev.containerId == L"No Container" || dev.containerId == L"GUID Error" || dev.containerId.IsEmpty()) {
			continue;
		}

		UnicodeString currentBest = bestContainerNames[dev.containerId];
		UnicodeString candidate = dev.containerName;

		bool candidateIsBoring = (
			candidate.Pos(L"Универсальный том") > 0 ||
			candidate.Pos(L"Generic volume") > 0 ||
			candidate.Pos(L"Запоминающее устройство") > 0 ||
			candidate.Pos(L"Mass Storage") > 0 ||
			candidate.Pos(L"Volume") > 0 ||
			candidate.Pos(L"Том") > 0
		);

		bool currentIsBoring = (
			currentBest.Pos(L"Универсальный том") > 0 ||
			currentBest.Pos(L"Generic volume") > 0 ||
			currentBest.Pos(L"Запоминающее устройство") > 0 ||
			currentBest.Pos(L"Mass Storage") > 0 ||
			currentBest.Pos(L"Volume") > 0 ||
			currentBest.Pos(L"Том") > 0
		);

		if (currentBest.IsEmpty()) {
			bestContainerNames[dev.containerId] = candidate;
		} else {
			if (!candidateIsBoring && currentIsBoring) {
				bestContainerNames[dev.containerId] = candidate;
			}
			else if (!candidateIsBoring && !currentIsBoring && candidate.Length() > currentBest.Length()) {
				bestContainerNames[dev.containerId] = candidate;
			}
		}
	}

	const UnicodeString SYSTEM_CONTAINER_ID = L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}";

	// Этап 2: Применяем найденное лучшее имя ко всем устройствам
	// + проверяем серийники
	for (auto& dev : v_tempDevList) {
		if (dev.containerId == SYSTEM_CONTAINER_ID) {
			dev.containerName = myComputerName;
		}
		else if (dev.containerId != L"No Container" && dev.containerId != L"GUID Error" && !dev.containerId.IsEmpty()) {
			dev.containerName = bestContainerNames[dev.containerId];
		}
		// ...проверяем серийники
        bool find = false;
		for(auto& regUsb: regUsbList) { // файл reristered
			find = CompareStr_DamerayLevenshtaine(dev.serialNumber, regUsb.serial);
			if (find) {
				dev.serialKnow = true;
				dev.serialErr  = false;
				dev.regName      = regUsb.name;
				dev.regCatName   = regUsb.catName;
				dev.regCatNumber = regUsb.catNumber;
				break;
			}
		}
		if (!find && badCharSerial>0) {
			for(auto &regUsb: regUsbList) {
				for (int i = 1; i <= badCharSerial; i++) {
					find = CompareStr_DamerayLevenshtaine(dev.serialNumber, regUsb.serial, i);
					if (find) {
						dev.serialKnow = true;
						dev.serialErr  = true;
						dev.regName      = regUsb.name;
						dev.regCatName   = regUsb.catName;
						dev.regCatNumber = regUsb.catNumber;
						break;
					}
				if (find) break;
				}
			}
		}

	}

	return v_tempDevList;
}
/* Подключение к БД */
void __fastcall TForm1::createDB() {
	try {
		FDQuery1->IndexesActive = true;
		FDConnection1->Open();
		FDConnection1->ExecSQL("DROP TABLE IF EXISTS devices;");
		// НАШЕЙ ТАБЛИЦЫ:
		// Выполняем SQL-запрос, который создаст таблицу devices, если её ещё нет в файле
		FDConnection1->ExecSQL(
			"CREATE TABLE IF NOT EXISTS devices ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT, "
			"class_name VARCHAR(255), "
			"enumerator_name VARCHAR(255), "
			"friendly_name VARCHAR(255), "
			"dev_desc VARCHAR(255), "
			"dev_instance_id VARCHAR(255) UNIQUE, "
			"serial_number VARCHAR(255), "
			"status VARCHAR(255), "
			"containerId VARCHAR(255), "
			"containerName VARCHAR(255), "
			"regName VARCHAR(255), "
			"regCatName VARCHAR(255), "
			"regCatNumber INT, "
			"first_install DATETIME, "
			"last_install DATETIME, "
			"last_connect DATETIME, "
			"last_disconnect DATETIME, "
			"serialKnow INT, "
			"serialErr INT"
			");"
		);
	}
	catch (const Exception &e) {
		printLog("Ошибка БД: " + e.Message);
	}
}
/* Перенос данных в БД */
void __fastcall TForm1::vectorToBD(std::vector<deviceInfo> &devicesList) {
	// 1. Записываем их в БД через FDQuery
	FDConnection1->StartTransaction();
	try {
        // Очищаем старые статусы или старые записи, если история не нужна
		FDConnection1->ExecSQL("DELETE FROM devices;");

		FDQuery1->SQL->Text =
			"INSERT INTO devices ( "
				"class_name, "
				"enumerator_name, "
				"friendly_name, "
				"dev_desc, "
				"dev_instance_id, "
				"serial_number, "
				"status, "
				"containerId, "
				"containerName, "
				"regName, "
				"regCatName, "
				"regCatNumber, "
				"first_install, "
				"last_install, "
				"last_connect, "
				"last_disconnect, "
				"serialKnow, "
				"serialErr "
			") "
			"VALUES ( "
				":class, "
				":enum, "
				":friendly, "
				":desc, "
				":inst, "
				":serial, "
				":status, "
				":containerId, "
				":containerName, "
				":regName, "
				":regCatName, "
				":regCatNumber, "
				":first_install, "
				":last_install, "
				":last_connect, "
				":last_disconnect, "
				":serialKnow, "
				":serialErr "
			");";

		for (const auto &device : devicesList) {
			FDQuery1->ParamByName("class")->AsString = device.className;
			FDQuery1->ParamByName("enum")->AsString = device.enumeratorName;
			FDQuery1->ParamByName("friendly")->AsString = device.friendlyName;
			FDQuery1->ParamByName("desc")->AsString = device.devDesc;
			FDQuery1->ParamByName("inst")->AsString = device.devInstanceID;
			FDQuery1->ParamByName("serial")->AsString = device.serialNumber;
			FDQuery1->ParamByName("status")->AsString = device.status;
			FDQuery1->ParamByName("containerId")->AsString   = device.containerId;
			FDQuery1->ParamByName("containerName")->AsString = device.containerName;
			FDQuery1->ParamByName("regName")->AsString       = device.regName;
			FDQuery1->ParamByName("regCatName")->AsString    = device.regCatName;
			FDQuery1->ParamByName("regCatNumber")->AsInteger = device.regCatNumber; //short
			FDQuery1->ParamByName("serialKnow")->AsInteger = device.serialKnow; //bool
			FDQuery1->ParamByName("serialErr")->AsInteger  = device.serialErr;  //boll
			// 1. Дата последнего подключения
			if (double(device.lastConnect) == 0) {
				FDQuery1->ParamByName(L"last_connect")->DataType = ftDateTime; // Явно указываем тип перед очисткой
				FDQuery1->ParamByName(L"last_connect")->Clear();
			} else {
				FDQuery1->ParamByName(L"last_connect")->AsDateTime = device.lastConnect;
			}
			// 2. Дата последнего отключения
			if (double(device.lastDisconnect) == 0) {
				FDQuery1->ParamByName(L"last_disconnect")->DataType = ftDateTime; // Исправляет вашу ошибку!
				FDQuery1->ParamByName(L"last_disconnect")->Clear();
			} else {
				FDQuery1->ParamByName(L"last_disconnect")->AsDateTime = device.lastDisconnect;
			}
			// 3. Дата первой установки
			if (double(device.firstInstallDate) == 0) {
				FDQuery1->ParamByName(L"first_install")->DataType = ftDateTime;
				FDQuery1->ParamByName(L"first_install")->Clear();
			} else {
				FDQuery1->ParamByName(L"first_install")->AsDateTime = device.firstInstallDate;
			}
			// 4. Дата последней установки
			if (double(device.installDate) == 0) {
				FDQuery1->ParamByName(L"last_install")->DataType = ftDateTime;
				FDQuery1->ParamByName(L"last_install")->Clear();
			} else {
				FDQuery1->ParamByName(L"last_install")->AsDateTime = device.installDate;
			}
			// Выполняем
			FDQuery1->ExecSQL();
		}
		FDConnection1->Commit();
    }
    catch (const Exception &e) {
		FDConnection1->Rollback();
        printLog("Ошибка записи в БД: " + e.Message);
	}
}
/* Вывод на TDBGrid */
void __fastcall TForm1::refrechDBGrid() {
	// Обновляем TDBGrid через FDQuery
	try {
		FDQuery1->Close(); // Закрываем предыдущий запрос
		FDQuery1->SQL->Text =
			"SELECT * FROM devices;";
		FDQuery1->Open();  // Открываем — TDBGrid автоматически отобразит данные
	}
    catch (const Exception &e) {
        printLog("Ошибка отображения данных: " + e.Message);
	}
    // Лямбда-функция для поиска и изменения видимости колонки по её имени в БД
	auto setColumnVisible = [&](UnicodeString fieldName, bool visible) {
		for (int i = 0; i < DBGrid1->Columns->Count; i++) {
			if (DBGrid1->Columns->Items[i]->FieldName.LowerCase() == fieldName.LowerCase()) {
				DBGrid1->Columns->Items[i]->Visible = visible;
				break; // Нашли и выходим
			}
		}
	};
	// ТЕПЕРЬ ОДНОЙ СТРОКОЙ СКРЫВАЕМ:
	setColumnVisible(L"id", false);
	setColumnVisible(L"containerId", false);
	setColumnVisible(L"regCatNumber", false);
	setColumnVisible(L"serialKnow", false);
	setColumnVisible(L"serialErr", false);
	setColumnVisible(L"last_install", false);
}
/* Оптимизируем ширину столбцов TDBGrid */
void optimizeGridColumns(TDBGrid* grid) {
	// Временно отключаем отрисовку для скорости
	grid->DataSource->DataSet->DisableControls();
//	if (grid->Columns->Count >= 7) {
//		//grid->Columns->Items[0]->Title->Caption = "ID";
//		grid->Columns->Items[0]->Title->Caption = "Класс устройства";
//		grid->Columns->Items[1]->Title->Caption = "Перечислитель";
//		grid->Columns->Items[2]->Title->Caption = "Имя устройства";
//		grid->Columns->Items[3]->Title->Caption = "Описание";
//		grid->Columns->Items[4]->Title->Caption = "Серийный номер";
//		grid->Columns->Items[5]->Title->Caption = "Статус";
//		grid->Columns->Items[6]->Title->Caption = "Контейнер";
//	}
    try {
        for (int i = 0; i < grid->Columns->Count; i++) {
            // Берем ширину заголовка столбца как стартовую
            int maxWidth = grid->Canvas->TextWidth(grid->Columns->Items[i]->Title->Caption) + 20;

            // Проверяем первые ~50 записей, чтобы не тормозить на огромных базах
            grid->DataSource->DataSet->First();
            int rowsChecked = 0;
            while (!grid->DataSource->DataSet->Eof && rowsChecked < 50) {
                int cellWidth = grid->Canvas->TextWidth(grid->Columns->Items[i]->Field->DisplayText) + 15;
				if (cellWidth > maxWidth) {
					if (cellWidth > 300) {
						maxWidth = 300;
					} else maxWidth = cellWidth;
				}
				grid->DataSource->DataSet->Next();
                rowsChecked++;
            }
            // Возвращаем указатель на первую запись
            grid->DataSource->DataSet->First();

            // Устанавливаем высчитанную ширину
            grid->Columns->Items[i]->Width = maxWidth;
        }
    }
    __finally {
        grid->DataSource->DataSet->EnableControls();
    }
}
/* НЕИСПОЛЬЗУЕТСЯ - Заполняем фильтр по устройствам */
void __fastcall TForm1::UpdateClassFilterList()
{
	TFDQuery* tempQuery = new TFDQuery(NULL);
	tempQuery->Connection = FDConnection1;

    // Выбираем только уникальные классы из базы
	tempQuery->SQL->Text = "SELECT DISTINCT class_name FROM devices WHERE class_name IS NOT NULL;";
	tempQuery->Open();

    ListBox_Filter->Items->Clear();
	ListBox_Filter->Items->Add("(Все классы)");

    while (!tempQuery->Eof) {
		ListBox_Filter->Items->Add(tempQuery->FieldByName("class_name")->AsString);
        tempQuery->Next();
	}

	delete tempQuery;
}
/* Читаем registered.txt */
std::vector<registeredUsb> readRegUsbFile(fs::path &p_file) {
	std::vector<registeredUsb> tempRegUsbList;
	TStringList *regUsbFile = new TStringList;
	// Читаем файл
	if(exists(p_file)) {
		regUsbFile->LoadFromFile(p_file.c_str(), TEncoding::UTF8);
	} else {
		printLog(" [!] Нема registered.txt");
		return tempRegUsbList;
	}
	// -- обрабатываем файл с извесными флешками, заполняем вектор "tempRegUsbList"
	for (auto strRegUsb: regUsbFile) {
		registeredUsb tempRegUsb;
		UnicodeString tempStr = strRegUsb.SubString(0,strRegUsb.LastDelimiter("#")-1);

		tempRegUsb.catName = strRegUsb.SubString(strRegUsb.LastDelimiter("#")+1, strRegUsb.Length());
		tempRegUsb.serial = tempStr.SubString(tempStr.LastDelimiter("#")+1, tempStr.Length());
		tempRegUsb.name = tempStr.SubString(0, tempStr.LastDelimiter("#")-1);
		try { tempRegUsb.catNumber = m_catNumber.at(tempRegUsb.catName); }
		catch (const std::out_of_range& error) { tempRegUsb.catNumber = 0; }
		tempRegUsbList.push_back(tempRegUsb);
	}
	printLog(UnicodeString(tempRegUsbList.size()));
	return tempRegUsbList;
}
/* Сравнение текста с ошибкой */
bool CompareStr_DamerayLevenshtaine(const UnicodeString &m, const UnicodeString &n, short a)
{
	int mL = m.Length(), nL = n.Length();
    if (mL == 0 || nL == 0) return false; //проверка на пустые строки
	if (a == 0) {
		if (mL == nL && m == n) return true;
		else return false;
	}
	short minScore = 0;
	//крайние случаи
	if (mL < nL) minScore = nL - mL;
	if (mL > nL) minScore = mL - nL;
	if (minScore > a) return false;
	//
	const int INF = mL + nL;
	int H[mL+2][nL+2];
    H[0][0] = INF;
	for ( int i = 0; i <= mL; ++i ) { H[i+1][1] = i; H[i+1][0] = INF; }
	for ( int j = 0; j <= nL; ++j ) { H[1][j+1] = j; H[0][j+1] = INF; }

	const int alphabet_size = std::numeric_limits<wchar_t>::max();
	std::vector<wchar_t> DA( alphabet_size );
	for ( int d = 0; d < alphabet_size; ++d ) DA[d] = 0;
	for ( int i = 1; i <= mL; ++i ) {
        size_t DB = 0;
		for ( int j = 1; j <= nL; ++j ) {
			const int i1 = DA[ n[j] ];
            const int j1 = DB;
			const int d = (m[i]==n[j]) ? 0 : 1;
			if ( d == 0 ) DB = j;
			H[i+1][j+1] = std::min(
				std::min(H[i][j]+d, H[i+1][j]+1),
				std::min(H[i][j+1]+1, H[i1][j1] + (i-i1-1) + 1 + (j-j1-1) ) );
        }
        DA[ m[i] ] = i;
	}
	minScore =H[mL][nL];
	if (minScore <= a) return true;
	else return false;
}
/* Проверка на включение строки в строку */
bool compareStrInSring(UnicodeString &strFull, UnicodeString &strSearch) {
	bool ret = false;
//	UnicodeString fix_strFull   = (strFull).LowerCase();
//	UnicodeString fix_strSearch = fixDirName(strSearch).LowerCase();
	if (strFull.Length() < strSearch.Length()) return ret;
	for(int i = 0; i < strFull.Length()+1 - strSearch.Length()+1; i++) {
		UnicodeString strTemp = strFull.SubString(i, strSearch.Length());
		if (strTemp == strSearch) {
			ret = true;
			break;
		}
	}
	return ret;
}
bool compareStrInVector(UnicodeString &strFull, std::vector<UnicodeString> &v_str) {
	for(auto &t_str: v_str) {
		if (compareStrInSring(strFull, t_str)) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_DeviceUpdateCurPCClick(TObject *Sender)
{
	devicesList = scanDevices();
    if (devicesList.empty()) {
        printLog("Устройства не найдены.");
        return;
	}
	//UpdateClassFilterList();
	vectorToBD(devicesList);
	refrechDBGrid();
	optimizeGridColumns(Form1->DBGrid1);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1TitleClick(TColumn *Column)
{
    // Проверяем, что датасет открыт и в нем есть данные
    if (!FDQuery1->Active || FDQuery1->IsEmpty()) return;

    UnicodeString fieldName = Column->FieldName;
    UnicodeString indexName = fieldName + L"_Idx";

    // Ищем, существует ли уже такой индекс в памяти
    TFDIndex* idx = FDQuery1->Indexes->FindIndex(indexName);

    if (idx == nullptr) {
        // Если индекса нет — создаем его для сортировки по возрастанию (Ascending)
        idx = FDQuery1->Indexes->Add();
        idx->Name = indexName;
        idx->Fields = fieldName;
        idx->Active = true;
    } else {
        // Если индекс уже был, меняем направление: Ascending <-> Descending
        if (idx->Options.Contains(soDescending)) {
			idx->Options >> soDescending;
        } else {
            idx->Options << soDescending;
        }
    }

    // Применяем индекс к Query — грид мгновенно перестроится!
    FDQuery1->IndexName = indexName;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox_FilterClick(TObject *Sender)
{
	if (!FDQuery1->Active) return;

    UnicodeString listboxFilter = L"";

	// 1. Собираем условия из ListBox (фильтр по классам)
    for (int i = 0; i < ListBox_Filter->Items->Count; i++)
    {
        if (ListBox_Filter->Selected[i])
        {
            UnicodeString value = ListBox_Filter->Items->Strings[i];

			if (value == "(Усі класи пристроїв)")
			{
				listboxFilter = L""; // Сбрасываем фильтр классов
                break;
            }

            if (!listboxFilter.IsEmpty()) {
                listboxFilter += L" OR ";
            }

			listboxFilter += L"class_name = " + QuotedStr(value);
		}
    }

    // 2. Проверяем состояние Чекбокса (фильтр по материнской плате)
    UnicodeString finalFilter = L"";
    const UnicodeString SYSTEM_CONTAINER_ID = L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}";
    UnicodeString mbFilter = L"";

    // Если ЧЕКБОКС СНЯТ: Исключаем системный контейнер
    // (Если чекбокс установлен, mbFilter остается пустой строкой = показываем всё)
	if (!CheckBox_FilterMotherboard->Checked)
	{
		mbFilter = L"containerId <> " + QuotedStr(SYSTEM_CONTAINER_ID);
	}

    // 3. Объединяем оба фильтра
    if (mbFilter.IsEmpty())
    {
        // Чекбокс стоит, фильтровать по материнке не нужно. Берем только список классов.
        finalFilter = listboxFilter;
    }
    else
    {
        // Чекбокс снят.
        if (listboxFilter.IsEmpty()) {
            finalFilter = mbFilter; // Выбрано "Все классы", но материнку скрываем
        } else {
            // Берем классы в скобки и добавляем отсечение материнки
            finalFilter = L"(" + listboxFilter + L") AND " + mbFilter;
        }
    }

    // 4. Применяем итоговый фильтр к FireDAC
    if (finalFilter.IsEmpty())
    {
        // Если выбрано "Все классы" И чекбокс установлен
        FDQuery1->Filtered = false;
        FDQuery1->Filter = L"";
        printLog(L"Фильтры сброшены. Показываются абсолютно все устройства.");
    }
    else
    {
        FDQuery1->Filtered = false; // Отключаем перед применением нового
        FDQuery1->Filter = finalFilter;
        FDQuery1->Filtered = true;
        printLog(L"Применен фильтр: " + finalFilter);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_FilterContainerIDClick(TObject *Sender)
{
    ListBox_Filter->ClearSelection();
	// 1. Убеждаемся, что запрос активен и в гриде есть данные
    if (!FDQuery1->Active || FDQuery1->IsEmpty()) {
        return;
    }

    // 2. Получаем Container ID выделенной строки (текущей записи)
    // ВАЖНО: Замените "containerId" на точное имя этого поля в вашей таблице SQLite!
    UnicodeString selectedContainerId = FDQuery1->FieldByName(L"containerId")->AsString;

    // 3. Проверяем, что у устройства вообще есть нормальный контейнер
    if (selectedContainerId.IsEmpty() || selectedContainerId == L"No Container" || selectedContainerId == L"GUID Error") {
        printLog(L"У выделенного устройства нет контейнера для фильтрации.");
        return;
    }

    // 4. Применяем фильтр к FireDAC
    FDQuery1->Filtered = false; // Обязательно отключаем перед изменением

    // Формируем строку фильтра. QuotedStr автоматически обернет GUID в одинарные кавычки
    FDQuery1->Filter = L"containerId = " + QuotedStr(selectedContainerId);

    FDQuery1->Filtered = true; // Включаем фильтр

	printLog(L"Отображаются устройства контейнера: " + selectedContainerId);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox_FilterMotherboardClick(TObject *Sender)
{
	// При клике на чекбокс просто вызываем пересчет общего фильтра
	ListBox_FilterClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar_CountErrSerialChange(TObject *Sender)
{
    badCharSerial = TrackBar_CountErrSerial->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
    // 1. Получаем указатель на сам грид, который вызвал событие
    TDBGrid *grid = (TDBGrid*)Sender;

    // 2. Вытаскиваем значения полей ТЕКУЩЕЙ строки, которую сейчас рисует система.
    // ВАЖНО: Замените "status" и "class" на точные имена полей в вашей БД SQLite!
	UnicodeString devStatus = grid->DataSource->DataSet->FieldByName(L"status")->AsString;
	UnicodeString devClass  = grid->DataSource->DataSet->FieldByName(L"class_name")->AsString;
	UnicodeString devName  = grid->DataSource->DataSet->FieldByName(L"friendly_name")->AsString;
	UnicodeString devDescription  = grid->DataSource->DataSet->FieldByName(L"dev_desc")->AsString;
	short devCat  = grid->DataSource->DataSet->FieldByName(L"regCatNumber")->AsInteger;
	short devKnow = grid->DataSource->DataSet->FieldByName(L"serialKnow")->AsInteger;
	short devErr  = grid->DataSource->DataSet->FieldByName(L"serialErr")->AsInteger;

    // 3. Проверяем, выделена ли эта строка пользователем (кликнули ли по ней мышкой).
    // Если строка выделена, мы НЕ должны менять её фон на серый или белый,
    // иначе пользователь не увидит стандартное синее выделение Windows.
    if (!State.Contains(gdSelected))
    {
        // Условие 1: Если устройство отключено — делаем фон светло-серым
		if (devStatus == L"DISCONNECT")
        {
            grid->Canvas->Brush->Color = (TColor)0x00F8F8F8; // Светло-серый цвет в HEX (BGR)
            grid->Canvas->Font->Color  = clGray;            // Серый цвет текста
        }
        // Условие 2: Если устройство подключено и это флешка/диск — делаем фон слегка зеленоватым
		else if (devClass == L"DiskDrive")
        {
            grid->Canvas->Brush->Color = (TColor)0x00F0FFF0; // Очень бледный зеленый (Mint)
            grid->Canvas->Font->Color  = clBlack;
		}
		// Условие 3: Обычное подключенное устройство
        else
        {
            grid->Canvas->Brush->Color = clWhite; // Стандартный белый фон
            grid->Canvas->Font->Color  = clBlack; // Стандартный черный текст
		}
		//Устройство с нарушением
		if (devCat > catPC || compareStrInVector(devName, v_allertName) || compareStrInVector(devDescription, v_allertName))
		{
			grid->Canvas->Brush->Color = (TColor)0x00D0D0FF; // Очень бледный красный
		}

    }
    else
    {
        // Если строка выделена пользователем, оставляем системные цвета выделения
        grid->Canvas->Brush->Color = clHighlight;
        grid->Canvas->Font->Color  = clHighlightText;
    }

	// --- Отдельные ячейки ---
	// "CONNECT" жирным и зеленым:
	if (Column->FieldName == L"status" && devStatus == L"CONNECT" && !State.Contains(gdSelected))
	{
		grid->Canvas->Font->Color = clGreen;
        grid->Canvas->Font->Style = TFontStyles() << fsBold;
	}
	// Извесный серийник зеленый или желтый
	if (Column->FieldName == L"serial_number" && devKnow == 1 && !State.Contains(gdSelected))
	{
		if (devErr == 0) grid->Canvas->Font->Color = (TColor)0x00006600; //Темно зеленый
		if (devErr == 1) grid->Canvas->Font->Color = (TColor)0x000099CC; //Темно желтый
        grid->Canvas->Font->Style = TFontStyles() << fsBold;
	}
	// нарушение категории
	if ((Column->FieldName == L"regName" || Column->FieldName == L"regCatName") && devCat > catPC && !State.Contains(gdSelected))
	{
		grid->Canvas->Font->Color = clRed;
        grid->Canvas->Font->Style = TFontStyles() << fsBold;
	}
	// нарушение в названии
	if (Column->FieldName == L"friendly_name" && compareStrInVector(devName, v_allertName))
	{
		grid->Canvas->Font->Color = clRed;
		grid->Canvas->Font->Style = TFontStyles() << fsBold;
//		grid->Canvas->Brush->Color = (TColor)0x00D0D0FF;
	}
	if (Column->FieldName == L"dev_desc" && compareStrInVector(devDescription, v_allertName))
	{
		grid->Canvas->Font->Color = clRed;
		grid->Canvas->Font->Style = TFontStyles() << fsBold;
//		grid->Canvas->Brush->Color = (TColor)0x00D0D0FF;
	}

    // 4. ОБЯЗАТЕЛЬНО вызываем стандартный метод отрисовки!
    // Он возьмет настроенные нами цвета Canvas (Brush и Font) и красиво напечатает текст.
    grid->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox_CategPCChange(TObject *Sender)
{
	try { catPC = m_catNumber.at(ComboBox_CategPC->Text); }
	catch (const std::out_of_range& error) { catPC = 0; }
    DBGrid1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false; // Выключаем таймер
    printLog(L"Система Windows сообщила об изменении оборудования. Обновляю список...");
	Button_DeviceUpdateCurPCClick(this); // Обновляем данные
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_DelDeviceClick(TObject *Sender)
{

    // Проверяем состояние клавиши Shift через GetKeyState.
    // Если старший бит возвращаемого значения равен 1 (меньше 0), значит Shift нажат.
    if (GetKeyState(VK_SHIFT) < 0)
    {
		// --- КОД ДЛЯ SHIFT + КЛИК ---
		printLog(L"Запускаю удаление всего контейнера...");
		DelContainerDevice();
	}
    else
    {
        // --- ОБЫЧНЫЙ КОД (БЕЗ SHIFT) ---
		printLog(L"Запускаю удаление одного устройства...");
		DelDevice();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_ShowUSBClick(TObject *Sender)
{
	CheckBox_FilterMotherboard->Checked = false;
	UnicodeString targetText = L"DiskDrive"; // Текст, который мы ищем

	// Находим индекс строки
	int index = ListBox_Filter->Items->IndexOf(targetText);

	if (index != -1)
	{
		// 1. Очищаем любые старые выделения в ListBox (критично для MultiSelect)
		ListBox_Filter->ClearSelection();

		// 2. Явно выделяем нужный пункт синим цветом (работает для любого режима)
		ListBox_Filter->Selected[index] = true;
		ListBox_Filter->ItemIndex = index;

		// 3. Возвращаем фокус на ListBox, чтобы Windows отрисовала выделение активным
		ListBox_Filter->SetFocus();

		// 4. Прокручиваем список к выделенному элементу, если он скрыт скроллом
		ListBox_Filter->TopIndex = index;

		// 5. Принудительно заставляем Windows перерисовать компонент прямо сейчас
		ListBox_Filter->Update();

		// 6. Вызываем вашу функцию фильтрации данных
		ListBox_FilterClick(ListBox_Filter);
	}
	else
	{
		printLog(L"Пункт '" + targetText + L"' не найден в ListBox_Filter.");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_ShowUnknowUSBClick(TObject *Sender)
{
	Button_ShowUSBClick(this);
	//ListBox_Filter->ClearSelection();
	// 1. Убеждаемся, что запрос активен и в гриде есть данные
    if (!FDQuery1->Active || FDQuery1->IsEmpty()) {
        return;
	}

	// Применяем фильтр к FireDAC
    FDQuery1->Filtered = false; // Обязательно отключаем перед изменением

	// Формируем строку фильтра.
	FDQuery1->Filter = L"serialKnow = " + QuotedStr("0") + " AND class_name = " + QuotedStr("DiskDrive") +
		" AND serial_number IS NOT NULL AND serial_number <> ''";

    FDQuery1->Filtered = true; // Включаем фильтр

	printLog(L"Отображаются только неизвесные USB устройства");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_ShowAllertClick(TObject *Sender)
{
	CheckBox_FilterMotherboard->Checked = false;
	ListBox_Filter->ClearSelection();
	// 1. Проверяем, активна ли таблица (DataSet)
    if (!FDQuery1->Active) {
        printLog(L"Фильтрация невозможна: FDQuery1 не активен.");
        return;
	}

    // Отключаем фильтрацию перед формированием нового условия
    FDQuery1->Filtered = false;

    const UnicodeString SYSTEM_CONTAINER_ID = L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}";
    UnicodeString filterStr = L"";
	UnicodeString nameConditions = L"";

    // 2. Строим условия для поиска ключевых слов из вектора v_allertName
    for (size_t i = 0; i < v_allertName.size(); ++i)
    {
        UnicodeString keyword = v_allertName[i].Trim();
        if (keyword.IsEmpty()) continue;

        // Экранируем одинарные кавычки в ключевом слове для безопасности фильтра FireDAC
        keyword = StringReplace(keyword, L"'", L"''", TReplaceFlags() << rfReplaceAll);

        if (!nameConditions.IsEmpty()) {
            nameConditions += L" OR ";
        }

        // FireDAC поддерживает синтаксис LIKE с подстановочными знаками '%'
        nameConditions += L"(class_name LIKE '%" + keyword + L"%' OR friendly_name LIKE '%" + keyword + L"%')";
    }

    // 3. Объединяем условия по именам и условие по категории (regCatNumber > catPC)
    // ВАЖНО: сверьте точное имя столбца категории в вашей БД (например, regCatNumber или devCat)
    UnicodeString catCondition = L"regCatNumber > " + IntToStr(catPC);

    if (!nameConditions.IsEmpty())
    {
        // Итоговое условие: (Группа_Имен) OR (Категория)
        filterStr = L"(" + nameConditions + L") OR (" + catCondition + L")";
    }
    else
    {
        // Если вектор слов пустой, фильтруем только по превышению категории
		filterStr = catCondition;
	}

	if (!CheckBox_FilterMotherboard->Checked)
	{
		filterStr += L" AND containerId <> " + QuotedStr(SYSTEM_CONTAINER_ID);
	}

    // 4. Применяем фильтр к набору данных
    FDQuery1->Filter = filterStr;
	FDQuery1->Filtered = true;

    printLog(L"Применен alert-фильтр: " + filterStr);
}
//---------------------------------------------------------------------------

