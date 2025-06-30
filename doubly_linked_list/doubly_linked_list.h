#pragma once

#include <stdlib.h>
#include <stdbool.h>

/**
 * @struct d_node
 * @brief Doubly linked list's node.
 */
struct d_node {
    /** Data of the node. */
    void *data;
    /** Pointer to next node. */
    struct d_node *next;
    /** Pointer to previous node. */
    struct d_node *prev;
};

/**
 * @struct d_linked
 * @brief Doubly linked list.
 */
struct d_linked {
    /** Data size of the node's data. */
    size_t data_size;
    /** Head of the list. */
    struct d_node *head;
    /** Tail of the list. */
    struct d_node *tail;
};

/**
 * @brief Initializes the doubly linked list.
 * 
 * @param[in]  data_size Data size of the node's data. 
 * @param[out] list      Pointer to caller allocated d_linked struct.
 */
void d_linked_init(const size_t data_size, struct d_linked *list);
/**
 * @brief Inserts a node into the linked list.
 * 
 * @param[in] list Pointer to d_linked struct. 
 * @param[in] data Data to add into the node. Must be of the same size as initialized with the list.
 */
void d_linked_insert(struct d_linked *list, const void *data);
/**
 * @brief Removes a node from the linked list.
 * 
 * @param[in] list Pointer to d_linked struct. 
 */
void d_linked_remove(struct d_linked *list);
/**
 * @brief Get's a node's data by its index.
 * 
 * @param[in]  list  Pointer to d_linked struct.
 * @param[in]  index Index of the data.
 * @param[out] out   Pointer to caller allocated buffer to copy to.
 * 
 * @return true if found and copied successfully, false otherwise.
 */
bool d_linked_get(const struct d_linked *list, const size_t index, void *out);
/**
 * @brief Destroys the doubly linked list.
 * 
 * @param[in] list Pointer to d_linked struct. 
 */
void d_linked_destroy(struct d_linked *list);