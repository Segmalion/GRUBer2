//---------------------------------------------------------------------------

#ifndef UpdateCheckH
#define UpdateCheckH

#include <atomic>
#include <vector>
#include <filesystem>

#include "EsetDownload.h" // перевикористовуємо typedef EsetDlProgressCb + fs alias

//---------------------------------------------------------------------------
// один ассет релізу на GitHub (напр. "GRUBer.exe")
struct UpdateAsset {
	UnicodeString name;
	__int64 id = 0;   // /repos/.../releases/assets/<id>
	__int64 size = 0;
};
// метадані останнього релізу /repos/Segmalion/GRUBer2/releases/latest
struct UpdateRelease {
	bool valid = false;
	UnicodeString tagName;     // короткий git-хеш комміту (== GIT_COMMIT_HASH при збігу версій)
	UnicodeString name;
	UnicodeString body;
	UnicodeString publishedAt; // ISO-8601
	std::vector<UpdateAsset> assets;
};

// GET /repos/Segmalion/GRUBer2/releases/latest (Authorization: Bearer <PAT>).
// false як "помилки немає, оновлень просто немає" (404, порожній токен) -
// відрізнити від справжньої мережевої помилки можна по errMsg.IsEmpty().
bool Update_FetchLatestRelease(UpdateRelease &out, UnicodeString &errMsg);

// tagName релізу відрізняється від поточного GIT_COMMIT_HASH і не дорівнює
// раніше відхиленому skipTag
bool Update_IsNewer(const UpdateRelease &rel, UnicodeString skipTag);

// пошук ассету за точним іменем файлу (напр. "DeviceLister.exe")
bool Update_FindAsset(const UpdateRelease &rel, UnicodeString assetName, UpdateAsset &out);

// GET /repos/Segmalion/GRUBer2/releases/assets/<id>, Accept: application/octet-stream.
// ВАЖЛИВО: сам обробляє редирект на підписаний blob-URL (Azure/S3) БЕЗ
// пересилання туди заголовку Authorization - див. коментар у .cpp.
bool Update_DownloadAsset(const UpdateAsset &asset, const fs::path &destPath, short updateMs,
	std::atomic<bool> &cancelFlag, EsetDlProgressCb progressCb, UnicodeString &errMsg);

#endif
