#pragma once

#include <stdbool.h>
#include <stddef.h>

struct linked_list {
    void *data;
    size_t data_size;
    struct linked_list *next;
};

/**
 * @brief Initializes the head of a linked list with the given data.
 * 
 * Caller has the freedom to allocate `head` on the stack or heap,
 * and also retains responsibility for freeing the memory when needed.
 * 
 * @param[in]  data       Pointer to data to be copied into the node.
 * @param[in]  data_size  Size of the data in bytes.
 * @param[out] head       Pointer to a user-allocated linked list node to initialize.
 * 
 * @return true on success, false on failure (e.g., allocation failure or invalid inputs).
 */
bool linked_list_initialize(const void *data, const size_t data_size, struct linked_list *head);

/**
 * @brief Inserts a new node at the end of the linked list.
 * 
 * @param[in]  data      Pointer to data to be copied into the new node.
 * @param[in]  head      Pointer to the head of the list (must be initialized).
 * @param[out] new_node  Pointer to a user-allocated struct to become the new node.
 *                       This function initializes the node's memory.
 * 
 * @return true on success, false on failure (e.g., allocation failure or invalid inputs).
 */
bool linked_list_insert_node(const void *data, const struct linked_list *head, struct linked_list *new_node);

/**
 * @brief Removes the last node from the linked list.
 * 
 * @param[in,out] head  Pointer to the head of the list. If it's the only node,
 *                      its contents are freed but the struct remains valid.
 * 
 * @return true on success, false on failure (e.g., empty list).
 */
bool linked_list_remove_node(struct linked_list *head);

/**
 * @brief Retrieves a copy of the data at a specified index in the linked list.
 * 
 * @param[in]  index     Index of the node to access.
 * @param[in]  head      Pointer to the head of the list.
 * @param[out] out_data  Pointer to memory allocated by the caller to receive the data copy.
 *                       Must be large enough to hold the data (same size as node's data_size).
 * 
 * @return true on success, false if index is out of bounds or inputs are invalid.
 */
bool linked_list_get_node_data(const size_t index, const struct linked_list *head, void *out_data);

/**
 * @brief Frees the dynamically allocated contents of a single node.
 * 
 * @param[in,out] head  Pointer to the node to clear. Only clears contents, not the struct itself.
 * 
 * @return true on success, false if input is NULL or already freed.
 */
bool linked_list_deinitialize_node(struct linked_list *head);

/**
 * @brief Frees the data of all nodes in the linked list.
 * 
 * The list structure itself (the node structs) are not deallocated — the caller must manage them.
 * 
 * @param[in,out] head  Pointer to the head of the list.
 * 
 * @return true on success, false if input is NULL or list is already cleared.
 */
bool linked_list_deinitialize_all(struct linked_list *head);