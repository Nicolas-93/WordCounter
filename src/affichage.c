#include <stdio.h>
#include "affichage.h"

void AFF_print_tab(const TabMots* tab) {

    for(int i = 0; i < tab->len; ++i)
        printf("%*s %d", tab->max_str_len, tab->mots[i], tab->mots[i].nb_occ);

    putchar("\n");
}
