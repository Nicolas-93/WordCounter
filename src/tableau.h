#ifndef TABLEAU_INCLUDED
#define TABLEAU_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include "mot.h"

#define TAILLE_BLOC 150

typedef struct mot {
    char* mot;
    int nb_occ;
} MotEntry;

typedef struct tableau {
    MotEntry* mots;
    int max_str_len;
    int max_size;
    int len;
} TabMots;

/**
 * @brief Trie le tableau par ordre lexicographique
 * 
 * @param tab 
 * @param croissant 
 */
void TAB_tri_lexico(TabMots* tab, bool croissant);

/**
 * @brief Trie le tableau par nombre d'occurences.
 * 
 * @param tab 
 * @param croissant 
 */
void TAB_tri_occ(TabMots* tab, bool croissant);

/**
 * @brief Ajoute un mot au tableau.
 * 
 * @param tab 
 */
int TAB_ajouter_mot(TabMots* tab, char* mot);

/**
 * @brief Adapte la taille du tableau par TAILLE_BLOC
 * 
 * @param tab 
 * @param nv_size 
 * @return int 
 */
bool TAB_redimensionne(TabMots* tab);

/**
 * @brief Cherche et renvoie, en cas d'existence,
 * la position du mot dans le tableau.
 * 
 * @param tab 
 * @return int Index du mot dans le tableau, -1 si inexistance
 */
int TAB_cherche_mot(const TabMots* tab, char* mot);

/**
 * @brief Cherche et supprime le mot du tableau
 * 
 * @param tab 
 * @param mot 
 */
void TAB_supprimer_mot(const TabMots* tab, char* mot);

/**
 * @brief Détermine si le mot existe déjà.
 * 
 * @param tab 
 * @param mot 
 */
bool TAB_appartient(const TabMots* tab, char* mot);

/**
 * @brief Alloue et initialise un tableau sur le tas.
 * 
 * @return TabMots* 
 */
TabMots* TAB_initialiser();


#endif
