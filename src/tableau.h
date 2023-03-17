#ifndef TABLEAU_INCLUDED
#define TABLEAU_INCLUDED

#include "ABR.h"

typedef struct TabMots {
    MotEntry** tab;
    int len;
    int max_str_len;
} TabMots;

typedef enum ModeTri {
    TRI_LEXICO = 0,
    TRI_NB_OCCURENCES = 1,
    TRI_APPARITION = 2,
} ModeTri;

typedef int (*TriFunc)(const void*, const void*);

/**
 * @brief Transforme l'arbre en un tableau de pointeurs
 * vers des noeuds de l'arbre.
 * Le tableau est trié selon l'ordre lexicographique.
 * 
 * @param ens 
 * @return TabMots* 
 */
TabMots* TAB_arbre_en_tab(const Mots* ens);

/**
 * @brief Libère la mémoire alloué pour un tableau
 * de pointeurs sur noeuds.
 * 
 * @param mots 
 */
void TAB_libere(TabMots* mots); 

/**
 * @brief Trie le tableau selon mode défini.
 * 
 * @param tab 
 * @param mode 
 * @param croissant 
 */
void TAB_tri(TabMots* tab, ModeTri mode, bool croissant);

/**
 * Fonction de comparaison
*/

// Ordre lexicographique
int TAB_compare_tri_lexico_croissant(const void* a, const void* b);
int TAB_compare_tri_lexico_decroissant(const void* a, const void* b);

// Ordre sur le nombre d'occurrences
int TAB_compare_tri_occ_croissant(const void* a, const void* b);
int TAB_compare_tri_occ_decroissant(const void* a, const void* b);

// Ordre par apparition dans le texte
int TAB_compare_tri_apparition_croissant(const void* a, const void* b);
int TAB_compare_tri_apparition_decroissant(const void* a, const void* b);

/**
 * @brief Fonction auxillière permettant de créer un tableau
 * représantant l'arbre à l'aide d'un parcours infixe.
 * L'arbre étant trié par ordre lexicographique, la fonction
 * devrait natuellement renvoyer un tableau trié pointant
 * vers les noeuds selon cet ordre.
 * 
 * @param tab Addresse d'un tableau vers des pointeurs de noeuds.
 * @param arbre Arbre source
 * @param i Adresse d'un entier initialisé à 0.
 */
void TAB_arbre_en_tab_aux(MotEntry** tab, MotEntry* arbre, int* i);

extern int (*cmp_funcs[2][3])(const void* a, const void* b);

#endif
