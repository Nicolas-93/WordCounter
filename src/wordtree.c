#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "wordtree.h"
#include <ctype.h>

bool Word_is_correct(const char* word) {
    if (!word)
        return false;

    for ( ; *word; ++word) {
        if (!isalpha(*word))
            return false;
    }

    return true;
}

void Word_to_lower(char* word) {
    if (!word)
        return;

    for ( ; *word; ++word) {
        *word = tolower(*word);
    }
}


int Word_replace(char** word, size_t* bufsize, char* new_word) {
    if (!new_word)
        return 0;

    int len = strlen(new_word);
    int new_size = len + 1;

    if (!*word) {
        if (!(*word = malloc(new_size * sizeof(char))))
            return 0;
    }
    else if (*bufsize < len) {
        if (!(*word = realloc(*word, new_size * sizeof(char))))
            return 0;
    }

    strcpy(*word, new_word);

    return 1;
}
