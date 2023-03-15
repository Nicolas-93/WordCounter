#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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


int MOT_remplace_mot(char** mot, size_t* bufsize, char* nouveau_mot) {
    if (!nouveau_mot)
        return 0;

    int len = strlen(nouveau_mot);
    int new_size = len + 1;

    if (!*mot) {
        if (!(*mot = malloc(new_size * sizeof(char))))
            return 0;
    }
    else if (*bufsize < len) {
        if (!(*mot = realloc(*mot, new_size * sizeof(char))))
            return 0;
    }

    strcpy(*mot, nouveau_mot);

    return 1;
}
