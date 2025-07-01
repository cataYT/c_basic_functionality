#include "binary_tree.h"

#include <string.h>

void b_tree_init(const size_t data_size, struct b_tree *tree)
{
    if (data_size == 0 || !tree) {
        return;
    }

    tree->data_size = data_size;
    tree->root = NULL;
    tree->cmp = NULL;
}

/**
 * @brief Initializes a binary node.
 * 
 * @param[in] data      Data to insert. 
 * @param[in] data_size Data's size.
 * 
 * @return Pointer to dynamically allocated b_node struct if successful, NULL otherwise. 
 */
static struct b_node *b_node_init(const void *data, const size_t data_size)
{
    struct b_node *node = malloc(sizeof(struct b_node));
    if (!node) {
        return NULL;
    }

    node->data = malloc(data_size);
    if (!node->data) {
        free(node);
        node = NULL;
        return NULL;
    }

    memcpy(node->data, data, data_size);

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

struct b_node *b_tree_search(const struct b_tree *tree, const void *data)
{
    if (!tree || !tree->root || !data || !tree->cmp) {
        return NULL;
    }

    struct b_node *curr = tree->root;

    // start from root, go to left if smaller else right.
    while (curr) {
        int cmp = tree->cmp(data, curr->data);

        // found.
        if (cmp == 0) {
            return curr;
        }

        if (cmp < 0) {
            curr = curr->left;
            continue;
        }

        curr = curr->right;
    }

    return NULL;
}

void b_tree_insert(struct b_tree *tree, const void *data)
{
    if (!tree || !tree->cmp || !data) {
        return;
    }

    struct b_node *new_node = b_node_init(data, tree->data_size);
    if (!new_node) {
        return;
    }

    // edge case, first node.
    if (!tree->root) {
        tree->root = new_node;
        return;
    }

    struct b_node *curr   = tree->root;
    struct b_node *parent = NULL;

    // start from root, go left if smaller else right.
    while (curr) {
        parent = curr;

        if (tree->cmp(data, curr->data) < 0) {
            curr = curr->left;
            continue;
        }

        curr = curr->right;
    }

    // attach the node.
    new_node->parent = parent;

    if (tree->cmp(data, parent->data) < 0) {
        parent->left = new_node;
        return;
    }

    parent->right = new_node;
}

/**
 * @brief Finds the smallest node in terms of value.
 * 
 * @param[in] node Node from where to conduct the search.
 * 
 * @return Smallest node if successful, NULL otherwise.
 */
static struct b_node *b_node_find_min(struct b_node *node)
{
    if (!node) {
        return NULL;
    }

    while (node->left) {
        node = node->left;
    }

    return node;
}

/**
 * @brief Destroys the nodes recursively.
 * 
 * @param[in] node Pointer to b_node struct. 
 */
static void b_node_destroy(struct b_node *node)
{
    if (!node) {
        return;
    }

    b_node_destroy(node->left);
    b_node_destroy(node->right);

    free(node->data);
    free(node);
}

/**
 * @brief Deletes the binary tree recursively.
 * 
 * @param[in] tree Pointer to b_tree struct. 
 * @param[in] node Node from where to start the deletion.
 * @param[in] data Data to delete.
 * 
 * @return Pointer to new child if didnt arrange the tree, NULL otherwise.
 */
struct b_node *b_tree_delete_rec(struct b_tree *tree, struct b_node *node, void *data)
{
    if (!tree || !node || !data) {
        return NULL;
    }

    int cmp = tree->cmp(data, node->data);

    if (cmp < 0) {
        node->left = b_tree_delete_rec(tree, node, data);
    } else if (cmp > 0) {
        node->right = b_tree_delete_rec(tree, node, data);
    } else {
        // no children, just delete the node.
        if (!node->left && !node->right) {
            free(node->data);
            free(node);
            node = NULL;
            return NULL;
        // children either in left or right.
        } else if (!node->left || !node->right) {
            // find the only child.
            //      10
            //     /
            //    5
            //     \
            //      7
            struct b_node *child = node->left ? node->left : node->right;
            // child takes place of its parent.
            //      10
            //     /
            //    7
            child->parent = node->parent;
            free(node->data);
            free(node);
            node = NULL;
            return child;
        // children in both
        } else {
            // find smallest from the right branch.
            //    10
            //   /  \
            //  5    15
            //        \
            //         20
            struct b_node *min_node = b_node_find_min(node->right);
            // copy its data to its parent.
            //      15
            //     /  \
            //    5    15
            //          \
            //           20
            memcpy(node->data, min_node->data, tree->data_size);
            // remove the duplicate.
            //      15
            //     /  \
            //    5    20
            node->right = b_tree_delete_rec(tree, node->right, min_node->data);
        }
    }

    return node;
}

void b_tree_delete(struct b_tree *tree, void *data)
{
    if (!tree || !tree->root || !data) {
        return;
    }

    tree->root = b_tree_delete_rec(tree, tree->root, data);
}

void b_tree_destroy(struct b_tree *tree)
{
    if (!tree) {
        return;
    }

    b_node_destroy(tree->root);
    tree->root = NULL;
}