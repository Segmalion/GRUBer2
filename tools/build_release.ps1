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
$destDir = "D:\UsersFiles\JOB-PROJECTS\TEST\GRUBer-RELEASE\$folderName"
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

Write-Host "DONE: $destDir"
