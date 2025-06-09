#pragma once

#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief A generic dynamically resizable array (vector) implementation.
 * 
 * This vector supports elements of arbitrary type by storing their size
 * and performing operations with raw memory.
 */
struct vector
{
    void *items;       ///< Pointer to the contiguous block of elements.
    size_t e_size;     ///< Size of each element in bytes.
    size_t size;       ///< Current number of elements in the vector.
    size_t capacity;   ///< Total allocated slots (in elements).
};

/**
 * @brief Initializes a vector with a given capacity and element size.
 * 
 * The caller may allocate the struct itself on the stack or heap, but is responsible
 * for calling `free_vector()` to release internal memory.
 * 
 * @param[in]  capacity  Initial number of elements the vector can hold.
 * @param[in]  e_size    Size of each element in bytes.
 * @param[out] vec       Pointer to a user-allocated vector struct to initialize.
 * 
 * @return true on success, false on allocation failure or invalid parameters.
 */
bool create_vector(const size_t capacity, const size_t e_size, struct vector *vec);

/**
 * @brief Retrieves the element at a specified index in the vector.
 * 
 * This function copies the element at the specified index into `element`.
 * 
 * @param[in]  vec      Pointer to the initialized vector.
 * @param[in]  index    Index of the element to retrieve.
 * @param[out] element  Pointer to memory where the element will be copied (must be at least `e_size` bytes).
 * 
 * @return true on success, false if index is out of bounds or arguments are invalid.
 */
bool get_vector_element(const struct vector *vec, const size_t index, void *element);

/**
 * @brief Appends an element to the end of the vector.
 * 
 * Automatically resizes the vector's internal array (typically doubling capacity)
 * if the current size equals the capacity. The element is copied by value using
 * the vector's `e_size`.
 * 
 * @param[in,out] vec      Pointer to the initialized vector.
 * @param[in]     element  Pointer to the element to add (must be at least `e_size` bytes).
 * 
 * @return true on success, false on allocation failure or invalid input.
 */
bool push_back(struct vector *vec, const void *element);

/**
 * @brief Searches for and removes the first occurrence of an element.
 * 
 * The comparison is performed using `memcmp()` over `e_size` bytes. If a match is found,
 * the element is removed and subsequent elements are shifted to maintain order.
 * 
 * @param[in,out] vec      Pointer to the initialized vector.
 * @param[in]     element  Pointer to the element to remove (compared by value).
 * 
 * @return true if the element was found and removed, false otherwise.
 */
bool pop_search(struct vector *vec, const void *element);

/**
 * @brief Removes the element at the specified index from the vector.
 * 
 * The element is copied into the `element` buffer (must be large enough), and all
 * subsequent elements are shifted left to fill the gap. The size of the vector is decremented.
 * 
 * @param[in,out] vec      Pointer to the initialized vector.
 * @param[in]     index    Index of the element to remove.
 * @param[out]    element  Buffer to copy the removed element into (must be at least `e_size` bytes).
 * 
 * @return true on success, false if index is out of bounds or input is invalid.
 */
bool pop_index(struct vector *vec, const size_t index, void *element);

/**
 * @brief Frees the internal storage used by the vector.
 * 
 * The vector struct itself is not freed, but its internal `items` memory is released
 * and the structure is reset to a clean state.
 * 
 * @param[in,out] vec  Pointer to the vector to free.
 * 
 * @return true on success, false if `vec` is NULL or already freed.
 */
bool free_vector(struct vector *vec);