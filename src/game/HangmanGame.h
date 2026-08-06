#pragma once

#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <algorithm>
#include <cctype>
#include <random>
#include "Difficulty.h"

class HangmanGame {
public:
    static constexpr int kMaxWrongGuesses = 6;

    HangmanGame() = default;

    void startNewGame(std::string_view word, std::string_view category, Difficulty difficulty = Difficulty::Medium) {
        m_word = std::string(word);
        m_category = std::string(category);
        m_difficulty = difficulty;
        m_maxWrongGuesses = maxWrongGuessesForDifficulty(difficulty);
        m_revealed.assign(m_word.size(), false);
        m_used.fill(false);
        m_wrongGuesses = 0;
        m_won = false;
        m_lost = false;
        m_hintsUsed = 0;

        for (size_t i = 0; i < m_word.size(); ++i) {
            if (m_word[i] == ' ') {
                m_revealed[i] = true;
            }
        }
    }

    bool guess(char letter) {
        letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
        if (!std::isalpha(static_cast<unsigned char>(letter))) {
            return false;
        }
        int idx = letter - 'A';
        if (idx < 0 || idx >= 26 || m_used[idx]) {
            return false;
        }
        m_used[idx] = true;

        bool found = false;
        for (size_t i = 0; i < m_word.size(); ++i) {
            if (std::toupper(static_cast<unsigned char>(m_word[i])) == letter) {
                m_revealed[i] = true;
                found = true;
            }
        }

        if (!found) {
            ++m_wrongGuesses;
            if (m_wrongGuesses >= m_maxWrongGuesses) {
                m_lost = true;
            }
        } else {
            checkWin();
        }

        return true;
    }

    bool useHint() {
        if (m_hintsUsed >= hintsForDifficulty(m_difficulty)) {
            return false;
        }

        std::vector<size_t> hidden;
        for (size_t i = 0; i < m_word.size(); ++i) {
            if (!m_revealed[i] && m_word[i] != ' ') {
                hidden.push_back(i);
            }
        }

        if (hidden.empty()) {
            return false;
        }

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<std::size_t> dist(0, hidden.size() - 1);
        size_t idx = hidden[dist(rng)];
        m_revealed[idx] = true;
        ++m_hintsUsed;

        checkWin();
        return true;
    }

    bool isWon() const { return m_won; }
    bool isLost() const { return m_lost; }
    bool isGameOver() const { return m_won || m_lost; }
    int getWrongGuesses() const { return m_wrongGuesses; }
    int getMaxWrongGuesses() const { return m_maxWrongGuesses; }
    int getRemainingLives() const { return m_maxWrongGuesses - m_wrongGuesses; }
    int getHintsUsed() const { return m_hintsUsed; }
    int getHintsRemaining() const { return hintsForDifficulty(m_difficulty) - m_hintsUsed; }
    Difficulty getDifficulty() const { return m_difficulty; }
    std::string_view getWord() const { return m_word; }
    std::string_view getCategory() const { return m_category; }

    std::string getMaskedWord() const {
        std::string masked;
        masked.reserve(m_word.size());
        for (size_t i = 0; i < m_word.size(); ++i) {
            if (m_word[i] == ' ') {
                masked += ' ';
            } else if (m_revealed[i]) {
                masked += m_word[i];
            } else {
                masked += '_';
            }
        }
        return masked;
    }

    std::string getUsedLetters() const {
        std::string used;
        for (int i = 0; i < 26; ++i) {
            if (m_used[i]) {
                used.push_back(static_cast<char>('A' + i));
            }
        }
        return used;
    }

    bool isLetterUsed(char letter) const {
        letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
        int idx = letter - 'A';
        if (idx < 0 || idx >= 26) return true;
        return m_used[idx];
    }

    std::string revealWord() const {
        return m_word;
    }

private:
    void checkWin() {
        for (size_t i = 0; i < m_word.size(); ++i) {
            if (m_word[i] != ' ' && !m_revealed[i]) {
                return;
            }
        }
        m_won = true;
    }

    std::string m_word;
    std::string m_category;
    std::vector<bool> m_revealed;
    std::array<bool, 26> m_used{};
    int m_wrongGuesses{0};
    int m_maxWrongGuesses{kMaxWrongGuesses};
    int m_hintsUsed{0};
    bool m_won{false};
    bool m_lost{false};
    Difficulty m_difficulty{Difficulty::Medium};
};
