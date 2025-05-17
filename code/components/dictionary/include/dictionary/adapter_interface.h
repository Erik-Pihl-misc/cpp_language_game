/**
 * @brief Dictionary adapter interface implementation.
 */
#pragma once

#include <list>

#include "utils/phrase.h"

namespace language
{
namespace dictionary
{
/**
 * @brief Dictionary adapter interface for providing the file path from which to load phrases
 *        and the number of phrases to run.
 */
class AdapterInterface
{
public:
    /**
     * @brief Delete dictionary adapter.
     */
    virtual ~AdapterInterface() noexcept = default;

    /**
     * @brief Get phrases to put in the dictionary. 
     * 
     *        The phrases are paired in target and primary language.
     * 
     * @return Phrases to put in the dictionary.
     */
    virtual const std::list<Phrase> &phrases() const = 0;

    /**
     * @brief Get the number of phrases to use during the game.
     * 
     * @return Number of phrases to use during the game.
     */
    virtual std::size_t phraseCountToUse() const = 0;

    /** 
     * @brief Get the print interval in milliseconds.
     * 
     * @return The print interval in milliseconds.
     */
    virtual std::size_t printIntervalMs() const = 0;
};
} // namespace dictionary
} // namespace language