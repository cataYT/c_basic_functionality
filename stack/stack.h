#pragma once

#include <stdbool.h>
#include <stdlib.h>

struct stack {
    void **items;
    size_t item_size;
    size_t size;
    size_t capacity;
};

#define NULL_STACK (struct stack){NULL, 0, 0, 0}

struct stack create_stack(void *item, size_t item_size, size_t capacity);
void *peek(struct stack *s);
bool stack_push(struct stack *s, void *item);
void *stack_pop(struct stack *s);
bool stack_is_empty(struct stack *s);
bool free_stack(struct stack *s);