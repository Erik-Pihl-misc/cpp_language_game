/**
 * @brief Implementation of language game.
 */
#pragma once

#include <memory>

namespace language
{
namespace dictionary
{
/** Dictionary adapter implementation. */
class AdapterInterface; 
} // namespace dictionary

namespace game
{
/** Game implementation. */
class GameImpl;

/**
 * @brief Implementation of translation game.
 */
class Game final
{
public:
    /**
     * @brief Create language game.
     *
     * @param[in] adapter Adapter providing information about the phrases to load.
     */
    explicit Game(dictionary::AdapterInterface &dictionaryAdapter);

    /**
     * @brief Delete game.
     */
    ~Game() noexcept;

    /**
     * @brief Play the game.
     * 
     * @param reverse Play the game in reverse (default = false).
     * 
     * @return True if the game was played, otherwise false.
     */
    bool play(bool reverse = false);

    Game()                       = delete; // No default constructor.
    Game(const Game&)            = delete; // No copy constructor.
    Game(Game&&)                 = delete; // No move constructor.
    Game& operator=(const Game&) = delete; // No move assignment.
    Game& operator=(Game&&)      = delete; // No copy assignment.
    
private:

    /** Game implementation. */
    std::unique_ptr<GameImpl> myImpl;
};
} // namespace game
} // namespace language