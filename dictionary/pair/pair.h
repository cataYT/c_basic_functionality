#pragma once

#include <stdbool.h>

struct pair {
    void *key;
    size_t key_size;
    void *value;
    size_t value_size;
};

bool create_pair(const void *key, const void *value, const size_t key_size, const size_t value_size, struct pair *p);
bool check_pair_null(const struct pair *pair);
bool free_pair(struct pair *pair);