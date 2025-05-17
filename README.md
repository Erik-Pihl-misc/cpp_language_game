# C++ language game

## Description

This is a command-line language game designed to help users practice translation between a primary and a target language. The game loads phrase pairs from a user-provided text file, where each pair is separated by a blank line. By default, all loaded phrase pairs are used in the game. Users are prompted to translate phrases from the primary language to the target language. After completing the initial round, the game offers the option to reverse the direction and translate from the target language back to the primary language.

## Setup

In a Linux environment, install necessary libraries, such as the `GCC` compiler and `CMake`:

```bash
sudo apt -y update
sudo apt -y install build-essential cmake
```
Then build the game and place all build files in a directory called `build`:

```bash
cmake -S . -B build
cmake --build build
```

Try running the game with the attached file `example.txt`, which contains a few phrases to
translate to German: 

```bash
./LanguageGame example.txt
```

## Play the game

To play, run the program with the path to your phrase file as an argument. Optionally, you can specify the number of phrases to translate. For example:

```bash
./LanguageGame path/to/phrases.txt 10
```

This will load up to 10 phrase pairs from the file and start the translation game. If you do not specify a number, all phrase pairs in the file will be used.

Potential duplicates in the file will be removed when the file is read.

## Print phrases

To print phrases from a file, please use the `PhrasePrinter` command-line utility found [here](./utils/README.md).

For example:

```bash
./PhrasePrinter path/to/phrases.txt 10 500
```

In this command:
* `path/to/phrases.txt` is the path to your phrase file,
* `10` is the maximum number of phrase pairs to print,
* `500` is the interval in milliseconds between each printed pair.

If you do not specify a number or interval, all phrase pairs are printed with a default interval of 2000 ms.