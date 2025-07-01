#pragma once

#include <stdlib.h>
#include <stdbool.h>

/**
 * @struct iterator
 * @brief Iterator for generic types.
 */
struct iterator {
    /** Data of the iterator. */
    void *data;
    /** Data's size. */
    size_t data_size;
    /** Index of the current iteration. */
    size_t index;
    /** Total capacity of the iterator. */
    size_t capacity;
};

/**
 * @brief Initializes an iterator.
 * 
 * @param[in]  data      Data to be consumed in iterator. 
 * @param[in]  data_size Individual element's size.
 * @param[in]  capacity  Total capacity of the iterator.
 * @param[out] it        Pointer to caller allocated iterator struct.
 */
void iterator_init(void *data, const size_t data_size, const size_t capacity, struct iterator *it);
/**
 * @brief Gets the current element in the iterator.
 * 
 * @param[in] it Pointer to iterator struct.
 *  
 * @return Current element if successful, NULL otherwise.
 */
void *iterator_current(const struct iterator *it);
/**
 * @brief Determines whether there is next item in the iterator or not.
 * 
 * @param[in] it Pointer to iterator struct.
 *  
 * @return true if exists, false otherwise.
 */
bool iterator_has_next(const struct iterator *it);
/**
 * @brief Gets the next element in the iterator.
 * 
 * @param[in] it Pointer to iterator struct. 
 * 
 * @return Next element if successful, NULL otherwise.
 */
void *iterator_next(struct iterator *it);
/**
 * @brief Gets the element before the current index.
 * 
 * @param[in] it Pointer to iterator struct.
 * 
 * @return Before element if successful, NULL otherwise.
 */
void *iterator_before(struct iterator *it);
/**
 * @brief Jumps the iterator by the index.
 * 
 * @param[in] it     Pointer to iterator struct.
 * @param[in] amount Amount to jump by. Can be negative to jump backwards.
 * 
 * @return Element at jumped index if successful, NULL otherwise.
 */
void *iterator_jump(struct iterator *it, const size_t amount);
/**
 * @brief Gives the element at the peeked index.
 * 
 * @param[in] it     Pointer to iterator struct.
 * @param[in] amount Amount to peek by. Can be negative to peek backwards.
 * 
 * @return Element at the peeked index if successful, NULL otherwise.
 */
void *iterator_peek(const struct iterator *it, const size_t amount);
/**
 * @brief Resets the iterator by setting index to 0.
 * 
 * @param[in] it Pointer to iterator struct. 
 */
void iterator_reset(struct iterator *it);