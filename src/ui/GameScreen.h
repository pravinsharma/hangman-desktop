#pragma once

#include "Renderer.h"
#include "game/GameState.h"
#include "game/HangmanGame.h"
#include "game/ScoreManager.h"
#include "game/Difficulty.h"
#include "ui/HangmanRenderer.h"
#include "ui/KeyboardWidget.h"
#include "assets/AudioManager.h"
#include "utils/LocalizationManager.h"
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
          m_windowHeight(windowHeight) {}

    GameState handleEvent(const SDL_Event& event, HangmanGame& game, ScoreManager& scoreManager, AudioManager& audioManager) {
        if (event.type != SDL_EVENT_KEY_DOWN) return GameState::Playing;

        SDL_Keycode key = event.key.key;

        if (key == SDLK_H) {
            if (game.useHint()) {
                if (audioManager.isInitialized()) {
                    audioManager.playSound("assets/sounds/hint.wav");
                }
                scoreManager.saveHighScore(game.getCategory(), calculateScore(game) - 10);
            }
            return GameState::Playing;
        }

        if (key == SDLK_M) {
            audioManager.toggleMusic();
            return GameState::Playing;
        }

        if (key >= SDLK_A && key <= SDLK_Z) {
            int prevWrong = game.getWrongGuesses();
            game.guess(static_cast<char>(key));
            int currWrong = game.getWrongGuesses();

            if (currWrong > prevWrong) {
                m_hangmanRenderer.startShake();
                if (audioManager.isInitialized()) {
                    audioManager.playSound("assets/sounds/wrong.wav");
                }
            } else if (currWrong == prevWrong && !game.isGameOver()) {
                if (audioManager.isInitialized()) {
                    audioManager.playSound("assets/sounds/correct.wav");
                }
            }

            if (game.isWon()) {
                if (audioManager.isInitialized()) {
                    audioManager.playSound("assets/sounds/win.wav");
                }
                int score = calculateScore(game);
                scoreManager.saveHighScore(game.getCategory(), score);
                m_lastScore = score;
                return GameState::Won;
            }
            if (game.isLost()) {
                if (audioManager.isInitialized()) {
                    audioManager.playSound("assets/sounds/lose.wav");
                }
                m_lastScore = calculateScore(game);
                return GameState::Lost;
            }
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

    void draw(const Renderer& renderer, const HangmanGame& game, int highScore, const LocalizationManager& localization) {
        renderer.clear(18, 18, 24, 255);

        m_hangmanRenderer.draw(renderer, game.getWrongGuesses());

        float centerX = m_windowWidth / 2.0f;

        SDL_Color wordColor{230, 240, 255, 255};
        std::string masked = game.getMaskedWord();
        renderer.drawText(masked, centerX, m_windowHeight * 0.54f, wordColor, m_font);

        SDL_Color usedColor{140, 155, 190, 255};
        std::string used = game.getUsedLetters();
        if (!used.empty()) {
            renderer.drawTextLeft("Used: " + used, centerX - 180.0f, m_windowHeight * 0.61f, usedColor, m_font);
        }

        float livesVal = static_cast<float>(game.getRemainingLives()) / std::max(1, game.getMaxWrongGuesses());
        SDL_Color livesColor{240, 120, 120, 255};
        std::string lives = "Lives: " + std::to_string(game.getRemainingLives());
        renderer.drawTextLeft(lives, centerX - 180.0f, m_windowHeight * 0.67f, livesColor, m_font);

        SDL_Color hintsColor{150, 200, 255, 255};
        std::string hints = "Hints: " + std::to_string(game.getHintsRemaining());
        renderer.drawTextLeft(hints, centerX + 40.0f, m_windowHeight * 0.67f, hintsColor, m_font);

        SDL_Color scoreColor{255, 235, 150, 255};
        std::string scoreText = "Score: " + std::to_string(calculateScore(game));
        renderer.drawText(scoreText, centerX, m_windowHeight * 0.74f, scoreColor, m_font);

        SDL_Color highScoreColor{150, 235, 170, 255};
        std::string highScoreText = "Best: " + std::to_string(highScore);
        renderer.drawText(highScoreText, centerX, m_windowHeight * 0.785f, highScoreColor, m_font);

        float keyboardY = m_windowHeight * 0.83f;
        KeyboardWidget keyboard(80.0f, keyboardY, 38.0f, 38.0f, 5.0f);
        keyboard.update(0.016f);
        keyboard.draw(renderer, m_font, game);

        SDL_Color hintKeyColor{100, 115, 145, 255};
        std::string controls = "[H] Hint   [M] Music   [S] Settings";
        renderer.drawText(controls, centerX, m_windowHeight * 0.96f, hintKeyColor, m_font);
    }

    int getLastScore() const { return m_lastScore; }

private:
    int calculateScore(const HangmanGame& game) const {
        int baseScore = game.getRemainingLives() * 10;
        int hintPenalty = game.getHintsUsed() * 10;
        int wrongPenalty = game.getWrongGuesses() * 2;
        return std::max(0, baseScore - hintPenalty - wrongPenalty);
    }

    HangmanRenderer m_hangmanRenderer;
    TTF_Font* m_font{nullptr};
    float m_windowWidth{1280.0f};
    float m_windowHeight{720.0f};
    int m_lastScore{0};
};
