#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "array.h"

struct array create_array(const void *items, const size_t size, const size_t item_size)
{
    if (!items) {
        fprintf(stderr, "items is null, cannot create array");
        return NULL_ARRAY;
    }

    if (size <= 0) {
        fprintf(stderr, "size cannot be 0 or negative");
        return NULL_ARRAY;
    }

    if (item_size <= 0) {
        fprintf(stderr, "item size cannot be 0 or negative");
        return NULL_ARRAY;
    }

    struct array arr = NULL_ARRAY;

    arr.items = malloc(size * item_size);

    if (!arr.items) {
        fprintf(stderr, "malloc failed");
        return NULL_ARRAY;
    }

    memcpy(arr.items, items, size * item_size);
    arr.item_size = item_size;
    arr.size = size;

    return arr;
}

void *get_element(const struct array *arr, const size_t index)
{
    if (!arr) {
        fprintf(stderr, "array is null, cannot access any element\n");
        return NULL;
    }

    if (index >= arr->size) {
        fprintf(stderr, "index is out of bounds\n");
        return NULL;
    }

    // Use byte-wise pointer arithmetic
    return (char *)arr->items + (index * arr->item_size);
}

const bool free_array(struct array *arr)
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