#ifndef TEST_INCLUDED
#define TEST_INCLUDED

#include "algo.h"
#include "mot.h"
#include "tableau.h"
#include "affichage.h"
#include "ABR.h"
#include <stdio.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_R "\x1b[0m"

#define COLOR_STR(color, str) color str COLOR_R

#define test_assert(expr) \
    do { \
        int res = !!(expr); \
        test_assert_print(__FILE__, __LINE__, __func__, #expr, res); \
        if (!(res)) { \
            return 0; \
        } \
    } while (0)

#define SIZEOF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

#define STRING_ARRAY_TO_ENS(array, ens) \
    do { \
        for (int i = 0; i < SIZEOF_ARRAY(array); i++) { \
            ABR_ajouter_mot(ens, array[i]); \
        } \
    } while (0)

#define ABR_ASSERT_OCCURENCES(ens, mot, nb) \
    (ABR_cherche_mot(ens, mot)->nb_occ == (nb))

typedef int (*TestFunc)(void);

/**
 * @brief Lance tous les tests unitaires.
 * 
 * @return int 
 */
int test();

/**
 * @brief Affiche le résultat d'une assertion.
 * 
 */
void test_assert_print(const char* file, int line, const char* func, const char* expr, int res) ;

/* mot */
int test_MOT_est_correct();

int test_MOT_normaliser();

/* tableau */
int test_TAB_arbre_en_tab();

int test_TAB_tri();

/* algo */

int test_ALG_mots_avant_x();

int test_ALG_compter_mots();

int test_ALG_mots_apres_x();

int test_ALG_expressions();

/* ABR */

int test_ABR_initialiser();

int test_ABR_alloue_noeud();

int test_ABR_cherche_mot();

int test_ABR_appartient();

int test_ABR_ajouter_mot();

#endif
