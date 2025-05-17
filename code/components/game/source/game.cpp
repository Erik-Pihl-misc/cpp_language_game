/**
 * @brief Implementation details of class language::game::Game.
 */
#include <memory>

#include "game/game.h"
#include "game_impl.h"

namespace language
{
namespace game
{
// ---------------------------------------------------------------------------
Game::Game(dictionary::AdapterInterface &dictionaryAdapter)
    : myImpl{std::make_unique<GameImpl>(dictionaryAdapter)}
{}

// ---------------------------------------------------------------------------
Game::~Game() noexcept = default;

// ---------------------------------------------------------------------------
bool Game::play(const bool reverse) { return myImpl->play(reverse); }

} // namespace game
} // namespace language