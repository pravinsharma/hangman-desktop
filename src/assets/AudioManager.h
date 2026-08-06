#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <string_view>
#include <unordered_map>

class AudioManager {
public:
    AudioManager() = default;

    bool init() {
        m_initialized = SDL_WasInit(SDL_INIT_AUDIO) != 0;
        if (!m_initialized) {
            if (SDL_InitSubSystem(SDL_INIT_AUDIO)) {
                m_initialized = true;
            } else {
                SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "SDL audio init failed: %s", SDL_GetError());
            }
        }
        return m_initialized;
    }

    ~AudioManager() {
        cleanup();
    }

    bool playSound(std::string_view path) {
        if (!m_initialized) return false;
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Playing sound: %s", path.data());
        return true;
    }

    bool playMusic(std::string_view path, int loops = -1) {
        if (!m_initialized) return false;
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Playing music: %s (loops=%d)", path.data(), loops);
        return true;
    }

    void pauseMusic() {
        if (!m_initialized) return;
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Music paused");
    }

    void resumeMusic() {
        if (!m_initialized) return;
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Music resumed");
    }

    void toggleMusic() {
        if (!m_initialized) return;
        if (m_musicPaused) {
            m_musicPaused = false;
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Music resumed");
        } else {
            m_musicPaused = true;
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Music paused");
        }
    }

    bool isMusicPaused() const { return m_musicPaused; }
    bool isInitialized() const { return m_initialized; }

private:
    void cleanup() {
        if (!m_initialized) return;
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        m_initialized = false;
    }

    std::unordered_map<std::string, bool> m_soundLoaded;
    bool m_initialized{false};
    bool m_musicPaused{false};
};
