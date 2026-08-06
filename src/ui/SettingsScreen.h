#pragma once

#include "Renderer.h"
#include "game/GameState.h"
#include "utils/LocalizationManager.h"
#include "utils/SettingsManager.h"
#include <string>
#include <string_view>

class SettingsScreen {
public:
    SettingsScreen() = default;

    GameState handleEvent(const SDL_Event& event, SettingsManager& settings, LocalizationManager& localization) {
        if (event.type != SDL_EVENT_KEY_DOWN) return GameState::Playing;

        SDL_Keycode key = event.key.key;

        if (key == SDLK_ESCAPE) {
            return GameState::Menu;
        }

        if (key == SDLK_LEFT || key == SDLK_RIGHT) {
            int idx = static_cast<int>(m_selectedOption);
            if (key == SDLK_LEFT) {
                idx = (idx - 1 + 3) % 3;
            } else {
                idx = (idx + 1) % 3;
            }
            m_selectedOption = static_cast<Option>(idx);
        }

        if (key == SDLK_1) {
            localization.setLanguage(LocalizationManager::Language::English);
        } else if (key == SDLK_2) {
            localization.setLanguage(LocalizationManager::Language::Hindi);
        }

        if (key == SDLK_UP || key == SDLK_DOWN) {
            if (key == SDLK_UP) {
                m_selectedOption = static_cast<Option>((static_cast<int>(m_selectedOption) - 1 + 3) % 3);
            } else {
                m_selectedOption = static_cast<Option>((static_cast<int>(m_selectedOption) + 1) % 3);
            }
        }

        if (key == SDLK_RETURN) {
            switch (m_selectedOption) {
                case Option::TextSize:
                    settings.setTextSize(SettingsManager::TextSize::Normal);
                    break;
                case Option::ColorBlind:
                    settings.setColorBlindMode(!settings.getColorBlindMode());
                    break;
                case Option::Sound:
                    break;
            }
        }

        return GameState::Playing;
    }

    void draw(const Renderer& renderer, TTF_Font* font, const SettingsManager& settings, const LocalizationManager& localization) {
        renderer.clear(30, 30, 30, 255);

        SDL_Color titleColor{255, 255, 255, 255};
        renderer.drawText(localization.get("settings_title"), 640.0f, 120.0f, titleColor, font);

        SDL_Color langColor{220, 220, 220, 255};
        std::string langText = localization.get("language") + " [1] EN [2] HI";
        renderer.drawText(langText, 640.0f, 220.0f, langColor, font);

        SDL_Color textSizeColor = (m_selectedOption == Option::TextSize) ? SDL_Color{255, 255, 150, 255} : SDL_Color{220, 220, 220, 255};
        std::string textSizeStr = settings.textSizeToString(settings.getTextSize());
        std::string textSizeText = localization.get("text_size") + " " + textSizeStr;
        renderer.drawText(textSizeText, 640.0f, 280.0f, textSizeColor, font);

        SDL_Color cbColor = (m_selectedOption == Option::ColorBlind) ? SDL_Color{255, 255, 150, 255} : SDL_Color{220, 220, 220, 255};
        std::string cbText = localization.get("color_blind") + " " + (settings.getColorBlindMode() ? "ON" : "OFF");
        renderer.drawText(cbText, 640.0f, 340.0f, cbColor, font);

        SDL_Color soundColor = (m_selectedOption == Option::Sound) ? SDL_Color{255, 255, 150, 255} : SDL_Color{220, 220, 220, 255};
        renderer.drawText(localization.get("sound") + " ON", 640.0f, 400.0f, soundColor, font);

        SDL_Color hintColor{120, 120, 120, 255};
        renderer.drawText(localization.get("back"), 640.0f, 500.0f, hintColor, font);
    }

private:
    enum class Option { TextSize, ColorBlind, Sound } m_selectedOption{Option::TextSize};
};
