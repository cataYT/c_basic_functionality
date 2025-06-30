#pragma once

#include <stdbool.h>
#include <stdlib.h>

/**
 * @struct queue
 * @brief A generic fixed-size circular queue.
 *
 * This structure represents a circular queue using a single block of memory
 * to hold items of any type (via void pointers).
 */
struct queue {
    /** Pointer to the queue's item buffer */
    void *items;
    /** Size of each item in bytes */
    size_t item_size;
    /** Index of the front item */
    size_t front;
    /** Index where the next item will be inserted */
    size_t rear;
    /** Current number of items in the queue */
    size_t size;
    /** Maximum number of items the queue can hold */
    size_t capacity;
};

/**
 * @brief Initializes a new queue.
 *
 * Allocates memory and sets up the metadata for a fixed-size circular queue.
 *
 * @param[in]  item_size Size of each item in bytes.
 * @param[in]  capacity  Maximum number of items the queue can hold.
 * @param[out] q         Pointer to the queue structure to initialize.
 * 
 * @return true if the queue is successfully created, false otherwise.
 */
bool queue_initialize(const size_t item_size, const size_t capacity, struct queue *q);

/**
 * @brief Checks if the queue is full.
 *
 * @param[in] q Pointer to the queue.
 * 
 * @return true if the queue is full, false otherwise.
 */
bool queue_is_full(const struct queue *q);

/**
 * @brief Checks if the queue is empty.
 *
 * @param[in] q Pointer to the queue.
 * 
 * @return true if the queue is empty, false otherwise.
 */
bool queue_is_empty(const struct queue *q);

/**
 * @brief Checks if the queue structure or its internal buffer is null.
 *
 * @param[in] q Pointer to the queue.
 * 
 * @return true if the queue or its data is NULL, false otherwise.
 */
bool queue_is_null(const struct queue *q);

/**
 * @brief Adds an item to the rear of the queue.
 *
 * Copies the given item into the next available position in the queue.
 *
 * @param[in]  q    Pointer to the queue.
 * @param[out] item Pointer to the item to enqueue.
 * 
 * @return true if the item was enqueued successfully, false if the queue is full.
 */
bool queue_enqueue(struct queue *q, const void *item);

/**
 * @brief Removes the item from the front of the queue.
 *
 * Does not return the removed item, only adjusts the internal pointers.
 *
 * @param[in] q Pointer to the queue.
 * 
 * @return true if an item was dequeued, false if the queue is empty.
 */
bool queue_dequeue(struct queue *q);

/**
 * @brief Retrieves the front item without removing it.
 *
 * Copies the front item into the provided memory location.
 *
 * @param[in]  q    Pointer to the queue.
 * @param[out] item Pointer to memory where the front item will be copied.
 * 
 * @return true if the queue is not empty and the item was copied, false otherwise.
 */
bool queue_peek_front(const struct queue *q, void *item);

/**
 * @brief Retrieves the rear (most recently enqueued) item without removing it.
 *
 * Copies the rear item into the provided memory location.
 *
 * @param[in]  q    Pointer to the queue.
 * @param[out] item Pointer to memory where the rear item will be copied.
 * 
 * @return true if the queue is not empty and the item was copied, false otherwise.
 */
bool queue_peek_back(const struct queue *q, void *item);

/**
 * @brief Frees the memory allocated for the queue.
 *
 * Releases all resources and resets the queue fields.
 *
 * @param[in] q Pointer to the queue.
 * 
 * @return true if the queue was successfully freed, false otherwise.
 */
bool queue_deinitialize(struct queue *q);