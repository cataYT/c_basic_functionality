#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "array.h"

bool create_array(const void *items, size_t item_size, const size_t size, struct array *arr)
{
    if (!arr) {
        fprintf(stderr, "arr pointer is null at create_array()\n");
        return false;
    }
    if (!items) {
        fprintf(stderr, "items pointer is null at create_array()\n");
        return false;
    }
    if (!arr->items) {
        fprintf(stderr, "arr->items pointer is null at create_array(), must be preallocated\n");
        return false;
    }
    if (size == 0) {
        fprintf(stderr, "size is zero at create_array()\n");
        return false;
    }
    if (item_size == 0) {
        fprintf(stderr, "item_size is zero at create_array()\n");
        return false;
    }

    memcpy(arr->items, items, size * item_size);

    arr->item_size = item_size;
    arr->size = size;

    return true;
}

bool get_element(const struct array *arr, const size_t index, void *element)
{
    if (!arr) {
        fprintf(stderr, "array is null at get_element()\n");
        return false;
    }

    if (index >= arr->size) {
        fprintf(stderr, "index is out of bounds at get_element()\n");
        return false;
    }

    // Use byte-wise pointer arithmetic
    void *src = (char *)arr->items + (index * arr->item_size);
    memcpy(element, src, arr->item_size);
    return true;
}

int compare_ints(const void *a, const void *b)
{
    if (!a) {
        fprintf(stderr, "first integer is null for comparison in compare_ints()\n");
        return 0;
    }

    if (!b) {
        fprintf(stderr, "second integer is null for comparison in compare_ints()\n");
        return 0;
    }

    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

bool sort_array(struct array *arr, struct array *sorted_array) {
    if (!arr) {
        fprintf(stderr, "array is null at sort_array()\n");
        return false;
    }

    if (!sorted_array) {
        fprintf(stderr, "sorted_array is null at sort_array()\n");
        return false;
    }

    if (!sorted_array->items) {
        fprintf(stderr, "sorted_array->items is null, allocation must be done by caller\n");
        return false;
    }

    // Copy the data from arr to sorted_array
    memcpy(sorted_array->items, arr->items, arr->size * arr->item_size);
    sorted_array->size = arr->size;
    sorted_array->item_size = arr->item_size;

    // Sort the copied data (assuming int elements here)
    qsort(sorted_array->items, sorted_array->size, sorted_array->item_size, compare_ints);

    return true;
}

bool free_array(struct array *arr)
{
    if (!arr) {
        return false;
    }

    // free(arr->items);
    arr->items = NULL;
    arr->item_size = 0;
    arr->size = 0;

    return true;
}