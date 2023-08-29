/********************************************************************************
 * @brief Dictionary for translation between two languages.
 ********************************************************************************/
#pragma once

#include <utils.hpp>
#include <limits>

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
     ********************************************************************************/
    Dictionary(const std::string& file_path) { Load(file_path); }

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
     ********************************************************************************/
    Dictionary(const int argc, const char** argv) { Load(argc, argv); }

    /********************************************************************************
     * @brief Provides the number of phrases stored in the dictionary.
     * 
     * @return
     *        The number of phrases in the dictionary.
     ********************************************************************************/
    bool NumPhrases(void) const { return phrases_.size(); }

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
     * @return
     *        True if the data was loaded from the file, else false.
     ********************************************************************************/
    bool Load(const std::string& file_path) { 
        return utils::LoadPhrasePairs(file_path, phrases_); 
    }

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
     * @return
     *        True if the data was loaded, else false.
     ********************************************************************************/
    bool Load(const int argc, const char** argv);

   /********************************************************************************
     * @brief Provides a random phrase stored in the dictionary.
     * 
     * @return
     *        Reference to a pair containing a random phrase in two languages.
     ********************************************************************************/
    const std::pair<std::string, std::string>& GetRandomPhrase(void) const;

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
    void TranslateToTarget(const size_t max_num_phrases = std::numeric_limits<size_t>::max(),
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
    void TranslateToPrimary(const size_t max_num_phrases = std::numeric_limits<size_t>::max(),
                            const bool print_start_info = true);

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
    static size_t GetMaxNumPhrasesFromTerminal(const int argc, const char** argv) {
        return argc >= 3 ? static_cast<size_t>(std::atoi(argv[2])) 
                         : std::numeric_limits<size_t>::max();
    }

  private:
    std::vector<std::pair<std::string, std::string>> phrases_{};
    size_t num_guesses_{};
    size_t num_errors_{};
    std::vector<size_t> index_vector_{};
    bool reverse_{false};

    double GetPrecision(void) const {
        return (num_guesses_ - num_errors_) / static_cast<double>(num_guesses_) * 100;
    }

    bool PrecisionContainsDecimals(void) const {
        return (GetPrecision() - static_cast<int>(GetPrecision()));
    }

    size_t NumCorrectAnswers(void) const {
        return num_guesses_ - num_errors_;
    }

    void RunGame(const size_t max_num_phrases = std::numeric_limits<size_t>::max(),
                 const bool print_start_info = true);
    void RunRound(std::vector<std::pair<std::string, std::string>>& phrases,
                 const size_t max_num_phrases = std::numeric_limits<size_t>::max());
    void RunPhrases(std::vector<std::pair<std::string, std::string>>& phrases,
                    const size_t max_num_phrases);
    void RunNextPhrase(const std::pair<std::string, std::string>& phrase,
                       std::vector<std::pair<std::string, std::string>>& incorrect_phrases);
    void CheckGuess(const std::string& guess, 
                    const std::pair<std::string, std::string>& phrase,
                    std::vector<std::pair<std::string, std::string>>& incorrect_phrases);
    void PrintStartInfo(const size_t max_num_phrases) const;
    void PrintCurrentStatus(void) const;
    void PrintResults(void) const;
    void ResizeIndexVector(const size_t size);
    void ShuffleIndexVector(void);
    void InitIndexVector(const size_t size);
    void AnalyzeError(const std::string& guess, const std::string& answer);
    void ClearStats(void);
    static bool PerformAnalysis(void);
    static void InitNumberOfPhrasesToRun(std::vector<std::pair<std::string, std::string>>& phrases,
                                         const size_t max_num_phrases);
    static void RemoveAdditionalPhraseInfo(std::string& s);
    static bool PlayAgainInReverse(void);
};

} /* namespace languages */
