#pragma once

#include <stdbool.h>
#include <stdlib.h>

/**
 * @struct stack
 * @brief A generic stack data structure.
 *
 * This structure manages a dynamic array of void pointers, supporting stack operations
 * for items of any type.
 */
struct stack {
    /** Array of pointers to stack items */
    void **items;
    /** Size of each item in bytes */
    size_t item_size;
    /** Current number of items in the stack */
    size_t size;
    /** Maximum number of items the stack can hold */
    size_t capacity;
};

/**
 * @brief Initializes a new stack.
 *
 * Allocates memory for a stack to hold items of the specified size and capacity.
 *
 * @param[in]  item      A prototype item for initialization (can be NULL).
 * @param[in]  item_size Size of each item in bytes.
 * @param[in]  capacity  Maximum number of elements the stack can hold.
 * @param[out] s         Pointer to the stack structure to initialize.
 * 
 * @return true if the stack was successfully created, false otherwise.
 */
bool stack_initialize(void *item, size_t item_size, size_t capacity, struct stack *s);

/**
 * @brief Retrieves the top item from the stack without removing it.
 *
 * Copies the top element into the provided memory location.
 *
 * @param[in]  s    Pointer to the stack.
 * @param[out] item Pointer to memory where the top item will be copied.
 * 
 * @return true if the stack is not empty and the item was copied, false otherwise.
 */
bool stack_peek(struct stack *s, void *item);

/**
 * @brief Pushes an item onto the top of the stack.
 *
 * Copies the provided item into the stack.
 *
 * @param[in] s    Pointer to the stack.
 * @param[in] item Pointer to the item to be pushed.
 * 
 * @return true if the item was successfully pushed, false if the stack is full or memory allocation failed.
 */
bool stack_push(struct stack *s, void *item);

/**
 * @brief Removes the top item from the stack and copies it out.
 *
 * Copies the removed item into the provided memory location.
 *
 * @param[in]  s Pointer to the stack.
 * @param[out] item Pointer to memory where the popped item will be copied.
 * 
 * @return true if an item was popped, false if the stack is empty.
 */
bool stack_pop(struct stack *s, void *item);

/**
 * @brief Checks whether the stack is empty.
 *
 * @param[in] s Pointer to the stack.
 * 
 * @return true if the stack contains no items, false otherwise.
 */
bool stack_is_empty(struct stack *s);

/**
 * @brief Frees the memory allocated for the stack.
 *
 * Releases all resources associated with the stack and resets its fields.
 *
 * @param[in] s Pointer to the stack.
 * 
 * @return true if the stack was successfully freed, false otherwise.
 */
bool stack_deinitialize(struct stack *s);