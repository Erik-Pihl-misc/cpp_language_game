/**
 * @brief Miscellaneous utility functions for language game.
 */
#pragma once

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>
#include <type_traits>

#include "phrase.h"

namespace language
{
namespace utils
{
namespace
{

// ---------------------------------------------------------------------------
void initRandomGenerator() noexcept
{
    // Only initialize the random generator once.
    static bool isInitialized{false};
    if (isInitialized) { return; }

    // Initialize the random generator.
    std::srand(std::time(nullptr));
    isInitialized = true;
}

/**
 * @brief Generate a random integer within the specified span counted from 0.
 *
 * @tparam T The integral type to use for the return value.
 * @param[in] range The range of permitted integers, which corresponds to [0, range - 1].
 *
 * @return Random integer within range [0, range - 1].
 */
template <typename T = int>
constexpr T getRandomInt(const T range) noexcept
{
    static_assert(std::is_integral<T>::value, 
        "Non-integer type passed to languages::utils::getRandomInt!");
    initRandomGenerator();
    return static_cast<T>(std::rand() % range);
}

/**
 * @brief Generate a random integer within the specified range [min, max].
 *
 * @tparam T The integral type to use for the return value.
 * @param[in] min The minimum value of the random integer.
 * @param[in] max The maximum value of the random integer.
 *
 * @return Random integer within range [min, max].
 */
template <typename T = int>
constexpr T getRandomInt(const T min, const T max) noexcept
{
    static_assert(std::is_integral<T>::value, 
        "Non-integer type passed to languages::utils::getRandomInt!");
    initRandomGenerator();
    return static_cast<T>((std::rand() % (max + 1 - min)) + min);
}

/**
 * @brief Return the smallest of two numbers.
 *
 * @tparam T The arithmetic type to use for the comparison and return value.
 * @param[in] x The first number to compare.
 * @param[in] y The second number to compare.
 *
 * @return The value of the smallest number.
 */
template <typename T = int>
constexpr T min(const T x, const T y) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::min!");
    return x <= y ? x : y;
}

/**
 * @brief Return the biggest of two numbers.
 *
 * @tparam T The arithmetic type to use for the comparison and return value.
 * @param[in] x The first number to compare.
 * @param[in] y The second number to compare.
 *
 * @return The value of the biggest number.
 */
template <typename T = int>
constexpr T max(const T x, const T y) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::max!");
    return x >= y ? x : y;
}

/**
 * @brief Return the smallest of multiple numbers.
 *
 * @tparam T The arithmetic type to use for the comparison and return value.
 * @tparam AdditionalNumbers Variadic template parameter for additional numbers.
 * @param[in] x The first number to compare.
 * @param[in] numbers Additional numbers to compare.
 *
 * @return The value of the smallest number.
 */
template <typename T = int, typename... AdditionalNumbers>
constexpr T min(const T x, AdditionalNumbers... numbers) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::min!");
    return min(x, min(numbers...));
}

/**
 * @brief Return the biggest of multiple numbers.
 *
 * @tparam T The arithmetic type to use for the comparison and return value.
 * @tparam AdditionalNumbers Variadic template parameter for additional numbers.
 * @param[in] x The first number to compare.
 * @param[in] numbers Additional numbers to compare.
 *
 * @return The value of the biggest number.
 */
template <typename T = int, typename... AdditionalNumbers>
constexpr T max(T x, const AdditionalNumbers... numbers) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::max!");
    return max(x, max(numbers...));
}

/**
 * @brief Check if the specified number exists among numbers stored in the vector.
 *
 * @tparam T The arithmetic type of the numbers to search for.
 * @param[in] searchedNumber The number to search for.
 * @param[in] numbers Reference to vector containing the numbers to search through.
 *
 * @return True if the specified number was found, else false.
 */
template <typename T = int>
bool numberFoundInVector(T searchedNumber, const std::vector<T>& numbers) noexcept
{
    static_assert(std::is_arithmetic<T>::value, 
        "Non-arithmetic type passed to languages::utils::numberFoundInVector!");
    for (auto& number : numbers)
    {
        if (number == searchedNumber) { return true; }
    }
    return false;
}
} // namespace
/**
 * @brief Read a line from the terminal and store it in the referenced string.
 *
 * @param[out] str Reference to string storing the entered line as text.
 * @param[in] space Space to print after the input has been read (default = no space).
 *
 */
void readLine(std::string& str, const char* space = "");

/**
 * @brief Load phrases in primary and target language from file and store them in given vector.
 *
 * @param[in] filePath Path to file containing phrase pairs to load the vector with.
 * @param[out] phrases Reference to vector storing the loaded phrase pairs.
 * @return Number of loaded phrases.
 */
std::size_t loadPhrasesFromFile(const std::string& filePath, std::list<Phrase>& phrases);

/**
 * @brief Write phrases in primary and target language to a file.
 *
 * @param[in] filePath Path to the file where phrase pairs will be written.
 * @param[in] phrases Vector containing the phrases to write to the file.
 * @return True if writing was successful, false otherwise.
 */
bool writePhrasesToFile(const std::string& filePath, const std::list<Phrase>& phrases);

/**
 * @brief Retrieve non-empty lines from a file and store them in a vector.
 *
 * @param[in] filePath Path to the file to read from.
 * @param[out] data Vector to store the non-empty lines read from the file.
 * @return True if at least one line was loaded, false otherwise.
 */
bool retrieveFromFile(const std::string& filePath, std::vector<std::string>& data);

/**
 * @brief Remove trailing whitespace characters from a string.
 *
 * @param[in,out] str String to remove trailing whitespaces from.
 */
void removeTrailingWhitespaces(std::string& str);

} // namespace utils
} // namespace language
