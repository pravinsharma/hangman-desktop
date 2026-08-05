#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

class WordBank {
public:
    WordBank() = default;

    bool loadCategory(std::string_view category, std::string_view filePath) {
        std::ifstream file(filePath.data());
        if (!file.is_open()) {
            return false;
        }

        std::vector<std::string>& words = m_words[std::string(category)];
        std::string line;
        while (std::getline(file, line)) {
            std::string trimmed;
            std::ranges::copy_if(line, std::back_inserter(trimmed), [](unsigned char c) { return !std::isspace(c); });
            if (!trimmed.empty()) {
                words.push_back(std::move(trimmed));
            }
        }
        return !words.empty();
    }

    std::string getRandomWord(std::string_view category, std::mt19937& rng) const {
        auto it = m_words.find(std::string(category));
        if (it == m_words.end() || it->second.empty()) {
            return {};
        }
        std::uniform_int_distribution<std::size_t> dist(0, it->second.size() - 1);
        return it->second[dist(rng)];
    }

    bool hasCategory(std::string_view category) const {
        return m_words.contains(std::string(category));
    }

    std::vector<std::string> getCategories() const {
        std::vector<std::string> cats;
        cats.reserve(m_words.size());
        for (const auto& [cat, _] : m_words) {
            cats.push_back(cat);
        }
        return cats;
    }

private:
    std::unordered_map<std::string, std::vector<std::string>> m_words;
};
