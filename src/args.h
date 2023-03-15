#ifndef ARGS_INCLUDED
#define ARGS_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include "tableau.h"
#include "algo.h"

typedef struct Parameters {
    char* filename;
    FILE* file;

    struct {
        ModeTri mode;
        bool croissant;
    } tri;

    ModeRecherche mode;
    union {
        char* mot;
        int len_expr;
    } recherche;

    bool test_unitaire;

} Parameters;

Parameters parse_args(int argc, char* argv[]);

#endif
