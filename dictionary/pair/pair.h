#pragma once

struct pair {
    void *key;
    size_t key_size;
    void *value;
    size_t value_size;
};

#define NULL_PAIR (struct pair){NULL, 0, NULL, 0}

struct pair create_pair(const void *key, const void *value, const size_t key_size, const size_t value_size);
const bool check_pair_null(const struct pair *pair);
const bool free_pair(struct pair *pair);