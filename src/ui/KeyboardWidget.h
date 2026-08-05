#pragma once

#include "Renderer.h"
#include "game/HangmanGame.h"
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <functional>

class KeyboardWidget {
public:
    using GuessCallback = std::function<void(char)>;

    KeyboardWidget(float startX, float startY, float keyWidth, float keyHeight, float spacing)
        : m_startX(startX), m_startY(startY), m_keyWidth(keyWidth), m_keyHeight(keyHeight), m_spacing(spacing) {}

    void handleEvent(const SDL_Event& event, GuessCallback callback) {
        if (event.type != SDL_EVENT_KEY_DOWN) return;

        SDL_Keycode key = event.key.key;
        if (key >= SDLK_A && key <= SDLK_Z) {
            callback(static_cast<char>(key));
        }
    }

    void draw(const Renderer& renderer, TTF_Font* font, const HangmanGame& game) const {
        const char* keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const int cols = 10;

        for (int i = 0; i < 26; ++i) {
            int row = i / cols;
            int col = i % cols;
            float x = m_startX + col * (m_keyWidth + m_spacing);
            float y = m_startY + row * (m_keyHeight + m_spacing);

            char letter = keys[i];
            bool used = game.isLetterUsed(letter);

            SDL_Color bgColor = used ? SDL_Color{80, 80, 80, 255} : SDL_Color{60, 60, 60, 255};
            SDL_Color textColor = used ? SDL_Color{120, 120, 120, 255} : SDL_Color{220, 220, 220, 255};

            renderer.drawRect(x, y, m_keyWidth, m_keyHeight, bgColor);

            std::string letterStr(1, letter);
            renderer.drawText(letterStr, x + m_keyWidth / 2.0f, y + m_keyHeight / 2.0f, textColor, font);
        }
    }

private:
    float m_startX{0.0f};
    float m_startY{0.0f};
    float m_keyWidth{40.0f};
    float m_keyHeight{40.0f};
    float m_spacing{4.0f};
};
