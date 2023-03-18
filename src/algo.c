#define _GNU_SOURCE

#include "algo.h"
#include "ABR.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


int ALG_mots_apres_x(Mots* dest, FILE* f, char* x) {
    assert(f);

    char* line = NULL;
    size_t len_buf = 0;
    ssize_t len_line;
    char* token;

    bool trouve_avant = false;

    // On bufferise les lignes avec getline qui alloue également l'espace nécessaire
    while ((len_line = getline(&line, &len_buf, f)) != EOF) {
        FOREACH_TOKEN(token, line) {
            if (!MOT_est_correct(token)) continue;
            
            if (strcmp(token, x) == 0) {
                if (trouve_avant)
                    ABR_ajouter_mot(dest, token);
                trouve_avant = true;
            }
            else if (trouve_avant) {
                ABR_ajouter_mot(dest, token);
                trouve_avant = false;
            }
        }
    }

    free(line);
    return 1;
}

int ALG_mots_avant_x(Mots* dest, FILE* f, char* x) {
    assert(f);

    char* line = NULL;
    size_t len_buf = 0;
    ssize_t len_line;
    char* token;

    char* mot_prec = NULL;
    size_t bufsize_mot_prec = 0;

    // On bufferise les lignes avec getline qui alloue également l'espace nécessaire
    while ((len_line = getline(&line, &len_buf, f)) != EOF) {
        FOREACH_TOKEN(token, line) {
            if (!MOT_est_correct(token)) continue;
            
            if (mot_prec && strcmp(token, x) == 0) {
                ABR_ajouter_mot(dest, mot_prec);
            }

            MOT_remplace_mot(&mot_prec, &bufsize_mot_prec, token);
        }
    }

    free(mot_prec);
    free(line);
    return 1;
}

int ALG_compter_mots(Mots* dest, FILE* f) {
    char* line = NULL;
    size_t len_buf = 0;
    ssize_t len_line;
    char* token;

    while ((len_line = getline(&line, &len_buf, f)) != EOF) {
        FOREACH_TOKEN(token, line) {
            if (!MOT_est_correct(token)) continue;
            ABR_ajouter_mot(dest, token);
        }
    }
    free(line);

    return 1;
}

void ALG_expressions(Mots* dest, FILE* f, int n) {
    char chaine[MAX_WORD_SIZE];
    char suffix[(n-1)*MAX_WORD_SIZE];
    
    char* token;
    char* chaine_token;
    char* chaine_saveptr;

    memset(suffix, 0, (n-1)*MAX_WORD_SIZE);

    int i = 0;

    while (fscanf(f, "%s ", chaine) != EOF) {
        FOREACH_TOKEN_SAFE(chaine_token, chaine, &chaine_saveptr) {

            if (!MOT_est_correct(chaine_token)) continue;

            strcat(suffix, chaine_token);
            strcat(suffix, " ");

            // On doit initaliser le tableau d'une première expression
            if (i++ < n - 1) continue;

            ABR_ajouter_mot(dest, suffix);
            token = strtok(suffix, " ");
            memmove(
                suffix,
                suffix + strlen(token) + 1,
                (n-1)*MAX_WORD_SIZE - strlen(token) + 1);
        }
    }
}
