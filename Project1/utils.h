#pragma once
#include <algorithm>
#include <string>
#include <vector>

inline std::vector<std::string> split(const std::string& txt, char ch = ' ')
{
    std::vector<std::string> strs;
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs;
}
