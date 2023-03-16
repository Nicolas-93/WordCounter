#ifndef ALGO_INCLUDED
#define ALGO_INCLUDED

#include "ABR.h"
#include "mot.h"
#include <stdio.h>
#include <string.h>

#define SEPARATORS " \n,;:.?!\\\"()-'’"

#define FOREACH_TOKEN(token, line) \
    for (token = strtok(line, SEPARATORS), MOT_normaliser(token); \
         token;                                                   \
         token = strtok(NULL, SEPARATORS), MOT_normaliser(token))

typedef enum ModeRecherche {
    MODE_COMPTER_MOTS = 0,
    MODE_MOTS_AVANT_X = 1,
    MODE_MOTS_APRES_X = 2,
    MODE_EXPRESSION = 4,
} ModeRecherche;

/**
 * @brief Crée un tableau contenant les mots qui suivent
 * le mot x, depuis le fichier f.
 * (Option s)
 * 
 * @param dest Adresse du tableau de destination
 * @param f 
 * @return int 
 */
int ALG_mots_apres_x(Mots* dest, FILE* f, char* x);


/**
 * @brief Crée un tableau contenant les mots qui précèdent
 * le mot x, depuis le fichier f.
 * (Option s)
 * 
 * @param dest Adresse du tableau de destination
 * @param f 
 * @return int 
 */
int ALG_mots_avant_x(Mots* dest, FILE* f, char* x);

/**
 * @brief Compte le nombre d'occurences de tous les mots.
 * 
 * @param dest 
 * @param f 
 * @return int 
 */
int ALG_compter_mots(Mots* dest, FILE* f);

#endif
