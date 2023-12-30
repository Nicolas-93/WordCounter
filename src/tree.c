#include "tree.h"
#include "wordtree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


WordTree* Tree_new(void) {
    WordTree *res = malloc(sizeof(WordTree));
    
    if (res == NULL)
        return NULL;

    res->root = NULL;
    res->len = 0;
    res->max_str_len = 0;

    return res;
}

WordNode* Tree_new_node(char* mot, int id) {
    WordNode *n;
    if ((n = malloc(sizeof(WordNode)))) {
        n->fg = NULL;
        n->fd = NULL;
        n->word = strdup(mot);
        n->id = id;
        n->nb_occ = 1;
    }
    return n;
}

WordNode* Tree_search_word(const WordTree* self, char* mot) {
    WordNode* a = self->root;

    if (!mot)
        return NULL;

    int cmp;

    while (a) {
        cmp = strcmp(mot, a->word);
        if (cmp == 0)
            return a;
        if (cmp < 0)
            a = LEFT_NODE(a);
        else
            a = RIGHT_NODE(a);
    }

    return NULL;
}

bool Tree_in(const WordTree *self, char* mot) {
    return Tree_search_word(self, mot);
}

void Tree_refresh_max_str_size(WordTree* self, int len) {
    if (len > self->max_str_len)
        self->max_str_len = len;
}

WordNode* Tree_add_helper(WordNode** a, char* word, int id) {

    if (IS_EMPTY_TREE(*a)) {
        *a = Tree_new_node(word, id);
        return *a;
    }

    int cmp = strcmp(word, (*a)->word);
    if (cmp == 0)
        return *a;
    if (cmp < 0)
        return Tree_add_helper(&LEFT_NODE(*a), word, id);
    else
        return Tree_add_helper(&RIGHT_NODE(*a), word, id);
}

int Tree_add_word(WordTree *self, char* word) {

    WordNode* entry;

    if (!word)
        return -1;

    if ((entry = Tree_search_word(self, word))) {
        entry->nb_occ += 1;
        return 0;
    }

    if (!Tree_add_helper(&self->root, word, self->len))
        return -1;

    self->len++;
    Tree_refresh_max_str_size(self, strlen(word));

    return 1;
}

void Tree_free_helper(WordNode** a) {
    if (IS_EMPTY_TREE(*a))
        return;

    Tree_free_helper(&((*a)->fg));
    Tree_free_helper(&((*a)->fd));
    free((*a)->word);
    free(*a);

    *a = NULL;
}

void Tree_free(WordTree* ens) {
    Tree_free_helper(&ens->root);
    free(ens);
}
