#pragma once

#include <stdbool.h>
#include <stdlib.h>

struct queue {
    void *items;
    size_t item_size;
    size_t front;
    size_t rear;
    size_t size;
    size_t capacity;
};

bool create_queue(const size_t item_size, const size_t capacity, struct queue *q);
bool queue_is_full(const struct queue *q);
bool queue_is_empty(const struct queue *q);
bool queue_is_null(const struct queue *q);
bool enqueue(struct queue *q, const void *item);
bool dequeue(struct queue *q);
void *peek(const struct queue *q);
void *peek_back(const struct queue *q);
bool free_queue(struct queue *q);