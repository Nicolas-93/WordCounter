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
        TriFunc func;
    } tri;

    ModeRecherche mode;
    union {
        char* mot;
        int len_expr;
    } recherche;

    bool test_unitaire;

} Parameters;

Parameters ARGS_parse(int argc, char* argv[]);
void ARGS_print_help(char* progname);
TabMots* ARGS_execute_tri(const Mots* mots, Parameters params);
Mots* ARGS_execute_lecture(Parameters params);

#endif
