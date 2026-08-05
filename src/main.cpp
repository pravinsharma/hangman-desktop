#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <cmath>

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

    SDL_Window* window = SDL_CreateWindow("SDL3 Vanilla Scaffold", width, height, 0);
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

    const char* fontPath = "C:\\Windows\\Fonts\\arial.ttf";
    const int fontSize = 120;
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "TTF_OpenFont failed: %s", SDL_GetError());
    }

    SDL_Color color = {255, 255, 255, 255};
    const char* text = "Hello World!";
    SDL_Surface* surface = font ? TTF_RenderText_Blended(font, text, 0, color) : nullptr;

    SDL_Texture* texture = nullptr;
    SDL_FRect textRect{};
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture) {
            float texW = static_cast<float>(surface->w);
            float texH = static_cast<float>(surface->h);
            textRect.x = (width - texW) / 2.0f;
            textRect.y = (height - texH) / 2.0f;
            textRect.w = texW;
            textRect.h = texH;
        }
        SDL_DestroySurface(surface);
    }

    const char* imagePath = "assets/images/cat.gif";
    IMG_Animation* anim = IMG_LoadAnimation(imagePath);
    SDL_Texture** animTextures = nullptr;
    Uint32* animDelays = nullptr;
    int animFrames = 0;
    int animCurrentFrame = 0;
    Uint32 animLastTime = 0;
    SDL_FRect animRect{};

    if (anim && anim->count > 0) {
        animFrames = anim->count;
        animTextures = new SDL_Texture*[animFrames];
        animDelays = new Uint32[animFrames];

        for (int i = 0; i < animFrames; i++) {
            animTextures[i] = SDL_CreateTextureFromSurface(renderer, anim->frames[i]);
            animDelays[i] = anim->delays[i];
        }

        float maxDim = 200.0f;
        float scale = std::min(maxDim / static_cast<float>(anim->w), maxDim / static_cast<float>(anim->h));
        float imgW = static_cast<float>(anim->w) * scale;
        float imgH = static_cast<float>(anim->h) * scale;
        animRect.w = imgW;
        animRect.h = imgH;
        animRect.x = (width - imgW) / 2.0f;
        animRect.y = textRect.y - imgH - 20.0f;
        if (animRect.y < 10.0f) animRect.y = 10.0f;

        animLastTime = SDL_GetTicks();
    }

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        if (anim && animFrames > 0) {
            Uint32 now = SDL_GetTicks();
            if (now - animLastTime >= animDelays[animCurrentFrame]) {
                animLastTime = now;
                animCurrentFrame = (animCurrentFrame + 1) % animFrames;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        if (anim && animCurrentFrame < animFrames && animTextures[animCurrentFrame]) {
            SDL_RenderTexture(renderer, animTextures[animCurrentFrame], nullptr, &animRect);
        }

        if (texture) {
            SDL_RenderTexture(renderer, texture, nullptr, &textRect);
        }

        SDL_RenderPresent(renderer);
    }

    if (animTextures) {
        for (int i = 0; i < animFrames; i++) {
            if (animTextures[i]) SDL_DestroyTexture(animTextures[i]);
        }
        delete[] animTextures;
    }
    if (animDelays) delete[] animDelays;
    if (anim) IMG_FreeAnimation(anim);

    if (texture) SDL_DestroyTexture(texture);
    if (font) TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
