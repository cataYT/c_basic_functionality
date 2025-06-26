#pragma once

#include <stdbool.h>
#include <stdlib.h>

/**
 * @struct pair
 * @brief A generic key-value pair.
 *
 * This structure holds dynamically allocated key-value data of arbitrary types.
 */
struct pair {
    /** Pointer to the key */
    void *key;
    /** Size of the key in bytes */          
    size_t key_size;
    /** Pointer to the value */  
    void *value;
    /** Size of the value in bytes */        
    size_t value_size;
};

/**
 * @brief                 Creates a new key-value pair.
 *                        Allocates and copies the given key and value into the pair structure.
 *
 * @param[in]  key        Pointer to the key data.
 * @param[in]  value      Pointer to the value data.
 * @param[in]  key_size   Size of the key in bytes.
 * @param[in]  value_size Size of the value in bytes.
 * @param[out] p          Pointer to the pair structure to initialize.
 * 
 * @return                true if the pair was successfully created, false otherwise.
 */
bool pair_initialize(const void *key, const void *value, const size_t key_size, const size_t value_size, struct pair *pair);

/**
 * @brief          Checks if a pair is null.
 *                 A pair is considered null if either the key or value pointer is NULL.
 *
 * @param[in] pair Pointer to the pair.
 * 
 * @return         true if the pair is null or uninitialized, false otherwise.
 */
bool pair_is_null(const struct pair *pair);

/**
 * @brief          Frees the memory used by a pair.
 *                 Releases the memory allocated for both the key and value.
 *
 * @param[in] pair Pointer to the pair to free.
 * 
 * @return         true if the pair was successfully freed, false otherwise.
 */
bool pair_deinitialize(struct pair *pair);