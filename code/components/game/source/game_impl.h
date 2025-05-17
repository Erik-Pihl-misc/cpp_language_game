/**
 * @brief Implementation details of class language::Game.
 */
#pragma once

#include <limits>
#include <string>
#include <vector>

#include "dictionary/dictionary.h"
#include "utils/phrase.h"

namespace language
{
namespace dictionary
{
/** Dictionary adapter implementation. */
class AdapterInterface;

/** Dictionary implementation. */
class Dictionary;
} // namespace dictionary

namespace game
{
/**
 * @brief Implementation details of translation game.
 */
class GameImpl
{
public:
    /**
     * @brief Create language game.
     *
     * @param[in] adapter Adapter providing information about the phrases to load.
     */
    explicit GameImpl(dictionary::AdapterInterface &dictionaryAdapter);

    /**
     * @brief Play the game.
     * 
     * @param reverse Play the game in reverse (default = false).
     * 
     * @return True if the game was played, otherwise false.
     */
    bool play(const bool reverse);

    GameImpl()                           = delete; // No default constructor.
    GameImpl(const GameImpl&)            = delete; // No copy constructor.
    GameImpl(GameImpl&&)                 = delete; // No move constructor.
    GameImpl& operator=(const GameImpl&) = delete; // No move assignment.
    GameImpl& operator=(GameImpl&&)      = delete; // No copy assignment.
    
private:
    std::vector<Phrase> phrases() const;
    void runRound(std::vector<Phrase>& phrases);
    void runRemainingPhrases(std::vector<Phrase>& phrases);
    void runNextPhrase(const Phrase& phrase, std::vector<Phrase>& incorrectPhrases);
    void checkGuess(const std::string& guess, const Phrase& phrase,
                    std::vector<Phrase>& incorrectPhrases);
    void printStartInfo() const noexcept;
    void printCurrentStatus() const noexcept;
    void printResults() const noexcept;
    void setPhraseIndexCount(const std::size_t size) noexcept;
    void shufflePhraseIndexes() noexcept;
    void initPhraseIndexes(const std::size_t size) noexcept;
    void analyzeError(const std::string& guess, const std::string& answer);
    void clearStats() noexcept;
    double getPrecision() const noexcept;
    bool precisionContainsDecimals() const noexcept;
    std::size_t correctAnswerCount() const noexcept;
    void preparePhrasesForSession(std::vector<Phrase>& phrases);
    std::size_t phraseCountForSession() const;

    static constexpr std::size_t kMaxPhraseCount{std::numeric_limits<std::size_t>::max()};

    /** Dictionary implementation. */
    dictionary::Dictionary myDictionary;

    /** The number of made guesses. */
    std::size_t myGuessCount;

    /** The number of errors. */
    std::size_t myErrorCount;

    /** Vector holding randomized phrases indexes. */
    std::vector<std::size_t> myPhraseIndexes;

    /** Indicate whether to play the game in reverse. */
    bool myReverse;
};
} // namespace game
} // namespace language