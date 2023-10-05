/********************************************************************************
 * @brief Contains utility functions for language game.
 ********************************************************************************/
#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <type_traits>
#include <cstdlib>

namespace languages {
namespace utils {

namespace {

/********************************************************************************
 * @brief Initializes random generator. Always call this function before 
 *        generating random numbers.
 ********************************************************************************/
inline void InitRandomGenerator(void) {
    static bool init{false};
    if (!init) {
        std::srand(time(nullptr));
        init = true;
    }
}

/********************************************************************************
 * @brief Provides a random integer within specified span counted from 0.
 * 
 * @param span
 *        The range of permitted integers, which corresponds to [0, span - 1].
 * @return
 *        Random integer within range [0, span - 1].
 ********************************************************************************/
template <typename T = int>
constexpr T GetRandomInt(const T range) {
    static_assert(std::is_integral<T>::value, 
        "Non-integer type passed to languages::utils::GetRandomInt!");
    InitRandomGenerator();
    return static_cast<T>(std::rand() % range);
}

/********************************************************************************
 * @brief Provides a random integer within specified range [min, max].
 * 
 * @param min
 *        The minimum value of the random integer.
 * @param max
 *        The maximum value of the random integer.
 * @return
 *        Random integer within range [min, max].
 ********************************************************************************/
template <typename T = int>
constexpr T GetRandomInt(const T min, const T max) {
    static_assert(std::is_integral<T>::value, 
        "Non-integer type passed to languages::utils::GetRandomInt!");
    InitRandomGenerator();
    return static_cast<T>((std::rand() % (max + 1 - min)) + min);
}

/********************************************************************************
 * @brief Provides the smallest of two numbers.
 * 
 * @param x 
 *         The first number to compare.
 * @param y 
 *         The second number to compare.
 * @return 
 *         The value of the smallest number.
 ********************************************************************************/
template <typename T = int>
constexpr T Min(const T x, const T y) {
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::Min!");
    return x <= y ? x : y;
}

/********************************************************************************
 * @brief Provides the biggest of two numbers.
 * 
 * @param x 
 *         The first number to compare.
 * @param y 
 *         The second number to compare.
 * @return 
 *         The value of the biggest number.
 ********************************************************************************/
template <typename T = int>
constexpr T Max(const T x, const T y) {
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::Max!");
    return x >= y ? x : y;
}


/********************************************************************************
 * @brief Provides the smallest of multiple numbers.
 * 
 * @param x 
 *         The first number to compare.
 * @param numbers
 *         Additional numbers to compare.
 * @return 
 *         The value of the smallest number.
 ********************************************************************************/
template <typename T = int, typename... AdditionalNumbers>
constexpr T Min(const T x, AdditionalNumbers... numbers) {
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::Min!");
    return Min(x, Min(numbers...));
}

/********************************************************************************
 * @brief Provides the biggest of multiple numbers.
 * 
 * @param x 
 *         The first number to compare.
 * @param numbers
 *         Additional numbers to compare.
 * @return 
 *         The value of the biggest number.
 ********************************************************************************/
template <typename T = int, typename... AdditionalNumbers>
constexpr T Max(const T x, const AdditionalNumbers... numbers) {
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::Max!");
    return Max(x, Max(numbers...));
}

/********************************************************************************
 * @brief Indicates if specified number exists among numbers stored in vector.
 * 
 * @param searched_number
 *        The number to search for.
 * @param num_vect
 *        Reference to vector containing the numbers to search through.
 * @return 
 *        True if the specified number was found, else false.
 ********************************************************************************/
template <typename T = int>
bool NumberFoundInVector(const T searched_number, const std::vector<T>& num_vect) {
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::NumberNotFound!");
    for (auto& number : num_vect) {
        if (number == searched_number) return true;
    }
    return false;
}

/********************************************************************************
 * @brief Reads a line from the terminal and stores in referenced string.
 * 
 * @param s
 *        Reference to string storing the entered line as text.
 * @param space
 *        Space to print after the input has been read (default = no space).
 ********************************************************************************/
inline void ReadLine(std::string& s, const char* space = "") {
    std::getline(std::cin, s);
    std::cout << space << std::endl;
    std::cin.clear();
}
} /* namespace */

/********************************************************************************
 * @brief Loads pairs of primary and target language phrases stored in file at 
 *        specified path and stores them in referenced vector.
 * 
 * @param file_path
 *        Path to file containing phrase pairs to load the vector with.
 * @param phrases
 *        Reference to vector storing the loaded phrase pairs.
 * @return
 *        The number of loaded phrases.
 ********************************************************************************/
std::size_t LoadPhrasePairs(const std::string& file_path, 
                            std::vector<std::pair<std::string, std::string>>& phrases);

/********************************************************************************
 * @brief Writes pairs of primary and target language phrases stored to file at 
 *        specified path.
 * 
 * @param file_path
 *        Destination file path that the phrase pairs are written to.
 * @param phrases
 *        Reference to vector storing the phrase pairs to write.
 * @return
 *        True if at least one phrase pair was written, else false.
 ********************************************************************************/
bool WritePhrasePairsToFile(const std::string& file_path, 
                            const std::vector<std::pair<std::string, std::string>>& phrases);

/********************************************************************************
 * @brief Reads all non-blank lines of file at specified path and stores them
 *        as text in referenced vector.
 * 
 * @param file_path
 *        Path to file containing the data to retrieve.
 * @param data
 *        Reference to vector storing the loaded lines as text.
 * @return
 *        True if at least one line was retrieved, else false.
 ********************************************************************************/
bool RetrieveFromFile(const std::string& file_path, std::vector<std::string>& data);

/********************************************************************************
 * @brief Removes potential trailing whitespaces of referenced string.
 * 
 * @param s
 *        Reference to the string whose potential whitespaces is to be removed.
 ********************************************************************************/
void RemoveTrailingWhitespaces(std::string& s);

} /* namespace utils */
} /* namespace languages */

