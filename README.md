# SDL3 Vanilla Scaffold

Minimal C++17 + SDL3 + CMake + vcpkg + Ninja project.

## Prerequisites

- CMake >= 3.20
- vcpkg with `VCPKG_ROOT` set
- Ninja in PATH

## Build

```bash
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Run

```bash
./build/sdl3-vanilla-scaffold
```
