#ifndef TEST_INCLUDED
#define TEST_INCLUDED

#include "algo.h"
#include "wordtree.h"
#include "wordarray.h"
#include "output.h"
#include "tree.h"
#include <stdio.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_R "\x1b[0m"

#define COLOR_STR(color, str) color str COLOR_R

/**
 * @brief Affiche le résultat d'une assertion
 * mais ne quitte pas le programme.
 * 
 */
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
            Tree_add_word(ens, array[i]); \
        } \
    } while (0)

#define ABR_ASSERT_OCCURENCES(ens, mot, nb) \
    (Tree_search_word(ens, mot)->nb_occ == (nb))

typedef int (*TestFunc)(void);

/**
 * @brief LRun unit tests.
 * 
 * @return int 
 */
int test(void);

/**
 * @brief Print the result of an assertion.
 * 
 */
void test_assert_print(const char* file, int line, const char* func, const char* expr, int res) ;

#endif
