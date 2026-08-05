# Contributing

## Getting Started

1. Clone the repo
2. Install prerequisites per `docs/BUILD.md`
3. Run `.\scripts\build.ps1` to verify setup

## Development Workflow

1. Create a feature branch from `main`
2. Make changes following the coding conventions
3. Build and test locally: `.\scripts\run.ps1`
4. Commit with a descriptive message
5. Open a Pull Request

## Coding Standards

- **Standard**: C++20
- **Formatting**: Use `clang-format` with the project's `.clang-format` (if present)
- **Naming**: `PascalCase` types, `camelCase` functions/variables, `kConstantCase` constants
- **Headers**: One class per `.h`/`.cpp` pair; include guards or `#pragma once`
- **Memory**: Prefer RAII; avoid raw `new`/`delete`
- **SDL**: Wrap SDL resources in smart pointers or custom deleters

## Module Organization

- `src/game/` — Game rules, state, scoring
- `src/ui/` — Screens, widgets, rendering
- `src/assets/` — Font/image loading
- `src/utils/` — Generic helpers

## Submitting Changes

- Keep PRs focused on a single milestone from `ROADMAP.md`
- Update `docs/ROADMAP.md` if the PR advances a milestone
- Add new word categories to `data/words/` if applicable
- Do not commit build artifacts or `assets/` copies

## Reporting Issues

- Use the GitHub issue tracker
- Include: OS, build config, steps to reproduce, expected vs actual behavior
