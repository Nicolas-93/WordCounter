#ifndef MOT_INCLUDED
#define MOT_INCLUDED
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Vérifie si un mot contient uniquement des
 * caractères alphabétiques.
 *
 * @param mot 
 * @return true Contient uniquement des caractères alphabétiques
 * @return false Si contient des caractères non alphabétiques
 * si pointeur NULL
 */
bool MOT_est_correct(const char* mot);

/**
 * @brief Minusculise le mot
 * 
 * @param rep 
 */
void MOT_normaliser(char* mot);

/**
 * @brief Ecrit le nouveau mot dans mot,
 * et réalloue la mémoire si nécessaire.
 * 
 * @param mot Adresse du mot à remplacer, si NULL, alloue la mémoire
 * @param nouveau_mot Nouveau mot à écrire dans mot
 * @return int 1 si réussi, 0 sinon
 */
int MOT_remplace_mot(char** mot, size_t* bufsize, char* nouveau_mot);

#endif
