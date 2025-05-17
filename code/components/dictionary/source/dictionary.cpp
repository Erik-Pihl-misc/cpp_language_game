/**
 * @brief Implementation details of class language::dictionary::Dictionary.
 */
#include <chrono>
#include <iostream>
#include <list>
#include <thread>

#include "dictionary/adapter.h"
#include "dictionary/dictionary.h"
#include "utils/phrase.h"

namespace language
{
namespace dictionary
{
/** Dictionary adapter implementation. */
class AdapterInterface;

// ---------------------------------------------------------------------------
Dictionary::Dictionary(AdapterInterface &adapter)
    : myAdapter{adapter}
{}

// ---------------------------------------------------------------------------
const std::list<Phrase>& Dictionary::phrases() const noexcept { return myAdapter.phrases(); }

// ---------------------------------------------------------------------------
std::size_t Dictionary::phraseCount() const noexcept { return myAdapter.phrases().size(); }

// ---------------------------------------------------------------------------
std::size_t Dictionary::phraseCountToUse() const noexcept { return myAdapter.phraseCountToUse(); }

// ---------------------------------------------------------------------------
std::size_t Dictionary::printIntervalMs() const noexcept { return myAdapter.printIntervalMs(); }

// ---------------------------------------------------------------------------
bool Dictionary::empty() const noexcept { return myAdapter.phrases().empty(); }

// ---------------------------------------------------------------------------
void Dictionary::print(std::ostream& ostream) const
{
    std::size_t printedPhrases{};

    for (const auto &phrase : myAdapter.phrases())
    {
        if (phraseCountToUse() <= printedPhrases++) { break; }
        ostream << phrase.primary << "\n";
        ostream << phrase.target << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(printIntervalMs()));
    }
}
} // namespace dictionary
} // namespace language