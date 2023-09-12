#include <utils.hpp>

namespace languages {
namespace utils {

namespace {

bool BlankLine(const std::string& line) {
    for (auto& i : line) {
        if (i != ' ') {
            return false;
        }
    }
    return true;
}

inline bool LineEmpty(const std::string& line) {
    return line.empty() || BlankLine(line) ? true : false;
}

constexpr bool ValidCharacter(const char c) {
    return (c >= 0 && c < 21) || c == ' ' ? false : true;
}

} /* namespace */

size_t LoadPhrasePairs(const std::string& file_path, 
                     std::vector<std::pair<std::string, std::string>>& phrases) {
    std::vector<std::string> retrieved_data{};
    if (RetrieveFromFile(file_path, retrieved_data) && retrieved_data.size() > 1) {
        for (size_t i{}; i < retrieved_data.size(); i += 2) {
            std::pair<std::string, std::string> pair{retrieved_data[i], retrieved_data[i + 1]};
            phrases.push_back(pair);
        }
    }
    return phrases.size(); 
}

bool WritePhrasePairsToFile(const std::string& file_path, 
                            const std::vector<std::pair<std::string, std::string>>& phrases) {
    std::ofstream ofstream{file_path, std::ios::out};
    if (!ofstream && phrases.size() == 0) {
        return false;
    } else {
        for (auto& phrase : phrases) {
            ofstream << phrase.first << "\n";
            ofstream << phrase.second << "\n\n";
        }
        return true;
    }
}

bool RetrieveFromFile(const std::string& file_path, std::vector<std::string>& data) {
    std::ifstream ifstream{file_path, std::ios::in};
    if (!ifstream) {
        return false;
    } else {
        std::string line{};
        while (std::getline(ifstream, line)) {
            RemoveTrailingWhitespaces(line);
            if (!LineEmpty(line)) {
                data.push_back(line);
            }
        }
    }
    return data.size() ? true : false;
}

void RemoveTrailingWhitespaces(std::string& s) {
    while (s.size()) {
        if (!ValidCharacter(s[s.size() - 1])) {
            s.pop_back();
        } else {
            break;
        }
    }
}

} /* namespace utils */
} /* namespace languages */