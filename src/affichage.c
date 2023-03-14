#include <stdio.h>
#include "affichage.h"
#include "tableau.h"

void AFF_print_tab(const TabMots tab) {
    for(int i = 0; i < tab.len; ++i) {
        // fprintf(stderr, "tab[%d]=%s\n", i, tab.tab[i]->mot);
        printf("%-*s %d\n", tab.max_str_len, tab.tab[i]->mot, tab.tab[i]->nb_occ);
    }
}
