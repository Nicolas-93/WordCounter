#include "tableau.h"
#include "ABR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int (*cmp_funcs[2][3])(const void* a, const void* b) = {
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

TabMots TAB_arbre_en_tab(const Mots* ens) {
    TabMots tab;
    tab.len = ens->len;
    tab.tab = malloc(tab.len * sizeof(MotEntry*));
    tab.max_str_len = ens->max_str_len;
    
    int i = 0;
    TAB_arbre_en_tab_aux(tab.tab, ens->racine, &i);

    return tab;
}

void TAB_libere(TabMots* mots) {
    free(mots->tab);
}

void TAB_tri(TabMots* tab, ModeTri mode, bool croissant) {
    int (*compare)(const void* a, const void* b);
    
    // Vérification des paramètres
    assert(mode >= TRI_LEXICO && mode <= TRI_APPARITION);
    croissant = !!croissant;

    compare = cmp_funcs[croissant][mode];
    qsort(tab->tab, tab->len, sizeof(MotEntry*), compare);
}

// Fonctions de comparaison

int TAB_compare_tri_lexico_croissant(const void* a, const void* b) {
    const MotEntry* entry_a = *(MotEntry**)a;
    const MotEntry* entry_b = *(MotEntry**)b;

    return strcmp(entry_a->mot, entry_b->mot);
}

int TAB_compare_tri_occ_croissant(const void* a, const void* b) {
    const MotEntry* entry_a = *(MotEntry**)a;
    const MotEntry* entry_b = *(MotEntry**)b;
    
    return entry_a->nb_occ - entry_b->nb_occ;
}

int TAB_compare_tri_apparition_croissant(const void* a, const void* b) {
    const MotEntry* entry_a = *(MotEntry**)a;
    const MotEntry* entry_b = *(MotEntry**)b;
    
    return entry_a->apparition - entry_b->apparition;
}

int TAB_compare_tri_lexico_decroissant(const void* a, const void* b) {
    return -TAB_compare_tri_lexico_croissant(a, b);
}

int TAB_compare_tri_occ_decroissant(const void* a, const void* b) {
    return -TAB_compare_tri_occ_croissant(a, b);
}

int TAB_compare_tri_apparition_decroissant(const void* a, const void* b) {
    return -TAB_compare_tri_apparition_croissant(a, b);
}
