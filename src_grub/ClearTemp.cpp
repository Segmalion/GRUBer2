//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <vector>

#include "ClearTemp.h"
#include "Help.h"
#include "Text.h"
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
struct fille {
	UnicodeString str;
	long long size;
	bool dir;
};
struct patchList {
	std::vector<fille> list;
	int dir = 0;
	int fille = 0;
	long long sumSize = 0;
} patch;
//---------------------------------------------------------------------------
patchList scanDirToFille(UnicodeString dir)
{
	patchList find;
	std::vector<UnicodeString> list(0);
	TSearchRec sr;
	if (dir.Length()) {
		// проверяем на слеш в конце, и если есть - удаляем
		if (dir.LastDelimiter("\\") == dir.Length()) {
			dir = dir.SubString(0, dir.Length() - 1);
		}
		// процедура поиска
		if (!FindFirst(dir + "\\*.*", faAnyFile, sr))
			do {
				if (!(sr.Name == "." || sr.Name == "..")) { // это не трогаем
					if ((sr.Attr & faDirectory) != 0) {
						patchList tmpFind = scanDirToFille(dir + "\\" + sr.Name); //рекурсия
						find.list.insert(find.list.end(), tmpFind.list.begin(), tmpFind.list.end());
						find.dir += tmpFind.dir;
						find.fille += tmpFind.fille;
						find.sumSize += tmpFind.sumSize;
						find.dir++;
						find.list.push_back({dir + "\\" + sr.Name, sr.Size, true});
					}
					if (!((sr.Attr & faDirectory) != 0)) {
						find.fille++;
                        find.sumSize = find.sumSize + sr.Size;
						find.list.push_back({dir + "\\" + sr.Name, sr.Size, false});
					}
				}
			} while (!FindNext(sr)); // ищем пока не найдем все
		FindClose(sr);
	}
	return find;
}
//---------------------------------------------------------------------------
__fastcall TFormClearTempDir::TFormClearTempDir(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TFormClearTempDir::Button_CleanClick(TObject *Sender)
{
	//кнопка очистки
	long long delSize = 0, unDelSize = 0;
	long long delCount = 0, unDelCount = 0;
	//очистка временых папок
	Memo_LOG->Lines->Add("Видалення тимчасових файлів...");
	for(auto i: patch.list) {
		if ((FileGetAttr(i.str) & faDirectory) != 0) {
			FileSetAttr(i.str, faDirectory);
			RemoveDir(i.str);
		} else {
			FileSetAttr(i.str, 0);
			if(DeleteFile(i.str)) {
				delSize += i.size;
				delCount++;
			} else {
				unDelSize += i.size;
				unDelCount++;
			}
        }
	}
	//очистка корзины
    Memo_LOG->Lines->Add("Очищення кошика...");
    SHQUERYRBINFO recInfo;
	recInfo.cbSize = 64;
	SHQueryRecycleBinW(0, &recInfo);
	long long recSize = recInfo.i64Size;
	SHEmptyRecycleBinW(0,0,SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
	delCount += recInfo.i64NumItems;
	delSize += recInfo.i64Size;
	//вывод
	Label5->Caption = delCount;
	Memo_LOG->Lines->Add("==================================");
	Memo_LOG->Lines->Add("Не вдалось видалити " + UnicodeString(unDelCount) + " (" + byteToStr(unDelSize) + ")");
	Memo_LOG->Lines->Add("Видаленно " + UnicodeString(delCount) + " (" + byteToStr(delSize) + ")");
	Memo_LOG->Lines->Add("==================================");
}
//---------------------------------------------------------------------------
void __fastcall TFormClearTempDir::FormShow(TObject *Sender)
{
	patch = {};
    Memo_LOG->Clear();
	Label4->Caption = "-";
	Label5->Caption = "-";
	// --- готовим список пользовательских папок ---
	Memo_LOG->Lines->Add("Знайденні теки користувачів:");
	std::vector<UnicodeString> userListBad {
		"All Users",
		"Default",
		"Default User",
		"Public"
	};
	std::vector<UnicodeString> userDirList;
	UnicodeString dirUser = "C:\\Users";
	TSearchRec srUser;
	if (dirUser.Length()) {
		// проверяем на слеш в конце, и если есть - удаляем
		if (dirUser.LastDelimiter("\\") == dirUser.Length()) {
			dirUser = dirUser.SubString(0, dirUser.Length() - 1);
		}
		// процедура поиска
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
	}
	for (auto a: userDirList) {
		Memo_LOG->Lines->Add("- " + UnicodeString(a));
	}
	// --- готовим список папок ---
	for (auto dir: dirListFull) {
		patchList tmpPatch = scanDirToFille(dir);
		patch.list.insert(patch.list.end(), tmpPatch.list.begin(), tmpPatch.list.end());
		patch.dir += tmpPatch.dir ;
		patch.fille += tmpPatch.fille ;
		patch.sumSize += tmpPatch.sumSize;
	}
	for (auto userDir: userDirList) {
		for (auto dir: dirListUser) {
			patchList tmpPatch = scanDirToFille(userDir + "\\" + dir);
			patch.list.insert(patch.list.end(), tmpPatch.list.begin(), tmpPatch.list.end());
			patch.dir += tmpPatch.dir;
			patch.fille += tmpPatch.fille;
            patch.sumSize += tmpPatch.sumSize;
        }
	}
	Memo_LOG->Lines->Add("==================================");
	Memo_LOG->Lines->Add("Знайденні тимчасові файли - " + UnicodeString(patch.fille));
	Memo_LOG->Lines->Add("Загальний обсяг файлів ---- " + byteToStr(patch.sumSize));
	Memo_LOG->Lines->Add("==================================");
	// --- корзина ---
	SHQUERYRBINFO recInfo;
	recInfo.cbSize = 64;
	SHQueryRecycleBinW(0, &recInfo);
	long long recSize = recInfo.i64Size;
	Memo_LOG->Lines->Add("Файлів в кошику ----------- " + UnicodeString(recInfo.i64NumItems));
	Memo_LOG->Lines->Add("Загальний обсяг файлів ---- " + byteToStr(recSize));
    Memo_LOG->Lines->Add("==================================");
//    Memo_LOG->Lines->Add("Знайденні тимчасові файли:");
	patch.fille = patch.fille + recInfo.i64NumItems;
	Label4->Caption = UnicodeString(patch.fille);
//	for(auto i: patch.list) {
//		if (!i.dir) Memo_LOG->Lines->Add("-> [" + byteToStr(i.size) + "] - " + i.str);
//	}
}
//---------------------------------------------------------------------------

