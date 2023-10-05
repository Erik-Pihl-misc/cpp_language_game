#include <dictionary.hpp>

namespace languages {

Dictionary::Dictionary(const std::string& file_path, const bool print_result) { 
    Load(file_path, print_result); 
}

Dictionary::Dictionary(const int argc, const char** argv, const bool print_result) { 
    Load(argc, argv, print_result); 
}

const std::pair<std::string, std::string>& Dictionary::GetRandomPhrase(void) const {
    return phrases_[utils::GetRandomInt<std::size_t>(NumPhrases())];
}

void Dictionary::PrintPhrases(const std::size_t num_phrases,
                              const std::uint16_t print_interval_ms, 
                              std::ostream& ostream) const {
    
    std::size_t num_printed_phrases{};
    for (const auto& i : phrases_) {
        if (num_printed_phrases++ >= num_phrases) break;
        ostream << i.first << "\n";
        ostream << i.second << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(print_interval_ms));
    }
}

void Dictionary::PrintPhrases(const int argc, const char** argv, std::ostream& ostream) const {
    const auto num_phrases{GetMaxNumPhrasesFromTerminal(argc, argv)};
    const auto print_interval_ms{argc >= 4 ? static_cast<std::size_t>(std::atoi(argv[3])) : 2000};
    PrintPhrases(num_phrases, print_interval_ms, ostream);
}

bool Dictionary::Load(const std::string& file_path, const bool print_success) { 
    if (utils::LoadPhrasePairs(file_path, phrases_) == 0) {
        std::cerr << "File \"" << file_path << "\" wasn't found or contains insufficient data!\n\n";
        return false;
    } else {
        if (print_success) {
            std::cout << "Language data from file \"" << file_path << "\" successfully loaded!\n\n";
        }
        return true;  
    }
}

bool Dictionary::Load(const int argc, const char** argv, const bool print_success) {
    std::cout << "\n";
    if (argc == 1) {
        std::cerr << "Cannot load dictionary due to missing file path!\n\n";
        return false;
    }
    const auto file_path{argv[1]}; 
    Load(file_path);
    if (Empty()) {
        return false;
    } else {
        return true;
    }
}

void Dictionary::TranslateToTarget(const std::size_t max_num_phrases, const bool print_start_info) {
    reverse_ = false;
    max_num_phrases_ = max_num_phrases;
    RunGame(print_start_info);
}

void Dictionary::TranslateToPrimary(const std::size_t max_num_phrases, const bool print_start_info) {
    reverse_ = true;
    max_num_phrases_ = max_num_phrases;
    RunGame(print_start_info);
}

bool Dictionary::ClearDuplicatesInFile(const std::string& file_path) {
    Dictionary source{file_path, false}, copy{};
    if (source.Empty()) return false;
    source.GetCopyWithoutDuplicates(copy);
    const auto num_duplicates{source.NumPhrases() - copy.NumPhrases()};
    if (num_duplicates) {
        if (num_duplicates == 1) {
            std::cout << "Removed one duplicate from file at path \"" << file_path << "\"!\n\n";
        } else {
            std::cout << "Removed " << num_duplicates << " duplicates from file at path \"" << file_path << "\"!\n\n";
        }
        return utils::WritePhrasePairsToFile(file_path, copy.Phrases());
    } else {
        std::cout << "Found no duplicates in file at path \"" << file_path << "\"!\n\n";
        return true;
    }
}

bool Dictionary::ClearDuplicatesInFile(const int argc, const char** argv) {
    if (argc >= 2) {
        return ClearDuplicatesInFile(argv[1]);
    } else {
        std::cerr << "Cannot clear duplicates! No file path specified!\n\n";
        return false;
    }
}

void Dictionary::RunGame(const bool print_start_info) {
    std::vector<std::pair<std::string, std::string>> remaining_phrases{phrases_};
    InitNumberOfPhrasesToRun(remaining_phrases);
    auto phrase_backup{remaining_phrases};
    if (print_start_info) PrintStartInfo();
    RunRound(remaining_phrases);
    if (PlayAgainInReverse()) {
        reverse_ = !reverse_;
        RunRound(phrase_backup);
    }
}

void Dictionary::RunRound(std::vector<std::pair<std::string, std::string>>& phrases) {
    while (phrases.size() && (NumCorrectAnswers() < max_num_phrases_)) {
        RunPhrases(phrases);
    }
    PrintResults();
    ClearStats();
}

void Dictionary::RunPhrases(std::vector<std::pair<std::string, std::string>>& phrases) {
    std::vector<std::pair<std::string, std::string>> incorrect_phrases{};
    InitIndexVector(phrases.size());
    for (auto& i : index_vector_) {
        PrintCurrentStatus();
        RunNextPhrase(phrases[i], incorrect_phrases);
        if (NumCorrectAnswers() >= max_num_phrases_) return;
    }
    phrases = incorrect_phrases;
}

void Dictionary::RunNextPhrase(const std::pair<std::string, std::string>& phrase,
                               std::vector<std::pair<std::string, std::string>>& incorrect_phrases) {
    std::string guess{};
    std::cout << "Translate the following phrase:\n";
    if (reverse_) std::cout << phrase.second << "\n";
    else std::cout << phrase.first << "\n";
    utils::ReadLine(guess);
    utils::RemoveTrailingWhitespaces(guess);
    CheckGuess(guess, phrase, incorrect_phrases);
}

void Dictionary::CheckGuess(const std::string& guess, 
                            const std::pair<std::string, std::string>& phrase,
                            std::vector<std::pair<std::string, std::string>>& incorrect_phrases) {
    auto answer{reverse_ ? phrase.first : phrase.second};
    RemoveAdditionalPhraseInfo(answer);
    if (guess == answer) {
        std::cout << "Correct answer!\n\n";
    } else {
        std::cout << "Wrong answer!\n";
        std::cout << "Your guess:\t" << guess << "\n";
        std::cout << "Correct answer:\t" << answer << "\n\n";
        incorrect_phrases.push_back(phrase);
        num_errors_++;
        if (PerformAnalysis()) {
            AnalyzeError(guess, answer);
        }
    }
    num_guesses_++;
}

void Dictionary::PrintStartInfo(void) const {
    const std::size_t loaded_phrases{utils::Min<std::size_t>(max_num_phrases_, phrases_.size())};
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "Starting translation game!\n";
    std::cout << loaded_phrases << " phrases have been loaded!\n";
    std::cout << "--------------------------------------------------------------------------------\n\n";
}

void Dictionary::PrintCurrentStatus(void) const {
    if (num_guesses_ == 0) return;
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "Number of guesses:\t\t" << num_guesses_ << "\n";
    std::cout << "Number of correct answers:\t" << NumCorrectAnswers() << "\n";
    std::cout << "Number of incorrect guesses:\t" << num_errors_ << "\n";
    std::cout << "Number of phrases remaining:\t" << NumPhrases() - NumCorrectAnswers() << "\n";
    std::cout << "--------------------------------------------------------------------------------\n\n";
}

void Dictionary::PrintResults(void) const {
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "Total number of guesses:\t" << num_guesses_ << "\n";
    std::cout << "Number of correct answers:\t" << NumCorrectAnswers() << "\n";
    std::cout << "Number of incorrect answers:\t" << num_errors_ << "\n";
    std::cout << "Success rate:\t\t\t";

    if (PrecisionContainsDecimals()) {
        std::cout << std::fixed << std::setprecision(1) << GetPrecision() << " %\n";
    } else {
        std::cout << static_cast<int>(GetPrecision()) << " %\n";
    }
    std::cout << "--------------------------------------------------------------------------------\n\n";
}

void Dictionary::ResizeIndexVector(const std::size_t size) {
    index_vector_.resize(size);
    for (std::size_t i{}; i < index_vector_.size(); ++i) {
        index_vector_[i] = i;
    }
}

void Dictionary::ShuffleIndexVector(void) {
    for (std::size_t i{}; i < index_vector_.size(); ++i) {
        const auto r{utils::GetRandomInt<std::size_t>(index_vector_.size())};
        const auto temp{index_vector_[i]};
        index_vector_[i] = index_vector_[r];
        index_vector_[r] = temp;
    }
}

void Dictionary::InitIndexVector(const std::size_t size) {
    ResizeIndexVector(size);
    ShuffleIndexVector();
}

void Dictionary::AnalyzeError(const std::string& guess, const std::string& answer) {
    auto GetOutput = [](const char c, const bool upper_case = false) {
        return c != ' ' ? std::string{'"', c, '"'} : 
        upper_case ? std::string{"Blank line"} : std::string{"blank line"};
    };
    for (std::size_t i{}; i < answer.size(); ++i) {
        if (i < guess.size()) {
            if (guess[i] != answer[i]) {
                std::cout << GetOutput(guess[i], true) << " at index " << i 
                          << " should be replaced with " << GetOutput(answer[i]) << "\n\n";
            }
        }
    }
}

void Dictionary::ClearStats(void) {
    num_guesses_ = 0;
    num_errors_ = 0;
}

bool Dictionary::PerformAnalysis(void) {
    std::string s{};
    std::cout << "Analyze error? Y/n\n";
    while (1) {
        utils::ReadLine(s);
        if (s[0] == 'Y' || s[0] == 'y') {
            return true;
        } else if (s[0] == 'N' || s[0] == 'n') {
            return false;
        } else {
            std::cout << "Invalid input, try again!\n";
        }
    }
}

void Dictionary::InitNumberOfPhrasesToRun(std::vector<std::pair<std::string, std::string>>& phrases) {
    InitRandomGenerator();
    const auto num_phrases{max_num_phrases_ < phrases.size() ? max_num_phrases_ : phrases.size()};
    for (std::size_t i{}; i < num_phrases; ++i) {
        const auto r{std::rand() % phrases.size()};
        const auto temp{phrases[i]};
        phrases[i] = phrases[r];
        phrases[r] = temp;
    }
    if (max_num_phrases_ < phrases.size()) {
        phrases.resize(max_num_phrases_);
    }
}

void Dictionary::RemoveAdditionalPhraseInfo(std::string& s) {
    for (std::size_t i{}; i < s.size(); ++i) {
        if (s[i] == '(') {
            s = s.std::string::substr(0, i);
            utils::RemoveTrailingWhitespaces(s);
            break;
        }
    }
}

bool Dictionary::PlayAgainInReverse(void) {
    std::cout << "Do you wanna play the game in reverse? Y/n\n";
    while (1) {
        std::string s{};
        utils::ReadLine(s);
        if (s[0] == 'Y' || s[0] == 'y') {
            return true;
        } else if (s[0] == 'N' || s[0] == 'n') {
            return false;
        } else {
            std::cout << "Invalid input, try again!\n";
        }
    }
}

void Dictionary::GetCopyWithoutDuplicates(Dictionary& copy) {
    for (auto& phrase : phrases_) {
        copy.AddPhrase(phrase);
    }
}

bool Dictionary::PhraseExists(const std::pair<std::string, std::string>& searched_phrase) {
    for (auto& stored_phrase : phrases_) {
        if (stored_phrase.first == searched_phrase.first && stored_phrase.second == searched_phrase.second) {
            return true;
        }
    }
    return false;
}

bool Dictionary::AddPhrase(const std::pair<std::string, std::string>& new_phrase) {
    if (PhraseExists(new_phrase)) {
        return false;
    } else {
        phrases_.push_back(new_phrase);
        return true;
    }
}

void Dictionary::InitRandomGenerator(void) {
    static bool rand_init{false};
    if (!rand_init) {
        std::srand(std::time(nullptr));
        rand_init = true;
    }
}

} /* namespace languages */
