#pragma once

#include <algorithm>
#include <cctype>
#include <locale>
#include <vector>

namespace utils {
static std::vector<std::string> split(const std::string& line,
                                      const char separator) {
    if (line.empty()) {
        return {""};
    }

    std::vector<std::string> result;
    std::string buffer;

    for (char ch : line) {
        if (ch != separator) {
            buffer += ch;
        } else {
            result.push_back(buffer);
            buffer = "";
        }
    }

    if (!buffer.empty()) {
        result.push_back(buffer);
    }

    return result;
}

static std::pair<std::string, std::string> splitTwo(const std::string& line,
                                                    const char separator) {
    const auto splitLine = split(line, separator);

    if (splitLine.size() < 2) {
        throw std::logic_error("Could not split line into two parts!");
    }

    return std::make_pair(splitLine[0], splitLine[1]);
}

static inline void ltrim_inplace(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
}

static inline void rtrim_inplace(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) {
                             return !std::isspace(ch);
                         })
                .base(),
            s.end());
}

static inline void trim_inplace(std::string& s) {
    ltrim_inplace(s);
    rtrim_inplace(s);
}

static inline std::string ltrim(std::string s) {
    ltrim_inplace(s);
    return s;
}

static inline std::string rtrim(std::string s) {
    rtrim_inplace(s);
    return s;
}

static inline std::string trim(std::string s) {
    trim_inplace(s);
    return s;
}

template <typename T>
static std::optional<T*> optionalOf(T* value) {
    return value ? std::make_optional(value) : std::nullopt;
}
}  // namespace utils
