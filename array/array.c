#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "array.h"

bool create_array(const void *items, size_t item_size, const size_t size, struct array *arr)
{
    if (!items) {
        fprintf(stderr, "items pointer is null at create_array()\n");
        return false;
    }

    if (size == 0) {
        fprintf(stderr, "size is null at create_array()\n");
        return false;
    }

    if (item_size == 0) {
        fprintf(stderr, "item_size is null at create_array()\n");
        return false;
    }

    arr->items = malloc(size * item_size);
    if (!arr->items) {
        fprintf(stderr, "malloc failed\n");
        return false;
    }

    memcpy(arr->items, items, size * item_size);

    arr->item_size = item_size;
    arr->size = size;

    return true;
}

void *get_element(const struct array *arr, const size_t index)
{
    if (!arr) {
        fprintf(stderr, "array is null at get_element()\n");
        return NULL;
    }

    if (index >= arr->size) {
        fprintf(stderr, "index is out of bounds at get_element()\n");
        return NULL;
    }

    // Use byte-wise pointer arithmetic
    return (char *)arr->items + (index * arr->item_size);
}

bool free_array(struct array *arr)
{
    if (!arr) {
        return false;
    }

    free(arr->items);
    arr->items = NULL;
    arr->item_size = 0;
    arr->size = 0;

    return true;
}