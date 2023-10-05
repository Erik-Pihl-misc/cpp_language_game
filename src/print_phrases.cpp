/********************************************************************************
 * @brief Loads phrases from file at specified path and prints selected
 *        number of phrases with selected print interval.
 * 
 *        The file path must be entered after the run command, for instance
 * 
 *        ./print_phrases dir/file.txt
 * 
 *        to load phrases from "file.txt" in directory "dir" when running the 
 *        program and "print_phrases" is the name of the executable.
 * 
 *        As default, all loaded phrases are printed. Optionally the maximum 
 *        number of phrases to print can be entered after the file path.
 *        For instance, to print a maximum of ten phrases loaded from 
 *        "file.txt" when running the program "print_phrases", type
 * 
 *        ./print_phrases dir/file.txt 10
 * 
 *        As default, the print interval is set to 2000 ms. Optionally the
 *        print interval can be entered in ms after the number of phrases
 *        to print. For instance, to print a maximum of ten phrases loaded 
 *        from "file.txt" with a print interval of 500 ms when running the
 *        program "print_phrases", type
 * 
 *        ./print_phrases dir/file.txt 10 500
 ********************************************************************************/
#include <dictionary.hpp>

/********************************************************************************
 * @brief Loads phrases from specified file path (if any) and prints the 
 *        selected number of phrases with selected print interval. As default
 *        all phrases are printed with a print interval of 2000 ms.
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
    dict.PrintPhrases(argc, argv, std::cout);
    return 0;
}

