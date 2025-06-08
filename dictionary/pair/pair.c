#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pair.h"

struct pair create_pair(const void *key, const void *value, const size_t key_size, const size_t value_size)
{
    if (!key) {
        fprintf(stderr, "key is null\n");
        return NULL_PAIR;
    }

    if (!value) {
        fprintf(stderr, "value is null\n");
        return NULL_PAIR;
    }

    if (key_size <= 0) {
        fprintf(stderr, "key size cannot be 0 or negative\n");
        return NULL_PAIR;
    }

    if (value_size <= 0) {
        fprintf(stderr, "value size cannot be 0 or negative\n");
        return NULL_PAIR;
    }

    struct pair p = NULL_PAIR;

    p.key = malloc(key_size);
    if (!p.key) {
        fprintf(stderr, "malloc failed\n");
        return NULL_PAIR;
    }
    
    p.value = malloc(value_size);
    if (!p.value) {
        fprintf(stderr, "malloc failed\n");
        free(p.key);
        return NULL_PAIR;
    }

    memcpy(p.key, key, key_size);
    p.key_size = key_size;
    memcpy(p.value, value, value_size);
    p.value_size = value_size;

    return p;
}

const bool check_pair_null(const struct pair *pair)
{
    if (!pair->key || !pair->value || pair->key_size == 0 || pair->value_size == 0) {
        return false;
    }
    return true;
}

const bool free_pair(struct pair *pair)
{
    if (!pair) {
        return false;
    }

    free(pair->key);
    pair->key = NULL;
    free(pair->value);
    pair->value = NULL;

    pair->key_size = 0;
    pair->value_size = 0;
    return true;
}