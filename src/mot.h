#ifndef MOT_INCLUDED
#define MOT_INCLUDED
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Vérifie si un mot contient uniquement des
 * caractères alphabétiques.
 *
 * @param mot 
 * @return true 
 * @return false 
 */
bool MOT_est_correct(const char* mot);

// Mot* mot_allouer(char* rep);

// void mot_liberer(Mot* mot);

/**
 * @brief Minusculise le mot/
 * 
 * @param rep 
 */
void MOT_normaliser(char* rep);





#endif