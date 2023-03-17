#include "test.h"
#include "tableau.h"
#include "ABR.h"
#include <string.h>
#include <stdio.h>


static char* t1[] = {
    "zzz", "zzz", "zzz", "zzz", "zzz",
    "abc", "abc", "abc", "abc",
    "aaa", "aaa", "aaa",
    "caa", "caa",
    "pfff"
};

TestFunc tests[] = {
        test_MOT_normaliser,
        test_TAB_tri,
        test_ALG_compter_mots,
        test_ALG_mots_apres_x,
        test_ALG_mots_avant_x,
        test_ABR_initialiser,
        test_ABR_alloue_noeud,
        // test_ABR_cherche_mot,
        // test_ABR_appartient,
        // test_ABR_actualise_max_str_size,
        // test_ABR_ajout_aux,
        // test_ABR_ajouter_mot,
};

int test() {
    int res = 1;
    for (int i = 0; i < SIZEOF_ARRAY(tests); i++) {
        res &= tests[i]();
    }
    return res;
}

int test_MOT_normaliser() {
    char t1[] = "HelLo WORLd";
    char t2[] = "LicEnCE 1";
    char t3[] = "ù$*ùù Corr$^*ùm*pu";
    
    MOT_normaliser(t1);
    MOT_normaliser(t2);
    MOT_normaliser(t3);

    test_assert(STR_EQUALS(t1, "hello world"));
    test_assert(STR_EQUALS(t2, "licence 1"));
    test_assert(STR_EQUALS(t3, "ù$*ùù corr$^*ùm*pu"));

    return 1;
}

int test_TAB_tri() {

    Mots* ens1 = ABR_initialiser();
    
    STRING_ARRAY_TO_ENS(t1, ens1);
    TabMots* tab = TAB_arbre_en_tab(ens1);
    // l'arbre est sense etre deja trie lexicographiquement
    test_assert(STR_EQUALS(tab->tab[0]->mot, "aaa"));
    test_assert(STR_EQUALS(tab->tab[4]->mot, "zzz"));
    
    TAB_tri(tab, TRI_LEXICO, false);
    test_assert(STR_EQUALS(tab->tab[0]->mot, "zzz"));
    test_assert(STR_EQUALS(tab->tab[4]->mot, "aaa"));
    
    TAB_tri(tab, TRI_APPARITION, true);
    test_assert(STR_EQUALS(tab->tab[0]->mot, "zzz"));
    test_assert(STR_EQUALS(tab->tab[4]->mot, "pfff"));
    
    TAB_tri(tab, TRI_NB_OCCURENCES, false);
    test_assert(STR_EQUALS(tab->tab[0]->mot, "zzz"));
    test_assert(STR_EQUALS(tab->tab[4]->mot, "pfff"));

    TAB_libere(tab);
    ABR_libere(ens1);
    return 1;
}

int test_ALG_compter_mots() {
    Mots* ens1 = ABR_initialiser(), *ens2 = ABR_initialiser();
    test_assert(ens1);
    
    FILE* f1 = fopen("textes/sujet_test_mot_suivant_x.txt", "r");
    FILE* f2 = fopen("textes/casse_doublons.txt", "r");
    test_assert(f1 && f2);

    ALG_compter_mots(ens1, f1);
    ALG_compter_mots(ens2, f2);
    fclose(f1);
    fclose(f2);

    test_assert(ABR_ASSERT_OCCURENCES(ens1, "ab", 8));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "aaa", 3));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "abc", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "a", 3));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "b", 3));
    
    test_assert(ABR_ASSERT_OCCURENCES(ens2, "bonjour", 2));
    test_assert(ABR_ASSERT_OCCURENCES(ens2, "salut", 3));
    test_assert(ABR_ASSERT_OCCURENCES(ens2, "voila", 1));

    ABR_libere(ens1);
    ABR_libere(ens2);
    return 1;
}


int test_ALG_mots_apres_x() {
    Mots* ens1 = ABR_initialiser();
    test_assert(ens1);
    
    FILE* f = fopen("textes/sujet_test_mot_suivant_x.txt", "r");
    test_assert(f);

    ALG_mots_apres_x(ens1, f, "ab");
    fclose(f);

    test_assert(ABR_ASSERT_OCCURENCES(ens1, "ab", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "aaa", 3));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "a", 2));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "b", 2));
    
    test_assert(ABR_cherche_mot(ens1, "abc") == NULL);

    ABR_libere(ens1);
    return 1;
}


int test_ALG_mots_avant_x() {
    Mots* ens1 = ABR_initialiser();
    test_assert(ens1);
    
    FILE* f = fopen("textes/sujet_test_mot_suivant_x.txt", "r");
    test_assert(f);

    ALG_mots_avant_x(ens1, f, "ab");
    fclose(f);

    test_assert(ABR_ASSERT_OCCURENCES(ens1, "a", 3));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "ab", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "aaa", 2));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "b", 1));
    
    test_assert(ABR_cherche_mot(ens1, "abc") == NULL);

    ABR_libere(ens1);
    return 1;
}

int test_ABR_initialiser() {
    Mots* ens = ABR_initialiser();
    test_assert(ens);
    
    test_assert(ens->racine == NULL);
    test_assert(ens->len == 0);
    test_assert(ens->max_str_len == 0);

    ABR_libere(ens);

    return 1;
}

int test_ABR_alloue_noeud() {
    char* mot = "there is no node";
    MotEntry* entry = ABR_alloue_noeud(mot, 89);
    test_assert(entry);
    
    test_assert(STR_EQUALS(entry->mot, mot));
    test_assert(entry->mot != mot); // Le mot est copié
    
    test_assert(entry->fg == NULL);
    test_assert(entry->fd == NULL);
    test_assert(entry->apparition == 89);
    test_assert(entry->nb_occ == 1);

    ABR_libere_helper(&entry);

    return 1;
}
