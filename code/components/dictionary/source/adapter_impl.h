/**
 * @brief Implementation details of class language::dictionary::Dictionary.
 */
#pragma once

#include <list>
#include <string>

#include "utils/phrase.h"

namespace language
{
namespace dictionary
{
/**
 * @brief Implementation details of dictionary adapter.
 */
class AdapterImpl
{
public:
    /**
     * @brief Create dictionary adapter implementation.
     * 
     * @param[in] phrases Phrases to put in the dictionary.
     */
    AdapterImpl(const std::list<Phrase> &phrases);

    /**
     * @brief Create dictionary adapter.
     * 
     * @param[in] filePath Path to the file from where to load the phrases.
     */
    AdapterImpl(const std::string &filePath);

    /**
     * @brief Create dictionary adapter.
     * 
     * @param[in] argc The number of input arguments entered from the terminal at runtime.
     * @param[in] argv Vector storing all input arguments entered from the terminal at runtime.
     */
    AdapterImpl(int argc, const char **argv);

    /**
     * @brief Delete dictionary adapter.
     */
    ~AdapterImpl() noexcept = default;

    /**
     * @brief Get phrases to put in the dictionary. 
     * 
     *        The phrases are paired in target and primary language.
     * 
     * @return Phrases to put in the dictionary.
     */
    const std::list<Phrase> &phrases() const;

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

    AdapterImpl()                                = delete; // No default constructor.
    AdapterImpl(const AdapterImpl &)             = delete; // No copy constructor.
    AdapterImpl(AdapterImpl &&)                  = delete; // No move constructor.
    AdapterImpl & operator=(const AdapterImpl &) = delete; // No move assignment.
    AdapterImpl & operator=(AdapterImpl &&)      = delete; // No copy assignment.

private:
    bool load(const std::string &filePath);
    bool load(int argc, const char **argv);
    void setPhraseCountToUse() noexcept;
    void setPhraseCountToUse(std::size_t count) noexcept;

    /** Default print interval in milliseconds. */
    static constexpr std::size_t kDefaultPrintIntervalMs{2000U};

    /** Phrases to put in the dictionary. */
    std::list<Phrase> myPhrases;

    /** The number of phrases to use during a game. */
    std::size_t myPhraseCountToUse;

    /** Print interval in milliseconds. */
    std::size_t myPrintIntervalMs;
};
} // namespace dictionary
} // namespace language