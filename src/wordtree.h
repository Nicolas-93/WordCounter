#ifndef MOT_INCLUDED
#define MOT_INCLUDED
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Check if the word contains only alphabetic characters
 *
 * @param mot 
 * @return true
 * @return false 
 */
bool Word_is_correct(const char* word);

/**
 * @brief Lower the word
 * 
 * @param rep 
 */
void Word_to_lower(char* mot);

/**
 * @brief Write the new word in word, and realloc memory if needed.
 * 
 * @param word Word to write in
 * @param nouveau_mot New word to write in word
 * @return int 1 if success, 0 otherwise
 */
int Word_replace(char** word, size_t* bufsize, char* new_word);

#endif
