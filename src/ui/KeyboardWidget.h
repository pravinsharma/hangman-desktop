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
            char letter = static_cast<char>(std::toupper(key - SDLK_A + 'A'));
            int idx = letter - 'A';
            m_flashTimer[idx] = 0.25f;
            callback(letter);
        }
    }

    void update(float dt) {
        for (float& timer : m_flashTimer) {
            if (timer > 0.0f) {
                timer -= dt;
                if (timer < 0.0f) timer = 0.0f;
            }
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
            bool flashing = m_flashTimer[i] > 0.0f;

            SDL_Color bgColor = used ? SDL_Color{35, 42, 58, 255} : SDL_Color{45, 55, 75, 255};
            SDL_Color borderColor = used ? SDL_Color{55, 65, 85, 255} : SDL_Color{65, 80, 110, 255};
            SDL_Color textColor = used ? SDL_Color{90, 105, 130, 255} : SDL_Color{220, 230, 255, 255};

            if (flashing && !used) {
                float flash = m_flashTimer[i] / 0.25f;
                bgColor.r = static_cast<Uint8>(45 + 180 * flash);
                bgColor.g = static_cast<Uint8>(55 + 200 * flash);
                bgColor.b = static_cast<Uint8>(75 + 220 * flash);
                borderColor = SDL_Color{100, 160, 255, 255};
                textColor = SDL_Color{255, 255, 255, 255};
            }

            renderer.drawRoundedRect(x, y, m_keyWidth, m_keyHeight, 8.0f, bgColor);

            SDL_Color borderTopLeft{80, 100, 140, 255};
            SDL_Color borderBottomRight{25, 32, 45, 255};
            renderer.drawLine(x + 2.0f, y + m_keyHeight - 2.0f, x + m_keyWidth - 2.0f, y + m_keyHeight - 2.0f, borderBottomRight);
            renderer.drawLine(x + m_keyWidth - 2.0f, y + 2.0f, x + m_keyWidth - 2.0f, y + m_keyHeight - 2.0f, borderBottomRight);
            renderer.drawLine(x + 2.0f, y + 2.0f, x + m_keyWidth - 2.0f, y + 2.0f, borderTopLeft);
            renderer.drawLine(x + 2.0f, y + 2.0f, x + 2.0f, y + m_keyHeight - 2.0f, borderTopLeft);

            std::string letterStr(1, letter);
            renderer.drawText(letterStr, x + m_keyWidth / 2.0f, y + m_keyHeight / 2.0f, textColor, font);
        }
    }

private:
    float m_startX{0.0f};
    float m_startY{0.0f};
    float m_keyWidth{44.0f};
    float m_keyHeight{44.0f};
    float m_spacing{6.0f};
    std::array<float, 26> m_flashTimer{};
};
