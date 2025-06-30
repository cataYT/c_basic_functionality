/**
 * @file  linked_list.h
 * @brief Singly linked list interface for generic data storage.
 *
 * This header provides an interface to create, manage, and manipulate a 
 * generic singly linked list that stores data of arbitrary types using void pointers.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @struct l_node
 * @brief  Represents a node in a singly linked list.
 *
 * Each node holds a pointer to the data and the next node in the list.
 */
struct l_node {
    /** Pointer to the data stored in the node */
    void *data;
    /** Pointer to the next node */
    struct l_node *next;
};

/**
 * @struct s_linked
 * @brief  Represents the singly linked list structure.
 *
 * This structure maintains the head pointer and the size of the data each node stores.
 */
struct s_linked {
    /** Pointer to the first node in the list */
    struct l_node *head;
    /** Size of the data each node stores */
    size_t data_size;
};

/**
 * @brief Initializes a singly linked list.
 *
 * @param[in]  data_size Size of the data to be stored in each node.
 * @param[out] list      Pointer to the list to initialize.
 * 
 * @return true on successful initialization, false on failure.
 */
bool s_linked_init(const size_t data_size, struct s_linked *list);

/**
 * @brief Inserts a new node with data at the end of the list.
 *
 * @param[in] list Pointer to the list.
 * @param[in] data Pointer to the data to insert.
 * 
 * @return true on success, false on failure.
 */
bool s_linked_insert(struct s_linked *list, const void *data);

/**
 * @brief Removes the last node from the list.
 *
 * @param[in] list Pointer to the list.
 * 
 * @return true on successful removal, false if the list is empty or invalid.
 */
bool s_linked_remove(struct s_linked *list);

/**
 * @brief Retrieves the data at a specified index.
 *
 * @param[in]  list     Pointer to the list.
 * @param[in]  index    Zero-based index of the node to retrieve.
 * @param[out] out_data Pointer to a buffer where the data will be copied.
 * 
 * @return true if the index is valid and data is retrieved, false otherwise.
 */
bool s_linked_get(const struct s_linked *list, const size_t index, void *out_data);

/**
 * @brief Frees all memory used by the list and resets its state.
 *
 * @param[in] list Pointer to the list.
 * 
 * @return true on successful destruction, false if the list is invalid.
 */
bool s_linked_destroy(struct s_linked *list);