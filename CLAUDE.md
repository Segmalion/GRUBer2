# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

GRUBer2 is a Windows desktop toolkit for IT technicians who service/audit workstations ("ARM" — Ukrainian
"автоматизоване робоче місце") in an organization. It is built with **Embarcadero C++Builder / RAD Studio**
(VCL, not a cross-platform framework). The repo is a groupproj with two independent applications:

- `src_grub/` — **GRUBer** (`GRUBer.cbproj`), the main app. For a given PC it:
  - collects hardware/system info (SMBIOS via `GetSMB`, serials, users, installed software),
  - generates a documentation bundle ("грабу"/"grub" folder) of `.txt` files via the `job_*` functions
    (`job_infoFille`, `job_softFille`, `job_usb`, `job_net1/2`, `job_license`, `job_audit`, `job_esetLog`, ...),
  - checks policy compliance / "порушення" (violations): blacklisted software, extra admin accounts,
    ESET antivirus quarantine contents — see `computeSoftDefection`/`computeUsersDefection`/`computeEsetDefection`,
  - manages local ESET mirror updates, runs helper utilities (HWiNFO, CPU-Z, Process Explorer, etc.) via `RunApp`.
- `src_devLister/` — **DeviceLister** (`DeviceLister.cbproj`), a companion app that enumerates USB/PnP
  devices (`cfgmgr32`/SetupAPI), tracks device history in a local SQLite DB (FireDAC), and flags
  unknown/unregistered devices per PC category.

Both apps are launched from/at each other (GRUBer has a button to open DeviceLister) but build and ship as
separate `.exe`s.

## Build

This is a RAD Studio project — there is no cross-platform CLI toolchain; build with `msbuild` from a RAD
Studio developer command prompt (after running `rsvars.bat`), or open `GRUBer2.groupproj` in the IDE.

```
# from a RAD Studio command prompt (rsvars.bat loaded)
msbuild GRUBer2.groupproj /t:Build /p:Config=Debug   /p:Platform=Win64x
msbuild GRUBer2.groupproj /t:Build /p:Config=Release  /p:Platform=Win64x

# build just one sub-app
msbuild src_grub\GRUBer.cbproj /t:Build /p:Config=Debug /p:Platform=Win64x
msbuild src_devLister\DeviceLister.cbproj /t:Build /p:Config=Debug /p:Platform=Win64x
```

- Both apps target **Win64x only** — Win32/Win64(classic) support was dropped (`TargetedPlatforms` in both
  `.cbproj` files reflects this); always pass `/p:Platform=Win64x`. Leftover `Base_Win32`/`Cfg_1_Win32`/
  `Cfg_2_Win32` (and classic `Win64`) `PropertyGroup`s may still exist in the `.cbproj` XML as inert IDE
  cruft — that's normal RAD Studio behavior when a platform is unchecked in Project Options, not a sign that
  Win32/Win64 is still a supported target.
- Valid `Config` values: `Debug` (`Cfg_1`), `Release` (`Cfg_2`).
- Output goes to `Win64x\<Config>\` under each project folder (e.g. `src_grub\Win64x\Debug\`).
- There is no automated test suite in this repo — verification is manual (build + run the app).

### Versioning — commit-traceable version string
The `Major.Minor.Release.Build` version baked into `VerInfo_*`/`VerInfo_Keys` in each `.cbproj` (e.g.
`0.3.5.2`) is still bumped by hand per patch — it only conveys release intent, not an exact build.
To make the version shown to the user traceable to the exact git commit it was built from, both
`.cbproj` files run **`tools\gen_gitversion.bat`** as a `PreBuildEvent` (fires on every IDE/`msbuild`
build). It shells out to `git rev-parse --short HEAD` / `git status --porcelain` and writes a
`GitVersion.h` into the project directory (`src_grub\GitVersion.h`, `src_devLister\GitVersion.h`)
defining `GIT_COMMIT_HASH`, `GIT_COMMIT_DATE`, `GIT_DIRTY`. `GetFullAppVersion()`
(`src_grub/Help.cpp`, duplicated in `src_devLister/MainDevLister.cpp` alongside the existing
`GetAppVersion()` duplication) combines the two into what's actually shown in About/status
bar/log: `0.3.5.2 (3a1f9c2)`, or `0.3.5.2 (3a1f9c2-dirty)` if there were uncommitted changes at
build time. `GitVersion.h` is **generated, gitignored, and never hand-edited or committed** — if
git isn't found on the build machine the script falls back to placeholder values instead of
failing the build.

## Architecture notes

### VCL forms + global singletons
Each `.h`/`.cpp`/`.dfm` triple is a VCL form or data module designed in the IDE (don't hand-edit `.dfm`
component layouts unless necessary — they're IDE-generated resource scripts). Business/domain state lives in
plain C++ classes instantiated as globals and referenced across files via `extern`, notably:

- `Arm` (`Arm.h`/`.cpp`) — all data about the current PC/ARM (manual info, license, serials, installed
  software, users, USB/ESET/network history), persisted to `C:\ProgramData\GRUBer\gruber_info.ini`.
- `Config` (`Config.h`/`.cpp`) — app settings (checkboxes/toggles, partitions, LGPO lists, blacklists),
  persisted to its own ini file.
- Instances such as `curPC`, `curConfig`, `curDefection` are referenced from many files as globals — grep
  for the declaration (usually in `MainForm.cpp`) before assuming a type's shape.

### Background thread / VCL thread-safety pattern
`Th_Gruber` (`Th_Gruber.h`/`.cpp`) is a `TThread` that runs the whole grab job sequence (`job_*` calls) off
the main/UI thread. **VCL controls must only be touched from the main thread.** The established pattern
(see `thread-safety-fix.patch` and `split-heavy-ui-defection.patch` for the reasoning) is to split any
function that both does disk/data work and updates the form into two halves:

- a **"heavy" `compute*`** function — no VCL access, safe to call from `Th_Gruber` directly (e.g.
  `computeSoftDefection`, `computeUsersDefection`, `computeEsetDefection`, `computeDefection`),
- a **"light" `apply*`** function — only touches `Form1` controls, must run on the main thread via
  `TThread::Synchronize` (e.g. `applySoftDefection`, `applyUsersDefection`, `applyEsetDefection`,
  `applyDefectionLabels`).

Old combined entry points (`showSoft`, `showUsers`, `checkEsetQuarantine`, `checkDefection`) are kept as thin
`compute + apply` wrappers for call sites that are already on the main thread (form constructor, button
handlers) — don't remove them. `printLog`/`printLogDebug`/`jobDone`/`progressBarGo`/`blockGrub` follow the
same rule: they check `GetCurrentThreadId() == MainThreadID` and wrap in `Synchronize` when called off the
main thread. When adding new code that runs inside `Th_Gruber::Execute()` or is called from it, follow this
same split rather than touching `Form1->*` directly from the background thread.

### File encoding — UTF-8 only
All `.cpp`/`.h` source files in both `src_grub/` and `src_devLister/` are UTF-8 (verified 2026-08-20 — every
non-ASCII file decodes as strict UTF-8; an earlier note here about mixed Windows-1251/UTF-8 files no longer
reflects reality and was corrected). Most files carry no BOM, which the Clang-based `bcc64x` toolchain this
project builds with handles fine — don't add one just for consistency. Keep it that way going forward: save
new files as UTF-8, and if a file you're editing was ever saved in another codepage (e.g. pasted from a
Windows-1251 source), re-save it as UTF-8 rather than leaving mixed encodings in the repo. `.dfm` files are
exempt from this concern — Delphi/C++Builder escapes non-ASCII caption text as `#NNNN` decimal Unicode
codepoints in the text format, so they carry no raw non-ASCII bytes regardless of file encoding.

### Cyrillic string literals must be wide (`L"..."`)
Any Cyrillic/Ukrainian string literal in `.cpp`/`.h` code (both `src_grub/` and `src_devLister/`) **must**
use a wide prefix — `L"текст"` (or `u"текст"`, matching the handful of pre-existing spots that use it, e.g.
some `Caption` assignments in `MainForm.cpp`) — **never** a plain narrow `"текст"` literal. A narrow literal
assigned to `UnicodeString` gets implicitly converted through an 8-bit `AnsiString` using the OS's "language
for non-Unicode programs" codepage (`CP_ACP`), resolved at **runtime**, not by the source file's UTF-8
encoding. On a Ukrainian/Russian-locale Windows machine `CP_ACP` happens to decode the bytes correctly; on
an English-locale machine it doesn't, and the text renders as mojibake (e.g. "Без відділу" → "Áåç
â³ää³ëó"). `.dfm`-sourced captions are immune (pre-compiled UTF-16 resources), which is why only
code-constructed strings (dialog text, log messages, `Items->Add(...)`, default field values, `Format(...)`
arguments) are at risk. This bit ~300 narrow literals across `src_grub` and ~33 across `src_devLister`
(fixed in bulk — see git history around 2026-09-11); neither project has any legitimate reason to hold
Cyrillic text in `AnsiString`/`UTF8String`/raw `char*`, so a new narrow Cyrillic literal found in review is
almost certainly this bug, not an intentional byte-oriented use.

### Language
UI strings, log messages, and most comments are in Ukrainian (with some Russian in older comments). Keep
new user-facing strings and comments consistent with the existing language per file/area rather than
switching to English.

### Root-level `.patch` files
`thread-safety-fix.patch` and `split-heavy-ui-defection.patch` in the repo root are historical patches that
have already been applied and committed (see commits `67be5bd`/`dc584e6`) — they're kept for reference on
the compute/apply thread-safety rationale, not as pending changes to apply.
