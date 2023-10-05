/********************************************************************************
 * @brief Utility program for removing potential duplicates in a text file.
 *        The file path must be entered after the run command, for instance
 * 
 *        ./utilities/remove_duplicates dir/file.txt
 * 
 *        to remove duplicates from "file.txt" in directory "dir" when running 
 *        the program, "remove_duplicates" is the name of the executable and 
 *        utilities is the directory it's located in.
 ********************************************************************************/
#include <dictionary.hpp>

/********************************************************************************
 * @brief Removes potential duplicate phrases in specified file, whose path
 *        is entered via the terminal.
 * 
 * @param argc
 *        The number of input arguments entered from the terminal when
 *        running the program.
 * @param argv
 *        Reference to vector storing all input arguments entered from the 
 *        terminal when running the program.
 * @return
 *        Success code 0 if potential duplicates were removed from the specified
 *        file, else error code 1.
 ********************************************************************************/
int main(const int argc, const char** argv) {
    return languages::Dictionary::ClearDuplicatesInFile(argc, argv) ? 0 : 1;
}