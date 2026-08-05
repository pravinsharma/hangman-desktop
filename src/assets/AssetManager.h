#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <string_view>
#include <unordered_map>

class AssetManager {
public:
    AssetManager() = default;

    TTF_Font* getFont(std::string_view path, int size) {
        std::string key = std::string(path) + "#" + std::to_string(size);
        auto it = m_fonts.find(key);
        if (it != m_fonts.end()) {
            return it->second;
        }
        TTF_Font* font = TTF_OpenFont(path.data(), size);
        if (font) {
            m_fonts[key] = font;
        }
        return font;
    }

    void cleanup() {
        for (auto& [_, font] : m_fonts) {
            if (font) TTF_CloseFont(font);
        }
        m_fonts.clear();
    }

private:
    std::unordered_map<std::string, TTF_Font*> m_fonts;
};
