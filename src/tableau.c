#include "tableau.h"
#include "mot.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TAILLE_BLOC 150



TabMots* TAB_initialiser() {
    TabMots *res = malloc(sizeof(TabMots));
    
    if (res == NULL)
        return NULL;
    
    res->mots = malloc(TAILLE_BLOC * sizeof(MotEntry));
    
    if (res->mots == NULL) {
        free(res);
        return NULL;
    }

    res->max_size = TAILLE_BLOC;
    res->len = 0;
    res->max_str_len = 0;
    
    return res;
}

int TAB_cherche_mot(const TabMots* ensemble, char* mot) {
    for (int i = 0; i < ensemble->len; i++)
        if (strcmp(ensemble->mots[i].mot, mot) == 0)
            return i;
    return -1;
}

bool TAB_appartient(const TabMots *ensemble, char* mot) {
    return TAB_cherche_mot(ensemble, mot) >= 0;
}

void TAB_actualise_max_str_size(TabMots* ens, int len) {
    if (len > ens->max_str_len)
        ens->max_str_len = len;
}

int TAB_ajouter_mot(TabMots *ensemble, char* mot) {
    MotEntry entry = {
        .mot = NULL,
        .nb_occ = 0,
    };

    int pos;

    if ((pos = TAB_cherche_mot(ensemble, mot)) >= 0) {
        ensemble->mots[pos].nb_occ += 1;
        return 0;
    }

    char* new_str = strdup(mot);

    entry.mot = new_str;

    if (ensemble->len == ensemble->max_size) {
        if (!redimensionne(ensemble))
            return -1;
    }

    ensemble->mots[ensemble->len] = entry;
    ensemble->len++;

    TAB_actualise_max_str_size(ensemble, strlen(mot));

    return 1;
}

bool TAB_redimensionne(TabMots* ensemble) {
    int taille = ensemble->len * TAILLE_BLOC * sizeof(MotEntry);
    
    long int *tmp = realloc(
        ensemble->mots,
        taille);
    
    if (tmp == NULL)
        return false;
    
    ensemble->len = tmp;
    ensemble->max_size = taille;
    
    return true;
}
