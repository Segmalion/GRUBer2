//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <windows.h>
#include <initguid.h>
#include <devpkey.h>      // Для DEVPKEY_Device_ContainerId
#include <combaseapi.h>   // Для конвертации GUID в строку
#include <algorithm>

#include <devquery.h>

#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

#pragma comment(lib, "cfgmgr32.lib") // <-- Добавили для работы функции статуса

#include <iostream>

#include <System.SysUtils.hpp>
#include <System.Zlib.hpp>

#include <System.JSON.hpp>
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>

#include "MainDevLister.h"
#include "GetSMB.h"
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

//---------------------------------------------------------------------------
HANDLE g_FontHandle = NULL;
short badCharSerial = 0;
//short catPC = 0;
double multipler;
std::vector<deviceInfo> devicesList;
std::vector<registeredUsb> regUsbList;

//bool sqlFull;
//---------------------------------------------------------------------------
std::map<UnicodeString, short> m_catNumber {
		{"НТ", 1}, {"НТ-БП", 1}, {"НТ-ІСД", 1}, {"НТ-ЕКМ", 1}, {"Не Таємно", 1},
		{"ДСК", 2},
		{"Т", 3}, {"Таємно", 3},
		{"ЦТ", 4}, {"Цілком Таємно", 4}
};
std::vector<UnicodeString> v_allertName {
	// Подключення смартфонів (MTP/PTP/ADB/Fastboot-режими, драйвери виробників)
	"android", "MTP", "ADB", "PTP", "Fastboot", "iPhone", "Apple Mobile Device",
	"AndroidUsbDeviceClass",
	"Samsung", "SM-", "Galaxy",
	"Xiaomi", "Redmi",
	"Huawei", "Honor",
	"OPPO", "vivo", "OnePlus", "Realme",
	"Pixel", "Nexus",
	"Xperia",
	"Motorola", "moto",
	"HTC", "Nokia", "ZTE", "Meizu", "LG Mobile",
	// Зовнішні мережеві пристрої (USB-Ethernet/Wi-Fi адаптери, модеми, роутери)
	"Ethernet", "RNDIS", "ASIX", "Realtek USB GbE",
	"WiFi", "WLAN", "802.11", "Wireless",
	"TP-Link", "D-Link", "Netgear", "Mercusys", "Tenda",
	"Ralink", "Atheros", "MediaTek", "Realtek RTL8188",
	//"Bluetooth",
	"Modem", "3G", "4G", "LTE", "HSPA", "WWAN", "Mobile Broadband",
	"Router", "Hotspot", "Tethering", "Access Point"
};
indefPCtype indefPC;
//---------------------------------------------------------------------------
String sql_usb =
	"SELECT *\n"
	"FROM devices\n"
	"WHERE class_name IN ('SCSIAdapter', 'USB', 'WPD', 'DiskDrive', 'Volume');";
String sql_all = "SELECT * FROM devices;";
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	// Исходное состояние "основного" фильтра — как у Button_ShowAllClick
	SetActiveFilter(mfmAll, L"");

	UnicodeString appVersion = GetAppVersion();
	printLog(L"Программа запущена. Версия: " + appVersion);
	StatusBar1->Panels->Items[1]->Text = ("v. " + appVersion + "     ");

	ComboBox_CategPC->ItemIndex = indefPC.catPC;
    LoadFontFromResource();
	// Инициализация БД
	createDB();
    // Читает файл registered.txt из каталога самого exe (а не из текущего рабочего
    // каталога, который зависит от способа запуска и может отличаться от каталога программы)
	fs::path p_fileRegUsb = fs::path(ExtractFilePath(Application->ExeName).c_str()) / "registered.txt";
	regUsbList = readRegUsbFile(p_fileRegUsb);
	// Получаем инфу о ПК
	getInfoPC();
	// Наполняем БД инфой об устройствах с текущего ПК
	Button_DeviceUpdateCurPCClick(this);
}
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	if (g_FontHandle != NULL)
    {
		RemoveFontMemResourceEx(g_FontHandle);
		g_FontHandle = NULL;
	}
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

    // ЖЁСТКАЯ ЗАЩИТА: системный контейнер материнской платы нельзя удалять целиком никогда,
    // даже если проверка выше по стеку (DelContainerDevice) будет обойдена или изменена.
    const UnicodeString SYSTEM_CONTAINER_ID = L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}";
    if (targetContainerId == SYSTEM_CONTAINER_ID) {
        printLog(L"Ошибка: попытка группового удаления системного контейнера материнской платы заблокирована.");
        return false;
    }

    // 1. Получаем список ВСЕХ устройств в системе (включая отключенные)
    HDEVINFO hDevInfo = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES);
    if (hDevInfo == INVALID_HANDLE_VALUE) {
        printLog(L"Ошибка SetupDiClassDevs: " + SysErrorMessage(GetLastError()));
        return false;
    }

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

    // Вспомогательная функция: узнать ЖИВОЙ (актуальный на данный момент) Container ID устройства
    auto getLiveContainerId = [&](SP_DEVINFO_DATA &devData) -> UnicodeString {
        wchar_t instanceIdBuf[512] = L"";
        if (!SetupDiGetDeviceInstanceIdW(hDevInfo, &devData, instanceIdBuf, 512, NULL)) {
            return L"";
        }
        UnicodeString currentInstanceId = UnicodeString(instanceIdBuf);

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
        return currentContainerId;
    };

    SP_DEVINFO_DATA devInfoData;
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    // === ПРОХОД 1: ЖИВАЯ проверка у ОС — нет ли в контейнере устройства, подключенного ПРЯМО СЕЙЧАС ===
    // Кэш в SQLite (быстрая проверка в DelContainerDevice) мог устареть с момента последнего
    // сканирования, поэтому непосредственно перед физическим удалением состояние
    // опрашивается заново через CM_Get_DevNode_Status.
    DWORD deviceIndex = 0;
    bool liveConnectedFound = false;
    while (SetupDiEnumDeviceInfo(hDevInfo, deviceIndex, &devInfoData))
    {
        deviceIndex++;
        if (getLiveContainerId(devInfoData) != targetContainerId) continue;

        ULONG devStatus = 0, devProblem = 0;
        if (CM_Get_DevNode_Status(&devStatus, &devProblem, devInfoData.DevInst, 0) == CR_SUCCESS) {
            liveConnectedFound = true;
            break;
        }
    }

    if (liveConnectedFound) {
        printLog(L"Отмена удаления: устройство из этого контейнера подключено ПРЯМО СЕЙЧАС (живая проверка ОС). Отключите оборудование физически и повторите попытку.");
        FreeLibrary(hCfgMgr);
        SetupDiDestroyDeviceInfoList(hDevInfo);
        return false;
    }

    // === ПРОХОД 2: физическое удаление — только если проход 1 подтвердил, что всё отключено ===
    deviceIndex = 0;
    int deletedCount = 0;
    int errorCount = 0;
    while (SetupDiEnumDeviceInfo(hDevInfo, deviceIndex, &devInfoData))
    {
        deviceIndex++;
        if (getLiveContainerId(devInfoData) != targetContainerId) continue;

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

    // 2.1. ЗАЩИТА: системный контейнер материнской платы удалять целиком нельзя —
    // это фактически все ключевые устройства ПК (чипсет, USB-контроллеры и т.д.)
    const UnicodeString SYSTEM_CONTAINER_ID_GUARD = L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}";
    if (containerId.UpperCase().Trim() == SYSTEM_CONTAINER_ID_GUARD) {
        MessageDlg(L"Нельзя удалять системный контейнер материнской платы — это выведет из строя ключевые устройства ПК.",
                   mtError, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    // 3. ПРОВЕРКА БЕЗОПАСНОСТИ: Нельзя удалять контейнер, если внутри есть хоть одно АКТИВНОЕ устройство!
    TFDQuery *FDQuery_Check = new TFDQuery(this);
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
	HMODULE hDevQueryDll = LoadLibraryW(L"cfgmgr32.dll");

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
			wchar_t buffer[1024];
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
		wchar_t instanceId[1024] = L"";
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
				// 3. ПРОВЕРКА НА ФИГУРНЫЕ СКОБКИ
				// GUID-подобный сегмент пути (типа {45803BBA-7064-11F1-B39C-005056C00008}#00000003FFEF4000)
				// — тоже не серийник, а сгенерированный Windows идентификатор.
				// 4. ПРОВЕРКА НА СЛИШКОМ КОРОТКИЕ ЗНАЧЕНИЯ
				// Серийник из 1-2 символов — это тоже мусор (обрезок пути/индекс), а не реальный серийный номер.
				if (serial.Pos(L"&") > 0 || serial.Pos(L"{") > 0 || serial.Pos(L"}") > 0 || serial.Length() <= 2) {
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
	FreeLibrary(hDevQueryDll);
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
	}

	return v_tempDevList;
}
void checkRegDevice(std::vector<deviceInfo> &devList) {
	for (auto& dev : devList) {
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
		FDConnection1->Commit();
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
void __fastcall TForm1::refrechDBGrid(String &sql) {
	// Обновляем TDBGrid через FDQuery
	try {
		FDQuery1->Close(); // Закрываем предыдущий запрос
		FDQuery1->SQL->Text = sql;
		FDQuery1->Open();  // Открываем — TDBGrid автоматически отобразит данные
	}
	catch (const Exception &e) {
		printLog("Ошибка отображения данных: " + e.Message);
	}
	// украшает таблицу
	optimizeGridColumns(Form1->DBGrid1);
}
/* Оптимизируем ширину столбцов TDBGrid */
void __fastcall TForm1::optimizeGridColumns(TDBGrid* grid) {
	try {
		if (FDQuery1->Active)
		{
			// Находим поле по имени в БД и задаем ему красивое отображаемое имя (DisplayLabel)
			if (FDQuery1->FindField(L"status")) {
				FDQuery1->FieldByName(L"status")->DisplayLabel = L"Статус";
				FDQuery1->FieldByName(L"status")->Index = 0;
				FDQuery1->FieldByName(L"status")->DisplayWidth = 12;
			}
			if (FDQuery1->FindField(L"class_name")) {
				FDQuery1->FieldByName(L"class_name")->DisplayLabel = L"Клас";
				FDQuery1->FieldByName(L"class_name")->Index = 1;
				FDQuery1->FieldByName(L"class_name")->DisplayWidth = 15;
			}
			if (FDQuery1->FindField(L"friendly_name")) {
				FDQuery1->FieldByName(L"friendly_name")->DisplayLabel = L"Ім'я пристрою";
				FDQuery1->FieldByName(L"friendly_name")->Index = 2;
				FDQuery1->FieldByName(L"friendly_name")->DisplayWidth = 30;
			}
			if (FDQuery1->FindField(L"serial_number")) {
				FDQuery1->FieldByName(L"serial_number")->DisplayLabel = L"Серійний номер";
				FDQuery1->FieldByName(L"serial_number")->Index = 3;
				FDQuery1->FieldByName(L"serial_number")->DisplayWidth = 25;
			}
			if (FDQuery1->FindField(L"regCatName")) {
				FDQuery1->FieldByName(L"regCatName")->DisplayLabel = L"Категорія";
				FDQuery1->FieldByName(L"regCatName")->Index = 4;
				FDQuery1->FieldByName(L"regCatName")->DisplayWidth = 8;
			}
			if (FDQuery1->FindField(L"regName")) {
				FDQuery1->FieldByName(L"regName")->DisplayLabel = L"Реєстрація";
				FDQuery1->FieldByName(L"regName")->Index = 5;
				FDQuery1->FieldByName(L"regName")->DisplayWidth = 20;
			}
			if (FDQuery1->FindField(L"dev_desc")) {
				FDQuery1->FieldByName(L"dev_desc")->DisplayLabel = L"Опис";
				FDQuery1->FieldByName(L"dev_desc")->Index = 6;
				FDQuery1->FieldByName(L"dev_desc")->DisplayWidth = 20;
			}
			if (FDQuery1->FindField(L"containerName")) {
				FDQuery1->FieldByName(L"containerName")->DisplayLabel = L"Контейнер";
				FDQuery1->FieldByName(L"containerName")->Index = 7;
				FDQuery1->FieldByName(L"containerName")->DisplayWidth = 20;
			}
			if (FDQuery1->FindField(L"last_disconnect")) {
				FDQuery1->FieldByName(L"last_disconnect")->DisplayLabel = L"Останне відключеня";
				FDQuery1->FieldByName(L"last_disconnect")->Index = 8;
				FDQuery1->FieldByName(L"last_disconnect")->DisplayWidth = 22;
			}
			if (FDQuery1->FindField(L"last_connect")) {
				FDQuery1->FieldByName(L"last_connect")->DisplayLabel = L"Останне підключеня";
				FDQuery1->FieldByName(L"last_connect")->Index = 9;
				FDQuery1->FieldByName(L"last_connect")->DisplayWidth = 22;
			}
			if (FDQuery1->FindField(L"first_install")) {
				FDQuery1->FieldByName(L"first_install")->DisplayLabel = L"Перше підключеня";
				FDQuery1->FieldByName(L"first_install")->Index = 10;
				FDQuery1->FieldByName(L"first_install")->DisplayWidth = 22;
			}
		}
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
	setColumnVisible(L"enumerator_name", false);
	setColumnVisible(L"dev_instance_id", false);
	setColumnVisible(L"rn", false);
}
/* Заполняем фильтр по устройствам */
void __fastcall TForm1::UpdateClassFilterList()
{
	// std::unique_ptr гарантирует delete даже если Open() бросит исключение
	// (например, при повреждённой/занятой БД) — раньше tempQuery в этом случае утекал.
	std::unique_ptr<TFDQuery> tempQuery(new TFDQuery(NULL));
	tempQuery->Connection = FDConnection1;

    // Выбираем только уникальные классы из базы
	tempQuery->SQL->Text = "SELECT DISTINCT class_name FROM devices WHERE class_name IS NOT NULL;";
	tempQuery->Open();

	ListBox_Filter->Items->Clear();
	ListBox_Filter->Items->Add("(Усі класи)");
	ListBox_Filter->Items->Add("(USB пристрої)");

    while (!tempQuery->Eof) {
		ListBox_Filter->Items->Add(tempQuery->FieldByName("class_name")->AsString);
        tempQuery->Next();
	}
}
/* Читаем registered.txt */
std::vector<registeredUsb> readRegUsbFile(fs::path &p_file) {
	std::vector<registeredUsb> tempRegUsbList;
	std::unique_ptr<TStringList> regUsbFile(new TStringList);
	// Читаем файл
	if(exists(p_file)) {
		regUsbFile->LoadFromFile(p_file.c_str(), TEncoding::UTF8);
	} else {
		printLog("Немає registered.txt :(");
		return tempRegUsbList;
	}
	// -- обрабатываем файл с извесными флешками, заполняем вектор "tempRegUsbList"
	int lineNumber = 0;
	for (auto strRegUsb: regUsbFile.get()) {
		lineNumber++;
		UnicodeString line = strRegUsb.Trim();
		if (line.IsEmpty()) continue; // порожні рядки (наприклад, останній рядок файлу) — не помилка

		// Очікуваний формат рядка: "Ім'я#Серійник#Категорія"
		int lastHash = line.LastDelimiter(L"#");
		if (lastHash <= 0) {
			printLog(L"Помилка в registered.txt, рядок " + IntToStr(lineNumber) +
					 L": немає роздільника '#' (\"" + line + L"\") — рядок пропущено.");
			continue;
		}
		UnicodeString tempStr = line.SubString(1, lastHash - 1);
		UnicodeString catName = line.SubString(lastHash + 1, line.Length());

		int midHash = tempStr.LastDelimiter(L"#");
		if (midHash <= 0) {
			printLog(L"Помилка в registered.txt, рядок " + IntToStr(lineNumber) +
					 L": очікується формат Ім'я#Серійник#Категорія (\"" + line + L"\") — рядок пропущено.");
			continue;
		}
		UnicodeString name   = tempStr.SubString(1, midHash - 1);
		UnicodeString serial = tempStr.SubString(midHash + 1, tempStr.Length());

		if (name.IsEmpty() || serial.IsEmpty() || catName.IsEmpty()) {
			printLog(L"Помилка в registered.txt, рядок " + IntToStr(lineNumber) +
					 L": порожнє ім'я, серійник або категорія (\"" + line + L"\") — рядок пропущено.");
			continue;
		}

		registeredUsb tempRegUsb;
		tempRegUsb.name = name;
		tempRegUsb.serial = serial;
		tempRegUsb.catName = catName;
		try { tempRegUsb.catNumber = m_catNumber.at(tempRegUsb.catName); }
		catch (const std::out_of_range& error) {
			tempRegUsb.catNumber = 0;
			printLog(L"Попередження в registered.txt, рядок " + IntToStr(lineNumber) +
					 L": невідома категорія \"" + catName + L"\" (встановлено 0).");
		}
		tempRegUsbList.push_back(tempRegUsb);
	}
	printLog("Завантаженно " + UnicodeString(tempRegUsbList.size()) + " відомих пристроїв з файлу registered.txt");
	return tempRegUsbList;
}
/* Сравнение текста с возможной ошибкой */
bool CompareStr_DamerayLevenshtaine(const UnicodeString &m, const UnicodeString &n, short a)
{
// 1. Приводим к нижнему регистру для корректного сравнения "MTP" и "mtp"
    UnicodeString strM = m.LowerCase();
    UnicodeString strN = n.LowerCase();

    int mL = strM.Length();
	int nL = strN.Length();

    // Крайние случаи
	if (mL == 0 || nL == 0) return false;

    if  (mL <= a || nL <= a) return false;

    if (a == 0) {
        return (strM == strN);
	}

    // Быстрая проверка: если разница длин больше допустимого порога `a`,
    // они точно не пройдут проверку.
    if (std::abs(mL - nL) > a) return false;

    const int INF = mL + nL + 2;

    // 2. Безопасное выделение памяти в куче (heap) вместо стека
    // Матрица размером (mL + 2) x (nL + 2). Используем одномерный вектор для скорости.
    int rows = mL + 2;
    int cols = nL + 2;
    std::vector<int> H(rows * cols, 0);

    // Макрос или лямбда для удобного обращения к двумерному вектору H[i][j]
    auto getH = [&](int r, int c) -> int& { return H[r * cols + c]; };

    getH(0, 0) = INF;

    // Инициализация границ матрицы
    for (int i = 0; i <= mL; ++i) {
        getH(i + 1, 1) = i;
        getH(i + 1, 0) = INF;
    }
    for (int j = 0; j <= nL; ++j) {
        getH(1, j + 1) = j;
        getH(0, j + 1) = INF;
    }

    // 3. Используем плоский массив/вектор для алфавита (размер 65536 для BMP Unicode)
    // thread_local вместо static: каждый поток получает свой экземпляр буфера,
    // так что параллельные вызовы этой функции из разных потоков безопасны,
    // при этом повторные вызовы из одного и того же потока по-прежнему не
    // перевыделяют память.
    thread_local std::vector<int> DA(65536, 0);
    // Очищаем только те элементы, которые реально могут быть затронуты (или всю, она быстрая)
    std::fill(DA.begin(), DA.end(), 0);

    // 4. Основной цикл алгоритма
    for (int i = 1; i <= mL; ++i) {
        int DB = 0;
        for (int j = 1; j <= nL; ++j) {

            // Защита от выхода за пределы таблицы символов (на случай суррогатных пар)
            wchar_t charM = (strM[i] < 65536) ? strM[i] : 0;
            wchar_t charN = (strN[j] < 65536) ? strN[j] : 0;

            int i1 = DA[charN];
            int j1 = DB;

            int d = (strM[i] == strN[j]) ? 0 : 1;

            if (d == 0) {
                DB = j;
            }

            // Вычисляем операции: замена, вставка, удаление и транспозиция (Дамерау)
            int substitution = getH(i, j) + d;
            int deletion     = getH(i + 1, j) + 1;
            int insertion    = getH(i, j + 1) + 1;
            int transposition= getH(i1, j1) + (i - i1 - 1) + 1 + (j - j1 - 1);

            getH(i + 1, j + 1) = std::min({ substitution, deletion, insertion, transposition });
        }

        wchar_t charM_idx = (strM[i] < 65536) ? strM[i] : 0;
        DA[charM_idx] = i;
    }

    // Результат для полных строк находится в самой последней ячейке матрицы
    int finalScore = getH(mL + 1, nL + 1);

    return (finalScore <= a);
}
/* Проверка на включение строки в строку */
bool compareStrInSring(UnicodeString &strFull, UnicodeString &strSearch) {
	if (strFull.IsEmpty() || strSearch.IsEmpty()) return false;
	// .Pos() возвращает индекс начала подстроки (от 1) или 0, если ничего не найдено.
	// Приведение к LowerCase() гарантирует, что "MTP", "Mtp" и "mtp" найдутся без проблем.
	return strFull.LowerCase().Pos(strSearch.LowerCase()) > 0;
}
bool compareStrInVector(UnicodeString &strFull, std::vector<UnicodeString> &v_str) {
	// Чтобы не переводить strFull в нижний регистр на каждой итерации цикла,
    // делаем это ОДИН РАЗ перед циклом. Это экономит кучу тактов процессора!
    UnicodeString lowerFull = strFull.LowerCase();

    for (const auto &t_str : v_str) {
        if (lowerFull.Pos(t_str.LowerCase()) > 0) {
            return true; // Ранний выход: нашли первое же совпадение — сразу возвращаем true
        }
	}
	return false;
}
/* ИНФО для ПК */
String getFastHash_CRC32(const String& Input)
{
    if (Input.IsEmpty()) {
        return L"00000000";
    }

    // Переводим UnicodeString в UTF-8 байты
    RawByteString utf8Str = UTF8Encode(Input);

    // bcc64x требует неконстантный указатель на байт.
    // Используем const_cast, чтобы удовлетворить сигнатуру функции из System.Zlib.hpp
    unsigned char* buffer = const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(utf8Str.c_str()));

    // Вычисляем CRC32
    unsigned int crc = crc32(0, buffer, utf8Str.Length());

    // Форматируем в 8-символьную шестнадцатеричную строку
	String hexHash = Format(L"%.8X", ARRAYOFCONST((static_cast<int>(crc))));
    hexHash.Insert(L"-", 5);
	return hexHash;
}
void getInfoPC() {
	DWORD bufCharCount = 32767;
	TCHAR infoBuf[32767];
	if( GetComputerName( infoBuf, &bufCharCount ) ) {
		indefPC.desktopName = UnicodeString(infoBuf);
	} else indefPC.desktopName = "ErrorNAME";
	//indefPC.catPC = t_cat;
	// получаем данные из SMB - serial
	UnicodeString errSer[] = {
		"To Be Filled By O.E.M.",
		"Not Applicable",
		"System Serial Number",
		"Default string",
		"serial number"
	};
	GetSMB g;
	PRAW_SMBIOS_DATA dataSMB = g.GetSmbiosData();
	if (dataSMB == NULL) {
		indefPC.sn_Main = "Помилка SMBIOS_DATA!";
		indefPC.sn_UUID = "Помилка SMBIOS_DATA!";
		indefPC.sn_serialMrb = "Помилка SMBIOS_DATA!";
		indefPC.sn_CPUID = "Помилка SMBIOS_DATA!";
	}
	indefPC.sn_Main = g.GetBiosString(dataSMB, SMB_TABLE_SYSTEM, 7);
	indefPC.sn_UUID = g.GetBiosValue(dataSMB, SMB_TABLE_SYSTEM, 8, 16);
	indefPC.sn_serialMrb = g.GetBiosString(dataSMB, SMB_TABLE_BASEBOARD, 7);
	indefPC.sn_CPUID = g.GetBiosValue(dataSMB, SMB_TABLE_PROCESSOR, 8, 8);
	UnicodeString toHash  = indefPC.sn_Main +
							indefPC.sn_UUID +
							indefPC.sn_serialMrb +
							indefPC.sn_CPUID;
//	unSerial = GetHashCRC32(toHash);
	indefPC.sn_hash = getFastHash_CRC32(toHash);
}
/* Работа с JSON */
bool SaveDataToJSON(const String& FilePath, const indefPCtype& indefPC, const std::vector<deviceInfo>& DataVector)
{
	// Используем std::unique_ptr для безопасного управления памятью корневого объекта
	std::unique_ptr<TJSONObject> root(new TJSONObject());

    try {
        // 1. Создаем и заполняем объект устройства
		TJSONObject* indeficatePC = new TJSONObject();
		indeficatePC->AddPair("desktopName", indefPC.desktopName);
		indeficatePC->AddPair("catPC", indefPC.catPC);
		indeficatePC->AddPair("sn_Main", indefPC.sn_Main);
		indeficatePC->AddPair("sn_serialMrb", indefPC.sn_serialMrb);
		indeficatePC->AddPair("sn_UUID", indefPC.sn_UUID);
		indeficatePC->AddPair("sn_CPUID", indefPC.sn_CPUID);
		indeficatePC->AddPair("sn_hash", indefPC.sn_hash);

        // Добавляем объект устройства в корень
		root->AddPair("indef", indeficatePC);

		// 2. Создаем массив для вектора данных
        TJSONArray* dataArray = new TJSONArray();
		for (const deviceInfo& record : DataVector) {
            TJSONObject* recordObj = new TJSONObject();
			recordObj->AddPair("className", record.className);
			recordObj->AddPair("enumeratorName", record.enumeratorName);
			recordObj->AddPair("friendlyName", record.friendlyName);
			recordObj->AddPair("devDesc", record.devDesc);
			recordObj->AddPair("devInstanceID", record.devInstanceID);
			recordObj->AddPair("serialNumber", record.serialNumber);
			recordObj->AddPair("status", record.status);
			recordObj->AddPair("containerId", record.containerId);
			recordObj->AddPair("containerName", record.containerName);
//			recordObj->AddPair("regName", record.regName);
//			recordObj->AddPair("regCatName", record.regCatName);
//			recordObj->AddPair("regCatNumber", String(record.regCatNumber)); //short
//			recordObj->AddPair("serialKnow", String(record.serialKnow)); //bool
//			recordObj->AddPair("serialErr", String(record.serialErr));  //boll
			recordObj->AddPair("lastConnect", FormatDateTime("dd.mm.yyyy hh:nn:ss", record.lastConnect));		   //DateTime
			recordObj->AddPair("lastDisconnect", FormatDateTime("dd.mm.yyyy hh:nn:ss", record.lastDisconnect));     //DateTime
			recordObj->AddPair("firstInstallDate", FormatDateTime("dd.mm.yyyy hh:nn:ss", record.firstInstallDate)); //DateTime

            dataArray->AddElement(recordObj); // Массив забирает владение recordObj
        }

        // Добавляем массив в корень
        root->AddPair("devices", dataArray);

        // 3. Форматируем JSON в строку (превращаем в "красивый" вид с отступами)
        // Если красивый вид не нужен, можно использовать просто root->ToString()
        String jsonString = root->Format(2);

        // 4. Записываем строку в файл (TFile автоматически создаст директории, если нужно)
		TFile::WriteAllText(FilePath, jsonString, TEncoding::UTF8);

        return true;
    }
    catch (const Exception& e) {
        // Здесь можно обработать ошибку записи или формата
        // OutputDebugString(e.Message.c_str());
        return false;
    }
}
bool LoadDataFromJSON(const UnicodeString& filePath)
{
	devicesList.clear();

    // 1. Проверяем существование файла
    if (!TFile::Exists(filePath)) {
        printLog(L"Ошибка загрузки JSON: Файл не найден (" + filePath + L")");
        return false;
    }

    try
    {
        // 2. Считываем весь текст из файла
        UnicodeString jsonText = TFile::ReadAllText(filePath);

        // 3. Парсим строку в корневой JSON-объект
        std::unique_ptr<TJSONObject> rootObject(dynamic_cast<TJSONObject*>(TJSONObject::ParseJSONValue(jsonText)));

        if (!rootObject) {
            printLog(L"Ошибка загрузки JSON: Некорректный формат файла.");
            return false;
        }

        // --- БЛОК 4: ЧТЕНИЕ МЕТАДАННЫХ КОМПЬЮТЕРА (indef) ---
        // ВАЖНО: перезаписываем indefPC данными ИЗ ЗАГРУЖЕННОГО ФАЙЛА. Без этого indefPC
        // (в частности catPC — категория секретности) оставался бы от локального ПК, и
        // вся логика "нарушение категорії" (regCatNumber > indefPC.catPC) сравнивала бы
        // устройства чужого ПК с неправильным порогом.
        TJSONObject* indefObj = dynamic_cast<TJSONObject*>(rootObject->Get(L"indef")->JsonValue);
        if (indefObj) {
            indefPC.desktopName  = indefObj->Values[L"desktopName"]  ? indefObj->Values[L"desktopName"]->Value()  : L"";
            indefPC.catPC        = indefObj->Values[L"catPC"]        ? (short)indefObj->Values[L"catPC"]->Value().ToIntDef(0) : 0;
            indefPC.sn_Main      = indefObj->Values[L"sn_Main"]      ? indefObj->Values[L"sn_Main"]->Value()      : L"";
            indefPC.sn_serialMrb = indefObj->Values[L"sn_serialMrb"] ? indefObj->Values[L"sn_serialMrb"]->Value() : L"";
            indefPC.sn_UUID      = indefObj->Values[L"sn_UUID"]      ? indefObj->Values[L"sn_UUID"]->Value()      : L"";
            indefPC.sn_CPUID     = indefObj->Values[L"sn_CPUID"]     ? indefObj->Values[L"sn_CPUID"]->Value()     : L"";
            indefPC.sn_hash      = indefObj->Values[L"sn_hash"]      ? indefObj->Values[L"sn_hash"]->Value()      : L"";

            printLog(L"Загружен лог компьютера: " + indefPC.desktopName + L" (категорія: " + IntToStr(indefPC.catPC) + L")");
        }

        // --- БЛОК 5: ЧТЕНИЕ МАССИВА УСТРОЙСТВ (devices) ---
        TJSONArray* devicesArray = dynamic_cast<TJSONArray*>(rootObject->Get(L"devices")->JsonValue);
        if (!devicesArray) {
            printLog(L"Ошибка JSON: Массив 'devices' не найден.");
            return false;
        }

        // Лямбда-помощник для безопасного чтения дат из строк JSON обратно в TDateTime
        auto parseJsonDate = [](UnicodeString dateStr) -> TDateTime {
            if (dateStr.StartsWith(L"30.12.1899")) return 0.0; // Пустая системная дата Delphi
            return StrToDateTimeDef(dateStr, 0.0);
        };

        // 6. Перебираем все элементы массива устройств
        for (int i = 0; i < devicesArray->Count; i++)
        {
            TJSONObject* devObj = dynamic_cast<TJSONObject*>(devicesArray->Items[i]);
            if (!devObj) continue;

            deviceInfo dev;

            // Безопасно вытаскиваем строковые значения по ключам
            dev.className     = devObj->Values[L"className"]     ? devObj->Values[L"className"]->Value()     : L"";
            dev.enumeratorName= devObj->Values[L"enumeratorName"]? devObj->Values[L"enumeratorName"]->Value(): L"";
            dev.friendlyName  = devObj->Values[L"friendlyName"]  ? devObj->Values[L"friendlyName"]->Value()  : L"";
            dev.devDesc       = devObj->Values[L"devDesc"]       ? devObj->Values[L"devDesc"]->Value()       : L"";
            dev.devInstanceID = devObj->Values[L"devInstanceID"] ? devObj->Values[L"devInstanceID"]->Value() : L"";
            dev.serialNumber  = devObj->Values[L"serialNumber"]  ? devObj->Values[L"serialNumber"]->Value()  : L"";
            dev.status        = devObj->Values[L"status"]        ? devObj->Values[L"status"]->Value()        : L"";
            dev.containerId   = devObj->Values[L"containerId"]   ? devObj->Values[L"containerId"]->Value()   : L"";
            dev.containerName = devObj->Values[L"containerName"] ? devObj->Values[L"containerName"]->Value() : L"";

            // Парсим даты обратно в честный TDateTime
            UnicodeString lastConnectStr    = devObj->Values[L"lastConnect"]    ? devObj->Values[L"lastConnect"]->Value()    : L"";
            UnicodeString lastDisconnectStr = devObj->Values[L"lastDisconnect"] ? devObj->Values[L"lastDisconnect"]->Value() : L"";
            UnicodeString firstInstallStr   = devObj->Values[L"firstInstallDate"]? devObj->Values[L"firstInstallDate"]->Value(): L"";

            dev.lastConnect      = parseJsonDate(lastConnectStr);
            dev.lastDisconnect   = parseJsonDate(lastDisconnectStr);
            dev.firstInstallDate = parseJsonDate(firstInstallStr);
            dev.installDate      = 0.0; // Если в JSON её нет, ставим пустую

            devicesList.push_back(dev);
        }

        printLog(L"Успешно распарсено устройств из JSON: " + IntToStr((int)devicesList.size()));
        return true;
    }
    catch (const Exception& e)
    {
        printLog(L"Критическая ошибка при чтении JSON: " + e.Message);
        return false;
    }
}
bool __fastcall TForm1::SaveDataToDB(const String& filePath) {
    // 1. Проверяем, активно ли подключение к базе в памяти
	if (!FDConnection1->Connected) {
        printLog(L"Ошибка сохранения: FDConnection1 не подключен.");
        return false;
    }

    try
    {
        // 2. Если файл с таким именем уже существует, удаляем его,
        // иначе SQLite выдаст ошибку при копировании
        if (TFile::Exists(filePath)) {
			TFile::Delete(filePath);
        }

        // 3. Формируем SQL-команду для копирования базы из памяти на диск.
        // Функция QuotedStr автоматически обернет путь в одинарные кавычки.
        UnicodeString sql = L"VACUUM INTO " + QuotedStr(filePath);

        // 4. Выполняем команду
        FDConnection1->ExecSQL(sql);

        printLog(L"База данных успешно сохранена в файл: " + filePath);
        return true;
    }
    catch (const Exception &e)
    {
        printLog(L"Критическая ошибка при сохранении БД на диск: " + e.Message);
        return false;
	}
}
// ------------
/* Строит содержимое txt-выгрузки для ESET по текущему (уже отфильтрованному по
   всем активным фильтрам) выводу FDQuery1. Первая строка — фиксированный заголовок
   плагина, дальше по строке на устройство: ,,serial_number,regName. Строки
   с пустым серийным номером и повторы уже встречавшегося серийного номера
   не сохраняются. */
UnicodeString __fastcall TForm1::BuildEsetTxtContent()
{
	UnicodeString content =
		L"# {\"product\":\"endpoint\",\"version\":\"10.1.2050\","
		L"\"path\":\"plugins.01000e00.settings.groups.1.params\","
		L"\"columns\":[\"vendor\",\"model\",\"serial\",\"description\"]}\r\n";

	std::map<UnicodeString, bool> seenSerials;

	TBookmark bm = FDQuery1->GetBookmark();
	FDQuery1->DisableControls();
	try
	{
		FDQuery1->First();
		while (!FDQuery1->Eof)
		{
			UnicodeString serial = FDQuery1->FieldByName(L"serial_number")->AsString.Trim();
			if (!serial.IsEmpty() && seenSerials.find(serial) == seenSerials.end())
			{
				seenSerials[serial] = true;
				UnicodeString description = FDQuery1->FieldByName(L"regName")->AsString.Trim();
				content += L",," + serial + L"," + description + L"\r\n";
			}
			FDQuery1->Next();
		}
	}
	__finally
	{
		if (FDQuery1->BookmarkValid(bm)) {
			FDQuery1->GotoBookmark(bm);
		}
		FDQuery1->FreeBookmark(bm);
		FDQuery1->EnableControls();
	}

	return content;
}
bool __fastcall TForm1::SaveDataToEsetTxt(const String& FilePath)
{
	if (!FDQuery1->Active) {
		printLog(L"Ошибка сохранения: FDQuery1 не активен.");
		return false;
	}

	try
	{
		UnicodeString content = BuildEsetTxtContent();
		TFile::WriteAllText(FilePath, content, TEncoding::UTF8);
		return true;
	}
	catch (const Exception &e)
	{
		printLog(L"Ошибка сохранения ESET txt: " + e.Message);
		return false;
	}
}
// ------------
bool LoadFontFromResource()
{
    // 1. Находим ресурс в собственном .exe модуле
    HRSRC resInfo = FindResource(HMODULE(HINSTANCE(NULL)), L"MY_EMBEDDED_FONT", RT_RCDATA);
    if (!resInfo) {
        // Если ресурс не найден, программа продолжит работать со стандартным шрифтом
        return false;
    }

    // 2. Загружаем ресурс в память
    HGLOBAL resData = LoadResource(HMODULE(HINSTANCE(NULL)), resInfo);
    if (!resData) return false;

    // 3. Получаем прямой указатель на байты шрифта в памяти и его размер
    void* fontData = LockResource(resData);
    DWORD fontSize = SizeofResource(HMODULE(HINSTANCE(NULL)), resInfo);

    if (fontData && fontSize > 0)
    {
        DWORD numFonts = 0;

        // 4. Регистрируем шрифт в системе ИСКЛЮЧИТЕЛЬНО для нашего процесса
        g_FontHandle = AddFontMemResourceEx(fontData, fontSize, NULL, &numFonts);

        return (g_FontHandle != NULL);
    }

    return false;
}
UnicodeString GetAppVersion()
{
    // Получаем полный путь к нашему запущенному .exe файлу
    UnicodeString exeName = Application->ExeName;
    DWORD dummy = 0;

    // Узнаем размер данных о версии
    DWORD size = GetFileVersionInfoSize(exeName.c_str(), &dummy);
    if (size == 0) return L"1.0.0.0"; // Если версия не задана в настройках

    // Выделяем память под данные (используем вектор для автоматической очистки памяти)
    std::vector<BYTE> buffer(size);

    // Считываем блок информации о версии
    if (!GetFileVersionInfo(exeName.c_str(), 0, size, buffer.data())) {
        return L"1.0.0.0";
    }

    VS_FIXEDFILEINFO* fileInfo = nullptr;
    UINT fileInfoSize = 0;

    // Извлекаем фиксированную структуру с номерами
    if (VerQueryValue(buffer.data(), L"\\", (LPVOID*)&fileInfo, &fileInfoSize) && fileInfoSize > 0)
    {
        // Вытаскиваем мажорную, минорную версию, релиз и билд
        int major = HIWORD(fileInfo->dwFileVersionMS);
        int minor = LOWORD(fileInfo->dwFileVersionMS);
        int release = HIWORD(fileInfo->dwFileVersionLS);
        int build = LOWORD(fileInfo->dwFileVersionLS);

        // Формируем красивую строку
        return UnicodeString().sprintf(L"%d.%d.%d.%d", major, minor, release, build);
    }

    return L"Неизвестно";
}
//---------------------------------------------------------------------------

/* Обновление устройств с текущего ПК */
void DeviceUpdate_ARM () {

}
void DeviceUpdate_JSON () {

}
void __fastcall TForm1::Button_DeviceUpdateCurPCClick(TObject *Sender)
{
	Button_DelDevice->Enabled = true;

	// сканируем устройства
	devicesList = scanDevices();
	if (devicesList.empty()) {
		printLog("Устройства не найдены.");
		return;
	}
	// распознаем извесные флешки
	checkRegDevice(devicesList);
	// переносим в БД
	vectorToBD(devicesList);
	// обновляем фильтр "по классам устройств"
	UpdateClassFilterList();
	// синхронизируем состояние активного основного фильтра, чтобы последующий клик
	// по доп.фильтру (ListBox_Filter/чекбоксы) не унаследовал устаревший режим
	SetActiveFilter(mfmAll, L"");
	// выводим данные с БД в таблицу
	refrechDBGrid(sql_all);

	return;
}
/* Обновление устройств с JSON */
void __fastcall TForm1::Button_LoadFromJSONClick(TObject *Sender)
{
	// Настраиваем фильтр файлов для OpenDialog
	OpenDialog_FromJSON->Filter = L"JSON файлы (*.json)|*.json|Все файлы (*.*)|*.*";
	OpenDialog_FromJSON->FileName = L"devList.json";

	if (OpenDialog_FromJSON->Execute())
	{
        UnicodeString selectedFile = OpenDialog_FromJSON->FileName;

		if (LoadDataFromJSON(selectedFile))
		{
			CheckBox_AutoUpdateDev->Checked = false;
			CheckBox_AutoUpdateDev->Enabled = false;
			Timer1->Enabled = false; // отменяем не сработавший debounce, чтобы он не всплыл поверх загруженного снимка
			Button_DelDevice->Enabled = false;
			// синхронизируем комбобокс категорії з даними ЗАГРУЖЕНОГО ПК (indefPC уже обновлен в LoadDataFromJSON)
			ComboBox_CategPC->ItemIndex = indefPC.catPC;
			// распознаем извесные флешки
			checkRegDevice(devicesList);
			// переносим в БД
			vectorToBD(devicesList);
			// обновляем фильтр "по классам устройств"
			UpdateClassFilterList();
			// синхронизируем состояние активного основного фильтра (см. Button_DeviceUpdateCurPCClick)
			SetActiveFilter(mfmAll, L"");
			// выводим данные с БД в таблицу
			refrechDBGrid(sql_all);
			printLog(L"База данных успешно обновлена данными из файла: " + ExtractFileName(selectedFile));
        }
		else
		{
			MessageDlg(L"Не удалось загрузить данные из выбранного JSON-файла.", mtError, TMsgDlgButtons() << mbOK, 0);
		}
	}
}
//---------------------------------------------------------------------------
/* СОРТИРОВКА таблицs по столбцу */
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
/* Фиксирует активный основной фильтр (режим + SQL-условие) без побочных эффектов —
   вызывается из обработчиков кнопок Show* / FilterContainerID и из мест, где нужно
   синхронизировать состояние без применения фильтра (Button_DeviceUpdateCurPCClick,
   Button_LoadFromJSONClick, конструктор). */
void __fastcall TForm1::SetActiveFilter(TMainFilterMode mode, const UnicodeString &condition)
{
	m_activeFilterMode = mode;
	m_activeFilterCondition = condition;
}
/* Базовый SQL под активный основной режим: USB-режимы используют sql_usb (дедуп по
   containerId), остальные — sql_all. */
String __fastcall TForm1::GetBaseSqlForMode(TMainFilterMode mode)
{
	switch (mode)
	{
		case mfmUsb:
		case mfmUnknownUsb:
			return sql_usb;
		default:
			return sql_all;
	}
}
/* Условие для режима "неизвестные USB": serialKnow=0 и непустой серийный номер. */
UnicodeString __fastcall TForm1::BuildUnknownUsbFilterCondition()
{
	return L"serialKnow = " + QuotedStr("0") +
		L" AND serial_number IS NOT NULL AND serial_number <> ''";
}
/* Условие для режима "нарушения": совпадение по class_name/friendly_name из
   v_allertName ИЛИ regCatNumber выше текущей категории ПК (indefPC.catPC). */
UnicodeString __fastcall TForm1::BuildAlertFilterCondition()
{
	UnicodeString nameConditions = L"";
	for (size_t i = 0; i < v_allertName.size(); ++i)
	{
		UnicodeString keyword = v_allertName[i].Trim();
		if (keyword.IsEmpty()) continue;

		keyword = StringReplace(keyword, L"'", L"''", TReplaceFlags() << rfReplaceAll);

		if (!nameConditions.IsEmpty()) {
			nameConditions += L" OR ";
		}
		nameConditions += L"(class_name LIKE '%" + keyword + L"%' OR friendly_name LIKE '%" + keyword + L"%')";
	}

	// Ни совпадение по имени/классу, ни превышение категории не считаются нарушением для
	// устройств, встроенных в материнскую плату (containerId = системный) — исключает
	// ложные срабатывания на штатные Bluetooth/Wi-Fi модули и прочее онбордовое "железо".
	const UnicodeString SYSTEM_CONTAINER_ID = L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}";
	UnicodeString notBuiltIn = L"containerId <> " + QuotedStr(SYSTEM_CONTAINER_ID);
	UnicodeString catCondition = L"regCatNumber > " + IntToStr(indefPC.catPC) + L" AND " + notBuiltIn;

	if (!nameConditions.IsEmpty()) {
		return L"((" + nameConditions + L") AND " + notBuiltIn + L") OR (" + catCondition + L")";
	}
	return catCondition;
}
/* Условие для чекбокса "тільки один SN": идём по текущему (ещё не отфильтрованному)
   набору данных и для каждого повторного вхождения непустого serial_number запоминаем
   id строки — в итоге остаётся только первое вхождение каждого серийного номера. */
UnicodeString __fastcall TForm1::BuildOnlyOneSNFilterCondition()
{
	if (!FDQuery1->Active) return L"";

	std::map<UnicodeString, bool> seenSerials;
	UnicodeString dupIds = L"";

	TBookmark bm = FDQuery1->GetBookmark();
	FDQuery1->DisableControls();
	try
	{
		FDQuery1->First();
		while (!FDQuery1->Eof)
		{
			UnicodeString sn = FDQuery1->FieldByName(L"serial_number")->AsString.Trim();
			if (!sn.IsEmpty())
			{
				if (seenSerials.find(sn) != seenSerials.end())
				{
					if (!dupIds.IsEmpty()) {
						dupIds += L",";
					}
					dupIds += FDQuery1->FieldByName(L"id")->AsString;
				}
				else
				{
					seenSerials[sn] = true;
				}
			}
			FDQuery1->Next();
		}
	}
	__finally
	{
		if (FDQuery1->BookmarkValid(bm)) {
			FDQuery1->GotoBookmark(bm);
		}
		FDQuery1->FreeBookmark(bm);
		FDQuery1->EnableControls();
	}

	if (dupIds.IsEmpty()) return L"";
	return L"id NOT IN (" + dupIds + L")";
}
//---------------------------------------------------------------------------
/* ОБЩИЙ ФИЛЬТР для FDQuery1: активный основной фильтр (кнопки Show* / FilterContainerID) +
   классы (ListBox) + материнская плата + пустой серийный номер (CheckBox_SNnotNULL) +
   известный серийный номер (CheckBox_ShowKnowUSB) + только один SN (CheckBox_OnlyOneSN). */
void __fastcall TForm1::ApplyDBGridFilter()
{
	// Выбираем базовый SQL под активный основной режим и переоткрываем датасет
	String baseSql = GetBaseSqlForMode(m_activeFilterMode);
	refrechDBGrid(baseSql);

	if (!FDQuery1->Active) return;

	FDQuery1->Filtered = false;

	// 1. Условия из ListBox (фильтр по классам)
	UnicodeString listboxFilter = L"";
	for (int i = 0; i < ListBox_Filter->Items->Count; i++)
	{
		if (ListBox_Filter->Selected[i])
		{
			UnicodeString value = ListBox_Filter->Items->Strings[i];

			if (value == "(Усі класи)")
			{
				listboxFilter = L"";
				break;
			}
			if (value == "(USB пристрої)")
			{
				listboxFilter = L"class_name IN ('SCSIAdapter', 'USB', 'WPD', 'DiskDrive', 'Volume')";
				break;
			}

			if (!listboxFilter.IsEmpty()) {
				listboxFilter += L" OR ";
			}

			listboxFilter += L"class_name = " + QuotedStr(value);
		}
	}
	if (!listboxFilter.IsEmpty()) {
		listboxFilter = L"(" + listboxFilter + L")";
	}

	// 2. Чекбокс фильтра по материнской плате
	const UnicodeString SYSTEM_CONTAINER_ID = L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}";
	UnicodeString mbFilter = L"";
	if (!CheckBox_FilterMotherboard->Checked)
	{
		mbFilter = L"containerId <> " + QuotedStr(SYSTEM_CONTAINER_ID);
	}

	// 3. Чекбокс CheckBox_WIP2 — отключить строки с пустым серийным номером
	UnicodeString emptySerialFilter = L"";
	if (CheckBox_SNnotNULL->Checked)
	{
		emptySerialFilter = L"serial_number IS NOT NULL AND serial_number <> ''";
	}

	// 4. Чекбокс CheckBox_ShowKnowUSB — показывать только устройства с известным серийным номером
	UnicodeString knownSerialFilter = L"";
	if (CheckBox_ShowKnowUSB->Checked)
	{
		knownSerialFilter = L"serialKnow = " + QuotedStr("1");
	}

	// 5. Чекбокс CheckBox_OnlyOneSN — убрать строки с дублирующимися серийными номерами,
	// оставив только первое вхождение каждого SN
	UnicodeString onlyOneSnFilter = L"";
	if (CheckBox_OnlyOneSN->Checked)
	{
		onlyOneSnFilter = BuildOnlyOneSNFilterCondition();
	}

	// 6. Объединяем условие активного основного фильтра (Show*/FilterContainerID) с
	// доп.фильтрами через AND — основной фильтр теперь всегда учитывается
	std::vector<UnicodeString> parts;
	if (!m_activeFilterCondition.IsEmpty()) parts.push_back(m_activeFilterCondition);
	if (!listboxFilter.IsEmpty()) parts.push_back(listboxFilter);
	if (!mbFilter.IsEmpty()) parts.push_back(mbFilter);
	if (!emptySerialFilter.IsEmpty()) parts.push_back(emptySerialFilter);
	if (!knownSerialFilter.IsEmpty()) parts.push_back(knownSerialFilter);
	if (!onlyOneSnFilter.IsEmpty()) parts.push_back(onlyOneSnFilter);

	UnicodeString finalFilter = L"";
	for (size_t i = 0; i < parts.size(); ++i)
	{
		if (!finalFilter.IsEmpty()) {
			finalFilter += L" AND ";
		}
		finalFilter += parts[i];
	}

	if (finalFilter.IsEmpty())
	{
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
	FDQuery1AfterOpen(FDQuery1);
}
//---------------------------------------------------------------------------
/* ФИЛЬТР общий по класам */
void __fastcall TForm1::ListBox_FilterClick(TObject *Sender)
{
	ApplyDBGridFilter();
}
//---------------------------------------------------------------------------
/* ==== КНОПКИ ФИЛЬТРА ==== */
/* Скинуть все ФИЛЬТРы */
void __fastcall TForm1::Button_ShowAllClick(TObject *Sender)
{
	CheckBox_FilterMotherboard->Checked = true;
	CheckBox_FilterMotherboard->Enabled = true;
	CheckBox_SNnotNULL->Enabled = true;
	CheckBox_SNnotNULL->Checked = false;
	CheckBox_ShowKnowUSB->Enabled = true;
	CheckBox_ShowKnowUSB->Checked = false;
	CheckBox_OnlyOneSN->Enabled = true;
	CheckBox_OnlyOneSN->Checked = false;
	ListBox_Filter->ClearSelection();

	SetActiveFilter(mfmAll, L"");
	ApplyDBGridFilter();

	printLog(L"Сброс всех фильтров");
}
/* ФИЛЬТР по всем флешкам */
void __fastcall TForm1::Button_ShowUSBClick(TObject *Sender)
{
	CheckBox_FilterMotherboard->Checked = false;
	CheckBox_FilterMotherboard->Enabled = false;
	CheckBox_SNnotNULL->Enabled = true;
	CheckBox_SNnotNULL->Checked = false;
    CheckBox_ShowKnowUSB->Enabled = true;
	CheckBox_ShowKnowUSB->Checked = false;
    CheckBox_OnlyOneSN->Enabled = true;
	CheckBox_OnlyOneSN->Checked = false;
	ListBox_Filter->ClearSelection();

	SetActiveFilter(mfmUsb, L"");
	ApplyDBGridFilter();

	printLog(L"Отображаются все USB устройства");
}
/* ФИЛЬТР по неизвесным флешкам */
void __fastcall TForm1::Button_ShowUnknowUSBClick(TObject *Sender)
{
	CheckBox_FilterMotherboard->Enabled = false;
	CheckBox_FilterMotherboard->Checked = false;
	CheckBox_SNnotNULL->Enabled = false;
	CheckBox_SNnotNULL->Checked = true;
	CheckBox_ShowKnowUSB->Enabled = false;
	CheckBox_ShowKnowUSB->Checked = false;
	CheckBox_OnlyOneSN->Enabled = false;
	CheckBox_OnlyOneSN->Checked = false;
	ListBox_Filter->ClearSelection();

	SetActiveFilter(mfmUnknownUsb, BuildUnknownUsbFilterCondition());
	ApplyDBGridFilter();

	printLog(L"Отображаются только неизвесные USB устройства");
}
/* ФИЛЬТР по НАРУШЕНИЯМ */
void __fastcall TForm1::Button_ShowAllertClick(TObject *Sender)
{
	CheckBox_FilterMotherboard->Enabled = false;
	CheckBox_FilterMotherboard->Checked = false;
	CheckBox_SNnotNULL->Enabled = false;
	CheckBox_SNnotNULL->Checked = true;
	CheckBox_ShowKnowUSB->Enabled = false;
	CheckBox_ShowKnowUSB->Checked = true;
	CheckBox_OnlyOneSN->Enabled = false;
	CheckBox_OnlyOneSN->Checked = true;
	ListBox_Filter->ClearSelection();

	SetActiveFilter(mfmAlert, BuildAlertFilterCondition());
	ApplyDBGridFilter();

	printLog(L"Применен alert-фильтр (клас/ім'я зі списку порушень або категорія вища за поточну)");
}
/* ФИЛЬТР по контейнеру */
void __fastcall TForm1::Button_FilterContainerIDClick(TObject *Sender)
{
	// 1. Убеждаемся, что запрос активен и в гриде есть данные
    if (!FDQuery1->Active || FDQuery1->IsEmpty()) {
        return;
    }

    // 2. Получаем Container ID выделенной строки (текущей записи) — ОБЯЗАТЕЛЬНО САМЫМ
    // ПЕРВЫМ ДЕЛОМ, до любых изменений чекбоксов/ListBox ниже. Программное присвоение
    // CheckBox->Checked, если оно реально меняет состояние, само вызывает OnClick этого
    // чекбокса (TCustomCheckBox.SetState -> Click в VCL), а тот обработчик вызывает
    // ApplyDBGridFilter()/refrechDBGrid(), которые переоткрывают датасет и сбрасывают
    // текущую позицию курсора на первую запись — из-за этого раньше иногда бралась
    // не выделенная пользователем строка, а первая (нестабильно, в зависимости от того,
    // менялось ли состояние чекбоксов относительно предыдущего активного фильтра).
    // ВАЖНО: Замените "containerId" на точное имя этого поля в вашей таблице SQLite!
    UnicodeString selectedContainerId = FDQuery1->FieldByName(L"containerId")->AsString;

    // 3. Проверяем, что у устройства вообще есть нормальный контейнер
    if (selectedContainerId.IsEmpty() || selectedContainerId == L"No Container" || selectedContainerId == L"GUID Error") {
        printLog(L"У выделенного устройства нет контейнера для фильтрации.");
        return;
	}

	CheckBox_FilterMotherboard->Enabled = true;
	CheckBox_FilterMotherboard->Checked = true;
	CheckBox_SNnotNULL->Enabled = true;
	CheckBox_SNnotNULL->Checked = false;
	CheckBox_ShowKnowUSB->Enabled = true;
	CheckBox_ShowKnowUSB->Checked = false;
	CheckBox_OnlyOneSN->Enabled = true;
	CheckBox_OnlyOneSN->Checked = false;
	ListBox_Filter->ClearSelection();

	SetActiveFilter(mfmContainer, L"containerId = " + QuotedStr(selectedContainerId));
	ApplyDBGridFilter();

	printLog(L"Отображаются устройства контейнера: " + selectedContainerId);
}
//---------------------------------------------------------------------------
/* ФИЛЬТР по системным устройствам */
void __fastcall TForm1::CheckBox_FilterMotherboardClick(TObject *Sender)
{
	// При клике на чекбокс просто вызываем пересчет общего фильтра
	ApplyDBGridFilter();
}
//---------------------------------------------------------------------------
/* ФИЛЬТР по пустому серийному номеру */
void __fastcall TForm1::CheckBox_SNnotNULLClick(TObject *Sender)
{
	ApplyDBGridFilter();
}
//---------------------------------------------------------------------------
/* ФИЛЬТР по известному серийному номеру (serialKnow = 1) */
void __fastcall TForm1::CheckBox_ShowKnowUSBClick(TObject *Sender)
{
	ApplyDBGridFilter();
}
//---------------------------------------------------------------------------
/* ФИЛЬТР по дублям серийного номера — оставляет только одну строку на каждый SN */
void __fastcall TForm1::CheckBox_OnlyOneSNClick(TObject *Sender)
{
	ApplyDBGridFilter();
}
//---------------------------------------------------------------------------
/* ПОИСК по серийному номеру — не фильтр, а подсветка совпадающих строк в текущем
   выводе (см. DBGrid1DrawColumnCell); срабатывает автоматически при каждом
   изменении поля. */
void __fastcall TForm1::LabeledEdit_SearchSNChange(TObject *Sender)
{
	DBGrid1->Repaint();
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
	UnicodeString devSerial = grid->DataSource->DataSet->FieldByName(L"serial_number")->AsString;
	UnicodeString devDescription  = grid->DataSource->DataSet->FieldByName(L"dev_desc")->AsString;
	UnicodeString devContainerId = grid->DataSource->DataSet->FieldByName(L"containerId")->AsString;
	short devCat  = grid->DataSource->DataSet->FieldByName(L"regCatNumber")->AsInteger;
	short devKnow = grid->DataSource->DataSet->FieldByName(L"serialKnow")->AsInteger;
	short devErr  = grid->DataSource->DataSet->FieldByName(L"serialErr")->AsInteger;

	// Ни совпадение с v_allertName, ни превышение категории не считаются нарушением для
	// устройств, встроенных в материнскую плату (containerId = системный) — исключает
	// ложные срабатывания на штатные Bluetooth/Wi-Fi модули и прочее онбордовое "железо".
	const UnicodeString SYSTEM_CONTAINER_ID = L"{00000000-0000-0000-FFFF-FFFFFFFFFFFF}";
	bool isBuiltIn = (devContainerId == SYSTEM_CONTAINER_ID);
	bool nameMatchesAlert = !isBuiltIn && compareStrInVector(devName, v_allertName);
	bool descMatchesAlert = !isBuiltIn && compareStrInVector(devDescription, v_allertName);
	bool catViolation = !isBuiltIn && (devCat > indefPC.catPC);

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
		//Устройство с нарушением — разные цвета для разных типов нарушения.
		// Нарушение по категории (важнее) перекрывает нарушение по названию, если оба сразу.
		if (catViolation)
		{
			grid->Canvas->Brush->Color = (TColor)0x00D0D0FF; // Очень бледный красный — нарушение категории
		}
		else if (nameMatchesAlert || descMatchesAlert)
		{
			grid->Canvas->Brush->Color = (TColor)0x00B2E0FF; // Очень бледный оранжевый — нарушение по названию
		}

		// Подсветка совпадения с полем поиска по серийному номеру (LabeledEdit_SearchSN) —
		// имеет наивысший приоритет среди фоновых подсветок этой строки
		UnicodeString searchSN = LabeledEdit_SearchSN->Text.Trim();
		if (!searchSN.IsEmpty() && devSerial.UpperCase().Pos(searchSN.UpperCase()) > 0)
		{
			grid->Canvas->Brush->Color = (TColor)0x0000FFFF; // Ярко-желтый (BGR)
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
	if ((Column->FieldName == L"regName" || Column->FieldName == L"regCatName") && catViolation && !State.Contains(gdSelected))
	{
		grid->Canvas->Font->Color = clRed;
		grid->Canvas->Font->Style = TFontStyles() << fsBold;
	}
	// нарушение в названии
	if (Column->FieldName == L"friendly_name" && nameMatchesAlert)
	{
		grid->Canvas->Font->Color = clRed;
		grid->Canvas->Font->Style = TFontStyles() << fsBold;
//		grid->Canvas->Brush->Color = (TColor)0x00D0D0FF;
	}
	if (Column->FieldName == L"dev_desc" && descMatchesAlert)
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
	try { indefPC.catPC = m_catNumber.at(ComboBox_CategPC->Text); }
	catch (const std::out_of_range& error) { indefPC.catPC = 0; }

	// Alert-условие зависит от indefPC.catPC (regCatNumber > indefPC.catPC) —
	// если сейчас активен режим "нарушения", пересчитываем его и переприменяем фильтр
	if (m_activeFilterMode == mfmAlert)
	{
		SetActiveFilter(mfmAlert, BuildAlertFilterCondition());
		ApplyDBGridFilter();
	}
	else
	{
		DBGrid1->Repaint();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false; // Выключаем таймер
	if (!CheckBox_AutoUpdateDev->Checked) return; // Автообновление могли выключить, пока таймер уже был взведён (например, во время загрузки JSON)
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

void __fastcall TForm1::Button_SaveToJSONClick(TObject *Sender)
{
	String t_str =
		"Слепок всех устройств в JSON файл (*.json)|*.json|"
		"Слепок всех устройств в SQLite DataBase (*.db)|*.db|"
		"Выгрузка для КП ESET (*.txt)|*.txt|"
		"Все файлы (*.*)|*.*";
	SaveDialog_ToFile->Filter = t_str.c_str();
	SaveDialog_ToFile->DefaultExt = L"json";
	SaveDialog_ToFile->FileName = L"devList";
	if (SaveDialog_ToFile->Execute()) {
		UnicodeString selectedFile = SaveDialog_ToFile->FileName;
		bool saved = false;
		if (SaveDialog_ToFile->FilterIndex == 1)      saved = SaveDataToJSON(selectedFile, indefPC, devicesList);
		else if (SaveDialog_ToFile->FilterIndex == 2) saved = SaveDataToDB(selectedFile);
		else if (SaveDialog_ToFile->FilterIndex == 3) saved = SaveDataToEsetTxt(selectedFile);
		else                                          printLog(L"Сохранение в этом формате не поддерживается.");

		if (saved) printLog(L"Устройства успешно записаны в файл: " + ExtractFileName(selectedFile));
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FDQuery1AfterOpen(TDataSet *DataSet)
{
    FDQuery1->FetchAll();
	int rowCount = 0;

    // 1. Если фильтр включен, берем количество отфильтрованных строк из Rows->Count
    if (FDQuery1->Filtered && FDQuery1->SourceView && FDQuery1->SourceView->Rows)
    {
        rowCount = FDQuery1->SourceView->Rows->Count;
    }
    else
    {
        // 2. Если фильтра нет (показываются вообще все устройства),
        // используем стандартный RecordCount
        rowCount = FDQuery1->RecordCount;
    }
	StatusBar1->Panels->Items[0]->Text = "ROW: " + IntToStr(rowCount);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

