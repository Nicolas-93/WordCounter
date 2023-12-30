#ifndef ARGS_INCLUDED
#define ARGS_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include "wordarray.h"
#include "algo.h"

typedef struct Args {
    char* filename;
    FILE* file;

    struct {
        SortMode mode;
        bool ascending;
    } tri;

    SearchMode mode;
    union {
        char* word;
        int len_expr;
    } search;

    bool unittest;

} Args;

Args ARGS_parse(int argc, char* argv[]);
void ARGS_print_help(char* progname);
WordArray* ARGS_sort(const WordTree* mots, Args params);
WordTree* ARGS_readfile(Args params);

#endif
