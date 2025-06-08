#pragma once

#include <stdlib.h>
#include <stdbool.h>

struct array
{
    void *items;
    size_t item_size;
    size_t size;
};

bool create_array(const void *items, const size_t item_size, const size_t size, struct array *arr);
void *get_element(const struct array *arr, const size_t index);
bool free_array(struct array *arr);