#include "ABR.h"
#include "mot.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


Mots* ABR_initialiser() {
    Mots *res = malloc(sizeof(Mots));
    
    if (res == NULL)
        return NULL;

    res->racine = NULL;
    res->len = 0;
    res->max_str_len = 0;

    return res;
}

MotEntry* ABR_alloue_noeud(char* mot, int apparition) {
    MotEntry *n;
    if ((n = malloc(sizeof(MotEntry)))) {
        n->fg = NULL;
        n->fd = NULL;
        n->mot = strdup(mot);
        n->apparition = apparition;
        n->nb_occ = 1;
    }
    return n;
}

MotEntry* ABR_cherche_mot(const Mots* ensemble, char* mot) {
    MotEntry* a = ensemble->racine;

    if (!mot)
        return NULL;

    int cmp;

    while (a) {
        cmp = strcmp(mot, a->mot);
        if (cmp == 0)
            return a;
        if (cmp < 0)
            a = LEFT_NODE(a);
        else
            a = RIGHT_NODE(a);
    }

    return NULL;
}

bool ABR_appartient(const Mots *ensemble, char* mot) {
    return ABR_cherche_mot(ensemble, mot);
}

void ABR_actualise_max_str_size(Mots* ens, int len) {
    if (len > ens->max_str_len)
        ens->max_str_len = len;
}

MotEntry* ABR_ajout_aux(MotEntry** a, char* mot, int apparition) {
    if (IS_EMPTY_TREE(*a)) {
        *a = ABR_alloue_noeud(mot, apparition);
        return *a;
    }
    if (STR_EQUALS((*a)->mot, mot))
        return *a;
    if (STR_LESS_THAN(mot, (*a)->mot))
        return ABR_ajout_aux(&LEFT_NODE(*a), mot, apparition);
    else
        return ABR_ajout_aux(&RIGHT_NODE(*a), mot, apparition);
}

int ABR_ajouter_mot(Mots *ensemble, char* mot) {

    MotEntry* entry;

    if ((entry = ABR_cherche_mot(ensemble, mot))) {
        entry->nb_occ += 1;
        return 0;
    }

    if (!ABR_ajout_aux(&ensemble->racine, mot, ensemble->len))
        return -1;

    ensemble->len++;
    ABR_actualise_max_str_size(ensemble, strlen(mot));

    return 1;
}

void ABR_libere_helper(MotEntry** a) {
    if (IS_EMPTY_TREE(*a))
        return;

    ABR_libere_helper(&((*a)->fg));
    ABR_libere_helper(&((*a)->fd));
    free((*a)->mot);
    free(*a);

    *a = NULL;
}

void ABR_libere(Mots* ens) {
    ABR_libere_helper(&ens->racine);
    free(ens);
}
