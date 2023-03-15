#include "ABR.h"
#include "algo.h"
#include "affichage.h"
#include "tableau.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    Mots* mots = ABR_initialiser();
    FILE* f = fopen("textes/brassens.txt", "r");
    TabMots tab;

    ALG_mots_avant_x(mots, f, "arbre");
    // ALG_compter_mots(mots, f);
    tab = TAB_arbre_en_tab(mots);
    TAB_tri(&tab, TRI_APPARITION, true);
    AFF_print_tab(tab);

    fclose(f);
    ABR_libere(mots);
    TAB_libere(&tab);

    return EXIT_SUCCESS;
}
