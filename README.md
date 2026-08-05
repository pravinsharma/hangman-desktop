# Hangman Desktop

Minimal C++20 + SDL3 + CMake + vcpkg + Ninja project.

## Documentation

- [Build Instructions](docs/BUILD.md)
- [Architecture](docs/ARCHITECTURE.md)
- [Roadmap](docs/ROADMAP.md)
- [Contributing](docs/CONTRIBUTING.md)

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
./build/hangman
```
