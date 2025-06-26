#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "pair/pair.h"

/**
 * @struct dictionary
 * @brief  A simple dynamic dictionary structure based on key-value pairs.
 *         This structure stores an array of `pair` structs, providing basic dictionary functionality.
 */
struct dictionary {
    /** Dynamically allocated array of key-value pairs */
    struct pair *pairs;
    /** Current number of pairs stored */
    size_t size;
    /** Maximum capacity of the dictionary */
    size_t capacity;
};

/**
 * @brief                   Creates and initializes a new dictionary.
 *                          Allocates space for a dictionary and inserts an initial key-value pair.
 *
 * @param[in]  initial_pair The first key-value pair to insert.
 * @param[in]  capacity     The maximum number of pairs the dictionary can hold.
 * @param[out] dict         Pointer to the dictionary structure to initialize.
 * 
 * @return                  true if the dictionary was successfully created, false otherwise.
 */
bool dictionary_initialize(const struct pair initial_pair, const size_t capacity, struct dictionary *dict);

/**
 * @brief                  Appends a key-value pair to the dictionary.
 *                         Inserts a new pair into the dictionary, assuming there is available capacity.
 *
 * @param[in,out] dict     Pointer to the dictionary.
 * @param[in]     new_pair The key-value pair to add.
 * 
 * @return                 true if the pair was successfully appended, false if capacity is exceeded or memory error occurs.
 */
bool dictionary_append(struct dictionary *dict, const struct pair new_pair);

/**
 * @brief               Removes an entry from the dictionary by its key.
 * 
 * @param[in]  dict     Dictionary to remove from.
 * @param[in]  key      Key to remove.
 * @param[in]  key_size Key's size.
 * @param[out] pair     Pair to store the removed entry.
 * 
 * @return              true if found and successful, false otherwise.
 */
bool dictionary_remove(struct dictionary *dict, const void *key, const size_t key_size, struct pair *pair);

/**
 * @brief          Prints the contents of the dictionary.
 *                 Outputs the keys and values of all pairs in the dictionary.
 *                 Note: This is a generic printer. Actual output depends on how keys/values are interpreted.
 *
 * @param[in] dict Pointer to the dictionary.
 */
void dictionary_print(const struct dictionary *dict);

/**
 * @brief                 Gets a pair from dictionary by its key.
 * 
 * @param[in]  dictionary The dictionary to search.
 * @param[in]  key        The actual key.
 * @param[in]  key_size   Key's size.
 * @param[out] pair       Pointer to pair struct to copy, can be NULL.
 * 
 * @return                true if found, false otherwise.
 */
bool dictionary_get(const struct dictionary *dict, const void *key, const size_t key_size, struct pair *pair);

/**
 * @brief          Frees the memory used by the dictionary and its contents.
 *                 Releases all memory used by the dictionary and its contained key-value pairs.
 *
 * @param[in] dict Pointer to the dictionary to free.
 * 
 * @return         true if the dictionary was successfully freed, false otherwise.
 */
bool dictionary_deinitialize(struct dictionary *dict);