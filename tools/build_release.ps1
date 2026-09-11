param(
    [ValidateSet("Debug","Release")][string]$Config = "Release"
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
if (Test-Path $archivePath) { Remove-Item $archivePath -Force }

Write-Host "Archiving to $archivePath ..."
& $sevenZip a -mx=9 $archivePath (Join-Path $destDir "*")
if ($LASTEXITCODE -ne 0) { throw "7z failed with exit code $LASTEXITCODE" }

# Build+sign+archive all succeeded at this point - safe to retire the previous release.
$oldVersionDir = Join-Path $releaseRoot "OLD_VERSION"
New-Item -ItemType Directory -Force -Path $oldVersionDir | Out-Null

Get-ChildItem -Path $releaseRoot -Directory | Where-Object {
    $_.FullName -ne $destDir -and $_.Name.StartsWith("[GRUBer_")
} | ForEach-Object {
    Write-Host "Removing previous release folder: $($_.FullName)"
    Remove-Item $_.FullName -Recurse -Force
}

Get-ChildItem -Path $releaseRoot -File | Where-Object {
    $_.Extension -eq ".7z" -and $_.FullName -ne $archivePath -and $_.Name.StartsWith("[GRUBer_")
} | ForEach-Object {
    Write-Host "Moving previous archive to OLD_VERSION: $($_.Name)"
    Move-Item $_.FullName -Destination $oldVersionDir -Force
}

Write-Host "DONE: $destDir"
Write-Host "Archive: $archivePath"
