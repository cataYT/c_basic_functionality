#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

bool linked_list_initialize(const void *data, const size_t data_size, struct linked_list *head)
{
    if (!data) {
        fprintf(stderr, "data is null at linked_list_initialize()\n");
        return false;
    }

    if (data_size == 0) {
        fprintf(stderr, "data size is null at linked_list_initialize()\n");
        return false;
    }

    head->data = malloc(data_size);
    if (!head->data) {
        fprintf(stderr, "malloc failed at linked_list_initialize()\n");
        return false;
    }
    memcpy(head->data, data, data_size);
    head->data_size = data_size;
    head->next = NULL;

    return true;
}

bool linked_list_insert_node(struct linked_list *head, const void *data, struct linked_list *new_node)
{
    if (!data) {
        fprintf(stderr, "data is null at linked_list_insert_node()\n");
        return false;
    }

    if (!new_node) {
        fprintf(stderr, "new node is null at linked_list_insert_node()\n");
        return false;
    }

    if (!head || head->data_size == 0) {
        fprintf(stderr, "head is null at linked_list_insert_node()\n");
        return false;
    }

    new_node->data_size = head->data_size;
    new_node->data = malloc(new_node->data_size);
    if (!new_node->data) {
        fprintf(stderr, "malloc failed at linked_list_insert_node()\n");
        return false;
    }
    memcpy(new_node->data, data, new_node->data_size);

    new_node->next = NULL;
    
    // Tranverse till end
    struct linked_list *curr = head;
    while (curr->next) {
        curr = curr->next;
    }

    curr->next = new_node;

    return true;
}

bool linked_list_remove_node(struct linked_list *head)
{
    if (!head) {
        fprintf(stderr, "linked list is empty at linked_list_remove_node()\n");
        return false;
    }

    if (!head->next) {
        free_linked_list_node(head);
        return true;
    }

    struct linked_list *curr = head;
    
    // Get second last node
    while (curr->next && curr->next->next) {
        curr = curr->next;
    }
    struct linked_list *last = curr->next;
    free_linked_list_node(last);
    curr->next = NULL;

    return true;
}

bool linked_list_get_node_data(const struct linked_list *head, const size_t index, void *out_data)
{
    if (!head || head->data_size == 0) {
        fprintf(stderr, "head is null at linked_list_get_node_data()\n");
        return false;
    }

    if (!out_data) {
        fprintf(stderr, "out_data is null at linked_list_get_node_data()\n");
        return false;
    }

    const struct linked_list *curr = head;
    size_t i = 0;

    while (curr) {
        if (i == index) {
            memcpy(out_data, curr->data, curr->data_size);
            return true;
        }
        curr = curr->next;
        i++;
    }

    // Index out of bounds
    return false;
}

bool linked_list_deinitialize_node(struct linked_list *head)
{
    if (!head || !head->data) {
        return false;
    }

    free(head->data);
    head->data = NULL;
    head->data_size = 0;
    head->next = NULL;

    return true;
}

bool linked_list_deinitialize_all(struct linked_list *head)
{
    if (!head || !head->data) {
        return false;
    }

    struct linked_list *curr = head;
    while (curr) {
        struct linked_list *next = curr->next;
        if (curr->data) {
            free(curr->data);
            curr->data = NULL;
        }
        curr = next;
    }

    return true;
}