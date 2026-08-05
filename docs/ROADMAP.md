# Hangman Desktop — Roadmap

> Last updated: 2026-08-05
> Status legend: `[ ]` Planned · `[~]` In Progress · `[x]` Complete

---

## Phase 0 — Scaffold & Foundation
| # | Milestone | Status |
|---|-----------|--------|
| 0.1 | CMake + Ninja + vcpkg build pipeline | `[x]` |
| 0.2 | SDL3, SDL3_ttf, SDL3_image integration | `[x]` |
| 0.3 | 1280×720 window + renderer bootstrap | `[x]` |
| 0.4 | Asset loading (TTF fonts, images/GIFs) | `[x]` |
| 0.5 | Main loop, event polling, cleanup | `[x]` |
| 0.6 | Windows post-build DLL copy & asset staging | `[x]` |

---

## Phase 1 — Core Game Engine
| # | Milestone | Status |
|---|-----------|--------|
| 1.1 | Word/dictionary management (load from file) | `[ ]` |
| 1.2 | Game state machine (Menu, Playing, Won, Lost) | `[ ]` |
| 1.3 | Hangman figure renderer (0–6 wrong guesses) | `[ ]` |
| 1.4 | Word mask & letter reveal logic | `[ ]` |
| 1.5 | Input handling (physical keyboard A–Z) | `[ ]` |
| 1.6 | Guess validation & feedback (correct / wrong / duplicate) | `[ ]` |
| 1.7 | Win/lose condition detection | `[ ]` |

---

## Phase 2 — UI & Rendering
| # | Milestone | Status |
|---|-----------|--------|
| 2.1 | Menu screen (Start Game, Category Select, Quit) | `[ ]` |
| 2.2 | Category-based word lists (Movies, Countries, Tech, etc.) | `[ ]` |
| 2.3 | HUD: remaining lives, current word mask, used letters | `[ ]` |
| 2.4 | Hangman SVG/bitmap assets + animation on wrong guess | `[ ]` |
| 2.5 | Victory / defeat overlay with stats | `[ ]` |
| 2.6 | Responsive layout (centered game area, scaling) | `[ ]` |

---

## Phase 3 — Game Features
| # | Milestone | Status |
|---|-----------|--------|
| 3.1 | Difficulty levels (Easy / Medium / Hard) | `[ ]` |
| 3.2 | Hint system (reveal a random unrevealed letter) | `[ ]` |
| 3.3 | Score tracking & high-score persistence | `[ ]` |
| 3.4 | Sound effects (correct, wrong, win, lose) via SDL3_mixer | `[ ]` |
| 3.5 | Background music toggle | `[ ]` |
| 3.6 | Word-of-the-day / daily challenge mode | `[ ]` |
| 3.7 | Hint cost / penalty balancing | `[ ]` |

---

## Phase 4 — Polish & UX
| # | Milestone | Status |
|---|-----------|--------|
| 4.1 | Animated transitions between screens (fade / slide) | `[ ]` |
| 4.2 | Keyboard key visual feedback (highlight on key press) | `[ ]` |
| 4.3 | Confetti / particle effect on win | `[ ]` |
| 4.4 | Localization support (EN + IN-HI) | `[ ]` |
| 4.5 | Accessibility: color-blind mode, larger text toggle | `[ ]` |
| 4.6 | In-game settings menu (sound, display, language) | `[ ]` |

---

## Phase 5 — Distribution & Deployment
| # | Milestone | Status |
|---|-----------|--------|
| 5.1 | Windows installer (Inno Setup / WiX) | `[ ]` |
| 5.2 | Portable ZIP build (single folder, no installer) | `[ ]` |
| 5.3 | GitHub Actions CI/CD (build + test + release artifact) | `[ ]` |
| 5.4 | Auto-update checker | `[ ]` |
| 5.5 | Cross-compilation support (Linux/macOS via vcpkg) | `[ ]` |

---

## Progress Summary

| Phase | Complete | Total | % |
|-------|----------|-------|---|
| Phase 0 — Scaffold & Foundation | 6 | 6 | 100% |
| Phase 1 — Core Game Engine | 0 | 7 | 0% |
| Phase 2 — UI & Rendering | 0 | 6 | 0% |
| Phase 3 — Game Features | 0 | 7 | 0% |
| Phase 4 — Polish & UX | 0 | 6 | 0% |
| Phase 5 — Distribution & Deployment | 0 | 5 | 0% |
| **Total** | **6** | **37** | **~16%** |
