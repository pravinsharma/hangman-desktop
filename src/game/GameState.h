#pragma once

#include <string>
#include <string_view>

enum class GameState {
    Menu,
    Playing,
    Won,
    Lost,
    Settings
};

inline std::string_view to_string(GameState state) {
    switch (state) {
        case GameState::Menu: return "Menu";
        case GameState::Playing: return "Playing";
        case GameState::Won: return "Won";
        case GameState::Lost: return "Lost";
        case GameState::Settings: return "Settings";
        default: return "Unknown";
    }
}
