#define _GNU_SOURCE

#include "algo.h"
#include "tableau.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int ALG_mots_apres_x(TabMots* dest, FILE* f, char* x) {
    if(!f) {
        fprintf(stderr, "Error reading the file\n");
        return -1;
    }
    bool trouve_avant = false;

    char* line = NULL;
    size_t len_buf = 0;
    ssize_t len_line;
    char* token;

    while ((len_line = getline(&line, &len_buf, f)) != EOF) {
        FOREACH_TOKEN(token, line) {
            if (strcmp(token, x) == 0) {
                trouve_avant = true;
            }
            else if (trouve_avant) {
                TAB_ajouter_mot(dest, token);
                trouve_avant = false;
            }
        }
    }

    return 1;
}

int ALG_mots_avant_x(TabMots* dest, FILE* f, char* x) {
    
}

int ALG_compter_mots(TabMots* dest, FILE* f) {
    bool trouve_avant = false;

    char* line = NULL;
    size_t len_buf = 0;
    ssize_t len_line;
    char* token;

    while ((len_line = getline(&line, &len_buf, f)) != EOF) {
        FOREACH_TOKEN(token, line) {
            TAB_ajouter_mot(dest, token);
        }
    }

    return 1;
}
