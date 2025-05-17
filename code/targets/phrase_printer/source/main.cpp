/**
 * @brief Print phrases loaded from a file. Set the number of phrases and print interval as needed.
 * 
 *        Store the phrases to print in a text file, one pair per line. 
 *        Please use a blank line between each pair.
 *        
 *        Enter the file path after the run command. For example, to print phrases from 'file.txt'
 *        in directory 'dir' when running 'PhrasePrinter', use the following command:
 *
 *        ./PhrasePrinter dir/file.txt
 * 
 *        Print all loaded phrases by default. Optionally limit the number of phrases to print
 *        after the file path. For example, to translate only ten phrases from the aforementioned 
 *        file, use the following command:
 * 
 *        ./PhrasePrinter dir/file.txt 10
 *
 *        Optionally set the print interval in ms after the number of phrases. For example, 
 *        to print ten phrases with a 500 ms interval, use the following command:
 * 
 *        ./PhasePrinter dir/file.txt 10 500
 */
#include "dictionary/adapter.h"
#include "dictionary/dictionary.h"

using namespace language;

/**
 * @brief Load phrases from file and print the selected number with the chosen print interval.
 *        Print all phrases with a 2000 ms interval by default.
 *
 * @param argc  Number of input arguments from the terminal.
 * @param argv  Vector of input arguments from the terminal.
 * @return      Return 0 if the program ran successfully, else return 1.
 */
int main(const int argc, const char** argv) 
{
    dictionary::Adapter adapter{argc, argv};
    dictionary::Dictionary dictionary{adapter};
    if (dictionary.empty()) { return 1; }
    dictionary.print();
    return 0;
}
