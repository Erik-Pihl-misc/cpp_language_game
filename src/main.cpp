/********************************************************************************
 * @brief Translation program for translating from a primary language to a
 *        target language. The phrases must be stored in a text file and added
 *        on separate lines. Preferably use a blank line between each phrase pair.
 * 
 *        The file path must be entered after the run command, for instance
 * 
 *        ./run_game dir/file.txt
 * 
 *        to load phrases from "file.txt" in directory "dir" when running the 
 *        program and "run_game" is the name of the executable.
 * 
 *        As default, all loaded phrases are translated. Optionally the maximum 
 *        number of phrases to translate can be entered after the file path.
 *        For instance, to translate a maximum of ten phrases loaded from 
 *        "file.txt" when running the program "run_game", type
 * 
 *        ./run_game dir/file.txt 10
 ********************************************************************************/
#include <dictionary.hpp>

/********************************************************************************
 * @brief Loads phrases from specified file path (if any) and lets the user
 *        translate from the primary language to the target language.
 *        After finishing the translations, the user is able to translate
 *        from the target language to the primary language too before the
 *        program terminates.
 * 
 * @param argc
 *        The number of input arguments entered from the terminal when
 *        running the program.
 * @param argv
 *        Reference to vector storing all input arguments entered from the 
 *        terminal when running the program.
 * @return
 *        Success code 0 if the translation program was running successfully,
 *        else error code 1.
 ********************************************************************************/
int main(const int argc, const char** argv) {
    languages::Dictionary dict{argc, argv};
    if (dict.Empty()) return 1;
    dict.TranslateToTarget(dict.GetMaxNumPhrasesFromTerminal(argc, argv));
    return 0;
}


