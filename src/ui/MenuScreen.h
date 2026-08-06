#pragma once

#include "Renderer.h"
#include "game/GameState.h"
#include "game/HangmanGame.h"
#include "game/WordBank.h"
#include "ui/KeyboardWidget.h"
#include "game/Difficulty.h"
#include <string>
#include <string_view>
#include <vector>
#include <memory>

class MenuScreen {
public:
    MenuScreen() = default;

    GameState handleEvent(const SDL_Event& event, std::string& selectedCategory, Difficulty& selectedDifficulty) {
        if (event.type != SDL_EVENT_KEY_DOWN) return GameState::Menu;

        SDL_Keycode key = event.key.key;

        if (key >= SDLK_1 && key <= SDLK_9) {
            int idx = static_cast<int>(key - SDLK_1);
            if (idx < static_cast<int>(m_categories.size())) {
                selectedCategory = m_categories[idx];
                return GameState::Playing;
            }
        }

        if (key == SDLK_LEFT || key == SDLK_RIGHT) {
            if (key == SDLK_LEFT) {
                int idx = static_cast<int>(m_selectedDifficulty);
                idx = (idx - 1 + 3) % 3;
                m_selectedDifficulty = static_cast<Difficulty>(idx);
            } else {
                int idx = static_cast<int>(m_selectedDifficulty);
                idx = (idx + 1) % 3;
                m_selectedDifficulty = static_cast<Difficulty>(idx);
            }
        }

        if (key == SDLK_D) {
            m_dailyMode = !m_dailyMode;
        }

        if (key == SDLK_ESCAPE) {
            return GameState::Menu;
        }
        selectedDifficulty = m_selectedDifficulty;
        return GameState::Menu;
    }

    void draw(const Renderer& renderer, TTF_Font* font) const {
        renderer.clear(30, 30, 30, 255);

        SDL_Color titleColor{255, 255, 255, 255};
        renderer.drawText("HANGMAN", 640.0f, 120.0f, titleColor, font);

        SDL_Color subtitleColor{180, 180, 180, 255};
        renderer.drawText("Select a category:", 640.0f, 190.0f, subtitleColor, font);

        for (size_t i = 0; i < m_categories.size(); ++i) {
            SDL_Color catColor{220, 220, 220, 255};
            std::string line = std::to_string(i + 1) + ". " + m_categories[i];
            float y = 250.0f + i * 50.0f;
            renderer.drawText(line, 640.0f, y, catColor, font);
        }

        SDL_Color diffColor{255, 255, 150, 255};
        std::string diffText = std::string("Difficulty: ") + std::string(to_string(m_selectedDifficulty));
        renderer.drawText(diffText, 640.0f, 480.0f, diffColor, font);

        SDL_Color dailyColor{150, 255, 150, 255};
        std::string dailyText = std::string("Daily Mode: ") + (m_dailyMode ? "ON" : "OFF");
        renderer.drawText(dailyText, 640.0f, 530.0f, dailyColor, font);

        SDL_Color hintColor{120, 120, 120, 255};
        renderer.drawText("Press 1-9 to select category", 640.0f, 600.0f, hintColor, font);
        renderer.drawText("LEFT/RIGHT to change difficulty | D to toggle daily mode", 640.0f, 640.0f, hintColor, font);
    }

    void setCategories(const std::vector<std::string>& cats) {
        m_categories = cats;
    }

    Difficulty getSelectedDifficulty() const { return m_selectedDifficulty; }
    bool isDailyMode() const { return m_dailyMode; }

private:
    std::vector<std::string> m_categories;
    Difficulty m_selectedDifficulty{Difficulty::Medium};
    bool m_dailyMode{false};
};
