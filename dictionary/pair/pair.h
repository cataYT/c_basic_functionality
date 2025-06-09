#pragma once

#include <stdbool.h>

/**
 * @struct pair
 * @brief A generic key-value pair.
 *
 * This structure holds dynamically allocated key-value data of arbitrary types.
 */
struct pair {
    void *key;          /**< Pointer to the key */
    size_t key_size;    /**< Size of the key in bytes */
    void *value;        /**< Pointer to the value */
    size_t value_size;  /**< Size of the value in bytes */
};

/**
 * @brief Creates a new key-value pair.
 *
 * Allocates and copies the given key and value into the pair structure.
 *
 * @param key Pointer to the key data.
 * @param value Pointer to the value data.
 * @param key_size Size of the key in bytes.
 * @param value_size Size of the value in bytes.
 * @param p Pointer to the pair structure to initialize.
 * @return true if the pair was successfully created, false otherwise.
 */
bool create_pair(const void *key, const void *value, const size_t key_size, const size_t value_size, struct pair *p);

/**
 * @brief Checks if a pair is null.
 *
 * A pair is considered null if either the key or value pointer is NULL.
 *
 * @param pair Pointer to the pair.
 * @return true if the pair is null or uninitialized, false otherwise.
 */
bool check_pair_null(const struct pair *pair);

/**
 * @brief Frees the memory used by a pair.
 *
 * Releases the memory allocated for both the key and value.
 *
 * @param pair Pointer to the pair to free.
 * @return true if the pair was successfully freed, false otherwise.
 */
bool free_pair(struct pair *pair);