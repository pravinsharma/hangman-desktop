#pragma once

#include "Renderer.h"
#include "game/GameState.h"
#include "game/WordBank.h"
#include "ui/KeyboardWidget.h"
#include "utils/LocalizationManager.h"
#include "utils/SettingsManager.h"
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

        if (key == SDLK_S) {
            return GameState::Settings;
        }

        if (key == SDLK_ESCAPE) {
            return GameState::Menu;
        }
        selectedDifficulty = m_selectedDifficulty;
        return GameState::Menu;
    }

    void draw(const Renderer& renderer, TTF_Font* font, const LocalizationManager& localization, const SettingsManager& settings) {
        renderer.clear(18, 18, 24, 255);

        float centerX = 640.0f;

        SDL_Color titleColor{230, 240, 255, 255};
        renderer.drawText(localization.get("title"), centerX, 100.0f, titleColor, font);

        SDL_Color subtitleColor{160, 180, 210, 255};
        renderer.drawText(localization.get("select_category"), centerX, 160.0f, subtitleColor, font);

        float cardY = 200.0f;
        float cardH = 36.0f;
        for (size_t i = 0; i < m_categories.size(); ++i) {
            float y = cardY + i * (cardH + 10.0f);
            SDL_Color cardBg{30, 38, 50, 255};
            renderer.drawRoundedRect(centerX - 260.0f, y, 520.0f, cardH, 12.0f, cardBg);

            SDL_Color catColor{220, 230, 255, 255};
            std::string line = std::to_string(i + 1) + ".  " + m_categories[i];
            renderer.drawTextLeft(line, centerX - 220.0f, y + cardH / 2.0f, catColor, font);
        }

        SDL_Color diffColor{255, 235, 150, 255};
        std::string diffText = localization.get("difficulty") + "  " + std::string(to_string(m_selectedDifficulty));
        renderer.drawText(diffText, centerX, 470.0f, diffColor, font);

        SDL_Color dailyColor{150, 235, 180, 255};
        std::string dailyText = localization.get("daily_mode") + "  " + (m_dailyMode ? localization.get("on") : localization.get("off"));
        renderer.drawText(dailyText, centerX, 515.0f, dailyColor, font);

        SDL_Color hintColor{120, 130, 155, 255};
        renderer.drawText(localization.get("select_category_hint"), centerX, 580.0f, hintColor, font);
        renderer.drawText(localization.get("difficulty_hint"), centerX, 615.0f, hintColor, font);
        renderer.drawText("[S] " + localization.get("settings_key"), centerX, 650.0f, hintColor, font);
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
