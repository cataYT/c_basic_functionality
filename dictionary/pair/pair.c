#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pair.h"

bool create_pair(const void *key, const void *value, const size_t key_size, const size_t value_size, struct pair *p)
{
    if (!key) {
        fprintf(stderr, "key is null at create_pair()\n");
        return false;
    }

    if (!value) {
        fprintf(stderr, "value is null at create_pair()\n");
        return false;
    }

    if (key_size == 0) {
        fprintf(stderr, "key size is 0 at create_pair()\n");
        return false;
    }

    if (value_size == 0) {
        fprintf(stderr, "value size is 0 at create_pair()\n");
        return false;
    }

    memset(p, 0, sizeof(*p));

    p->key = malloc(key_size);
    if (!p->key) {
        fprintf(stderr, "malloc failed at create_pair()\n");
        return false;
    }
    
    p->value = malloc(value_size);
    if (!p->value) {
        fprintf(stderr, "malloc failed at create_pair()\n");
        free(p->key);
        return false;
    }

    memcpy(p->key, key, key_size);
    p->key_size = key_size;
    memcpy(p->value, value, value_size);
    p->value_size = value_size;

    return true;
}

bool check_pair_null(const struct pair *pair)
{
    return !pair->key || !pair->value || pair->key_size == 0 || pair->value_size == 0;
}

bool free_pair(struct pair *pair)
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