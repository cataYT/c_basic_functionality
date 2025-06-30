#pragma once

#include <stdlib.h>
#include <stdbool.h>

/**
 * @struct array
 * @brief A generic, fixed-size array container.
 *
 * Provides a way to store and retrieve raw data elements of any type using a unified structure.
 *
 * @note The ownership of `items` memory depends on how the array is created:
 * - If created with `create_array`, memory is allocated internally and must be freed with `free_array`.
 * - If wrapping an existing buffer, the caller manages memory and should not call `free_array`.
 */
struct array
{
    /**Pointer to the raw data block containing all elements */
    void *items;
    /**Size of each element in bytes */
    size_t item_size;
    /**Total number of elements stored */
    size_t size;
};

/**
 * @brief Creates a new array and copies the initial data into it.
 *
 * Allocates memory and populates the array with the provided data.
 * The caller is responsible for calling `free_array` to release memory.
 *
 * @param[in]  items     Pointer to the initial items to copy.
 * @param[in]  item_size Size of each item in bytes.
 * @param[in]  size      Number of elements to copy.
 * @param[out] arr       Pointer to the array structure to initialize.
 * 
 * @return true if the array was successfully created, false otherwise.
 */
bool array_initialize(const void *items, const size_t item_size, const size_t size, struct array *arr);

/**
 * @brief Retrieves an element at a given index.
 *
 * Performs bounds checking and copies the element into the provided buffer.
 *
 * @param[in]  arr     Pointer to the array.
 * @param[in]  index   Index of the element to retrieve (0-based).
 * @param[out] element Pointer to memory where the element will be copied.
 * 
 * @return true if the element was successfully retrieved, false otherwise.
 */
bool array_get_element(const struct array *arr, const size_t index, void *element);

/**
 * @brief Sorts the contents of an array and stores the sorted data in another array.
 *
 * The sorted array's memory must be allocated by the caller and have enough capacity.
 * This function assumes the array elements are integers for sorting.
 *
 * @param[in]  arr          Pointer to the source array.
 * @param[out] sorted_array Pointer to the destination array to hold sorted data.
 * 
 * @return true if sorting was successful, false otherwise.
 */
bool array_sort(struct array *arr, struct array *sorted_array);

/**
 * @brief Frees the memory used by the array.
 *
 * Releases the dynamically allocated items buffer if owned.
 * After this call, the array structure is reset.
 *
 * @param[in] arr Pointer to the array to free.
 * 
 * @return true if memory was successfully freed or array was empty, false otherwise.
 */
bool array_deinitialize(struct array *arr);