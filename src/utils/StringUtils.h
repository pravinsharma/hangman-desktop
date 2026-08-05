#pragma once

#include <string>
#include <string_view>
#include <algorithm>

namespace StringUtils {
    inline std::string toUpper(std::string_view str) {
        std::string result(str);
        std::ranges::transform(result, result.begin(), [](unsigned char c) { return std::toupper(c); });
        return result;
    }

    inline bool iequals(std::string_view a, std::string_view b) {
        return std::equal(a.begin(), a.end(), b.begin(), b.end(),
            [](char a, char b) { return std::toupper(a) == std::toupper(b); });
    }
}
