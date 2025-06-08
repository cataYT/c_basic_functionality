#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

bool create_queue(const size_t item_size, const size_t capacity, struct queue *q)
{
    if (item_size == 0) {
        fprintf(stderr, "item size is null at create_queue()\n");
        return false;
    }

    if (capacity == 0) {
        fprintf(stderr, "capacity is null at create_queue()\n");
        return false;
    }

    q->items = malloc(item_size * capacity);
    if (!q->items) {
        fprintf(stderr, "malloc failed at create_queue()\n");
        return false;
    }

    q->item_size = item_size;
    q->capacity = capacity;

    return q;
}

bool queue_is_full(const struct queue *q)
{
    return q && q->size >= q->capacity;
}

bool queue_is_empty(const struct queue *q)
{
    return q && q->size == 0;
}

bool queue_is_null(const struct queue *q)
{
    return !q || !q->items;
}

bool enqueue(struct queue *q, const void *item)
{
    if (queue_is_null(q)) {
        fprintf(stderr, "queue is null at enqueue()\n");
        return false;
    }

    if (!item) {
        fprintf(stderr, "item is null at enqueue()\n");
        return false;
    }

    if (queue_is_full(q)) {
        fprintf(stderr, "queue is full at enqueue()\n");
        return false;
    }

    void *target = (char *)q->items + (q->rear * q->item_size);
    memcpy(target, item, q->item_size);

    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
    return true;
}

bool dequeue(struct queue *q)
{
    if (queue_is_null(q)) {
        fprintf(stderr, "queue is null at dequeue()\n");
        return false;
    }

    if (queue_is_empty(q)) {
        fprintf(stderr, "queue is empty at dequeue()\n");
        return false;
    }

    void *target = (char *)q->items + (q->front * q->item_size);
    memset(target, 0, q->item_size);
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return true;
}

void *peek(const struct queue *q)
{
    if (queue_is_null(q)) {
        fprintf(stderr, "queue is null at peek()\n");
        return NULL;
    }

    return (char *)q->items + (q->front * q->item_size);
}

void *peek_back(const struct queue *q)
{
    if (queue_is_null(q)) {
        fprintf(stderr, "queue is null at peek_back()\n");
        return NULL;
    }

    if (queue_is_empty(q)) {
        fprintf(stderr, "queue is empty at peek_back()\n");
        return NULL;
    }

    size_t back_index = (q->rear + q->capacity - 1) % q->capacity;
    return (char *)q->items + (back_index * q->item_size);
}

bool free_queue(struct queue *q)
{
    if (queue_is_null(q)) {
        return false;
    }

    free(q->items);
    q->items = NULL;
    q->size = 0;
    q->capacity = 0;
    q->front = 0;
    q->rear = 0;
}