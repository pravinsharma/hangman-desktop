#pragma once

#include "Renderer.h"
#include "game/GameState.h"
#include "game/HangmanGame.h"
#include "game/WordBank.h"
#include "ui/KeyboardWidget.h"
#include <string>
#include <string_view>
#include <vector>
#include <memory>

class MenuScreen {
public:
    MenuScreen() = default;

    GameState handleEvent(const SDL_Event& event, std::string& selectedCategory) const {
        if (event.type != SDL_EVENT_KEY_DOWN) return GameState::Menu;

        SDL_Keycode key = event.key.key;
        if (key >= SDLK_1 && key <= SDLK_9) {
            int idx = static_cast<int>(key - SDLK_1);
            if (idx < static_cast<int>(m_categories.size())) {
                selectedCategory = m_categories[idx];
                return GameState::Playing;
            }
        }
        if (key == SDLK_ESCAPE) {
            return GameState::Menu;
        }
        return GameState::Menu;
    }

    void draw(const Renderer& renderer, TTF_Font* font) const {
        renderer.clear(30, 30, 30, 255);

        SDL_Color titleColor{255, 255, 255, 255};
        renderer.drawText("HANGMAN", 640.0f, 150.0f, titleColor, font);

        SDL_Color subtitleColor{180, 180, 180, 255};
        renderer.drawText("Select a category:", 640.0f, 220.0f, subtitleColor, font);

        for (size_t i = 0; i < m_categories.size(); ++i) {
            SDL_Color catColor{220, 220, 220, 255};
            std::string line = std::to_string(i + 1) + ". " + m_categories[i];
            float y = 300.0f + i * 50.0f;
            renderer.drawText(line, 640.0f, y, catColor, font);
        }

        SDL_Color hintColor{120, 120, 120, 255};
        renderer.drawText("Press 1-9 to select, ESC to quit", 640.0f, 650.0f, hintColor, font);
    }

    void setCategories(const std::vector<std::string>& cats) {
        m_categories = cats;
    }

private:
    std::vector<std::string> m_categories;
};
