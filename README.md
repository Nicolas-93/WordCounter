# Word counter

## Description

This is a simple word counter that counts the number of words in a given text.

## Usage

```
Usage : %s [OPTION]... [FILE]

Options:
    -h, --help              Display this help message.
    -f, --apparition        Sort words by order of appearance in the text. (Default)
    -l, --lexico            Sort words by ascending lexicographic order.
    -n, --occ               Sort words by decreasing number of occurrences, then by lexicographic order.
    -c, --croissant         Force ascending order.
    -d, --decroissant       Force descending order.
    -b, --before=WORD       Display the words before the word WORD.
    -a, --after=WORD        Display the words after the word WORD.
    -e, --expr=N            Display expressions of length N words.
    -t, --test              Run unit tests.
```
