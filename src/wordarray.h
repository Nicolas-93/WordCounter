#ifndef TABLEAU_INCLUDED
#define TABLEAU_INCLUDED

#include "tree.h"

typedef struct WordArray {
    WordNode** tab;
    int len;
    int max_str_len;
} WordArray;

typedef enum SortMode {
    SORT_LEXICO = 0,
    SORT_NB_OCCURENCES = 1,
    SORT_APPARITION = 2,
} SortMode;

typedef int (*TriFunc)(const void*, const void*);

/**
 * @brief Create a new array of pointers to nodes from a word tree.
 * The array is sorted lexicographically.
 * 
 * @param ens 
 * @return WordArray* 
 */
WordArray* WordArray_from_WordTree(const WordTree* self);

/**
 * @brief Free the array.
 * 
 * @param mots 
 */
void WordArray_free(WordArray* self); 

/**
 * @brief Sort the array according to the given mode.
 * 
 * @param tab 
 * @param mode 
 * @param ascending 
 */
void WordArray_sort(WordArray* self, SortMode mode, bool ascending);


// Lexicographic order
int WordArray_cmp_lexico_asc(const void* a, const void* b);
int WordArray_cmp_lexico_desc(const void* a, const void* b);

// Order by number of occurrences
int WordArray_cmp_occ_asc(const void* a, const void* b);
int WordArray_cmp_occ_desc(const void* a, const void* b);

// Order by first appearance
int WordArray_cmp_appearance_asc(const void* a, const void* b);
int WordArray_cmp_appearance_desc(const void* a, const void* b);

/**
 * @brief Helper function to create an array representing the tree
 * using an infix traversal. The tree being sorted in lexicographic
 * order, the function should naturally return a sorted array
 * pointing to the nodes according to this order.
 * 
 * @param tab Destination array
 * @param arbre Source tree
 * @param i Pointer to the index of the array initially set to 0
 */
void WordArray_from_WordTree_helper(WordNode** self, WordNode* tree, int* i);

extern TriFunc cmp_funcs[2][3];

#endif
