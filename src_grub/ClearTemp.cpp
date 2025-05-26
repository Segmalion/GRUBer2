//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ClearTemp.h"
#include "Help.h"
#include "Text.h"
#include "Fille.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormClearTempDir *FormClearTempDir;
//---------------------------------------------------------------------------
std::vector<UnicodeString> dirListFull {
	"C:\\Windows\\Temp\\"
	};
std::vector<UnicodeString> dirListUser {
	"Temp\\",
	"AppData\\Local\\Temp\\",
	"AppData\\Roaming\\Microsoft\\Windows\\Recent\\",
	"AppData\\Roaming\\Microsoft\\Excel\\",
	"AppData\\Roaming\\Microsoft\\Word\\",
	"AppData\\Roaming\\Microsoft\\PowerPoint\\",
	"AppData\\Roaming\\Microsoft\\Office\\Recent\\",
	"AppData\\Roaming\\Microsoft\\Office\\Последние файлы\\",
	"AppData\\Roaming\\Microsoft\\Office\\Останні\\"
};
patchList fullList, tempList, recycleList;
//---------------------------------------------------------------------------
__fastcall TFormClearTempDir::TFormClearTempDir(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TFormClearTempDir::Button_CleanClick(TObject *Sender)
{
	ProgressBar_Clean->Position = 0;
	Button_Clean->Enabled = false;
	Memo_LOG->Lines->Add(fullList.countFille);
	long long step = fullList.countFille / 100;
	double tmpPos = 0;
	//кнопка очистки
	long long sizeDel  = 0, sizeUnDel  = 0;
	long long countDel = 0, countUnDel = 0, countAll = 0;
	//очистка временых папок
	Memo_LOG->Lines->Add("Видалення тимчасових файлів...");
	for(auto i: fullList.list) {
		if ((FileGetAttr(i.str) & faDirectory) != 0) {
			FileSetAttr(i.str, faDirectory);
			RemoveDir(i.str);
		} else {
			FileSetAttr(i.str, 0);
			if(DeleteFile(i.str)) {
				sizeDel += i.size;
				countDel++; countAll++;
			} else {
				sizeUnDel += i.size;
				countUnDel++; countAll++;
			}
		}
		if (step == 0) {
			tmpPos += 100 / (double)fullList.countFille;;
			ProgressBar_Clean->Position = tmpPos;
		} else if (countAll % step == 0) ProgressBar_Clean->Position ++;
	}
    //ProgressBar_Clean->Position = 100;
	//вывод
	Label5->Caption = countDel;
	//fullList.countFille = countUnDel;
	Memo_LOG->Lines->Add("----------------------------------");
	Memo_LOG->Lines->Add("Видаленно ----------- " + UnicodeString(countDel) + " (" + byteToStr(sizeDel) + ")");
	Memo_LOG->Lines->Add("Не вдалось видалити - " + UnicodeString(countUnDel) + " (" + byteToStr(sizeUnDel) + ")");
	Memo_LOG->Lines->Add("==================================");
}
//---------------------------------------------------------------------------
void __fastcall TFormClearTempDir::FormShow(TObject *Sender)
{
	ProgressBar_Clean->Position = 0;
    Button_Clean->Enabled = true;
	fullList = {};
	tempList = {};
	recycleList = {};
    Memo_LOG->Clear();
	Label4->Caption = "-";
	Label5->Caption = "-";
    Memo_LOG->Lines->Add("Пошук файлів...");
	// --- готовим список пользовательских папок (userDirList)---
	std::vector<UnicodeString> userListBad { //запрещеные пользователи
		"All Users",
		"Default",
		"Default User",
		"Public"
	};
	std::vector<UnicodeString> userDirList; //создаем вектор с папками пользователей
	// процедура поиска папок пользователей
	UnicodeString dirUser = "C:\\Users";
	TSearchRec srUser;
	if (!FindFirst(dirUser + "\\*.*", faAnyFile, srUser))
		do {
			if (!(srUser.Name == "." || srUser.Name == "..")) { // это не трогаем
				if ((srUser.Attr & faDirectory) != 0) {
					if (!compareVectorAndString(srUser.Name, userListBad)) {
						userDirList.push_back(dirUser + "\\" + srUser.Name);
					}
				}
			}
		} while (!FindNext(srUser)); // ищем пока не найдем все
	FindClose(srUser);
	/*
	for (auto a: userDirList) {
		Memo_LOG->Lines->Add("- " + UnicodeString(a));
	}
	*/
	// --- готовим список с папками корзин (recycleDirList) ---
	std::vector<UnicodeString> drives = getLocalDrivePatch();
	std::vector<UnicodeString> recycleDirList; //создаем вектор для папок корзин
	for(auto drive: drives) {
		//Memo_LOG->Lines->Add(drive);
		// процедура поиска папок пользователей
		UnicodeString dirRecycle = drive + "$Recycle.Bin";
		TSearchRec srRecycle;
		if (!FindFirst(dirRecycle + "\\*.*", faAnyFile, srRecycle))
			do {
				if (!(srRecycle.Name == "." || srRecycle.Name == "..")) { // это не трогаем
					if ((srRecycle.Attr & faDirectory) != 0) {
						recycleDirList.push_back(dirRecycle + "\\" + srRecycle.Name);
					}
				}
			} while (!FindNext(srRecycle)); // ищем пока не найдем все
		FindClose(srRecycle);
	}
	//Memo_LOG->Lines->Add("----------------------------------");
	//for(auto dir: recycleDirList) Memo_LOG->Lines->Add("-> " + dir);
	// ------------------------------------------------------------------
	// --- готовим список всех файлов во временых папках ---
	for (auto dir: dirListFull) {
		patchList temp = scanDirToFille(dir);
		tempList.list.insert(tempList.list.end(), temp.list.begin(), temp.list.end());
		tempList.countDir += temp.countDir ;
		tempList.countFille += temp.countFille ;
		tempList.size += temp.size;
	}
	for (auto userDir: userDirList) {
		for (auto dir: dirListUser) {
			patchList temp = scanDirToFille(userDir + "\\" + dir);
			tempList.list.insert(tempList.list.end(), temp.list.begin(), temp.list.end());
			tempList.countDir += temp.countDir;
			tempList.countFille += temp.countFille;
			tempList.size += temp.size;
		}
	}
	for (auto recycle: recycleDirList) {
		patchList temp = scanDirToFille(recycle);
		recycleList.list.insert(recycleList.list.end(), temp.list.begin(), temp.list.end());
		recycleList.countDir += temp.countDir ;
		recycleList.countFille += temp.countFille ;
		recycleList.size += temp.size;
	}
	fullList.list.insert(fullList.list.end(), tempList.list.begin(),    tempList.list.end());
	fullList.list.insert(fullList.list.end(), recycleList.list.begin(), recycleList.list.end());
	fullList.countDir 	= tempList.countDir   + recycleList.countDir;
	fullList.countFille = tempList.countFille + recycleList.countFille;
	fullList.size       = tempList.size       + recycleList.size;
	Memo_LOG->Lines->Add("----------------------------------");
	Memo_LOG->Lines->Add("ТИМЧАСОВІ ФАЙЛИ:");
	Memo_LOG->Lines->Add("Тек ---- " + UnicodeString(tempList.countDir));
	Memo_LOG->Lines->Add("Файлів - " + UnicodeString(tempList.countFille));
	Memo_LOG->Lines->Add("Розмір - " + byteToStr(tempList.size));
	Memo_LOG->Lines->Add("----------------------------------");
	Memo_LOG->Lines->Add("ФАЙЛИ В КОРЗИНІ:");
	Memo_LOG->Lines->Add("Тек ---- " + UnicodeString(recycleList.countDir));
	Memo_LOG->Lines->Add("Файлів - " + UnicodeString(recycleList.countFille));
	Memo_LOG->Lines->Add("Розмір - " + byteToStr(recycleList.size));
	Memo_LOG->Lines->Add("----------------------------------");
	Memo_LOG->Lines->Add("ЗАГАЛЬНО:");
	Memo_LOG->Lines->Add("Тек ---- " + UnicodeString(fullList.countDir));
	Memo_LOG->Lines->Add("Файлів - " + UnicodeString(fullList.countFille));
	Memo_LOG->Lines->Add("Розмір - " + byteToStr(fullList.size));
	Memo_LOG->Lines->Add("==================================");
//  Memo_LOG->Lines->Add("Знайденні тимчасові файли:");
//	patch.fille = patch.fille + recInfo.i64NumItems;
	Label4->Caption = UnicodeString(fullList.countFille);
//	for(auto i: patch.list) {
//		if (!i.dir) Memo_LOG->Lines->Add("-> [" + byteToStr(i.size) + "] - " + i.str);
//	}
}
//---------------------------------------------------------------------------

