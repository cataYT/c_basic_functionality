#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pair.h"
#include "dictionary.h"

bool dictionary_initialize(const struct pair initial_pair, const size_t capacity, struct dictionary *dict)
{
    if (pair_is_null(&initial_pair) == 0) {
        fprintf(stderr, "initial pair is null at dictionary_initialize()\n");
        return false;
    }

    if (capacity == 0) {
        fprintf(stderr, "capacity is 0 or negative at dictionary_initialize()\n");
        return false;
    }

    dict->pairs = malloc(sizeof(struct pair) * capacity);

    if (!dict->pairs) {
        fprintf(stderr, "malloc failed at dictionary_initialize()\n");
        return false;
    }

    struct pair temp_pair = {NULL};
    pair_initialize(initial_pair.key, initial_pair.value, initial_pair.key_size, initial_pair.value_size, &temp_pair);

    struct pair *first_pair = &dict->pairs[0];

    first_pair->key = temp_pair.key;
    first_pair->value = temp_pair.value;
    first_pair->key_size = temp_pair.key_size;
    first_pair->value_size = temp_pair.value_size;

    dict->size = 1;
    dict->capacity = capacity;

    return true;
}

bool dictionary_append(struct dictionary *dict, const struct pair new_pair)
{
    if (!dict) {
        fprintf(stderr, "dictionary is empty at dictionary_append()\n");
        return false;
    }

    if (!pair_is_null(&new_pair)) {
        fprintf(stderr, "new pair is empty at dictionary_append()\n");
        return false;
    }

    if (dict->size >= dict->capacity) {
        fprintf(stderr, "size is greater than capacity in dictionary_append()\n");
        return false;
    }

    struct pair temp_pair = {NULL};
    pair_initialize(new_pair.key, new_pair.value, new_pair.key_size, new_pair.value_size, &temp_pair);

    struct pair *last_pair = &dict->pairs[dict->size];

    last_pair->key = temp_pair.key;
    last_pair->value = temp_pair.value;
    last_pair->key_size = temp_pair.key_size;
    last_pair->value_size = temp_pair.value_size;

    dict->size++;
    return true;
}

void dictionary_print(const struct dictionary *dict)
{
    if (!dict) {
        return;
    }

    for (int i = 0; i < dict->size; i++) {
        char *key = (char*) dict->pairs[i].key;
        int *value = (int*) dict->pairs[i].value;
        printf("%s : %d\n", key, *value);
    }
}

const bool dictionary_deinitialize(struct dictionary *dict)
{
    if (!dict) {
        return false;
    }

    for (int i = 0; i < dict->size; i++) {
        if (!pair_deinitialize(dict->pairs)) {
            return false;
        }
    }

    dict->pairs = NULL;
    dict->size = 0;
    dict->capacity = 0;

    return true;
}