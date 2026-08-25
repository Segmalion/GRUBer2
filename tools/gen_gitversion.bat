@echo off
setlocal enabledelayedexpansion

rem Generates GitVersion.h in the given project directory, embedding the
rem current git commit hash so a built .exe can be traced back to the
rem exact commit it was compiled from. Run as a Pre-Build Event.
rem Usage: gen_gitversion.bat "<project-dir>"

set "PROJDIR=%~1"
if "%PROJDIR%"=="" set "PROJDIR=%~dp0"
set "OUTFILE=%PROJDIR%\GitVersion.h"
set "REPOROOT=%~dp0.."

set "GITHASH=nogit"
set "GITDATE=unknown"
set "GITDIRTY=0"

pushd "%REPOROOT%" 2>nul
if errorlevel 1 goto :write

for /f "delims=" %%H in ('git rev-parse --short HEAD 2^>nul') do set "GITHASH=%%H"
for /f "delims=" %%D in ('git log -1 --format^=%%cI 2^>nul') do set "GITDATE=%%D"
for /f "delims=" %%S in ('git status --porcelain 2^>nul') do set "GITDIRTY=1"

popd

:write
> "%OUTFILE%" (
    echo #pragma once
    echo #define GIT_COMMIT_HASH "%GITHASH%"
    echo #define GIT_COMMIT_DATE "%GITDATE%"
    echo #define GIT_DIRTY %GITDIRTY%
)

exit /b 0
