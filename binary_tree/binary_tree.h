#pragma once

#include <stdlib.h>

/**
 * @typedef cmp_func
 * @brief   Custom comparison function provided by caller.
 * 
 * @param[in] d1 Data to compare to.
 * @param[in] d2 Data to compare by.
 * 
 * @return 0 if equal, < 0 if smaller and > 0 if larger.
 */
typedef int (*cmp_func)(const void *, const void *);

/**
 * @struct b_node
 * @brief  Binary tree's node.
 */
struct b_node {
    /** Data to store. */
    void *data;
    /** Pointer to the parent of the node. */
    struct b_node *parent;
    /** Pointer to the left of the node. */
    struct b_node *left;
    /** Pointer to the right of the node. */
    struct b_node *right;
};

/**
 * @struct b_tree
 * @brief  Binary tree, values to left are smaller and values to right are larger.
 */
struct b_tree {
    /** Data's size. */
    size_t data_size;
    /** Root of the tree. */
    struct b_node *root;
    /** Custom comparision function. */
    cmp_func cmp;
};

/**
 * @brief Initializes the binary tree.
 * 
 * @param[in]  data_size Data size of each node.
 * @param[out] tree      Pointer to caller allocated b_tree struct.
 */
void b_tree_init(const size_t data_size, struct b_tree *tree);
/**
 * @brief Searches a node in the binary tree. Caller must provide its custom comparision function.
 * 
 * @param[in] tree Pointer to b_tree struct. 
 * @param[in] data Data to search for.
 * 
 * @return Pointer to b_node if successful, NULL otherwise. 
 */
struct b_node *b_tree_search(const struct b_tree *tree, const void *data);
/**
 * @brief Inserts a node into the binary tree. Caller must provide is custom comparision function.
 * 
 * @param[in] tree Pointer to b_tree struct. 
 * @param[in] data Data to insert.
 */
void b_tree_insert(struct b_tree *tree, const void *data);
/**
 * @brief Deletes a node from binary tree.
 * 
 * @param[in] tree Pointer to b_tree struct.
 * @param[in] data Data to delete.
 */
void b_tree_delete(struct b_tree *tree, void *data);
/**
 * @brief Destroys the binary tree.
 * 
 * @param[in] tree Pointer to b_tree struct. 
 */
void b_tree_destroy(struct b_tree *tree);