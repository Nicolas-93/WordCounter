#ifndef TEST_INCLUDED
#define TEST_INCLUDED

#include "algo.h"
#include "mot.h"
#include "tableau.h"
#include "affichage.h"
#include "ABR.h"

int test();

/* Les fonctions qui testent la fonctionnalité de celles du module mot */
int test_mot_normaliser();


/* tableau */
int test_TAB_arbre_en_tab();

int test_TAB_tri_lexico();

int test_TAB_tri_occ();

int test_TAB_tri_apparition();

int test_TAB_tri();

int test_TAB_compare_tri_lexico_croissant();

int test_TAB_compare_tri_lexico_decroissant();

int test_TAB_compare_tri_occ_croissant();

int test_TAB_compare_tri_occ_decroissant();

int test_TAB_compare_tri_apparition_croissant();

int test_TAB_compare_tri_apparition_decroissant();

int test_TAB_arbre_en_tab_aux();

/* algo */

int test_ALG_mots_avant_x();

int test_ALG_compter_mots();

int test_ALG_mots_apres_x();





#endif