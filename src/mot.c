#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mot.h"
#include <ctype.h>

bool MOT_est_correct(const char* mot) {
    if (!mot)
        return false;

    for ( ; *mot; ++mot) {
        if (!isalpha(*mot))
            return false;
    }

    return true;
}

void MOT_normaliser(char* mot) {
    if (!mot)
        return;

    for ( ; *mot; ++mot) {
        *mot = tolower(*mot);
    }
}
