# Copilot Instructions

## Project overview

Cross-platform modern C++ console app template for new projects, with **minimum standard C++20**, demonstrating colored, UTF-8/emoji-capable logging. It must stay compatible with **Windows, Linux, and macOS**, and must be easy to edit, build, and run from both **Visual Studio 2026** (via its built-in CMake support, see `.vs/`) and **VS Code** (via the CMake Tools extension, see `.vscode/`). Keep changes IDE-agnostic: build logic belongs in `CMakeLists.txt`/`CMakePresets.json`, never in IDE-specific project files.

Dependencies are managed by **vcpkg in manifest mode** (`vcpkg.json`): CLI11, spdlog (pinned to 1.15.3 via `overrides`), and fmt (transitively via spdlog). Build system is CMake (≥ 3.21) + Ninja, driven by presets in `CMakePresets.json`. All presets share one binary dir (`build/`) and use `$env{VCPKG_ROOT}` for the toolchain, so `VCPKG_ROOT` must be set (VS 2026 sets it automatically; otherwise set it to your vcpkg root).

Presets (each gated by a `hostSystemName` condition, so only relevant ones show up per OS):

| Preset | Platform / Compiler |
|---|---|
| `default` | Windows x64, MSVC, `x64-windows-static` triplet, static MSVC runtime |
| `linux-gcc` | Linux, GCC |
| `linux-clang` | Linux, Clang |
| `macos-clang` | macOS, Clang (Apple Silicon and Intel) |

Non-Windows presets intentionally omit `VCPKG_TARGET_TRIPLET` so vcpkg auto-detects it (`x64-linux`, `arm64-osx`, ...). Don't hardcode triplets for them.

## Build commands

On Windows, commands must run in a **Visual Studio Developer environment** (e.g. "Developer PowerShell for VS" or after calling `VsDevCmd.bat`/`vcvars64.bat`). The Windows preset uses `strategy: "external"` for architecture/toolset, so a bare PowerShell fails with `LNK1104: cannot open file 'kernel32.lib'`. Visual Studio 2026 and the VS Code CMake Tools extension set up this environment automatically — on Linux/macOS no special environment is needed.

```powershell
cmake --preset default            # configure (Windows; use linux-gcc / linux-clang / macos-clang elsewhere)
cmake --build build               # build
cmake --install build --prefix dist   # install to dist/bin
```

The executable is `build/HelloWorld.exe` on Windows and `build/HelloWorld` on Linux/macOS (Ninja is single-config — there is no per-config subdirectory). `.vscode/launch.json` reflects this: the "Debug" (MSVC) entry is for Windows, the "Debug (GDB)" entry is for Linux/macOS.

There are no tests, linters, or formatters configured in this repo.

## Conventions and gotchas

- **Keep everything portable**: guard platform-specific code with `#ifdef _WIN32` / `if(MSVC)` (see `setup_terminal_utf8()` and the `/utf-8` flag — both already guarded). Don't add Windows-only APIs outside such guards. Prefer standard C++20 over platform APIs. The code must compile warning-free with MSVC, GCC, and Clang.
- **Do not use `find_package(spdlog)`** — it is broken with CMake 4.x on this setup. `CMakeLists.txt` works around it by linking `spdlog`/`fmt` manually via `target_include_directories`/`target_link_directories` against `build/vcpkg_installed/${VCPKG_TARGET_TRIPLET}` (triplet comes from the preset or vcpkg auto-detection) with generator expressions that select the `d`-suffixed debug libs (`spdlogd`, `fmtd`) in Debug configs — vcpkg uses the same `d` postfix on all platforms, so this is portable. `find_package(CLI11 CONFIG REQUIRED)` is fine. When adding vcpkg packages, prefer `find_package` if it works, otherwise follow the existing manual-link pattern.
- **Adding a new platform/compiler**: add a configure preset inheriting the hidden `base` preset with a `hostSystemName` condition; don't duplicate shared settings or change the common CMake logic.
- **UTF-8/emoji support is deliberate and two-part**: `/utf-8` compile flag for MSVC in `CMakeLists.txt`, plus `setup_terminal_utf8()` in `src/main.cpp` (sets console code pages and enables virtual terminal processing — Windows-only by design; Linux/macOS terminals are UTF-8 natively). Keep both when touching logging or output code.
- **No machine-specific paths**: presets use `$env{VCPKG_ROOT}`; don't hardcode absolute paths (user dirs, tool locations) in `CMakePresets.json`, `.vscode/`, or CMake files.
- Log messages in `src/main.cpp` are in German with emojis — this is intentional demo output.
