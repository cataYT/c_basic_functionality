#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "pair.h"

struct dictionary {
    struct pair *pairs; // dynamic
    size_t size;
    size_t capacity;
};

#define NULL_DICT (struct dictionary){NULL, 0, 0}

struct dictionary create_dict(const struct pair initial_pair, const size_t capacity);
const bool append_dict(struct dictionary *dict, const struct pair new_pair);
void print_dict(struct dictionary *dict);
const bool free_dict(const struct dictionary *dict);