#ifndef ABR_INCLUDED
#define ABR_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include "mot.h"

typedef struct mot_entry {
    char* mot;
    int nb_occ;
    int apparition;
    struct mot_entry* fg;
    struct mot_entry* fd;
} MotEntry;

typedef struct tableau {
    MotEntry* racine;
    int max_str_len;
    int len;
} Mots;


// Fonctions de comparaison nécessaires pour un ABR
#define LESS_THAN(a, b)         (strcmp((a), (b)) <  0)
#define GREATHER_THAN(a, b)     (strcmp((a), (b)) >  0)
#define GREATHER_OR_EQUAL(a, b) (strcmp((a), (b)) >= 0)
#define LESS_OR_EQUAL(a, b)     (strcmp((a), (b)) <= 0)
#define EQUALS(a, b)            (strcmp((a), (b)) == 0)

// Initialisation d'un arbre
#define BTREE_INIT(tree) ((tree) = NULL)
#define IS_INTERN_NODE(node) (node->fg || node->fd)
#define IS_LEAF_NODE(node) (!(node->fg || node->fd))
#define IS_EMPTY_TREE(tree) (!(tree))
#define IS_COMPLETE_NODE(node) (node->fg && node->fd)
#define IS_BINARY_NODE(node) (IS_COMPLETE_NODE(node) || IS_LEAF_NODE(node))
#define LEFT_NODE(node) ((node)->fg)
#define RIGHT_NODE(node) ((node)->fd)

/**
 * Fonction publiques
 */

/**
 * @brief Alloue et initialise un ensemble Mots sur le tas.
 * 
 * @return TabMots* 
 */
Mots* ABR_initialiser();

/**
 * @brief Ajoute un mot, et alloue un mot au tableau.
 * 
 * @param tab 
 * @return int
 * - 1 en cas de succès
 * - 0 si le mot existe déjà (incrémentation de
 * son nombre d'occurences)
 * - -1 en cas d'erreur d'allocation
 */
int ABR_ajouter_mot(Mots* ens, char* mot);

/**
 * @brief Cherche un mot dans l'arbre et renvoie son
 * noeud.
 * 
 * @param tab 
 * @param mot 
 */
MotEntry* ABR_cherche_mot(const Mots* ens, char* mot);

/**
 * @brief Détermine si le mot existe déjà.
 * 
 * @param tab 
 * @param mot 
 */
bool ABR_appartient(const Mots* ens, char* mot);

/**
 * @brief Libère la mémoire allouée par l'ensemble.
 * 
 * @param ens 
 */
void ABR_libere(Mots* ens);


/**
 * Fonction privées
 */

/**
 * @brief Alloue et initialise un noeud avec une
 * copie du mot.
 * 
 * @param mot Mot à ajouter à l'arbre
 * @param apparition Numéro du noeud (correspond à la taille
 * de l'ensemble, au moment de l'insertion, et permet de
 * conserver l'ordre d'insertion).
 * @return MotEntry* 
 */
MotEntry* ABR_alloue_noeud(char* mot, int apparition);

/**
 * @brief Actualise la variable qui maintient la taille
 * maximum d'un mot de l'ensemble.
 * 
 * @param ens 
 * @param len Longueur du mot ajouté
 */
void ABR_actualise_max_str_size(Mots* ens, int len);

/**
 * @brief Fonction auxilière récursive permettant
 * l'ajout d'un noeud à l'arbre.
 * 
 * @param a 
 * @param mot 
 * @param apparition 
 * @return MotEntry* 
 */
MotEntry* ABR_ajout_aux(MotEntry** a, char* mot, int apparition);

/**
 * @brief Fonction auxilière récursive permettant
 * la libération de la mémoire alloué par l'arbre.
 * 
 * @param a 
 */
void ABR_libere_helper(MotEntry** a);

#endif
