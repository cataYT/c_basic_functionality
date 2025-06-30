#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

bool s_linked_init(const size_t data_size, struct s_linked *list)
{
    if (data_size == 0) {
        fprintf(stderr, "data size is null at s_linked_init()\n");
        return false;
    }

    if (!list) {
        fprintf(stderr, "list is null at s_linked_init()\n");
        return false;
    }

    list->head = NULL;
    list->data_size = data_size;

    return true;
}

bool s_linked_insert(struct s_linked *list, const void *data)
{
    if (!data) {
        fprintf(stderr, "data is null at s_linked_insert()\n");
        return false;
    }

    if (!list) {
        fprintf(stderr, "list is null at s_linked_insert()\n");
        return false;
    }

    struct l_node *new_node = malloc(sizeof(struct l_node));
    if (!new_node) {
        fprintf(stderr, "malloc failed for new_node at s_linked_insert()\n");
        return false;
    }

    new_node->data = malloc(list->data_size);
    if (!new_node->data) {
        fprintf(stderr, "malloc failed for new_node->data at s_linked_insert()\n");
        free(new_node);
        new_node = NULL;
        return false;
    }
    memcpy(new_node->data, data, list->data_size);

    new_node->next = NULL;

    // edge case, first node.
    if (!list->head) {
        list->head = new_node;
        return true;
    }

    // Tranverse till end.
    struct l_node *curr = list->head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = new_node;

    return true;
}

bool s_linked_remove(struct s_linked *list)
{
    if (!list || !list->head) {
        fprintf(stderr, "empty list in s_linked_remove()\n");
        return false;
    }

    struct l_node *curr = list->head;

    // edge case, last node.
    if (!curr->next) {
        free(curr->data);
        free(curr);
        list->head = NULL;
        return true;
    }

    // Find second last node
    while (curr->next && curr->next->next) {
        curr = curr->next;
    }

    struct l_node *to_delete = curr->next;
    free(to_delete->data);
    free(to_delete);
    curr->next = NULL;

    return true;
}

bool s_linked_get(const struct s_linked *list, const size_t index, void *out_data)
{
    if (!list || !out_data) {
        fprintf(stderr, "null argument to s_linked_get()\n");
        return false;
    }

    const struct l_node *curr = list->head;
    size_t i = 0;

    while (curr) {
        if (i == index) {
            memcpy(out_data, curr->data, list->data_size);
            return true;
        }
        curr = curr->next;
        i++;
    }

    fprintf(stderr, "index %zu out of bounds in s_linked_get()\n", index);
    return false;
}

bool s_linked_destroy(struct s_linked *list)
{
    if (!list) {
        return false;
    }

    struct l_node *curr = list->head;
    while (curr) {
        struct l_node *next = curr->next;
        free(curr->data);
        free(curr);
        curr = next;
    }

    list->head = NULL;
    list->data_size = 0;
    return true;
}