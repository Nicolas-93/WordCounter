#include <stdio.h>
#include "output.h"
#include "wordarray.h"

void OUT_print_words(const WordArray* words) {
    for(int i = 0; i < words->len; ++i) {
        printf("%-*s %d\n", words->max_str_len, words->tab[i]->word, words->tab[i]->nb_occ);
    }
}
