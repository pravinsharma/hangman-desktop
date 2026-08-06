#pragma once

#include "Renderer.h"
#include "game/GameState.h"
#include <string>
#include <string_view>

class ResultScreen {
public:
    ResultScreen() = default;

    GameState handleEvent(const SDL_Event& event) const {
        if (event.type != SDL_EVENT_KEY_DOWN) return GameState::Won;
        if (event.key.key == SDLK_RETURN || event.key.key == SDLK_SPACE) {
            return GameState::Menu;
        }
        return GameState::Won;
    }

    void draw(const Renderer& renderer, TTF_Font* font, bool won, std::string_view word, int score, int highScore) {
        renderer.clear(30, 30, 30, 255);

        SDL_Color titleColor = won ? SDL_Color{100, 255, 100, 255} : SDL_Color{255, 100, 100, 255};
        std::string title = won ? "YOU WON!" : "GAME OVER";
        renderer.drawText(title, 640.0f, 160.0f, titleColor, font);

        SDL_Color wordColor{255, 255, 255, 255};
        std::string wordText = "The word was: " + std::string(word);
        renderer.drawText(wordText, 640.0f, 230.0f, wordColor, font);

        SDL_Color scoreColor{255, 255, 150, 255};
        std::string scoreText = "Score: " + std::to_string(score);
        renderer.drawText(scoreText, 640.0f, 290.0f, scoreColor, font);

        SDL_Color highScoreColor{150, 255, 150, 255};
        std::string highScoreText = "High Score: " + std::to_string(highScore);
        renderer.drawText(highScoreText, 640.0f, 340.0f, highScoreColor, font);

        SDL_Color hintColor{150, 150, 150, 255};
        renderer.drawText("Press ENTER to return to menu", 640.0f, 420.0f, hintColor, font);
    }
};
