/********************************************************************************
 * @brief Dictionary for translation between two languages.
 ********************************************************************************/
#pragma once

#include <utils.hpp>
#include <limits>
#include <thread>
#include <chrono>
#include <ctime>

namespace languages {

/********************************************************************************
 * @brief Class for implementation of dictionary for translation game.
 ********************************************************************************/
class Dictionary {
  public:

    /********************************************************************************
     * @brief Creates empty dictionary.
     ********************************************************************************/
    Dictionary(void) = default;

    /********************************************************************************
     * @brief Creates new dictionary and loads it with data read from file at
     *        specified path.
     * 
     * @param file_path
     *        Path to file containing data to load the dictionary with.
     * @param print_success
     *        Indicates if a success message shall be printed in the terminal after
     *        successful load of the dictionary (default = true).
     ********************************************************************************/
    Dictionary(const std::string& file_path, const bool print_success = true);

    /********************************************************************************
     * @brief Loads dictionary with phrases stored in file at path entered from
     *        the terminal.
     * 
     * @note  The file path must be entered after the run command, for instance
     * 
     *        ./run_game file.txt
     * 
     *        to load phrases from "file.txt" when running the program and
     *        "run_game" is the name of the executable.
     * 
     * @param argc
     *        The number of input arguments entered from the terminal when
     *        running the program.
     * @param argv
     *        Reference to vector storing all input arguments entered from the 
     *        terminal when running the program.
     * @param print_success
     *        Indicates if a success message shall be printed in the terminal after
     *        successful load of the dictionary (default = true).
     ********************************************************************************/
    Dictionary(const int argc, const char** argv, const bool print_success = true);

    /********************************************************************************
     * @brief Provides all phrases stored in the dictionary.
     * 
     * @return
     *        Reference to vector storing all stored phrases in pairs.
     ********************************************************************************/
    const std::vector<std::pair<std::string, std::string>>& Phrases(void) const { return phrases_; }

    /********************************************************************************
     * @brief Provides the number of phrases stored in the dictionary.
     * 
     * @return
     *        The number of phrases in the dictionary.
     ********************************************************************************/
    std::size_t NumPhrases(void) const { return max_num_phrases_ <= phrases_.size() ?
                                                max_num_phrases_ : phrases_.size(); }

    /********************************************************************************
     * @brief Indicates if the dictionary is empty.
     * 
     * @return
     *        True if the dictionary is empty, else false.
     ********************************************************************************/
    bool Empty(void) const { return phrases_.size() == 0; }

    /********************************************************************************
     * @brief Loads dictionary with data stored in file at specified path.
     * 
     * @param file_path
     *        Path to file containing data to load the dictionary with.
     * @param print_success
     *        Indicates if a success message shall be printed in the terminal after
     *        successful load of the dictionary (default = true).
     * @return
     *        True if the data was loaded from the file, else false.
     ********************************************************************************/
    bool Load(const std::string& file_path, const bool print_success = true);

    /********************************************************************************
     * @brief Loads dictionary with data stored in file at path entered from
     *        the terminal.
     * 
     * @note  The file path must be entered after the run command, for instance
     * 
     *        ./run_game file.txt
     * 
     *        to load phrases from "file.txt" when running the program and
     *        "run_game" is the name of the executable.
     * 
     * @param argc
     *        The number of input arguments entered from the terminal when
     *        running the program.
     * @param argv
     *        Reference to vector storing all input arguments entered from the 
     *        terminal when running the program.
     * @param print_success
     *        Indicates if a success message shall be printed in the terminal after
     *        successful load of the dictionary (default = true).
     * @return
     *        True if the data was loaded, else false.
     ********************************************************************************/
    bool Load(const int argc, const char** argv, const bool print_success = true);

   /********************************************************************************
     * @brief Provides a random phrase stored in the dictionary.
     * 
     * @return
     *        Reference to a pair containing a random phrase in two languages.
     ********************************************************************************/
    const std::pair<std::string, std::string>& GetRandomPhrase(void) const;

    /********************************************************************************
     * @brief Prints selected number of phrases with specified print interval.
     *        As default, the content is printed in the terminal.
     * 
     * @param num_phrases
     *        The number of phrases to print (default = all).
     * @param print_interval_ms
     *        The print interval in milliseconds (default = 2000 ms).
     * @param ostream
     *        Reference to the output stream (default = stdout).
     ********************************************************************************/
    void PrintPhrases(const std::size_t num_phrases = std::numeric_limits<std::size_t>::max(), 
                      const std::uint16_t print_interval_ms = 2000, 
                      std::ostream& ostream = std::cout) const;

     /********************************************************************************
     * @brief Prints selected number of phrases with specified print interval.
     *        As default, all the phrases are printed with an interval of 2000 ms.
     * 
     * @note  The number of phrases to print and the print interval must be entered 
     *        after the file path when running the program, for instance
     * 
     *        ./print_phrases file.txt 10 1000
     * 
     *        to print ten phrases loaded from file path "file.txt" with a print
     *        interval of 1000 ms when running the program "print_phrases".
     * 
     * @param argc
     *        The number of input arguments entered from the terminal when
     *        running the program.
     * @param argv
     *        Reference to vector storing all input arguments entered from the 
     *        terminal when running the program.
     * @param ostream
     *        Reference to the output stream (default = stdout).
     ********************************************************************************/
    void PrintPhrases(const int argc, const char** argv, std::ostream& ostream = std::cout) const;

    /********************************************************************************
     * @brief Runs the game with translation from the primary language to the 
     *        target language.
     * 
     * @param max_num_phrases
     *        The maximum number of phrases to translate (default = all phrases).
     * @param print_start_info
     *        Indicates if starting info is to be printed, e.g. the number of
     *        phrases loaded etc (default = true).
     ********************************************************************************/
    void TranslateToTarget(const std::size_t max_num_phrases = std::numeric_limits<std::size_t>::max(),
                           const bool print_start_info = true);

    /********************************************************************************
     * @brief Runs the game with translation from the target language to the 
     *        primary language.
     * 
     * @param max_num_phrases
     *        The maximum number of phrases to translate (default = all phrases).
     * @param print_start_info
     *        Indicates if starting info is to be printed, e.g. the number of
     *        phrases loaded etc (default = true).
     ********************************************************************************/
    void TranslateToPrimary(const std::size_t max_num_phrases = std::numeric_limits<std::size_t>::max(),
                            const bool print_start_info = true);

    /********************************************************************************
     * @brief Clears potential duplicates in file at specified path.
     *   
     * @param file_path
     *        Path to file containing data to load the dictionary with.
     * @return
     *        True if the file was opened and potential duplicates were removed,
     *        else false.
     ********************************************************************************/
    static bool ClearDuplicatesInFile(const std::string& file_path);

    /********************************************************************************
     * @brief Clears potential duplicates in file at path entered from the terminal.
     * 
     * @note  The file path must be entered after the run command, for instance
     * 
     *        ./run_game file.txt
     * 
     *        to load phrases from "file.txt" when running the program and
     *        "run_game" is the name of the executable.
     * 
     * @param argc
     *        The number of input arguments entered from the terminal when
     *        running the program.
     * @param argv
     *        Reference to vector storing all input arguments entered from the 
     *        terminal when running the program.
     * @return
     *        True if the file was opened and potential duplicates were removed,
     *        else false.
     ********************************************************************************/
    static bool ClearDuplicatesInFile(const int argc, const char** argv);

    /********************************************************************************
     * @brief Provides the maximum number of phrases to translate, either a set
     *        number if it has been translated from the terminal, else all
     *        loaded phrases are translated when running the program.
     * 
     * @note  The number of phrases to read must be entered after the file path
     *        when running the program, for instance
     * 
     *        ./run_game file.txt 10
     * 
     *        to translate ten phrases loaded from file path "file.txt" when running 
     *        the program "run_game".
     * 
     * @param argc
     *        The number of input arguments entered from the terminal when
     *        running the program.
     * @param argv
     *        Reference to vector storing all input arguments entered from the 
     *        terminal when running the program.
     ********************************************************************************/
    static std::size_t GetMaxNumPhrasesFromTerminal(const int argc, const char** argv) {
        return argc >= 3 ? static_cast<std::size_t>(std::atoi(argv[2])) 
                         : std::numeric_limits<std::size_t>::max();
    }

  private:
    std::vector<std::pair<std::string, std::string>> phrases_{};
    std::size_t num_guesses_{};
    std::size_t num_errors_{};
    std::size_t max_num_phrases_{std::numeric_limits<std::size_t>::max()};
    std::vector<std::size_t> index_vector_{};
    bool reverse_{false};

    double GetPrecision(void) const {
        return (num_guesses_ - num_errors_) / static_cast<double>(num_guesses_) * 100;
    }

    bool PrecisionContainsDecimals(void) const {
        return (GetPrecision() - static_cast<int>(GetPrecision()));
    }

    std::size_t NumCorrectAnswers(void) const {
        return num_guesses_ - num_errors_;
    }

    void RunGame(const bool print_start_info = true);
    void RunRound(std::vector<std::pair<std::string, std::string>>& phrases);
    void RunPhrases(std::vector<std::pair<std::string, std::string>>& phrases);
    void RunNextPhrase(const std::pair<std::string, std::string>& phrase,
                       std::vector<std::pair<std::string, std::string>>& incorrect_phrases);
    void CheckGuess(const std::string& guess, 
                    const std::pair<std::string, std::string>& phrase,
                    std::vector<std::pair<std::string, std::string>>& incorrect_phrases);
    void PrintStartInfo(void) const;
    void PrintCurrentStatus(void) const;
    void PrintResults(void) const;
    void ResizeIndexVector(const std::size_t size);
    void ShuffleIndexVector(void);
    void InitIndexVector(const std::size_t size);
    void AnalyzeError(const std::string& guess, const std::string& answer);
    void ClearStats(void);
    static bool PerformAnalysis(void);
    void InitNumberOfPhrasesToRun(std::vector<std::pair<std::string, std::string>>& phrases);
    static void RemoveAdditionalPhraseInfo(std::string& s);
    static bool PlayAgainInReverse(void);
    void GetCopyWithoutDuplicates(Dictionary& copy);
    bool PhraseExists(const std::pair<std::string, std::string>& searched_phrase);
    bool AddPhrase(const std::pair<std::string, std::string>& new_phrase);
    static void InitRandomGenerator(void);
};

} /* namespace languages */
