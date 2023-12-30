#include "test.h"
#include "wordarray.h"
#include "tree.h"
#include <string.h>
#include <stdio.h>

static int test_Word_is_correct();
static int test_Word_to_lower();
static int test_WordArray_sort();
static int test_ALG_words_before_x();
static int test_ALG_count_words();
static int test_ALG_words_after_x();
static int test_ALG_expressions();
static int test_Tree_new();
static int test_Tree_new_node();
static int test_Tree_search_word();
static int test_Tree_in();
static int test_ABR_ajouter_mot();


static char* t1[] = {
    "zzz", "zzz", "zzz", "zzz", "zzz",
    "abc", "abc", "abc", "abc",
    "aaa", "aaa", "aaa",
    "caa", "caa",
    "pfff"
};

TestFunc tests[] = {
    test_Word_to_lower,
    test_Word_is_correct,
    test_Tree_new,
    test_Tree_new_node,
    test_ABR_ajouter_mot,
    test_Tree_search_word,
    test_Tree_in,
    test_ALG_count_words,
    test_WordArray_sort,
    test_ALG_words_before_x,
    test_ALG_words_after_x,
    test_ALG_expressions,
};

int test() {
    for (int i = 0; i < SIZEOF_ARRAY(tests); i++) {
        if (!tests[i]())
            return 0;
    }
    return 1;
}

void test_assert_print(const char* file, int line, const char* func, const char* expr, int res) {
    FILE* stream;
    char* msg;
    if (res) {
        stream = stdout;
        msg = COLOR_STR(COLOR_GREEN, "Assertion correcte : ");
    } else { 
        stream = stderr;
        msg = COLOR_STR(COLOR_RED, "Erreur d'assertion : ");
    } 
    fprintf(stream, 
        "%s"
        COLOR_STR(COLOR_BLUE, "%s:%d : ")
        COLOR_STR(COLOR_YELLOW, "%s : ")
        COLOR_STR(COLOR_R, "'%s'\n"),
        msg, file, line, func, expr);
}

static int test_Word_to_lower() {
    char t1[] = "HelLo WORLd";
    char t2[] = "LicEnCE 1";
    char t3[] = "ù$*ùù Corr$^*ùm*pu";
    
    Word_to_lower(t1);
    Word_to_lower(t2);
    Word_to_lower(t3);

    test_assert(STR_EQUALS(t1, "hello world"));
    test_assert(STR_EQUALS(t2, "licence 1"));
    test_assert(STR_EQUALS(t3, "ù$*ùù corr$^*ùm*pu"));

    return 1;
}

static int test_Word_is_correct() {
    test_assert(Word_is_correct("Hello"));
    test_assert(Word_is_correct(""));
    test_assert(!Word_is_correct("$ù*é-'"));
    test_assert(!Word_is_correct("sa1ut"));
    test_assert(!Word_is_correct("sa1ut3"));
    test_assert(!Word_is_correct("5a1ut"));

    return 1;
}

static int test_WordArray_sort() {

    WordTree* ens1 = Tree_new(), *ens2 = Tree_new();
    
    // Test 1 : Avec le tableau t1 //

    STRING_ARRAY_TO_ENS(t1, ens1);
    WordArray* tab1 = WordArray_from_WordTree(ens1);

    // l'arbre est sensé être déja trié lexicographiquement
    test_assert(STR_EQUALS(tab1->tab[0]->word, "aaa"));
    test_assert(STR_EQUALS(tab1->tab[4]->word, "zzz"));
    
    WordArray_sort(tab1, SORT_LEXICO, false);
    test_assert(STR_EQUALS(tab1->tab[0]->word, "zzz"));
    test_assert(STR_EQUALS(tab1->tab[4]->word, "aaa"));
    
    WordArray_sort(tab1, SORT_APPARITION, true);
    test_assert(STR_EQUALS(tab1->tab[0]->word, "zzz"));
    test_assert(STR_EQUALS(tab1->tab[4]->word, "pfff"));
    
    WordArray_sort(tab1, SORT_NB_OCCURENCES, false);
    test_assert(STR_EQUALS(tab1->tab[0]->word, "zzz"));
    test_assert(STR_EQUALS(tab1->tab[4]->word, "pfff"));

    // Test 2 : Avec le texte sujet_test_ordre.txt //

    FILE* f1 = fopen("textes/sujet_test_ordre.txt", "r");
    test_assert(f1);

    ALG_count_words(ens2, f1);
    WordArray* tab2 = WordArray_from_WordTree(ens2);
    fclose(f1);

    // l'arbre est sensé être déja trié lexicographiquement
    test_assert(STR_EQUALS(tab2->tab[0]->word, "deux"));
    test_assert(STR_EQUALS(tab2->tab[1]->word, "deuxdeux"));
    test_assert(STR_EQUALS(tab2->tab[3]->word, "un"));
    
    WordArray_sort(tab2, SORT_APPARITION, true);
    test_assert(STR_EQUALS(tab2->tab[0]->word, "trois"));
    test_assert(STR_EQUALS(tab2->tab[3]->word, "deuxdeux"));
    
    WordArray_sort(tab2, SORT_NB_OCCURENCES, false);
    test_assert(STR_EQUALS(tab2->tab[0]->word, "deux"));
    test_assert(STR_EQUALS(tab2->tab[3]->word, "trois"));

    // Retrions lexicographiquement
    WordArray_sort(tab2, SORT_LEXICO, true);
    test_assert(STR_EQUALS(tab2->tab[0]->word, "deux"));
    test_assert(STR_EQUALS(tab2->tab[1]->word, "deuxdeux"));
    test_assert(STR_EQUALS(tab2->tab[3]->word, "un"));

    WordArray_free(tab1);
    WordArray_free(tab2);
    Tree_free(ens1);
    Tree_free(ens2);

    return 1;
}

static int test_ALG_count_words() {
    WordTree* ens1 = Tree_new(), *ens2 = Tree_new();
    test_assert(ens1);
    
    FILE* f1 = fopen("textes/sujet_test_mot_suivant_x.txt", "r");
    FILE* f2 = fopen("textes/casse_doublons.txt", "r");
    test_assert(f1 && f2);

    ALG_count_words(ens1, f1);
    ALG_count_words(ens2, f2);
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

    Tree_free(ens1);
    Tree_free(ens2);
    return 1;
}


static int test_ALG_words_after_x() {
    WordTree* ens1 = Tree_new();
    test_assert(ens1);
    
    FILE* f = fopen("textes/sujet_test_mot_suivant_x.txt", "r");
    test_assert(f);

    ALG_words_after_x(ens1, f, "ab");
    fclose(f);

    test_assert(ABR_ASSERT_OCCURENCES(ens1, "ab", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "aaa", 3));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "a", 2));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "b", 2));
    
    test_assert(Tree_search_word(ens1, "abc") == NULL);

    Tree_free(ens1);
    return 1;
}


static int test_ALG_words_before_x() {
    WordTree* ens1 = Tree_new();
    test_assert(ens1);
    
    FILE* f = fopen("textes/sujet_test_mot_suivant_x.txt", "r");
    test_assert(f);

    ALG_words_before_x(ens1, f, "ab");
    fclose(f);

    test_assert(ABR_ASSERT_OCCURENCES(ens1, "a", 3));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "ab", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "aaa", 2));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "b", 1));
    
    test_assert(Tree_search_word(ens1, "abc") == NULL);

    Tree_free(ens1);
    return 1;
}

static int test_ALG_expressions() {
    WordTree* ens1 = Tree_new();
    test_assert(ens1);
    
    FILE* f1 = fopen("textes/sujet_exprs.txt", "r");
    test_assert(f1);

    ALG_expressions(ens1, f1, 2);
    fclose(f1);

    // Vérification des occurences
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "un un", 3));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "un deux", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "deux trois", 2));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "trois trois", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "trois un", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "un trois", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens1, "trois deux", 1));
    
    WordArray* tab1 = WordArray_from_WordTree(ens1);
    
    // Vérification de l'ordre d'id
    WordArray_sort(tab1, SORT_APPARITION, true);
    test_assert(STR_EQUALS(tab1->tab[0]->word, "un un"));
    test_assert(STR_EQUALS(tab1->tab[1]->word, "un deux"));
    test_assert(STR_EQUALS(tab1->tab[2]->word, "deux trois"));
    test_assert(STR_EQUALS(tab1->tab[3]->word, "trois trois"));
    test_assert(STR_EQUALS(tab1->tab[4]->word, "trois un"));
    test_assert(STR_EQUALS(tab1->tab[5]->word, "un trois"));
    test_assert(STR_EQUALS(tab1->tab[6]->word, "trois deux"));

    
    WordTree* ens2 = Tree_new();
    FILE* f2 = fopen("textes/brassens.txt", "r");
    test_assert(f2);

    ALG_expressions(ens2, f2, 3);
    fclose(f2);

    // Vérification des occurences
    test_assert(ABR_ASSERT_OCCURENCES(ens2, "de mon arbre", 2));
    test_assert(ABR_ASSERT_OCCURENCES(ens2, "heureux j aurais", 1));
    test_assert(ABR_ASSERT_OCCURENCES(ens2, "eloigner de mon", 1));

    WordArray* tab2 = WordArray_from_WordTree(ens2);

    // Vérification de l'ordre d'id
    WordArray_sort(tab2, SORT_APPARITION, true);
    test_assert(STR_EQUALS(tab2->tab[0]->word, "aupres de mon"));
    test_assert(STR_EQUALS(tab2->tab[1]->word, "de mon arbre"));
    test_assert(STR_EQUALS(tab2->tab[12]->word, "eloigner de mon"));

    Tree_free(ens1);
    Tree_free(ens2);
    WordArray_free(tab1);
    WordArray_free(tab2);

    return 1;
}

static int test_Tree_new() {
    WordTree* ens = Tree_new();
    test_assert(ens);
    
    test_assert(ens->root == NULL);
    test_assert(ens->len == 0);
    test_assert(ens->max_str_len == 0);

    Tree_free(ens);

    return 1;
}

static int test_Tree_new_node() {
    char* mot = "there is no node";
    WordNode* entry = Tree_new_node(mot, 89);
    test_assert(entry);
    
    test_assert(STR_EQUALS(entry->word, mot));
    test_assert(entry->word != mot); // Le mot est copié
    
    test_assert(entry->fg == NULL);
    test_assert(entry->fd == NULL);
    test_assert(entry->id == 89);
    test_assert(entry->nb_occ == 1);

    Tree_free_helper(&entry);

    return 1;
}

static int test_Tree_search_word() {
    WordTree* ens = Tree_new();
    WordNode* entry;
    test_assert(ens);
    
    // Recherche dans un arbre vide
    entry = Tree_search_word(ens, t1[0]);
    test_assert(entry == NULL);

    // Recherche dans un arbre non vide
    Tree_add_word(ens, t1[0]);
    Tree_add_word(ens, t1[0]);
    Tree_add_word(ens, t1[1]);

    entry = Tree_search_word(ens, t1[0]);
    test_assert(entry != NULL);
    test_assert(STR_EQUALS(entry->word, t1[0]));

    // Recherche d'un mot NULL
    entry = Tree_search_word(ens, NULL);
    test_assert(entry == NULL);

    Tree_free(ens);

    return 1;
}

static int test_Tree_in() {
    WordTree* ens = Tree_new();
    test_assert(ens);

    // Recherche dans un arbre vide
    test_assert(Tree_in(ens, t1[0]) == false);

    // Recherche dans un arbre non vide
    Tree_add_word(ens, t1[0]);
    Tree_add_word(ens, t1[0]);
    Tree_add_word(ens, t1[1]);

    test_assert(Tree_in(ens, t1[0]) == true);

    // Recherche d'un mot inexistant
    test_assert(Tree_in(ens, "Bye!") == false);

    // Recherche d'un mot NULL
    test_assert(Tree_in(ens, NULL) == false);

    Tree_free(ens);
    return 1;
}

static int test_ABR_ajouter_mot() {
    WordTree* ens = Tree_new();
    test_assert(ens);

    STRING_ARRAY_TO_ENS(t1, ens);
    test_assert(ABR_ASSERT_OCCURENCES(ens, "zzz", 5));
    test_assert(ABR_ASSERT_OCCURENCES(ens, "abc", 4));
    test_assert(ABR_ASSERT_OCCURENCES(ens, "aaa", 3));
    test_assert(ABR_ASSERT_OCCURENCES(ens, "caa", 2));
    test_assert(ABR_ASSERT_OCCURENCES(ens, "pfff", 1));

    test_assert(ens->max_str_len == 4);
    test_assert(ens->len == 5);

    // Ajout d'un mot NULL
    test_assert(Tree_add_word(ens, NULL) == -1);

    Tree_free(ens);
    return 1;
}
