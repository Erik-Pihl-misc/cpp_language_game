/**
 * @brief Implementation details of class language::dictionary::Adapter.
 */
#include <list>
#include <memory>
#include <string>

#include "dictionary/adapter.h"
#include "adapter_impl.h"

namespace language
{
namespace dictionary
{
// ---------------------------------------------------------------------------
Adapter::Adapter(const std::list<Phrase> &phrases)
    : myImpl{std::make_unique<AdapterImpl>(phrases)}
{}

// ---------------------------------------------------------------------------
Adapter::Adapter(const std::string &filePath)
    : myImpl{std::make_unique<AdapterImpl>(filePath)}
{}

// ---------------------------------------------------------------------------
Adapter::Adapter(const int argc, const char **argv)
    : myImpl{std::make_unique<AdapterImpl>(argc, argv)}
{}

// ---------------------------------------------------------------------------
Adapter::~Adapter() noexcept = default;

// ---------------------------------------------------------------------------
const std::list<Phrase> &Adapter::phrases() const { return myImpl->phrases(); }

// ---------------------------------------------------------------------------
std::size_t Adapter::phraseCountToUse() const noexcept { return myImpl->phraseCountToUse(); }

// ---------------------------------------------------------------------------
std::size_t Adapter::printIntervalMs() const noexcept { return myImpl->printIntervalMs(); }

} // namespace dictionary
} // namespace language