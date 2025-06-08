#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pair.h"
#include "dictionary.h"

bool create_dict(const struct pair initial_pair, const size_t capacity, struct dictionary *dict)
{
    if (check_pair_null(&initial_pair) == 0) {
        fprintf(stderr, "initial pair is null at create_dict()\n");
        return false;
    }

    if (capacity == 0) {
        fprintf(stderr, "capacity cannot be 0 or negative");
        return false;
    }

    dict->pairs = malloc(sizeof(struct pair) * capacity);

    if (!dict->pairs) {
        fprintf(stderr, "malloc failed");
        return false;
    }

    struct pair temp_pair = {NULL};
    create_pair(initial_pair.key, initial_pair.value, initial_pair.key_size, initial_pair.value_size, &temp_pair);

    struct pair *first_pair = &dict->pairs[0];

    first_pair->key = temp_pair.key;
    first_pair->value = temp_pair.value;
    first_pair->key_size = temp_pair.key_size;
    first_pair->value_size = temp_pair.value_size;

    dict->size = 1;
    dict->capacity = capacity;

    return true;
}

bool append_dict(struct dictionary *dict, const struct pair new_pair)
{
    if (!dict) {
        fprintf(stderr, "dictionary is empty at append_dict()\n");
        return false;
    }

    if (!check_pair_null(&new_pair)) {
        fprintf(stderr, "new pair is empty at append_dict()\n");
        return false;
    }

    if (dict->size >= dict->capacity) {
        fprintf(stderr, "size is greater than capacity in append_dict()\n");
        return false;
    }

    struct pair temp_pair = {NULL};
    create_pair(new_pair.key, new_pair.value, new_pair.key_size, new_pair.value_size, &temp_pair);

    struct pair *last_pair = &dict->pairs[dict->size];

    last_pair->key = temp_pair.key;
    last_pair->value = temp_pair.value;
    last_pair->key_size = temp_pair.key_size;
    last_pair->value_size = temp_pair.value_size;

    dict->size++;
    return true;
}

void print_dict(const struct dictionary *dict)
{
    for (int i = 0; i < dict->size; i++) {
        char *key = (char*) dict->pairs[i].key;
        int *value = (int*) dict->pairs[i].value;
        printf("%s : %d\n", key, *value);
    }
}

const bool free_dict(struct dictionary *dict)
{
    if (!dict) {
        return false;
    }

    for (int i = 0; i < dict->size; i++) {
        if (!free_pair(dict->pairs)) {
            return false;
        }
    }

    dict->pairs = NULL;
    dict->size = 0;
    dict->capacity = 0;

    return true;
}