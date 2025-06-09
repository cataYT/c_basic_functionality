#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "pair.h"

/**
 * @struct dictionary
 * @brief A simple dynamic dictionary structure based on key-value pairs.
 *
 * This structure stores an array of `pair` structs, providing basic dictionary functionality.
 */
struct dictionary {
    struct pair *pairs;   /**< Dynamically allocated array of key-value pairs */
    size_t size;          /**< Current number of pairs stored */
    size_t capacity;      /**< Maximum capacity of the dictionary */
};

/**
 * @brief Creates and initializes a new dictionary.
 *
 * Allocates space for a dictionary and inserts an initial key-value pair.
 *
 * @param initial_pair The first key-value pair to insert.
 * @param capacity The maximum number of pairs the dictionary can hold.
 * @param dict Pointer to the dictionary structure to initialize.
 * @return true if the dictionary was successfully created, false otherwise.
 */
bool create_dict(const struct pair initial_pair, const size_t capacity, struct dictionary *dict);

/**
 * @brief Appends a key-value pair to the dictionary.
 *
 * Inserts a new pair into the dictionary, assuming there is available capacity.
 *
 * @param dict Pointer to the dictionary.
 * @param new_pair The key-value pair to add.
 * @return true if the pair was successfully appended, false if capacity is exceeded or memory error occurs.
 */
bool append_dict(struct dictionary *dict, const struct pair new_pair);

/**
 * @brief Prints the contents of the dictionary.
 *
 * Outputs the keys and values of all pairs in the dictionary.
 * Note: This is a generic printer. Actual output depends on how keys/values are interpreted.
 *
 * @param dict Pointer to the dictionary.
 */
void print_dict(struct dictionary *dict);

/**
 * @brief Frees the memory used by the dictionary and its contents.
 *
 * Releases all memory used by the dictionary and its contained key-value pairs.
 *
 * @param dict Pointer to the dictionary to free.
 * @return true if the dictionary was successfully freed, false otherwise.
 */
bool free_dict(const struct dictionary *dict);