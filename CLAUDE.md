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

- Valid `Platform` values: `Win32`, `Win64`, `Win64x` (default/primary target is `Win64x`).
- Valid `Config` values: `Debug` (`Cfg_1`), `Release` (`Cfg_2`).
- Output goes to `<Platform>\<Config>\` under each project folder (e.g. `src_grub\Win64x\Debug\`).
- There is no automated test suite in this repo — verification is manual (build + run the app).

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

### File encodings are mixed — check before editing
Source files in `src_grub/` are **not** uniformly UTF-8. Several headers/sources (e.g. `Config.h`,
`Users.h`/`.cpp`, `Dir.h`, `GetSMB.h`, `RunApp.h`) are saved in a legacy Windows codepage (Cyrillic
Windows-1251, misreported as "ISO-8859" by `file`), while others (e.g. `MainForm.cpp`) are UTF-8 with a BOM.
Reading a Windows-1251 file as UTF-8 renders its Cyrillic/Ukrainian comments as mojibake — this is a file
encoding issue, not file corruption. Before editing a file with garbled comments, check its actual encoding
and preserve it; don't "fix" mojibake by rewriting comments in UTF-8 unless converting the whole file's
encoding is the intended change.

### Language
UI strings, log messages, and most comments are in Ukrainian (with some Russian in older comments). Keep
new user-facing strings and comments consistent with the existing language per file/area rather than
switching to English.

### Root-level `.patch` files
`thread-safety-fix.patch` and `split-heavy-ui-defection.patch` in the repo root are historical patches that
have already been applied and committed (see commits `67be5bd`/`dc584e6`) — they're kept for reference on
the compute/apply thread-safety rationale, not as pending changes to apply.
