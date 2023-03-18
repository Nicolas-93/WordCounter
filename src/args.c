#include <getopt.h>
#include "args.h"
#include "algo.h"
#include "tableau.h"
#include "test.h"

Parameters ARGS_parse(int argc, char* argv[]) {
    Parameters params = {
        .mode = MODE_COMPTER_MOTS,
        .tri = {
            .mode = TRI_APPARITION,
            .croissant = true,
        },
        .recherche = {
            .mot = NULL,
            .len_expr = 0,
        },
        .file = NULL,
        .test_unitaire = false,
    };

    int force_ordre_tri = -1;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"apparition", no_argument, 0, 'f'},
        {"lexico", no_argument, 0, 'a'},
        {"occ", no_argument, 0, 'n'},
        {"croissant", no_argument, 0, 'c'},
        {"decroissant", no_argument, 0, 'd'},
        {"avant", required_argument, 0, 'p'},
        {"apres", required_argument, 0, 's'},
        {"expr", required_argument, 0, 'e'},
        {"test", no_argument, 0, 't'},
        {0, 0, 0, 0},
    };

    int opt;
    int option_index = 0;

    while ((opt = getopt_long_only(argc, argv, "hanfcdtp:s:e:", long_options, &option_index)) != EOF) {
        switch (opt) {
        case 'a':
            params.tri.mode = TRI_LEXICO;
            params.tri.croissant = true;
            break;
        case 'n':
            params.tri.mode = TRI_NB_OCCURENCES;
            params.tri.croissant = false;
            break;
        case 'f':
            params.tri.mode = TRI_APPARITION;
            params.tri.croissant = true;
            break;
        
        case 'c':
            force_ordre_tri = true;
            break;
        case 'd':
            force_ordre_tri = false;
            break;

        case 'p':
            params.mode = MODE_MOTS_AVANT_X;
            params.recherche.mot = optarg;
            break;
        case 's':
            params.mode = MODE_MOTS_APRES_X;
            params.recherche.mot = optarg;
            break;
        case 't':
            params.test_unitaire = true;
            break;

        case 'e':
            params.mode = MODE_EXPRESSION;
            if ((params.recherche.len_expr = atoi(optarg)) < 2) {
                fprintf(
                    stderr,
                    "Erreur: la longueur de l'expression "
                    "doit être un entier supérieur ou égal à 2.\n");
                exit(EXIT_FAILURE);
            }
            break;

        case '?':
        case 'h':
            ARGS_print_help(argv[0]);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }

    if (force_ordre_tri != -1)
        params.tri.croissant = force_ordre_tri;

    if (params.test_unitaire)
        exit(!test());

    if (optind == argc) {
        fprintf(stderr, "Erreur: aucun fichier spécifié.\n");
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        params.filename = argv[optind];

        if (!(params.file = fopen(params.filename, "r"))) {
            perror("Erreur d'ouverture de fichier :");
            exit(EXIT_FAILURE);
        }
    }

    return params;
}

void ARGS_print_help(char* progname) {
    printf(
        "Usage : %s [OPTION]... [FICHIER]\n"
        "Options:\n"
        "  -h, --help\t\tAffiche ce message d'aide.\n"
        "  -f, --apparition\tTrie les mots par ordre d'apparition dans le texte. (Défaut)\n"
        "  -a, --lexico\t\tTrie les mots par ordre lexicographique croissant.\n"
        "  -n, --occ\t\tTrie les mots par nombre d'occurences décroissant, puis par ordre lexicographique.\n"
        "  -c, --croissant\tForce le tri par ordre croissant.\n"
        "  -d, --decroissant\tForce le tri par ordre décroissant.\n"
        "  -p, --avant=MOT\tAffiche les mots avant le mot MOT.\n"
        "  -s, --apres=MOT\tAffiche les mots après le mot MOT.\n"
        "  -e, --expr=N\t\tAffiche les expressions de longueur N mots.\n"
        "  -test\t\t\tExécute les tests unitaires.\n",
        progname);   
}

Mots* ARGS_execute_lecture(Parameters params) {

    Mots* mots = NULL;
    mots = ABR_initialiser();
    // mots->racine = NULL;

    switch (params.mode) {
    case MODE_COMPTER_MOTS:
        ALG_compter_mots(mots, params.file);
        break;
    case MODE_MOTS_AVANT_X:
        ALG_mots_avant_x(mots, params.file, params.recherche.mot);
        break;
    case MODE_MOTS_APRES_X:
        ALG_mots_apres_x(mots, params.file, params.recherche.mot);
        break;
    case MODE_EXPRESSION:
        ALG_expressions(mots, params.file, params.recherche.len_expr);
        break;
    default:
        break;
    }

    return mots;
}

TabMots* ARGS_execute_tri(const Mots* mots, Parameters params) {
    TabMots* tab;
    tab = TAB_arbre_en_tab(mots);
    TAB_tri(tab, params.tri.mode, params.tri.croissant);

    return tab;
}
