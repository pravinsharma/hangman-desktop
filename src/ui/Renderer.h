#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>

class AssetManager;

class Renderer {
public:
    explicit Renderer(SDL_Renderer* renderer) : m_renderer(renderer) {}

    void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) const {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
        SDL_RenderClear(m_renderer);
    }

    void present() const {
        SDL_RenderPresent(m_renderer);
    }

    void drawText(std::string_view text, float x, float y, SDL_Color color, TTF_Font* font) const {
        if (!font || text.empty()) return;
        SDL_Surface* surface = TTF_RenderText_Blended(font, text.data(), 0, color);
        if (!surface) return;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        if (!texture) {
            SDL_DestroySurface(surface);
            return;
        }

        SDL_FRect rect{};
        rect.w = static_cast<float>(surface->w);
        rect.h = static_cast<float>(surface->h);
        rect.x = x - rect.w / 2.0f;
        rect.y = y - rect.h / 2.0f;

        SDL_RenderTexture(m_renderer, texture, nullptr, &rect);
        SDL_DestroyTexture(texture);
        SDL_DestroySurface(surface);
    }

    void drawRect(float x, float y, float w, float h, SDL_Color color) const {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        SDL_FRect rect{x, y, w, h};
        SDL_RenderFillRect(m_renderer, &rect);
    }

    void drawOverlay(float alpha) const {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, static_cast<Uint8>(alpha * 255));
        SDL_FRect rect{0.0f, 0.0f, 2000.0f, 2000.0f};
        SDL_RenderFillRect(m_renderer, &rect);
    }

    void drawLine(float x1, float y1, float x2, float y2, SDL_Color color) const {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }

    void drawCircle(float cx, float cy, float radius, SDL_Color color) const {
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        const int steps = 64;
        for (int i = 0; i < steps; ++i) {
            float angle1 = 2.0f * 3.14159265f * i / steps;
            float angle2 = 2.0f * 3.14159265f * (i + 1) / steps;
            SDL_RenderLine(m_renderer,
                cx + radius * std::cos(angle1), cy + radius * std::sin(angle1),
                cx + radius * std::cos(angle2), cy + radius * std::sin(angle2));
        }
    }

    SDL_Renderer* get() const { return m_renderer; }

private:
    SDL_Renderer* m_renderer{nullptr};
};
