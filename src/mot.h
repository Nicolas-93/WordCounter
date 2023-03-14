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

#endif
