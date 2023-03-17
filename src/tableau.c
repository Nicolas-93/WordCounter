#include "tableau.h"
#include "ABR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * @brief Macros pour les fonctions de comparaison
 * 
 */
#define CMP_STR_ASC(a, b)       \
    do {                        \
        int cmp = strcmp(a, b); \
        if (cmp > 0) return 1;  \
        if (cmp < 0) return -1; \
    } while(0)

#define CMP_STR_DESC(a, b) \
    CMP_STR_ASC(b, a)

#define CMP_VAL_ASC(a, b)       \
    do {                        \
        int cmp = a - b;        \
        if (cmp > 0) return 1;  \
        if (cmp < 0) return -1; \
    } while(0)

#define CMP_VAL_DESC(a, b) \
    CMP_VAL_ASC(b, a)

#define CMP_EQUALS() return 0

#define CMP_CAST_ENTRIES(a, b) \
    const MotEntry* entry_a = *(MotEntry**)a; \
    const MotEntry* entry_b = *(MotEntry**)b

TriFunc cmp_funcs[2][3] = {
    {
        TAB_compare_tri_lexico_decroissant,
        TAB_compare_tri_occ_decroissant,
        TAB_compare_tri_apparition_decroissant,
    },
    {
        TAB_compare_tri_lexico_croissant,
        TAB_compare_tri_occ_croissant,
        TAB_compare_tri_apparition_croissant,
    },
};

void TAB_arbre_en_tab_aux(MotEntry** tab, MotEntry* arbre, int* i) {
    if (IS_EMPTY_TREE(arbre))
        return;

    TAB_arbre_en_tab_aux(tab, arbre->fg, i);
    tab[(*i)++] = arbre;
    TAB_arbre_en_tab_aux(tab, arbre->fd, i);
}

TabMots* TAB_arbre_en_tab(const Mots* ens) {
    TabMots* tab;

    if (!(tab = malloc(sizeof(TabMots))))
        return NULL;

    if (!(tab->tab = malloc(ens->len * sizeof(MotEntry*)))) {
        free(tab);
        return NULL;
    }
    
    tab->len = ens->len;
    tab->max_str_len = ens->max_str_len;
    
    int i = 0;
    TAB_arbre_en_tab_aux(tab->tab, ens->racine, &i);

    return tab;
}

void TAB_libere(TabMots* mots) {
    free(mots->tab);
    free(mots);
}

void TAB_tri(TabMots* tab, ModeTri mode, bool croissant) {
    TriFunc compare;
    // Vérification des paramètres
    assert(mode >= TRI_LEXICO && mode <= TRI_APPARITION);
    croissant = !!croissant;

    compare = cmp_funcs[croissant][mode];
    qsort(tab->tab, tab->len, sizeof(MotEntry*), compare);
}

// Fonctions de comparaison

int TAB_compare_tri_lexico_croissant(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_STR_ASC(entry_a->mot, entry_b->mot);
    CMP_EQUALS();
}

int TAB_compare_tri_occ_croissant(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_VAL_ASC(entry_a->nb_occ, entry_b->nb_occ);
    CMP_STR_ASC(entry_a->mot, entry_b->mot);
    CMP_EQUALS();
}

int TAB_compare_tri_apparition_croissant(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_VAL_ASC(entry_a->apparition, entry_b->apparition);
    CMP_EQUALS();
}

int TAB_compare_tri_lexico_decroissant(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_STR_DESC(entry_a->mot, entry_b->mot);
    CMP_EQUALS();
}

int TAB_compare_tri_occ_decroissant(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_VAL_DESC(entry_a->nb_occ, entry_b->nb_occ);
    CMP_STR_ASC(entry_a->mot, entry_b->mot);
    CMP_EQUALS();
}

int TAB_compare_tri_apparition_decroissant(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_VAL_DESC(entry_a->apparition, entry_b->apparition);
    CMP_EQUALS();
}
