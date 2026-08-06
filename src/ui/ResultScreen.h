#pragma once

#include "Renderer.h"
#include "game/GameState.h"
#include "utils/LocalizationManager.h"
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

    void draw(const Renderer& renderer, TTF_Font* font, bool won, std::string_view word, int score, int highScore, const LocalizationManager& localization) {
        renderer.clear(18, 18, 24, 255);

        float centerX = 640.0f;

        SDL_Color titleColor = won ? SDL_Color{120, 255, 170, 255} : SDL_Color{255, 120, 120, 255};
        std::string title = won ? localization.get("you_won") : localization.get("game_over");
        renderer.drawText(title, centerX, 160.0f, titleColor, font);

        SDL_Color wordColor{210, 220, 245, 255};
        std::string wordText = localization.get("the_word_was") + "  " + std::string(word);
        renderer.drawText(wordText, centerX, 230.0f, wordColor, font);

        SDL_Color scoreColor{255, 235, 150, 255};
        std::string scoreText = localization.get("score") + "  " + std::to_string(score);
        renderer.drawText(scoreText, centerX, 290.0f, scoreColor, font);

        SDL_Color highScoreColor{150, 235, 180, 255};
        std::string highScoreText = localization.get("high_score") + "  " + std::to_string(highScore);
        renderer.drawText(highScoreText, centerX, 340.0f, highScoreColor, font);

        SDL_Color hintColor{120, 130, 160, 255};
        renderer.drawText(localization.get("return_menu"), centerX, 420.0f, hintColor, font);
    }
};
