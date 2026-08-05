# Architecture

## Overview

Hangman Desktop is a native Windows desktop game built with **C++20**, **SDL3**, **SDL3_ttf**, and **SDL3_image**. The build system uses **CMake** (>= 3.20) with the **Ninja** generator, and dependencies are managed via **vcpkg**.

## Tech Stack

| Layer | Technology | Purpose |
|-------|-----------|---------|
| Language | C++20 | Core implementation |
| Windowing & Rendering | SDL3 | Window, renderer, events |
| Font Rendering | SDL3_ttf | Text rendering |
| Image Loading | SDL3_image | Bitmap/GIF asset loading |
| Build System | CMake + Ninja | Build orchestration |
| Package Manager | vcpkg | Dependency resolution |
| CI/CD | GitHub Actions | Automated builds (planned) |

## Directory Layout

```
hangman-desktop/
├── CMakeLists.txt          # Root build configuration
├── src/
│   ├── main.cpp            # Entry point, event loop
│   ├── game/               # Game logic (state machine, rules)
│   ├── ui/                 # Screens, widgets, rendering
│   ├── assets/             # Asset management (fonts, images)
│   └── utils/              # Helpers (file I/O, math, string)
├── assets/
│   ├── images/             # Hangman parts, backgrounds
│   └── fonts/              # TTF font files
├── data/
│   └── words/              # Category word lists (.txt)
├── scripts/
│   ├── build.ps1
│   ├── rebuild.ps1
│   ├── clean.ps1
│   ├── run.ps1
│   └── copy-deps.ps1
├── build/                  # Build output (gitignored)
├── docs/
│   ├── ROADMAP.md
│   ├── ARCHITECTURE.md
│   ├── BUILD.md
│   └── CONTRIBUTING.md
└── README.md
```

## Module Design

### `src/game/` — Game Logic
- `GameState` enum (Menu, Playing, Won, Lost)
- `HangmanGame` class: word selection, mask management, guess evaluation
- `WordBank` class: loads category word lists from `data/words/`
- `ScoreManager` class: reads/writes high scores to disk

### `src/ui/` — UI & Rendering
- `Screen` base class (MenuScreen, GameScreen, ResultScreen)
- `Button`, `Label`, `KeyboardWidget` reusable UI components
- `HangmanRenderer` draws the figure parts based on wrong guess count
- `Renderer` wrapper around SDL3 renderer for convenience

### `src/assets/` — Asset Management
- `AssetManager` loads and caches TTF fonts and images
- Handles animated GIFs via `IMG_LoadAnimation`

### `src/utils/` — Utilities
- `FileUtils`: word list parsing, config reading
- `StringUtils`: case-insensitive string comparison

## Data Flow

```
Main Loop
  ├── Poll Events (SDL_PollEvent)
  │     └── Keyboard input → GameState::handleInput()
  ├── Update (Game logic tick)
  │     └── HangmanGame::evaluateGuess(letter)
  └── Render (SDL_RenderClear → draw UI → SDL_RenderPresent)
```

## Build Targets

| Target | Output | Description |
|--------|--------|-------------|
| `hangman` (current) | `build/` | Minimal SDL3 demo |
| `hangman-desktop` (future) | `build/hangman-desktop.exe` | Full game |

## Platform Notes

- **Primary target**: Windows x64 (vcpkg triplet `x64-windows`)
- **Cross-compilation**: Planned via vcpkg `--triplet` flag for Linux/macOS
- **Runtime dependencies**: SDL3, SDL3_ttf, SDL3_image DLLs copied by `copy-deps.ps1`

## Coding Conventions

- C++20 features preferred (`std::format`, `std::span`, `concepts`, `std::ranges`, `std::jthread`, structured bindings)
- No raw pointers where `std::unique_ptr` / `std::shared_ptr` suffice
- SDL3 resources wrapped in RAII helpers where possible
- Constants in `constexpr` or `inline const`
- Header-only utilities in `utils/`, classes with `.h`/`.cpp` pairs in `game/` and `ui/`
