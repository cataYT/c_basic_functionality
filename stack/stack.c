#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

bool stack_initialize(void *item, size_t item_size, size_t capacity, struct stack *s)
{
    if (!item) {
        fprintf(stderr, "item is null at stack_initialize()\n");
        return false;
    }

    if (item_size == 0 || capacity == 0) {
        fprintf(stderr, "item_size or capacity is 0 at stack_initialize()\n");
        return false;
    }

    s->items = malloc(sizeof(item) * capacity);
    if (!s->items) {
        fprintf(stderr, "malloc failed at stack_initialize()\n");
        return false;
    }

    s->items[0] = item;

    return s;
}

bool stack_peek(struct stack *s, void *item)
{
    if (!s) {
        fprintf(stderr, "stack is null at stack_peek()\n");
        return false;
    }

    if (s->size == 0) {
        fprintf(stderr, "stack is empty at stack_peek()\n");
        return false;
    }

    if (!item) {
        fprintf(stderr, "item is null at stack_peek()\n");
        return false;
    }

    void *src = (char *)s->items + ((s->size - 1 )* s->item_size);
    memcpy(item, src, s->item_size);

    return true;
}

bool stack_push(struct stack *s, void *item)
{
    if (!s || !s->items) {
        fprintf(stderr, "stack is null at stack_push()\n");
        return false;
    }

    if (!item) {
        fprintf(stderr, "item is null at stack_push()\n");
        return false;
    }

    if (s->size >= s->capacity) {
        fprintf(stderr, "stack is full at stack_push()\n");
        return false;
    }

    s->items[s->size] = item;
    s->size++;

    return true;
}

bool stack_pop(struct stack *s, void *item)
{
    if (!s || !s->items) {
        fprintf(stderr, "stack is null at stack_pop()\n");
        return false;
    }

    if (!item) {
        fprintf(stderr, "item is null at stack_pop()\n");
        return false;
    }

    void *pop_item = s->items[s->size];
    memcpy(item, pop_item, s->item_size);

    s->items[s->size] = 0;
    s->size--;

    return true;
}

bool stack_is_empty(struct stack *s)
{
    if (!s || !s->items) {
        fprintf(stderr, "stack is null at stack_is_empty()\n");
        return false;
    }

    if (s->size == 0 || s->item_size == 0) {
        return true;
    }

    return false;
}

bool stack_deinitialize(struct stack *s)
{
    if (!s) {
        return false;
    }

    free(s->items);
    s->items = NULL;
    s->item_size = 0;
    s->items = 0;

    return true;
}