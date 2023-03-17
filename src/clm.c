#include "ABR.h"
#include "affichage.h"
#include "tableau.h"
#include "args.h"
#include <stdlib.h>
#include <stdio.h>

Mots* execute_lecture(Parameters params);
TabMots* execute_tri(const Mots* mots, Parameters params);

int main(int argc, char* argv[]) {
    
    Parameters params = ARGS_parse(argc, argv);
    Mots* mots;
    TabMots* tab;

    mots = ARGS_execute_lecture(params);
    tab = ARGS_execute_tri(mots, params);
    AFF_print_tab(tab);

    fclose(params.file);
    ABR_libere(mots);
    TAB_libere(tab);

    return EXIT_SUCCESS;
}
