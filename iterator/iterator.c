#include "iterator.h"
#include <stddef.h>
#include <stdbool.h>

void iterator_init(void *data, const size_t data_size, const size_t capacity, struct iterator *it)
{
    if (!data || !it || data_size == 0 || capacity == 0) {
        return;
    }

    it->data_size = data_size;
    it->data      = data;
    it->capacity  = capacity;
    it->index     = 0;
}

void *iterator_current(const struct iterator *it)
{
    return (it && it->index < it->capacity)
        ? (char *)it->data + (it->index * it->data_size)
        : NULL;
}

bool iterator_has_next(const struct iterator *it)
{
    return it && it->index < it->capacity;
}

void *iterator_next(struct iterator *it)
{
    return (it && it->index < it->capacity)
        ? (char *)it->data + (it->index++ * it->data_size)
        : NULL;
}

void *iterator_before(struct iterator *it)
{
    return (it && it->index > 0)
        ? (char *)it->data + (--it->index * it->data_size)
        : NULL;
}

void *iterator_jump(struct iterator *it, const size_t amount)
{
    if (!it || it->index + amount >= it->capacity) {
        return NULL;
    }

    it->index += amount;
    return (char *)it->data + (it->index * it->data_size);
}

void *iterator_peek(const struct iterator *it, const size_t amount)
{
    return (it && it->index + amount < it->capacity)
        ? (char *)it->data + ((it->index + amount) * it->data_size)
        : NULL;
}

void iterator_reset(struct iterator *it)
{
    if (it) {
        it->index = 0;
    }
}