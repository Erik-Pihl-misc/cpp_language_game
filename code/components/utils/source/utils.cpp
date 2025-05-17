/**
 * @brief Implementation details of utility functions.
 */
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <list>

#include "utils/phrase.h"
#include "utils/utils.h"

namespace language
{
namespace utils
{
namespace
{
// ---------------------------------------------------------------------------
bool blankLine(const std::string& line) 
{
    for (const auto& c : line) 
    {
        if (' ' != c) { return false; }
    }
    return true;
}

// ---------------------------------------------------------------------------
bool lineEmpty(const std::string& line) { return line.empty() || blankLine(line); }

}
// ---------------------------------------------------------------------------
void readLine(std::string& str, const char* space)
{
    // Read input from the terminal.
    std::getline(std::cin, str);

    // Add space if specified.
    if (space) { std::cout << space << std::endl; }

    // Clear the input buffer.
    std::cin.clear();
}

// ---------------------------------------------------------------------------
std::size_t loadPhrasesFromFile(const std::string& filePath, std::list<Phrase>& phrases)
{
    std::vector<std::string> data{};

    // If data was loaded from the file, store consecutive strings as phrase pairs.
    if (retrieveFromFile(filePath, data) && !data.empty()) 
    {
        for (std::size_t i{}; i < data.size(); i += 2U) 
        {
            Phrase phrase{data[i], data[i + 1U]};
            phrases.push_back(phrase);
        }
    }
    // Return the number of loaded phrases.
    return phrases.size(); 
}

// ---------------------------------------------------------------------------
bool writePhrasesToFile(const std::string& filePath, const std::list<Phrase>& phrases)
{
    // Open the file for writing.
    std::ofstream ofstream{filePath};

    // If the file couldn't be opened or no phrases are present, return false.
    if (!ofstream && phrases.empty()) { return false; }

    // Write each pair on two consecutive lines, followed by an additional blank line.
    for (const auto& phrase : phrases) 
    { 
        ofstream << phrase.primary << "\n" << phrase.target << "\n\n"; 
    }
    // Return true to indicate successful operation.
    return true;
}

// ---------------------------------------------------------------------------
bool retrieveFromFile(const std::string& filePath, std::vector<std::string>& data)
{
    // Open the file for reading.
    std::ifstream ifstream{filePath};

    // If the file couldn't be opened return false.
    if (!ifstream) { return false; }

    std::string line{};

    // Read the file line by line.
    while (std::getline(ifstream, line)) 
    {
        // Store each non-empty line.
        removeTrailingWhitespaces(line);
        if (!lineEmpty(line)) { data.push_back(line); }
    }
    // Return true if at least one line was loaded.
    return !data.empty();
}

// ---------------------------------------------------------------------------
void removeTrailingWhitespaces(std::string& str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch)
        { return !std::isspace(ch); }).base(), str.end());
}
} // namespace utils
} // namespace language