#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "pair.h"

struct dictionary {
    struct pair *pairs; // dynamic
    size_t size;
    size_t capacity;
};

bool create_dict(const struct pair initial_pair, const size_t capacity, struct dictionary *dict);
bool append_dict(struct dictionary *dict, const struct pair new_pair);
void print_dict(struct dictionary *dict);
bool free_dict(const struct dictionary *dict);