#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pair.h"

bool pair_initialize(const void *key, const void *value, const size_t key_size, const size_t value_size, struct pair *pair)
{
    if (!key) {
        fprintf(stderr, "key is null at pair_initialize()\n");
        return false;
    }

    if (!value) {
        fprintf(stderr, "value is null at pair_initialize()\n");
        return false;
    }

    if (key_size == 0) {
        fprintf(stderr, "key size is 0 at pair_initialize()\n");
        return false;
    }

    if (value_size == 0) {
        fprintf(stderr, "value size is 0 at pair_initialize()\n");
        return false;
    }

    pair->key = malloc(key_size);
    if (!pair->key) {
        fprintf(stderr, "malloc failed at pair_initialize()\n");
        return false;
    }
    
    pair->value = malloc(value_size);
    if (!pair->value) {
        fprintf(stderr, "malloc failed at pair_initialize()\n");
        free(pair->key);
        return false;
    }

    memcpy(pair->key, key, key_size);
    pair->key_size = key_size;
    memcpy(pair->value, value, value_size);
    pair->value_size = value_size;

    return true;
}

bool pair_is_null(const struct pair *pair)
{
    return !pair->key || !pair->value || pair->key_size == 0 || pair->value_size == 0;
}

bool pair_deinitialize(struct pair *pair)
{
    if (!pair) {
        return false;
    }

    free(pair->key);
    pair->key = NULL;
    free(pair->value);
    pair->value = NULL;

    pair->key_size   = 0;
    pair->value_size = 0;
    return true;
}