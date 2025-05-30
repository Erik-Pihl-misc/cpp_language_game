/**
 * @brief Implementation details of class language::game::GameImpl.
 */
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "dictionary/adapter_interface.h"
#include "dictionary/dictionary.h"
#include "game_impl.h"
#include "utils/phrase.h"
#include "utils/utils.h"

namespace language
{
namespace game
{
namespace
{
bool performAnalysis();
void removeAdditionalPhraseInfo(std::string& str);
bool playAgainInReverse();
bool response();
const std::string errorFilePath();
} // namespace

// ---------------------------------------------------------------------------
GameImpl::GameImpl(dictionary::AdapterInterface &dictionaryAdapter)
    : myDictionary{dictionaryAdapter}
    , myGuessCount{}
    , myErrorCount{}
    , myPhraseIndexes{}
    , myReverse{false}
    , myErrorsWrittenToFile{false}
{}   

// ---------------------------------------------------------------------------
bool GameImpl::play(const bool reverse)
{
    // Return false if no phrases are present.
    if (myDictionary.empty()) { return false; }

    myReverse             = reverse;
    myErrorsWrittenToFile = false;

    std::vector<Phrase> remainingPhrases{phrases()};
    preparePhrasesForSession(remainingPhrases);
    auto phraseBackup{remainingPhrases};

    printStartInfo();
    runRound(remainingPhrases);

    // Play the game again if desired.
    if (playAgainInReverse())
    {
        myReverse = !myReverse;
        runRound(phraseBackup);
    }

    // Return true to indicate success.
    return true;
}

// ---------------------------------------------------------------------------
std::vector<Phrase> GameImpl::phrases() const 
{ 
    const auto &phraseList{myDictionary.phrases()};
    return std::vector<Phrase>{phraseList.begin(), phraseList.end()}; 
}

// ---------------------------------------------------------------------------
void GameImpl::runRound(std::vector<Phrase>& phrases)
{
    while (!phrases.empty() && (correctAnswerCount() < phraseCountForSession())) 
    { 
        runRemainingPhrases(phrases); 
    }
    printResults();
    clearStats();
}

// ---------------------------------------------------------------------------
void GameImpl::runRemainingPhrases(std::vector<Phrase>& phrases)
{
    std::vector<Phrase> incorrectPhrases{};
    initPhraseIndexes(phrases.size());

    for (const auto& i : myPhraseIndexes)
    {
        printCurrentStatus();
        runNextPhrase(phrases[i], incorrectPhrases);
        if (correctAnswerCount() >= phraseCountForSession()) { return; }
    }

    writeErrorsToFile(incorrectPhrases);
    phrases = incorrectPhrases;
}

// ---------------------------------------------------------------------------
void GameImpl::runNextPhrase(const Phrase& phrase, std::vector<Phrase>& incorrectPhrases)
{
    const auto currentPhrase{!myReverse ? phrase.primary : phrase.target};
    std::cout << "Translate the following phrase:\n" << currentPhrase << "\n"; 
    std::string guess{};

    utils::readLine(guess);
    utils::removeTrailingWhitespaces(guess);
    checkGuess(guess, phrase, incorrectPhrases);
}

// ---------------------------------------------------------------------------
void GameImpl::checkGuess(const std::string& guess, const Phrase& phrase, 
                          std::vector<Phrase>& incorrectPhrases)
{
    auto answer{myReverse ? phrase.primary : phrase.target};
    removeAdditionalPhraseInfo(answer);

    if (guess == answer) { std::cout << "Correct answer!\n\n"; }
    else
    {
        std::cout << "Wrong answer!\n";
        std::cout << "Your guess:\t" << guess << "\n";
        std::cout << "Correct answer:\t" << answer << "\n\n";

        incorrectPhrases.push_back(phrase);
        ++myErrorCount;
        if (performAnalysis()) { analyzeError(guess, answer); }
    }
    ++myGuessCount;
}

// ---------------------------------------------------------------------------
void GameImpl::printStartInfo() const noexcept
{
    const auto loadedPhrases{utils::min<std::size_t>(phraseCountForSession(), myDictionary.phraseCount())};
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "Starting translation game!\n";
    std::cout << loadedPhrases << " phrases have been loaded!\n";
    std::cout << "--------------------------------------------------------------------------------\n\n";
}

// ---------------------------------------------------------------------------
void GameImpl::printCurrentStatus() const noexcept
{
    if (0U == myGuessCount) { return; }
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "Number of guesses:\t\t" << myGuessCount << "\n";
    std::cout << "Number of correct answers:\t" << correctAnswerCount() << "\n";
    std::cout << "Number of incorrect guesses:\t" << myErrorCount << "\n";
    std::cout << "Number of phrases remaining:\t" << phraseCountForSession() - correctAnswerCount() << "\n";
    std::cout << "--------------------------------------------------------------------------------\n\n";
}

// ---------------------------------------------------------------------------
void GameImpl::printResults() const noexcept
{
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "Total number of guesses:\t" << myGuessCount << "\n";
    std::cout << "Number of correct answers:\t" << correctAnswerCount() << "\n";
    std::cout << "Number of incorrect answers:\t" << myErrorCount << "\n";
    std::cout << "Success rate:\t\t\t";

    if (precisionContainsDecimals())
    {
        std::cout << std::fixed << std::setprecision(1U) << getPrecision() << " %\n";
    }
    else { std::cout << static_cast<int>(getPrecision()) << " %\n"; }
    std::cout << "--------------------------------------------------------------------------------\n\n";
}

// ---------------------------------------------------------------------------
void GameImpl::setPhraseIndexCount(const std::size_t size) noexcept
{
    myPhraseIndexes.resize(size);

    for (std::size_t i{}; i < myPhraseIndexes.size(); ++i) 
    { 
        myPhraseIndexes[i] = i; 
    }
}

// ---------------------------------------------------------------------------
void GameImpl::shufflePhraseIndexes() noexcept
{
    for (std::size_t i{}; i < myPhraseIndexes.size(); ++i)
    {
        const auto r{utils::getRandomInt<std::size_t>(myPhraseIndexes.size())};
        const auto temp{myPhraseIndexes[i]};
        myPhraseIndexes[i] = myPhraseIndexes[r];
        myPhraseIndexes[r] = temp;
    }
}

// ---------------------------------------------------------------------------
void GameImpl::initPhraseIndexes(const std::size_t size) noexcept
{
    setPhraseIndexCount(size);
    shufflePhraseIndexes();
}

// ---------------------------------------------------------------------------
void GameImpl::analyzeError(const std::string& guess, const std::string& answer)
{
    auto getOutput = [](const char c, const bool upper_case = false)
    {
        return c != ' ' ? std::string{'"', c, '"'} :
               upper_case ? std::string{"Blank line"} : std::string{"blank line"};
    };
    for (std::size_t i{}; i < answer.size(); ++i)
    {
        if (i < guess.size())
        {
            if (guess[i] != answer[i])
            {
                std::cout << getOutput(guess[i], true) << " at index " << i
                          << " should be replaced with " << getOutput(answer[i]) << "\n\n";
            }
        }
    }
}

// ---------------------------------------------------------------------------
void GameImpl::clearStats() noexcept
{
    myGuessCount = 0U;
    myErrorCount = 0U;
}

// ---------------------------------------------------------------------------
void GameImpl::preparePhrasesForSession(std::vector<Phrase>& phrases) 
{
    utils::initRandomGenerator();

    for (std::size_t i{}; i < phraseCountForSession(); ++i) 
    {
        const auto r{static_cast<std::size_t>(std::rand() % phrases.size())};
        const auto temp{phrases[i]};
        phrases[i] = phrases[r];
        phrases[r] = temp;
    }
    if (phrases.size() > phraseCountForSession()) { phrases.resize(phraseCountForSession()); }
}

// ---------------------------------------------------------------------------
double GameImpl::getPrecision() const noexcept
{
    return (myGuessCount - myErrorCount) / static_cast<double>(myGuessCount) * 100.0;
}

// ---------------------------------------------------------------------------
bool GameImpl::precisionContainsDecimals() const noexcept
{ 
    return (getPrecision() - static_cast<int>(getPrecision()));
}

// ---------------------------------------------------------------------------
std::size_t GameImpl::correctAnswerCount() const noexcept { return myGuessCount - myErrorCount; }

// ---------------------------------------------------------------------------
std::size_t GameImpl::phraseCountForSession() const { return myDictionary.phraseCountToUse(); }

// ---------------------------------------------------------------------------
void GameImpl::writeErrorsToFile(const std::vector<Phrase>& errors)
{
    if (!errors.empty() && !myErrorsWrittenToFile)
    {
        const std::string errorPath{errorFilePath()};
        utils::writePhrasesToFile(errorPath, errors);   
        myErrorsWrittenToFile = true;

        if (1U == errors.size())
        {
            std::cout << "One incorrectly guessed phrase "
                "has been written to file \"" << errorPath << "\"!\n\n";
        }
        else
        {
            std::cout << errors.size() << " incorrectly guessed phrases "
                "have been written to file \"" << errorPath << "\"!\n\n";
        }
    }
}

namespace
{
// ---------------------------------------------------------------------------
bool performAnalysis() 
{
    std::string s{};
    std::cout << "Analyze error? Y/n\n";
    return response();
}

// ---------------------------------------------------------------------------
void removeAdditionalPhraseInfo(std::string& str) 
{
    for (std::size_t i{}; i < str.size(); ++i) 
    {
        if ('(' == str[i]) 
        {
            str = str.std::string::substr(0U, i);
            utils::removeTrailingWhitespaces(str);
            break;
        }
    }
}

// ---------------------------------------------------------------------------
bool playAgainInReverse() 
{
    std::cout << "Do you wanna play the game in reverse? Y/n\n";
    return response();
}

// ---------------------------------------------------------------------------
bool response()
{
    std::string s{};
    while (1)
    {
        utils::readLine(s);
        if (s[0U] == 'Y' || s[0U] == 'y') { return true; }
        else if (s[0U] == 'N' || s[0U] == 'n') { return false; }
        else { std::cout << "Invalid input, try again!\n"; }
    }
}

// ---------------------------------------------------------------------------
const std::string errorFilePath()
{
    constexpr const char* errorRoot{"errors"};
    constexpr const char* format{".txt"};
    constexpr const char* defaultPath{"errors1.txt"};

    for (std::size_t fileId{1U}; 0U != fileId; ++fileId)
    {
        std::stringstream filePath{};
        filePath << errorRoot << fileId << format;
        if (!utils::fileExists(filePath.str())) { return filePath.str(); }
    }
    return defaultPath;
}
} // namespace
} // namespace game
} // namespace language
