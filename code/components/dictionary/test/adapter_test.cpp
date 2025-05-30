/**
 * @brief Unit test for class language::dictionary::Adapter.
 */
#include <fstream>
#include <list>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "dictionary/adapter.h"
#include "utils/phrase.h"

namespace 
{
using namespace language;

constexpr std::size_t kDefaultPrintIntervalMs{2000U};

// -----------------------------------------------------------------------------
void writePhrasesToFile(const std::string &filePath, const std::list<Phrase> &phrases)
{
    // Open the file for writing.
    std::ofstream ostream{filePath};
    if (!ostream) { return; }

    // Write each phrase pair to the file, separated by a blank line.
    for (const auto &phrase : phrases)
    {
        ostream << phrase.primary << "\n" << phrase.target << "\n\n";
    }
}

/**
 * @brief Verify that the dictionary adapter works correctly when passing phrases via a list.
 */
TEST(DictionaryAdapterTest, ListTest) 
{
    // Define phrases for the test.
    const std::list<Phrase> phrases{
        {"Welcome to my C++ language game.", "Willkommen zu meinem C++ Sprachspiel."},
        {"I hope it will be a great aid to you.", "Ich hoffe, es wird dir eine grosse Hilfe sein."},
        {"Please enter your answer.", "Bitte gib deine Antwort ein."},
        {"Good luck and have fun!", "Viel Glück und viel Spass!"}};

    // Create adapter with the defined phrases.
    dictionary::Adapter adapter{phrases};

    // Expect the stored phrases to be equal to the defined phrases.
    EXPECT_EQ(adapter.phrases(), phrases);

    // Expect the phrase count to use to be equal to the number of stored phrases, since no
    // other value has been specified.
    EXPECT_EQ(adapter.phraseCountToUse(), phrases.size());

    // Expect the print interval to be set to the default value.
    EXPECT_EQ(adapter.printIntervalMs(), kDefaultPrintIntervalMs);
}

/**
 * @brief Verify that the dictionary adapter works correctly when loading phrases from a file.
 */
TEST(DictionaryAdapterTest, FileTest) 
{
    // Define phrases for the test.
    const std::list<Phrase> phrases{
        {"Welcome to my C++ language game.", "Willkommen zu meinem C++ Sprachspiel."},
        {"I hope it will be a great aid to you.", "Ich hoffe, es wird dir eine grosse Hilfe sein."},
        {"Please enter your answer.", "Bitte gib deine Antwort ein."},
        {"Good luck and have fun!", "Viel Glück und viel Spass!"},
        {"Don't hesitate to ask me for help.", "Zögern Sie nicht, mich um Hilfe zu bitten."},
        {"The frog tries to hop away.", "Der Frosch versucht weg zuhüpfen."}};

    // Write the phrases to the file at path 'phrases.txt'.
    constexpr const char *filePath{"phrases.txt"};
    writePhrasesToFile(filePath, phrases);

    // Create adapter by passing the path to the file.
    dictionary::Adapter adapter{filePath};

    // Expect the stored phrases to be equal to the defined phrases.
    EXPECT_EQ(adapter.phrases(), phrases);

    // Expect the phrase count to use to be equal to the number of stored phrases, since no
    // other value has been specified.
    EXPECT_EQ(adapter.phraseCountToUse(), phrases.size());

    // Expect the print interval to be set to the default value.
    EXPECT_EQ(adapter.printIntervalMs(), kDefaultPrintIntervalMs);
}

/**
 * @brief Verify that duplicate phrases are removed when loading the file.
 */
TEST(DictionaryAdapterTest, DuplicateTest) 
{
    // Define phrases for the test.
    const std::list<Phrase> phrases{
        {"Welcome to my C++ language game.", "Willkommen zu meinem C++ Sprachspiel."},
        {"I hope it will be a great aid to you.", "Ich hoffe, es wird dir eine grosse Hilfe sein."},
        {"Please enter your answer.", "Bitte gib deine Antwort ein."},
        {"Good luck and have fun!", "Viel Glück und viel Spass!"},
        {"Don't hesitate to ask me for help.", "Zögern Sie nicht, mich um Hilfe zu bitten."},
        {"Welcome to my C++ language game.", "Willkommen zu meinem C++ Sprachspiel."},
        {"The frog tries to hop away.", "Der Frosch versucht weg zuhüpfen."},
        {"Good luck and have fun!", "Viel Glück und viel Spass!"}};

    const std::list<Phrase> expectedPhrases{
        {"Welcome to my C++ language game.", "Willkommen zu meinem C++ Sprachspiel."},
        {"I hope it will be a great aid to you.", "Ich hoffe, es wird dir eine grosse Hilfe sein."},
        {"Please enter your answer.", "Bitte gib deine Antwort ein."},
        {"Good luck and have fun!", "Viel Glück und viel Spass!"},
        {"Don't hesitate to ask me for help.", "Zögern Sie nicht, mich um Hilfe zu bitten."},
        {"The frog tries to hop away.", "Der Frosch versucht weg zuhüpfen."}};

    // Write the phrases to the file at path 'phrases.txt'.
    constexpr const char *filePath{"phrases.txt"};
    writePhrasesToFile(filePath, phrases);

    // Create adapter by passing the path to the file.
    dictionary::Adapter adapter{filePath};

    // Expect the stored phrases to be equal to the expected phrases.
    EXPECT_EQ(adapter.phrases(), expectedPhrases);

    // Expect the phrase count to use to be equal to the number of stored phrases, since no
    // other value has been specified.
    EXPECT_EQ(adapter.phraseCountToUse(), expectedPhrases.size());

    // Expect the print interval to be set to the default value.
    EXPECT_EQ(adapter.printIntervalMs(), kDefaultPrintIntervalMs);
}

/**
 * @brief Verify that the dictionary adapter works correctly when passing arguments from the terminal.
 */
TEST(DictionaryAdapterTest, ArgTest) 
{
    // Define phrases for the test.
    const std::list<Phrase> phrases{
        {"Welcome to my C++ language game.", "Willkommen zu meinem C++ Sprachspiel."},
        {"I hope it will be a great aid to you.", "Ich hoffe, es wird dir eine grosse Hilfe sein."},
        {"Please enter your answer.", "Bitte gib deine Antwort ein."},
        {"Good luck and have fun!", "Viel Glück und viel Spass!"},
        {"Don't hesitate to ask me for help.", "Zögern Sie nicht, mich um Hilfe zu bitten."},
        {"The frog tries to hop away.", "Der Frosch versucht weg zuhüpfen."},
        {"The stork swallowed the frog.", "Der Storch hat den Frosch verschluckt."},
        {"We laughed about it.", "Wir haben darüber gelacht."}};

    // Write the phrases to the file at path 'phrases.txt'.
    constexpr const char *filePath{"phrases.txt"};
    writePhrasesToFile(filePath, phrases);

    // Test 1 - Only passing the file path.
    {
        // Create arguments.
        const std::vector<const char *> args{"./runGame", "phrases.txt"};

        // Create adapter by passing the arguments and the argument count.
        dictionary::Adapter adapter{static_cast<int>(args.size()), const_cast<const char **>(args.data())};

        // Expect the stored phrases to be equal to the defined phrases.
        EXPECT_EQ(adapter.phrases(), phrases);

        // Expect the phrase count to use to be equal to the number of stored phrases, since no
        // other value has been specified.
        EXPECT_EQ(adapter.phraseCountToUse(), phrases.size());

        // Expect the print interval to be set to the default value.
        EXPECT_EQ(adapter.printIntervalMs(), kDefaultPrintIntervalMs);
    }

    // Test 2 - Passing the file path and the number of phrases to use.
    {
        // Set the expected phrase count to use to 5.
        constexpr std::size_t phraseCountToUse{5U};

        // Create arguments.
        const std::vector<const char *> args{"./runGame", "phrases.txt", "5"};

        // Create adapter by passing the arguments and the argument count.
        dictionary::Adapter adapter{static_cast<int>(args.size()), const_cast<const char **>(args.data())};

        // Expect the stored phrases to be equal to the defined phrases.
        EXPECT_EQ(adapter.phrases(), phrases);

        // Expect the phrase count to use to be set to 5.
        EXPECT_EQ(adapter.phraseCountToUse(), phraseCountToUse);

        // Expect the print interval to be set to the default value.
        EXPECT_EQ(adapter.printIntervalMs(), kDefaultPrintIntervalMs);
    }

    // Test 3 - Passing the file path, the number of phrases to use, and the print interval.
    {
        // Set the expected phrase count to use to 4.
        constexpr std::size_t phraseCountToUse{4U};

        // Set the expected print interval to 500 ms.
        constexpr std::size_t printIntervalMs{500U};

        // Create arguments.
        const std::vector<const char *> args{"./runGame", "phrases.txt", "4", "500"};

        // Create adapter by passing the arguments and the argument count.
        dictionary::Adapter adapter{static_cast<int>(args.size()), const_cast<const char **>(args.data())};

        // Expect the stored phrases to be equal to the defined phrases.
        EXPECT_EQ(adapter.phrases(), phrases);

        // Expect the phrase count to use to be set to 4.
        EXPECT_EQ(adapter.phraseCountToUse(), phraseCountToUse);

        // Expect the print interval to be set to 500 ms.
        EXPECT_EQ(adapter.printIntervalMs(), printIntervalMs);
    }
}
} // namespace

/**
 * @brief Run tests.
 * 
 * @param[in] argc The number of input arguments entered from the terminal at runtime.
 * @param[in] argv Vector storing all input arguments entered from the terminal at runtime.
 * 
 * @return Success code 0 if all tests succeeded, otherwise a non-zero value.
 */
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
