#define _GNU_SOURCE

#include "algo.h"
#include "tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


int ALG_words_after_x(WordTree* dest, FILE* f, char* x) {
    assert(f);

    char* line = NULL;
    size_t len_buf = 0;
    ssize_t len_line;
    char* token;

    bool found_before = false;

    // On bufferise les lignes avec getline qui alloue également l'espace nécessaire
    while ((len_line = getline(&line, &len_buf, f)) != EOF) {
        FOREACH_TOKEN(token, line) {
            if (!Word_is_correct(token)) continue;
            
            if (strcmp(token, x) == 0) {
                if (found_before)
                    Tree_add_word(dest, token);
                found_before = true;
            }
            else if (found_before) {
                Tree_add_word(dest, token);
                found_before = false;
            }
        }
    }

    free(line);
    return 1;
}

int ALG_words_before_x(WordTree* dest, FILE* f, char* x) {
    assert(f);

    char* line = NULL;
    size_t len_buf = 0;
    ssize_t len_line;
    char* token;

    char* prec_word = NULL;
    size_t bufsize_prec_word = 0;

    // On bufferise les lignes avec getline qui alloue également l'espace nécessaire
    while ((len_line = getline(&line, &len_buf, f)) != EOF) {
        FOREACH_TOKEN(token, line) {
            if (!Word_is_correct(token)) continue;
            
            if (prec_word && strcmp(token, x) == 0) {
                Tree_add_word(dest, prec_word);
            }

            Word_replace(&prec_word, &bufsize_prec_word, token);
        }
    }

    free(prec_word);
    free(line);
    return 1;
}

int ALG_count_words(WordTree* dest, FILE* f) {
    char* line = NULL;
    size_t len_buf = 0;
    ssize_t len_line;
    char* token;

    while ((len_line = getline(&line, &len_buf, f)) != EOF) {
        FOREACH_TOKEN(token, line) {
            if (!Word_is_correct(token)) continue;
            Tree_add_word(dest, token);
        }
    }
    free(line);

    return 1;
}

int ALG_expressions(WordTree* dest, FILE* f, int n) {
    char* line = NULL;
    char expr[n * MAX_WORD_SIZE];

    int len_token;
    char* token;
    char* str_token;
    char* str_saveptr;

    size_t len_buf = 0;
    ssize_t len_ligne;

    memset(expr, 0, (n * MAX_WORD_SIZE) * sizeof(char));

    int i = 0;

    while ((len_ligne = getline(&line, &len_buf, f)) != EOF) {
        FOREACH_TOKEN_SAFE(str_token, line, &str_saveptr) {
            if (!Word_is_correct(str_token)) continue;
            strcat(expr, str_token);

            // We must initialize the array with a first expression of n words
            if (i++ < n - 1) {
                strcat(expr, " ");
                continue;
            }

            Tree_add_word(dest, expr);
            strcat(expr, " ");

            token = strtok(expr, " ");
            len_token = strlen(token);

            memmove(
                expr,
                expr + len_token + 1,
                (n - 1) * MAX_WORD_SIZE - len_token + 1);
        }
    }

    free(line);
    return 1;
}
