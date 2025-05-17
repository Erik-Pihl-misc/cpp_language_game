# PhrasePrinter Utility

## Description

`PhrasePrinter` is a command-line utility designed to print phrase pairs from a text file, making it easy to review vocabulary or translation pairs. Phrases are loaded from a user-provided text file, where each pair is separated by a blank line. 
By default, all loaded phrase pairs are printed to the terminal with a 2000 ms interval between each pair.

You can optionally specify the number of phrases to print and the print interval (in milliseconds):

```bash
./PhrasePrinter path/to/phrases.txt [number_of_phrases] [interval_ms]
```

For example, the following command prints up to 10 phrase pairs from the file, displaying each pair with a 500 ms interval:

```bash
./PhrasePrinter path/to/phrases.txt 10 500
```

If you do not specify a number or interval, all phrase pairs are printed with a default interval of 2000 ms.

## Disclaimer

Before usage, the C++ language game must be built as described [here](../README.md).