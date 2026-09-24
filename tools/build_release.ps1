param(
    [ValidateSet("Debug","Release")][string]$Config = "Release",
    [switch]$Publish,
    [string]$Notes = ""
)
$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot
Set-Location $repoRoot

$rsvars = "C:\Program Files (x86)\Embarcadero\Studio\37.0\bin\rsvars.bat"
if (-not (Test-Path $rsvars)) { throw "rsvars.bat not found: $rsvars" }

Write-Host "Building GRUBer2.groupproj ($Config/Win64x)..."
cmd.exe /c "call `"$rsvars`" && msbuild GRUBer2.groupproj /t:Build /p:Config=$Config /p:Platform=Win64x"
if ($LASTEXITCODE -ne 0) { throw "msbuild failed with exit code $LASTEXITCODE" }

$gruberExe = Join-Path $repoRoot "src_grub\Win64x\$Config\GRUBer.exe"
$dlExe     = Join-Path $repoRoot "src_devLister\Win64x\$Config\DeviceLister.exe"
if (-not (Test-Path $gruberExe)) { throw "Not found: $gruberExe" }
if (-not (Test-Path $dlExe))     { throw "Not found: $dlExe" }

$gruberVer = (Get-Item $gruberExe).VersionInfo.FileVersion.Trim()
$dlVer     = (Get-Item $dlExe).VersionInfo.FileVersion.Trim()
$commit    = (git rev-parse --short HEAD).Trim()

$folderName = "[GRUBer_$gruberVer][DL_$dlVer][$commit]"
$releaseRoot = "D:\UsersFiles\JOB-PROJECTS\TEST\GRUBer-RELEASE"
$destDir = Join-Path $releaseRoot $folderName
New-Item -ItemType Directory -Force -Path $destDir | Out-Null

Copy-Item $gruberExe -Destination $destDir -Force
Copy-Item $dlExe -Destination $destDir -Force

$signtool = "C:\Program Files (x86)\Microsoft SDKs\ClickOnce\SignTool\signtool.exe"
$sha1 = "B4D511E8418E0957521FE045EAAB39BA72B70F18"
$signedExes = @((Join-Path $destDir "GRUBer.exe"), (Join-Path $destDir "DeviceLister.exe"))
foreach ($exe in $signedExes) {
    Write-Host "Signing $exe ..."
    & $signtool sign /sha1 $sha1 /fd sha256 /tr http://timestamp.digicert.com /td sha256 $exe
    if ($LASTEXITCODE -ne 0) { throw "signtool failed for $exe" }
}

$sevenZip = "C:\Program Files\7-Zip-Zstandard\7z.exe"
if (-not (Test-Path $sevenZip)) { throw "7z.exe not found: $sevenZip" }

$archivePath = Join-Path $releaseRoot "$folderName.7z"
if (Test-Path -LiteralPath $archivePath) { Remove-Item -LiteralPath $archivePath -Force }

Write-Host "Archiving to $archivePath ..."
& $sevenZip a -mx=9 $archivePath (Join-Path $destDir "*")
if ($LASTEXITCODE -ne 0) { throw "7z failed with exit code $LASTEXITCODE" }

# Публікація в GitHub Releases (Segmalion/GRUBer2, приватний репозиторій) -
# лише за явним -Publish, щоб локальна збірка без публікації лишалась
# можливою. tag_name = короткий commit hash - той самий рядок, що GRUBer.exe
# зчитує як GIT_COMMIT_HASH (tools\gen_gitversion.bat) - так перевірка
# оновлень у програмі порівнює свою версію з тегом релізу без окремого
# маніфесту. Токен тут - ОКРЕМИЙ, write-scoped, живе лише на цій машині
# розробника (env:GRUBER_RELEASE_TOKEN) - це НЕ той read-only токен, що
# зашивається у GRUBer.exe для читання релізів (UpdateSecrets.h).
if ($Publish) {
    $ghRepo = "Segmalion/GRUBer2"
    $commitFull = (git rev-parse HEAD).Trim()
    $releaseTitle = "GRUBer $gruberVer / DeviceLister $dlVer ($commit)"
    # текст, що GRUBer.exe покаже в діалозі "Доступне оновлення" (rel.body,
    # див. Th_UpdateCheck.cpp) - якщо викликач не передав -Notes, підставляємо
    # releaseTitle замість нього (той самий текст, що й раніше), а не порожній
    # рядок - через PowerShell 5.1 баг з елізією порожньоряткових аргументів
    # при виклику зовнішніх .exe (див. коментар нижче про --notes "").
    $releaseNotes = if ($Notes -and $Notes.Trim()) { $Notes } else { $releaseTitle }
    # лише два exe - без .7z. Автооновлення (Update_FindAsset у src_grub/UpdateCheck.cpp)
    # шукає ассети саме за іменами "GRUBer.exe"/"DeviceLister.exe"; архів там не потрібен,
    # а зайвий великий ассет лише сповільнював би перевірку/публікацію.
    $assets = @(
        (Join-Path $destDir "GRUBer.exe"),
        (Join-Path $destDir "DeviceLister.exe")
    )

    Write-Host "Publishing GitHub Release $commit ..."
    $ghCli = Get-Command gh -ErrorAction SilentlyContinue
    if ($ghCli) {
        if (-not $env:GRUBER_RELEASE_TOKEN) { throw "GRUBER_RELEASE_TOKEN not set - cannot publish (-Publish)" }
        # gh сам підхопить GH_TOKEN з середовища
        $env:GH_TOKEN = $env:GRUBER_RELEASE_TOKEN
        # gh release create сам виконує glob-розбір шляхів ассетів (Go filepath.Glob) -
        # квадратні дужки у назві $destDir ("[GRUBer_...][...]") трактуються як
        # символьний клас glob-патерну і не знаходять жодного співпадіння
        # ("no matches found for ..."). Тому копіюємо обидва підписаних exe у
        # тимчасову теку БЕЗ дужок у шляху і публікуємо звідти.
        $ghStageDir = Join-Path $env:TEMP "GRUBerReleaseAssets"
        Remove-Item -LiteralPath $ghStageDir -Recurse -Force -ErrorAction SilentlyContinue
        New-Item -ItemType Directory -Force -Path $ghStageDir | Out-Null
        $ghAssets = $assets | ForEach-Object {
            $dst = Join-Path $ghStageDir (Split-Path -Leaf $_)
            Copy-Item -LiteralPath $_ -Destination $dst -Force
            $dst
        }
        # УВАГА: --notes "<рядок>" напряму НЕ можна - Windows PowerShell 5.1
        # ламає реконструкцію argv для зовнішніх .exe у двох випадках: (1)
        # порожній рядок губиться, зсуваючи решту аргументів і "з'їдаючи"
        # шлях до GRUBer.exe як текст notes (лишаючи в релізі лише
        # DeviceLister.exe); (2) будь-яка "лапка всередині значення обрізає
        # решту рядка (перевірено на реальному релізі - body обірвався на
        # першій вбудованій "). Тому текст пишемо у файл і передаємо
        # --notes-file - це єдиний спосіб, не залежний від argv-квотування.
        $notesFile = Join-Path $ghStageDir "notes.txt"
        # UTF-8 без BOM: [Text.Encoding]::UTF8 пише BOM, і gh передає його в
        # body релізу як є - зайвий символ на початку "Що нового" в GRUBer.exe.
        [System.IO.File]::WriteAllText($notesFile, $releaseNotes, (New-Object System.Text.UTF8Encoding $false))
        & gh release create $commit --repo $ghRepo --title $releaseTitle --notes-file $notesFile @ghAssets
        $ghExit = $LASTEXITCODE
        Remove-Item -LiteralPath $ghStageDir -Recurse -Force -ErrorAction SilentlyContinue
        if ($ghExit -ne 0) { throw "gh release create failed with exit code $ghExit" }
        $releaseUrl = "https://github.com/$ghRepo/releases/tag/$commit"
    } else {
        $token = $env:GRUBER_RELEASE_TOKEN
        if (-not $token) { throw "GRUBER_RELEASE_TOKEN not set - cannot publish (-Publish)" }
        $headers = @{
            Authorization          = "Bearer $token"
            Accept                 = "application/vnd.github+json"
            "X-GitHub-Api-Version" = "2022-11-28"
            "User-Agent"           = "GRUBer-release-script"
        }
        $body = @{
            tag_name         = $commit
            target_commitish = $commitFull
            name             = $releaseTitle
            body             = $releaseNotes
            draft            = $false
            prerelease       = $false
        } | ConvertTo-Json
        # PowerShell 5.1 кодує рядковий -Body як ISO-8859-1 - кирилиця в notes
        # перетворилась би на "?". Передаємо байти UTF-8 (без BOM) явно.
        $bodyBytes = (New-Object System.Text.UTF8Encoding $false).GetBytes($body)
        $release = Invoke-RestMethod -Method Post `
            -Uri "https://api.github.com/repos/$ghRepo/releases" `
            -Headers $headers -Body $bodyBytes -ContentType "application/json; charset=utf-8"

        foreach ($asset in $assets) {
            $name = [System.IO.Path]::GetFileName($asset)
            Write-Host "Uploading asset $name ..."
            # УВАГА: хост завантаження ассетів - uploads.github.com, НЕ api.github.com
            Invoke-RestMethod -Method Post `
                -Uri "https://uploads.github.com/repos/$ghRepo/releases/$($release.id)/assets?name=$name" `
                -Headers $headers -ContentType "application/octet-stream" -InFile $asset | Out-Null
        }
        $releaseUrl = $release.html_url
    }
    Write-Host "Published: $releaseUrl"
}

# Build+sign+archive all succeeded at this point - safe to retire the previous release.
$oldVersionDir = Join-Path $releaseRoot "OLD_VERSION"
New-Item -ItemType Directory -Force -Path $oldVersionDir | Out-Null

Get-ChildItem -Path $releaseRoot -Directory | Where-Object {
    $_.FullName -ne $destDir -and $_.Name.StartsWith("[GRUBer_")
} | ForEach-Object {
    Write-Host "Removing previous release folder: $($_.FullName)"
    Remove-Item -LiteralPath $_.FullName -Recurse -Force
}

Get-ChildItem -Path $releaseRoot -File | Where-Object {
    $_.Extension -eq ".7z" -and $_.FullName -ne $archivePath -and $_.Name.StartsWith("[GRUBer_")
} | ForEach-Object {
    Write-Host "Moving previous archive to OLD_VERSION: $($_.Name)"
    Move-Item -LiteralPath $_.FullName -Destination $oldVersionDir -Force
}

Write-Host "DONE: $destDir"
Write-Host "Archive: $archivePath"
if ($Publish) { Write-Host "Release: $releaseUrl" }
