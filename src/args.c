#include <getopt.h>
#include "args.h"
#include "algo.h"

Parameters parse_args(int argc, char* argv[]) {
    Parameters params = {
        .mode = MODE_COMPTER_MOTS,
        .tri = {
            .mode = TRI_APPARITION,
            .croissant = true,
        },
        .file = NULL,
        .tri = TRI_APPARITION,
        .test_unitaire = false,
    };

    int opt;
    while ((opt = getopt(argc, argv, "hanp:s:e:")) != EOF) {
        switch (opt) {

            case 'a':
                params.tri.mode = TRI_LEXICO;
                params.tri.croissant = true;
                break;
            case 'n':
                params.tri.mode = TRI_NB_OCCURENCES;
                params.tri.croissant = false;
                break;

            case 'p':
                params.mode = MODE_MOTS_AVANT_X;
            case 's':
                params.mode = MODE_MOTS_APRES_X;
            case 'p':
            case 's':
                params.recherche.mot = optarg;
                break;

            case 'e':
                params.mode = MODE_EXPRESSION;
                if (!(params.recherche.len_expr = atoi(optarg))) {
                    fprintf(
                        stderr,
                        "Erreur: la longueur de l'expression"
                        "doit être supérieur ou égale à 1.\n");
                }
                break;
            case 'h':
                break;
            case '?':

            default:
                break;
        }
    }

    if (optind < argc) {

        // Pour respecter la consigne, et ne pas utiliser getopt_long_only
        if (strcmp(argv[optind], "-test") == 0) {
            params.test_unitaire = true;
        }
        else
            params.filename = argv[optind];

        if (!(params.file = fopen(params.filename, "r"))) {
            perror("Erreur d'ouverture de fichier :");
            exit(EXIT_FAILURE);
        }
    }

    return params;
}
