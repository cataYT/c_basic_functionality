#pragma once

#include <stdlib.h>
#include <stdbool.h>

struct array
{
    void *items;
    size_t item_size;
    size_t size;
};

#define NULL_ARRAY (struct array){NULL, 0, 0}

struct array create_array(const void *items, const size_t size, const size_t item_size);
void *get_element(const struct array *arr, const size_t index);
const bool free_array(struct array *arr);