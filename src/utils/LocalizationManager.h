#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

class LocalizationManager {
public:
    enum class Language { English, Hindi };

    LocalizationManager() {
        m_strings[Language::English] = {
            {"title", "HANGMAN"},
            {"select_category", "Select a category:"},
            {"difficulty", "Difficulty:"},
            {"daily_mode", "Daily Mode:"},
            {"on", "ON"},
            {"off", "OFF"},
            {"easy", "Easy"},
            {"medium", "Medium"},
            {"hard", "Hard"},
            {"hint_key", "[H] Hint"},
            {"music_key", "[M] Music"},
            {"settings_key", "[S] Settings"},
            {"back", "Press ESC to go back"},
            {"select_category_hint", "Press 1-9 to select category"},
            {"difficulty_hint", "LEFT/RIGHT to change difficulty | D to toggle daily mode"},
            {"you_won", "YOU WON!"},
            {"game_over", "GAME OVER"},
            {"the_word_was", "The word was:"},
            {"score", "Score:"},
            {"high_score", "High Score:"},
            {"return_menu", "Press ENTER to return to menu"},
            {"settings_title", "SETTINGS"},
            {"language", "Language:"},
            {"text_size", "Text Size:"},
            {"color_blind", "Color Blind Mode:"},
            {"sound", "Sound:"},
            {"small", "Small"},
            {"normal", "Normal"},
            {"large", "Large"}
        };

        m_strings[Language::Hindi] = {
            {"title", "हंगमैन"},
            {"select_category", "श्रेणी चुनें:"},
            {"difficulty", "कठिनाई:"},
            {"daily_mode", "दैनिक मोड:"},
            {"on", "चालू"},
            {"off", "बंद"},
            {"easy", "आसान"},
            {"medium", "मध्यम"},
            {"hard", "कठिन"},
            {"hint_key", "[H] संकेत"},
            {"music_key", "[M] संगीत"},
            {"settings_key", "[S] सेटिंग्स"},
            {"back", "वापस जाने के लिए ESC दबाएं"},
            {"select_category_hint", "श्रेणी चुनने के लिए 1-9 दबाएं"},
            {"difficulty_hint", "कठिनाई बदलने के लिए LEFT/RIGHT | D दैनिक मोड टॉगल"},
            {"you_won", "आप जीत गए!"},
            {"game_over", "खेल खत्म"},
            {"the_word_was", "शब्द था:"},
            {"score", "स्कोर:"},
            {"high_score", "उच्च स्कोर:"},
            {"return_menu", "मुख्य मेनू पर लौटने के लिए ENTER दबाएं"},
            {"settings_title", "सेटिंग्स"},
            {"language", "भाषा:"},
            {"text_size", "टेक्स्ट आकार:"},
            {"color_blind", "कलर ब्लाइंड मोड:"},
            {"sound", "ध्वनि:"},
            {"small", "छोटा"},
            {"normal", "सामान्य"},
            {"large", "बड़ा"}
        };
    }

    void setLanguage(Language lang) { m_currentLanguage = lang; }
    Language getLanguage() const { return m_currentLanguage; }

    std::string get(std::string_view key) const {
        auto it = m_strings.at(m_currentLanguage).find(std::string(key));
        if (it != m_strings.at(m_currentLanguage).end()) {
            return it->second;
        }
        return std::string(key);
    }

private:
    Language m_currentLanguage{Language::English};
    std::unordered_map<Language, std::unordered_map<std::string, std::string>> m_strings;
};
