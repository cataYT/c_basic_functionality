#include "doubly_linked_list.h"
#include <string.h>
#include <stdio.h>

void d_linked_init(const size_t data_size, struct d_linked *list)
{
    if (data_size == 0 || !list) {
        return;
    }

    list->data_size = data_size;
    list->head = NULL;
    list->tail = NULL;
}

void d_linked_insert(struct d_linked *list, const void *data)
{
    if (!list || !data) {
        return;
    }

    struct d_node *new_node = malloc(sizeof(struct d_node));
    if (!new_node) {
        return;
    }

    new_node->data = malloc(list->data_size);
    if (!new_node->data) {
        free(new_node);
        return;
    }

    memcpy(new_node->data, data, list->data_size);
    // head -> ... -> old_tail -> NULL will be head -> ... -> new_node (tail) -> NULL
    new_node->prev = list->tail;
    new_node->next = NULL;

    // edge case, if its the first entry.
    if (!list->head) {
        list->head = new_node;
        list->tail = new_node;
        return;
    }

    // Attach the node into the list.
    list->tail->next = new_node;
    list->tail = new_node;
}

void d_linked_remove(struct d_linked *list)
{
    if (!list || !list->tail) {
        return;
    }

    // head -> ... -> tail (will be removed) -> NULL
    struct d_node *to_remove = list->tail;

    // edge case, if its the last node.
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        // Shift tail to left.
        list->tail = to_remove->prev;
        list->tail->next = NULL;
    }

    free(to_remove->data);
    free(to_remove);
}

bool d_linked_get(struct d_linked *list, const size_t index, void *out)
{
    if (!list || !out) {
        return 0;
    }

    struct d_node *curr = list->head;
    size_t i = 0;
    while (curr) {
        if (i == index) {
            memcpy(out, curr->data, list->data_size);
            return true; // success
        }
        curr = curr->next;
        i++;
    }
    return false; // index out of bounds
}

void d_linked_destroy(struct d_linked *list)
{
    if (!list) {
        return;
    }

    struct d_node *curr = list->head;
    while (curr) {
        struct d_node *next = curr->next;
        free(curr->data);
        free(curr);
        curr = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->data_size = 0;
}