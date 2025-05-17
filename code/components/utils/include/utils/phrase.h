/**
 * @brief Phrase implementation for language game.
 */
#pragma once

#include <string>

namespace language
{
/**
 * @brief Struct representing a phrase in a primary and a target language.
 */
struct Phrase
{
    /** Primary language phrase. */
    std::string primary;

    /** Target language phrase. */
    std::string target;

    /**
     * @brief Match this phrase with another phrase.
     * 
     * @param[in] other Other phrase to match with.
     * 
     * @return True if the phrases match, otherwise false.
     */
    bool operator==(const Phrase &other) const
    {
        return (other.primary == primary) && (other.target == target);
    }
};
} // namespace language