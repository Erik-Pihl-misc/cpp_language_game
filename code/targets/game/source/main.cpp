/**
 * @brief Run translation program from primary to target language.
 * 
 *        To play the game, store phrases in a text file, one pair per line. 
 *        Please use a blank line between each pair.
 *        
 *        Enter the file path after the run command. For example, to load phrases from 'file.txt'
 *        in directory 'dir' when running 'LanguageGame', use the following command:
 *
 *        ./LanguageGame dir/file.txt
 * 
 *        Translate all loaded phrases by default. Optionally set the number of phrases
 *        to translate after the file path. For example, to translate only ten phrases from the
 *        aforementioned file, use the following command:
 * 
 *        ./LanguageGame dir/file.txt 10
 */
#include "dictionary/adapter.h"
#include "game/game.h"

using namespace language;

/**
 * @brief Load phrases from file and translate from primary to target language.
 *        After finishing, choose to translate from target to primary language before exit.
 *
 * @param[in] argc  Number of input arguments from the terminal.
 * @param[in] argv  Vector of input arguments from the terminal.
 *
 * @return Return 0 if the program ran successfully, else return 1.
 */
int main(const int argc, const char** argv) 
{
    dictionary::Adapter adapter{argc, argv};
    game::Game game{adapter};
    return game.play() ? 0 : 1;
}
