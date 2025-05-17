/**
 * @brief Implementation details of class language::dictionary::AdapterImpl.
 */
#include <iostream>
#include <limits>
#include <list>
#include <string>

#include "adapter_impl.h"
#include "utils/phrase.h"
#include "utils/utils.h"

namespace language
{
namespace dictionary
{
namespace
{
bool removeDuplicates(std::list<Phrase> &phrases);
void updateFile(const std::string &filePath, const std::list<Phrase> &phrases);
} // namespace

// ---------------------------------------------------------------------------
AdapterImpl::AdapterImpl(const std::list<Phrase> &phrases)
    : myPhrases{phrases}
    , myPhraseCountToUse{}
    , myPrintIntervalMs{kDefaultPrintIntervalMs}
{
    removeDuplicates(myPhrases);
    setPhraseCountToUse();
}

// ---------------------------------------------------------------------------
AdapterImpl::AdapterImpl(const std::string &filePath)
    : myPhrases{}
    , myPhraseCountToUse{}
    , myPrintIntervalMs{kDefaultPrintIntervalMs}
{
    load(filePath);
}

// ---------------------------------------------------------------------------
AdapterImpl::AdapterImpl(const int argc, const char **argv)
    : myPhrases{}
    , myPhraseCountToUse{}
    , myPrintIntervalMs{kDefaultPrintIntervalMs}
{
    load(argc, argv);
}

// ---------------------------------------------------------------------------
const std::list<Phrase> &AdapterImpl::phrases() const { return myPhrases; }

// ---------------------------------------------------------------------------
std::size_t AdapterImpl::phraseCountToUse() const noexcept { return myPhraseCountToUse; }

// ---------------------------------------------------------------------------
std::size_t AdapterImpl::printIntervalMs() const noexcept { return myPrintIntervalMs; }

// ---------------------------------------------------------------------------
bool AdapterImpl::load(const std::string& filePath)
{
    if (0U == utils::loadPhrasesFromFile(filePath, myPhrases))
    {
        std::cerr << "\nFile \"" << filePath << "\" wasn't found or contains insufficient data!\n\n";
        return false;
    }

    // Remove duplicate phrases, update file is duplicates were found.
    if (removeDuplicates(myPhrases)) { updateFile(filePath, myPhrases); }
    setPhraseCountToUse();

    std::cout << "\nLanguage data from file \"" << filePath << "\" successfully loaded!\n\n";
    return true;
}

// ---------------------------------------------------------------------------
bool AdapterImpl::load(const int argc, const char** argv)
{
    if (1 >= argc)
    {
        std::cerr << "Cannot load dictionary due to missing file path!\n\n";
        return false;
    }
    const auto filePath{argv[1U]};
    load(filePath);

    // Get number of phrases to run during the game.
    if (3 <= argc)
    {
        const auto phraseCount{static_cast<std::size_t>(std::atoi(argv[2U]))};
        setPhraseCountToUse(static_cast<std::size_t>(std::atoi(argv[2U])));
    }

    // Get the phrase interval in milliseconds.
    if (4 <= argc) { myPrintIntervalMs = static_cast<std::size_t>(std::atoi(argv[3U])); }
    return !myPhrases.empty();
}

// ---------------------------------------------------------------------------
void AdapterImpl::setPhraseCountToUse() noexcept { myPhraseCountToUse = myPhrases.size(); }

// ---------------------------------------------------------------------------
void AdapterImpl::setPhraseCountToUse(const std::size_t phraseCount) noexcept
{
    myPhraseCountToUse = (0U != phraseCount) ? phraseCount : myPhrases.size();
}

namespace
{
// ---------------------------------------------------------------------------
bool removeDuplicates(std::list<Phrase> &phrases)
{
    bool duplicateFound{false};
    if (phrases.empty()) { return duplicateFound; }

    for (auto i{phrases.begin()}; i != std::prev(phrases.end()); ++i)
    {
        for (auto j{std::next(i)}; j != phrases.end(); )
        {
            if (*i == *j) 
            { 
                // Put next element at address j is pointing at on match.
                j = phrases.erase(j); 
                duplicateFound = true;
            }
            else { ++j; }
        }
    }
    return duplicateFound;
}

// ---------------------------------------------------------------------------
void updateFile(const std::string &filePath, const std::list<Phrase> &phrases)
{
    utils::writePhrasesToFile(filePath, phrases);
}
} // namespace
} // namespace dictionary
} // namespace language