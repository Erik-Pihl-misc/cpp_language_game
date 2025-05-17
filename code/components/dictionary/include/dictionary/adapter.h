/**
 * @brief Dictionary adapter implementation.
 */
#pragma once

#include <list>
#include <memory>
#include <string>

#include "adapter_interface.h"
#include "utils/phrase.h"

namespace language
{
namespace dictionary
{
/** Dictionary adapter implementation. */
class AdapterImpl;

/**
 * @brief Dictionary adapter for providing the file path from which to load phrases and the number
 *        of phrases to run.
 */
class Adapter final : public AdapterInterface
{
public:
    /**
     * @brief Create dictionary adapter.
     * 
     * @param[in] phrases Phrases to put in the dictionary.
     */
    Adapter(const std::list<Phrase> &phrases);

    /**
     * @brief Create dictionary adapter.
     * 
     * @param[in] filePath Path to the file from where to load the phrases.
     */
    Adapter(const std::string &filePath);

    /**
     * @brief Create dictionary adapter.
     * 
     * @param[in] argc The number of input arguments entered from the terminal at runtime.
     * @param[in] argv Vector storing all input arguments entered from the terminal at runtime.
     */
    Adapter(int argc, const char **argv);

    /**
     * @brief Delete dictionary adapter.
     */
    ~Adapter() noexcept override;

    /**
     * @brief Get phrases to put in the dictionary. 
     * 
     *        The phrases are paired in target and primary language.
     * 
     * @return Phrases to put in the dictionary.
     */
    const std::list<Phrase> &phrases() const override;

    /**
     * @brief Get the number of phrases to use during the game.
     * 
     * @return Number of phrases to use during the game.
     */
    std::size_t phraseCountToUse() const noexcept override;

    /** 
     * @brief Get the print interval in milliseconds.
     * 
     * @return The print interval in milliseconds.
     */
    std::size_t printIntervalMs() const noexcept override;

    Adapter()                            = delete; // No default constructor.
    Adapter(const Adapter &)             = delete; // No copy constructor.
    Adapter(Adapter &&)                  = delete; // No move constructor.
    Adapter & operator=(const Adapter &) = delete; // No move assignment.
    Adapter & operator=(Adapter &&)      = delete; // No copy assignment.

private:
    /** Dictionary adapter implementation. */
    std::unique_ptr<AdapterImpl> myImpl;
};
} // namespace dictionary
} // namespace language