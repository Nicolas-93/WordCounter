#ifndef ALGO_INCLUDED
#define ALGO_INCLUDED

#include "tree.h"
#include "wordtree.h"
#include <stdio.h>
#include <string.h>

#define SEPARATORS " \n,;:.?!\\\"()-'’"
#define MAX_WORD_SIZE 1024

#define FOREACH_TOKEN(token, line) \
    for (token = strtok(line, SEPARATORS), Word_to_lower(token); \
         token;                                                   \
         token = strtok(NULL, SEPARATORS), Word_to_lower(token))

#define FOREACH_TOKEN_SAFE(token, line, saveptr) \
    for (token = strtok_r(line, SEPARATORS, (saveptr)), Word_to_lower(token); \
         token;                                                                   \
         token = strtok_r(NULL, SEPARATORS, (saveptr)), Word_to_lower(token))

typedef enum SearchMode {
    MODE_COUNT_WORDS = 0,
    MODE_WORDS_BEFORE_X = 1,
    MODE_WORDS_AFTER_X = 2,
    MODE_EXPRESSION = 4,
} SearchMode;

/**
 * @brief Create an array containing the words that follow
 * the word x, from the file f.
 * 
 * @param dest Destination array
 * @param f File to read from
 * @return int 
 */
int ALG_words_after_x(WordTree* dest, FILE* f, char* x);


/**
 * @brief Create an array containing the words that precede
 * the word x, from the file f.
 * 
 * @param dest Destination array
 * @param f File to read from
 * @return int 
 */
int ALG_words_before_x(WordTree* dest, FILE* f, char* x);

/**
 * @brief Count the number of occurences of all words.
 * 
 * @param dest Destination array
 * @param f File to read from
 * @return int 
 */
int ALG_count_words(WordTree* dest, FILE* f);

/**
 * @brief Compte expressions of n words.
 * 
 * @param dest Destination array
 * @param f File to read from
 * @param n Number of words in the expression
 * @return int 
 */
int ALG_expressions(WordTree* dest, FILE* f, int n);

#endif
