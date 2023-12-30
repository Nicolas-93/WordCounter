#ifndef ABR_INCLUDED
#define ABR_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include "wordtree.h"

typedef struct WordNode {
    char* word;
    int nb_occ;
    int id;
    struct WordNode* fg;
    struct WordNode* fd;
} WordNode;

typedef struct WordTree {
    WordNode* root;
    int max_str_len;
    int len;
} WordTree;


#define STR_LESS_THAN(a, b)         (strcmp((a), (b)) <  0)
#define STR_GREATHER_THAN(a, b)     (strcmp((a), (b)) >  0)
#define STR_GREATHER_OR_EQUAL(a, b) (strcmp((a), (b)) >= 0)
#define STR_LESS_OR_EQUAL(a, b)     (strcmp((a), (b)) <= 0)
#define STR_EQUALS(a, b)            (strcmp((a), (b)) == 0)

#define BTREE_INIT(tree) ((tree) = NULL)
#define IS_INTERN_NODE(node) (node->fg || node->fd)
#define IS_LEAF_NODE(node) (!(node->fg || node->fd))
#define IS_EMPTY_TREE(tree) (!(tree))
#define IS_COMPLETE_NODE(node) (node->fg && node->fd)
#define IS_BINARY_NODE(node) (IS_COMPLETE_NODE(node) || IS_LEAF_NODE(node))
#define LEFT_NODE(node) ((node)->fg)
#define RIGHT_NODE(node) ((node)->fd)

/**
 * @brief Init a new empty tree of words.
 * 
 * @return WordTree* 
 */
WordTree* Tree_new(void);

/**
 * @brief Add a word to the tree.
 * 
 * @param tab 
 * @return int
 * - 1 if success
 * - 0 if the word already exists (increment its
 * number of occurences)
 * - -1 if allocation error, or if the word is NULL
 */
int Tree_add_word(WordTree* self, char* word);

/**
 * @brief Search for a word in the tree.
 * 
 * @param tab 
 * @param word 
 */
WordNode* Tree_search_word(const WordTree* self, char* word);

/**
 * @brief Check if a word is in the tree.
 * 
 * @param tab 
 * @param word 
 */
bool Tree_in(const WordTree* self, char* word);

/**
 * @brief Free the memory allocated by the tree.
 * 
 * @param self 
 */
void Tree_free(WordTree* self);

/**
 * @brief Create a new node with a copy of the word.
 * 
 * @param word Word to add to the tree.
 * @param id Identifier of the node (corresponds to the
 * size of the set, at the time of insertion, and allows
 * to keep the insertion order).
 * @return WordNode* 
 */
WordNode* Tree_new_node(char* word, int id);

/**
 * @brief Refresh the maximum string size contained by the tree.
 * 
 * @param ens 
 * @param len Word's length.
 */
void Tree_refresh_max_str_size(WordTree* self, int len);

/**
 * @brief Helper function for Tree_add.
 * 
 * @param a 
 * @param word 
 * @param id 
 * @return WordNode* 
 */
WordNode* Tree_add_helper(WordNode** a, char* word, int id);

/**
 * @brief Helper function for Tree_free.
 * 
 * @param a 
 */
void Tree_free_helper(WordNode** a);

#endif
