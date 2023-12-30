#include "tree.h"
#include "output.h"
#include "wordarray.h"
#include "args.h"
#include <stdlib.h>
#include <stdio.h>

WordTree* execute_lecture(Args params);
WordArray* execute_tri(const WordTree* mots, Args params);

int main(int argc, char* argv[]) {
    
    Args params = ARGS_parse(argc, argv);
    WordTree* mots;
    WordArray* tab;

    mots = ARGS_readfile(params);
    tab = ARGS_sort(mots, params);
    OUT_print_words(tab);

    fclose(params.file);
    Tree_free(mots);
    WordArray_free(tab);

    return EXIT_SUCCESS;
}
