#ifndef TEST_INCLUDED
#define TEST_INCLUDED

#include "algo.h"
#include "mot.h"
#include "tableau.h"
#include "affichage.h"
#include "ABR.h"

#define RED_COLOR "\x1b[31m"
#define GREEN_COLOR "\x1b[32m"
#define RESET_COLOR "\x1b[0m"

#define test_assert(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, RED_COLOR"Erreur d'assertion : "RESET_COLOR "%s:%d: %s : '%s'\n",__FILE__, __LINE__, __func__, #expr); \
            return 0; \
        } else { \
            fprintf(stdout, GREEN_COLOR"Assertion correcte : "RESET_COLOR "%s:%d: %s : '%s'\n",__FILE__, __LINE__, __func__, #expr); \
        } \
    } while (0)

/**
 * @brief Lance tous les tests unitaires.
 * 
 * @return int 
 */
int test();

/* Les fonctions qui testent la fonctionnalité de celles du module mot */
int test_mot_normaliser();


/* tableau */
int test_TAB_arbre_en_tab();

int test_TAB_tri_lexico();

int test_TAB_tri_occ();

int test_TAB_tri_apparition();

int test_TAB_tri();

int test_TAB_compare_tri_occ_decroissant();

int test_TAB_arbre_en_tab_aux();

/* algo */

int test_ALG_mots_avant_x();

int test_ALG_compter_mots();

int test_ALG_mots_apres_x();

#endif
