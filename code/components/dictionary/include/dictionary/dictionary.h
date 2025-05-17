/**
 * @brief Implementation of dictionary for translation between two languages.
 */
#pragma once

#include <iostream>
#include <list>

#include "utils/phrase.h"

namespace language
{
namespace dictionary
{
/** Dictionary adapter implementation. */
class AdapterInterface;

/**
 * @brief Implementation of dictionary for a translation game.
 */
class Dictionary final
{
public:
    /**
     * @brief Create new dictionary and load it with given data.
     *
     * @param[in] adapter Adapter providing information about the phrases to load.
     */
    explicit Dictionary(AdapterInterface &adapter);

    /**
     * @brief Delete dictionary.
     */
    ~Dictionary() noexcept = default;

    /**
     * @brief Provide all phrases stored in the dictionary.
     *
     * @return Vector storing all stored phrases in pairs.
     */
    const std::list<Phrase>& phrases() const noexcept;

    /**
     * @brief Provide the number of phrases stored in the dictionary.
     *
     * @return Number of phrases in the dictionary.
     */
    std::size_t phraseCount() const noexcept;

    /**
     * @brief Get the number of phrases to use during the game.
     * 
     * @return Number of phrases to use during the game.
     */
    std::size_t phraseCountToUse() const noexcept;

    /** 
     * @brief Get the print interval in milliseconds.
     * 
     * @return The print interval in milliseconds.
     */
    std::size_t printIntervalMs() const noexcept;

    /**
     * @brief Check if the dictionary is empty.
     *
     * @return True if the dictionary is empty, else false.
     */
    bool empty() const noexcept;

    /**
     * @brief Print phrases stored in the dictionary.
     *
     * @param[in] ostream Reference to the output stream (default = stdout).
     */
    void print(std::ostream& ostream = std::cout) const;

    Dictionary()                             = delete; // No default constructor.
    Dictionary(const Dictionary&)            = delete; // No copy constructor.
    Dictionary(Dictionary&&)                 = delete; // No move constructor.
    Dictionary& operator=(const Dictionary&) = delete; // No move assignment.
    Dictionary& operator=(Dictionary&&)      = delete; // No copy assignment.
    
private:
    /** Dictionary adapter implementation. */
    AdapterInterface &myAdapter;
};
} // namespace dictionary
} // namespace language