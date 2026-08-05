#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <random>
#include <ctime>

#include "game/GameState.h"
#include "game/WordBank.h"
#include "game/HangmanGame.h"
#include "ui/Renderer.h"
#include "ui/MenuScreen.h"
#include "ui/GameScreen.h"
#include "ui/ResultScreen.h"
#include "assets/AssetManager.h"

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    const int width = 1280;
    const int height = 720;

    SDL_Window* window = SDL_CreateWindow("Hangman", width, height, 0);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow failed: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    AssetManager assetManager;
    const char* fontPath = "C:\\Windows\\Fonts\\arial.ttf";
    TTF_Font* titleFont = assetManager.getFont(fontPath, 64);
    TTF_Font* uiFont = assetManager.getFont(fontPath, 32);
    TTF_Font* smallFont = assetManager.getFont(fontPath, 24);

    WordBank wordBank;
    wordBank.loadCategory("Movies", "data/words/movies.txt");
    wordBank.loadCategory("Countries", "data/words/countries.txt");
    wordBank.loadCategory("Technology", "data/words/tech.txt");

    std::vector<std::string> categories = wordBank.getCategories();
    MenuScreen menuScreen;
    menuScreen.setCategories(categories);

    GameScreen gameScreen(200.0f, 600.0f, uiFont);
    ResultScreen resultScreen;

    HangmanGame game;
    std::string selectedCategory;
    GameState currentState = GameState::Menu;

    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            switch (currentState) {
                case GameState::Menu: {
                    GameState newState = menuScreen.handleEvent(event, selectedCategory);
                    if (newState == GameState::Playing && !selectedCategory.empty()) {
                        std::string word = wordBank.getRandomWord(selectedCategory, rng);
                        game.startNewGame(word, selectedCategory);
                        currentState = GameState::Playing;
                    }
                    break;
                }
                case GameState::Playing: {
                    GameState newState = gameScreen.handleEvent(event, game);
                    if (newState != GameState::Playing) {
                        currentState = newState;
                    }
                    break;
                }
                case GameState::Won:
                case GameState::Lost: {
                    GameState newState = resultScreen.handleEvent(event);
                    if (newState == GameState::Menu) {
                        currentState = GameState::Menu;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        Renderer sdlRenderer(renderer);

        switch (currentState) {
            case GameState::Menu:
                menuScreen.draw(sdlRenderer, titleFont);
                break;
            case GameState::Playing:
                gameScreen.draw(sdlRenderer, game);
                break;
            case GameState::Won:
                resultScreen.draw(sdlRenderer, uiFont, true, game.revealWord());
                break;
            case GameState::Lost:
                resultScreen.draw(sdlRenderer, uiFont, false, game.revealWord());
                break;
        }

        sdlRenderer.present();
    }

    assetManager.cleanup();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
