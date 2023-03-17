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

/* Les fonctions qui testent la fonctionnalité de celles du module mot */
int test_MOT_normaliser();


/* tableau */
int test_TAB_arbre_en_tab();

int test_TAB_tri();

/* algo */

int test_ALG_mots_avant_x();

int test_ALG_compter_mots();

int test_ALG_mots_apres_x();

/* ABR */

int test_ABR_initialiser();

int test_ABR_alloue_noeud();

int test_ABR_cherche_mot();

int test_ABR_appartient();

int test_ABR_ajouter_mot();

#endif
