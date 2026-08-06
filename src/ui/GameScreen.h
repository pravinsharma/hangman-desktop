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
    GameScreen(float hangmanX, float hangmanBaseY, TTF_Font* font,
               float windowWidth = 1280.0f, float windowHeight = 720.0f)
        : m_hangmanRenderer(hangmanX, hangmanBaseY),
          m_font(font),
          m_windowWidth(windowWidth),
          m_windowHeight(windowHeight),
          m_prevWrongGuesses(0) {}

    GameState handleEvent(const SDL_Event& event, HangmanGame& game) {
        if (event.type != SDL_EVENT_KEY_DOWN) return GameState::Playing;

        SDL_Keycode key = event.key.key;
        if (key >= SDLK_A && key <= SDLK_Z) {
            int prevWrong = game.getWrongGuesses();
            game.guess(static_cast<char>(key));
            int currWrong = game.getWrongGuesses();

            if (currWrong > prevWrong) {
                m_hangmanRenderer.startShake();
            }

            if (game.isWon()) return GameState::Won;
            if (game.isLost()) return GameState::Lost;
        }
        return GameState::Playing;
    }

    void update(float dt) {
        m_hangmanRenderer.update(dt);
    }

    void setWindowSize(float width, float height) {
        m_windowWidth = width;
        m_windowHeight = height;
    }

    void draw(const Renderer& renderer, const HangmanGame& game) {
        renderer.clear(30, 30, 30, 255);

        m_hangmanRenderer.draw(renderer, game.getWrongGuesses());

        float centerX = m_windowWidth / 2.0f;

        SDL_Color wordColor{255, 255, 255, 255};
        std::string masked = game.getMaskedWord();
        renderer.drawText(masked, centerX, m_windowHeight * 0.58f, wordColor, m_font);

        SDL_Color usedColor{150, 150, 150, 255};
        std::string used = game.getUsedLetters();
        if (!used.empty()) {
            renderer.drawText("Used: " + used, centerX, m_windowHeight * 0.65f, usedColor, m_font);
        }

        SDL_Color livesColor{255, 200, 200, 255};
        std::string lives = "Lives: " + std::to_string(game.getRemainingLives());
        renderer.drawText(lives, centerX, m_windowHeight * 0.72f, livesColor, m_font);

        float keyboardY = m_windowHeight * 0.78f;
        KeyboardWidget keyboard(100.0f, keyboardY, 44.0f, 44.0f, 6.0f);
        keyboard.draw(renderer, m_font, game);
    }

private:
    HangmanRenderer m_hangmanRenderer;
    TTF_Font* m_font{nullptr};
    float m_windowWidth{1280.0f};
    float m_windowHeight{720.0f};
    int m_prevWrongGuesses{0};
};
