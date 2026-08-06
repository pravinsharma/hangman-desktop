#pragma once

#include <string>
#include <string_view>

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

inline std::string_view to_string(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy: return "Easy";
        case Difficulty::Medium: return "Medium";
        case Difficulty::Hard: return "Hard";
        default: return "Unknown";
    }
}

inline Difficulty defaultDifficulty() {
    return Difficulty::Medium;
}

inline int maxWrongGuessesForDifficulty(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy: return 8;
        case Difficulty::Medium: return 6;
        case Difficulty::Hard: return 4;
        default: return 6;
    }
}

inline int hintsForDifficulty(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy: return 3;
        case Difficulty::Medium: return 2;
        case Difficulty::Hard: return 1;
        default: return 2;
    }
}

inline std::pair<size_t, size_t> wordLengthRangeForDifficulty(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy: return {4, 8};
        case Difficulty::Medium: return {5, 10};
        case Difficulty::Hard: return {8, 15};
        default: return {5, 10};
    }
}
