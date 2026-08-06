#pragma once

#include <string>
#include <string_view>

class SettingsManager {
public:
    enum class TextSize { Small, Normal, Large };

    SettingsManager() = default;

    TextSize getTextSize() const { return m_textSize; }
    void setTextSize(TextSize size) { m_textSize = size; }

    bool getColorBlindMode() const { return m_colorBlindMode; }
    void setColorBlindMode(bool enabled) { m_colorBlindMode = enabled; }

    int getFontSize(TextSize size) const {
        switch (size) {
            case TextSize::Small: return 24;
            case TextSize::Normal: return 32;
            case TextSize::Large: return 40;
            default: return 32;
        }
    }

    TextSize parseTextSize(const std::string& sizeStr) const {
        if (sizeStr == "Small") return TextSize::Small;
        if (sizeStr == "Large") return TextSize::Large;
        return TextSize::Normal;
    }

    std::string textSizeToString(TextSize size) const {
        switch (size) {
            case TextSize::Small: return "Small";
            case TextSize::Normal: return "Normal";
            case TextSize::Large: return "Large";
            default: return "Normal";
        }
    }

private:
    TextSize m_textSize{TextSize::Normal};
    bool m_colorBlindMode{false};
};
