#pragma once

#include <string>
#include <string_view>
#include <fstream>
#include <unordered_map>
#include <algorithm>

class ScoreManager {
public:
    static constexpr const char* kScoreFile = "data/scores.txt";

    ScoreManager() = default;

    int loadHighScore(std::string_view category) const {
        std::ifstream file(kScoreFile);
        if (!file.is_open()) {
            return 0;
        }

        std::string line;
        std::string targetCat = std::string(category) + ":";
        while (std::getline(file, line)) {
            if (line.starts_with(targetCat)) {
                size_t pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string scoreStr = line.substr(pos + 1);
                    std::erase_if(scoreStr, [](unsigned char c) { return !std::isdigit(c); });
                    if (!scoreStr.empty()) {
                        return std::stoi(scoreStr);
                    }
                }
            }
        }
        return 0;
    }

    void saveHighScore(std::string_view category, int score) {
        std::unordered_map<std::string, int> scores;
        std::ifstream inFile(kScoreFile);
        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) {
                size_t pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string cat = line.substr(0, pos);
                    std::string scoreStr = line.substr(pos + 1);
                    std::erase_if(scoreStr, [](unsigned char c) { return !std::isdigit(c); });
                    if (!scoreStr.empty()) {
                        scores[cat] = std::stoi(scoreStr);
                    }
                }
            }
            inFile.close();
        }

        std::string catStr = std::string(category);
        if (scores.contains(catStr)) {
            scores[catStr] = std::max(scores[catStr], score);
        } else {
            scores[catStr] = score;
        }

        std::ofstream outFile(kScoreFile);
        if (outFile.is_open()) {
            for (const auto& [cat, sc] : scores) {
                outFile << cat << ":" << sc << "\n";
            }
            outFile.close();
        }
    }
};
