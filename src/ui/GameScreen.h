#pragma once

#include "Renderer.h"
#include "game/GameState.h"
#include "game/HangmanGame.h"
#include "ui/HangmanRenderer.h"
#include "ui/KeyboardWidget.h"
#include <string>
#include <string_view>
#include <memory>

class GameScreen {
public:
    GameScreen(float hangmanX, float hangmanBaseY, TTF_Font* font)
        : m_hangmanRenderer(hangmanX, hangmanBaseY), m_keyboard(100.0f, 500.0f, 44.0f, 44.0f, 6.0f), m_font(font) {}

    GameState handleEvent(const SDL_Event& event, HangmanGame& game) {
        if (event.type != SDL_EVENT_KEY_DOWN) return GameState::Playing;

        SDL_Keycode key = event.key.key;
        if (key >= SDLK_A && key <= SDLK_Z) {
            game.guess(static_cast<char>(key));
            if (game.isWon()) return GameState::Won;
            if (game.isLost()) return GameState::Lost;
        }
        return GameState::Playing;
    }

    void draw(const Renderer& renderer, const HangmanGame& game) {
        renderer.clear(30, 30, 30, 255);

        m_hangmanRenderer.draw(renderer, game.getWrongGuesses());

        SDL_Color wordColor{255, 255, 255, 255};
        std::string masked = game.getMaskedWord();
        renderer.drawText(masked, 640.0f, 420.0f, wordColor, m_font);

        SDL_Color usedColor{150, 150, 150, 255};
        std::string used = game.getUsedLetters();
        if (!used.empty()) {
            renderer.drawText("Used: " + used, 640.0f, 470.0f, usedColor, m_font);
        }

        SDL_Color livesColor{255, 200, 200, 255};
        std::string lives = "Lives: " + std::to_string(game.getRemainingLives());
        renderer.drawText(lives, 640.0f, 520.0f, livesColor, m_font);

        m_keyboard.draw(renderer, m_font, game);
    }

private:
    HangmanRenderer m_hangmanRenderer;
    KeyboardWidget m_keyboard;
    TTF_Font* m_font{nullptr};
};
