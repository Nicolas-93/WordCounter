#include "wordarray.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define CMP_STR_ASC(a, b)       \
    do {                        \
        int cmp = strcmp(a, b); \
        if (cmp > 0) return 1;  \
        if (cmp < 0) return -1; \
    } while(0)

#define CMP_STR_DESC(a, b) \
    CMP_STR_ASC(b, a)

#define CMP_VAL_ASC(a, b)       \
    do {                        \
        int cmp = a - b;        \
        if (cmp > 0) return 1;  \
        if (cmp < 0) return -1; \
    } while(0)

#define CMP_VAL_DESC(a, b) \
    CMP_VAL_ASC(b, a)

#define CMP_EQUALS() return 0

#define CMP_CAST_ENTRIES(a, b) \
    const WordNode* entry_a = *(WordNode**)a; \
    const WordNode* entry_b = *(WordNode**)b

TriFunc cmp_funcs[2][3] = {
    {
        WordArray_cmp_lexico_desc,
        WordArray_cmp_occ_desc,
        WordArray_cmp_appearance_desc,
    },
    {
        WordArray_cmp_lexico_asc,
        WordArray_cmp_occ_asc,
        WordArray_cmp_appearance_asc,
    },
};

void WordArray_from_WordTree_helper(WordNode** self, WordNode* tree, int* i) {
    if (IS_EMPTY_TREE(tree))
        return;

    WordArray_from_WordTree_helper(self, tree->fg, i);
    self[(*i)++] = tree;
    WordArray_from_WordTree_helper(self, tree->fd, i);
}

WordArray* WordArray_from_WordTree(const WordTree* self) {
    WordArray* arr;

    if (!(arr = malloc(sizeof(WordArray))))
        return NULL;

    if (!(arr->tab = malloc(self->len * sizeof(WordNode*)))) {
        free(arr);
        return NULL;
    }
    
    arr->len = self->len;
    arr->max_str_len = self->max_str_len;
    
    int i = 0;
    WordArray_from_WordTree_helper(arr->tab, self->root, &i);

    return arr;
}

void WordArray_free(WordArray* mots) {
    free(mots->tab);
    free(mots);
}

void WordArray_sort(WordArray* self, SortMode mode, bool ascending) {
    TriFunc compare;
    // Vérification des paramètres
    assert(mode >= SORT_LEXICO && mode <= SORT_APPARITION);
    ascending = !!ascending;

    compare = cmp_funcs[ascending][mode];
    qsort(self->tab, self->len, sizeof(WordNode*), compare);
}

// Fonctions de comparaison

int WordArray_cmp_lexico_asc(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_STR_ASC(entry_a->word, entry_b->word);
    CMP_EQUALS();
}

int WordArray_cmp_occ_asc(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_VAL_ASC(entry_a->nb_occ, entry_b->nb_occ);
    CMP_STR_ASC(entry_a->word, entry_b->word);
    CMP_EQUALS();
}

int WordArray_cmp_appearance_asc(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_VAL_ASC(entry_a->id, entry_b->id);
    CMP_EQUALS();
}

int WordArray_cmp_lexico_desc(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_STR_DESC(entry_a->word, entry_b->word);
    CMP_EQUALS();
}

int WordArray_cmp_occ_desc(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_VAL_DESC(entry_a->nb_occ, entry_b->nb_occ);
    CMP_STR_ASC(entry_a->word, entry_b->word);
    CMP_EQUALS();
}

int WordArray_cmp_appearance_desc(const void* a, const void* b) {
    CMP_CAST_ENTRIES(a, b);

    CMP_VAL_DESC(entry_a->id, entry_b->id);
    CMP_EQUALS();
}
