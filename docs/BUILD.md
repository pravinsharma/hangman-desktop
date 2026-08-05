# Build Instructions

## Prerequisites

- **CMake** >= 3.20
- **vcpkg** installed with `VCPKG_ROOT` environment variable set
- **Ninja** in PATH (or use `-G "Visual Studio 17 2022"` for MSVC)
- **PowerShell 7+** (for convenience scripts in `scripts/`)

## Install Dependencies (one-time)

```powershell
vcpkg install sdl3:x64-windows sdl3-ttf:x64-windows sdl3-image:x64-windows
```

## Configure

```powershell
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
```

## Build

```powershell
cmake --build build
```

## Run

```powershell
.\build\hangman.exe
```

Or use the provided PowerShell scripts:

```powershell
.\scripts\build.ps1      # configure + build
.\scripts\rebuild.ps1    # clean + build
.\scripts\clean.ps1      # remove build/
.\scripts\run.ps1        # run built binary
```

## Cross-Platform Builds

### Linux

```bash
vcpkg install sdl3 sdl3-ttf sdl3-image
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

### macOS

```bash
vcpkg install sdl3 sdl3-ttf sdl3-image
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Troubleshooting

| Issue | Fix |
|-------|-----|
| `SDL3 not found` | Verify `VCPKG_ROOT` is set and `sdl3` is installed |
| `Ninja not found` | Install Ninja (`choco install ninja` or `scoop install ninja`) |
| `DLL missing at runtime` | Run `.\scripts\copy-deps.ps1` or build in Release mode |
| `CMake version too old` | Upgrade CMake to >= 3.20 |
