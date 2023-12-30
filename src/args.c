#include <getopt.h>
#include "args.h"
#include "algo.h"
#include "wordarray.h"
#include "test.h"

Args ARGS_parse(int argc, char* argv[]) {
    Args params = {
        .mode = MODE_COUNT_WORDS,
        .tri = {
            .mode = SORT_APPARITION,
            .ascending = true,
        },
        .search = {
            .word = NULL,
            .len_expr = 0,
        },
        .file = NULL,
        .unittest = false,
    };

    int force_sort_order = -1;

    static struct option long_options[] = {
        {"help",        no_argument,        0, 'h'},
        {"apparition",  no_argument,        0, 'f'},
        {"lexico",      no_argument,        0, 'l'},
        {"occ",         no_argument,        0, 'n'},
        {"ascending",   no_argument,        0, 'u'},
        {"descending",  no_argument,        0, 'd'},
        {"test",        no_argument,        0, 't'},
        {"before",      required_argument,  0, 'b'},
        {"after",       required_argument,  0, 'a'},
        {"expr",        required_argument,  0, 'e'},
        {0, 0, 0, 0},
    };

    int opt;
    int option_index = 0;

    while ((opt = getopt_long_only(argc, argv, "hflnudtb:a:e:", long_options, &option_index)) != EOF) {
        switch (opt) {
        case 'l':
            params.tri.mode = SORT_LEXICO;
            params.tri.ascending = true;
            break;
        case 'n':
            params.tri.mode = SORT_NB_OCCURENCES;
            params.tri.ascending = false;
            break;
        case 'f':
            params.tri.mode = SORT_APPARITION;
            params.tri.ascending = true;
            break;
        
        case 'c':
            force_sort_order = true;
            break;
        case 'd':
            force_sort_order = false;
            break;

        case 'b':
            params.mode = MODE_WORDS_BEFORE_X;
            params.search.word = optarg;
            break;
        case 'a':
            params.mode = MODE_WORDS_AFTER_X;
            params.search.word = optarg;
            break;
        case 't':
            params.unittest = true;
            break;

        case 'e':
            params.mode = MODE_EXPRESSION;
            if ((params.search.len_expr = atoi(optarg)) < 2) {
                fprintf(
                    stderr,
                    "Error: the length of the expression "
                    "must be an integer greater than or equal to 2.\n");
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

    if (force_sort_order != -1)
        params.tri.ascending = force_sort_order;

    if (params.unittest)
        exit(!test());

    if (optind == argc) {
        fprintf(stderr, "Error : no file specified\n");
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        params.filename = argv[optind];

        if (!(params.file = fopen(params.filename, "r"))) {
            perror("Error while opening file:");
            exit(EXIT_FAILURE);
        }
    }

    return params;
}

void ARGS_print_help(char* progname) {
    printf(
        "Usage : %s [OPTION]... [FILE]\n"
        "Options:\n"
        "  -h, --help\t\tDisplay this help message.\n"
        "  -f, --apparition\tSort words by order of appearance in the text. (Default)\n"
        "  -l, --lexico\t\tSort words by ascending lexicographic order.\n"
        "  -n, --occ\t\tSort words by decreasing number of occurrences, then by lexicographic order.\n"
        "  -c, --croissant\tForce ascending order.\n"
        "  -d, --decroissant\tForce descending order.\n"
        "  -b, --before=WORD\tDisplay the words before the word WORD.\n"
        "  -a, --after=WORD\tDisplay the words after the word WORD.\n"
        "  -e, --expr=N\t\tDisplay expressions of length N words.\n"
        "  -t, --test\t\tRun unit tests.\n",
        progname);
}

WordTree* ARGS_readfile(Args params) {

    WordTree* mots = NULL;
    mots = Tree_new();

    switch (params.mode) {
    case MODE_COUNT_WORDS:
        ALG_count_words(mots, params.file);
        break;
    case MODE_WORDS_BEFORE_X:
        ALG_words_before_x(mots, params.file, params.search.word);
        break;
    case MODE_WORDS_AFTER_X:
        ALG_words_after_x(mots, params.file, params.search.word);
        break;
    case MODE_EXPRESSION:
        ALG_expressions(mots, params.file, params.search.len_expr);
        break;
    default:
        break;
    }

    return mots;
}

WordArray* ARGS_sort(const WordTree* mots, Args params) {
    WordArray* tab;
    tab = WordArray_from_WordTree(mots);

    // The array is already sorted in ascending lexicographic order.
    if (params.tri.mode != SORT_LEXICO || !params.tri.ascending)
        WordArray_sort(tab, params.tri.mode, params.tri.ascending);

    return tab;
}
