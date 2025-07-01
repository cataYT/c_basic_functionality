#include "hash_map.h"

#include <string.h>

void hm_init(const size_t key_size, const size_t value_size, const size_t capacity, const cmp_func cmp, struct hash_map *map)
{
    if (key_size == 0 || value_size == 0 || capacity == 0 || !cmp || !map) {
        return;
    }

    map->table = calloc(capacity, sizeof(struct hm_entry));
    if (!map->table) {
        return;
    }

    map->key_size = key_size;
    map->value_size = value_size;
    map->cmp = cmp;
    map->capacity = capacity;
    map->size = 0;
}

/**
 * @brief Hashes the key based on a value.
 * 
 * @param[in] key      Key to hash. Assumes that key is a string.
 * @param[in] capacity Capacity of the hash map.
 * 
 * @return Index of the hashed key. 
 */
size_t hm_simple_hash(const void *key, const size_t capacity)
{
    // Assumes key is a string (char *)
    char *str = (char *)key;
    size_t hash = 5381;
    int c = 0;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % capacity;
}

void *hm_get(const struct hash_map *map, const void *key)
{
    if (!map || !key) {
        return NULL;
    }

    const size_t index = hm_simple_hash(key, map->capacity);
    
    for (size_t i = 0; i < map->capacity; i++) {
        size_t probe_entry = (index + i) % map->capacity;
        struct hm_entry *entry = &map->table[probe_entry];

        if (entry->state == EMPTY) {
            return NULL;
        }

        if (entry->state == OCCUPIED && map->cmp(entry->key, key) == 0) {
            return entry->value;
        }
    }

    return NULL;
}

/**
 * @brief Dynamically resizes the hash map if it reaches certain threshold.
 * 
 * @param[in] map Pointer to hash_map struct. 
 */
void hm_resize(struct hash_map *map)
{
    const size_t new_capacity = map->capacity * 2;
    struct hm_entry *new_table = malloc(new_capacity * sizeof(struct hm_entry));
    if (!new_table) {
        return;
    }

    for (size_t i = 0; i < new_capacity; i++) {
        new_table[i].state = EMPTY;
    }

    // Save old table
    struct hm_entry *old_table = map->table;
    const size_t old_capacity = map->capacity;

    map->table = new_table;
    map->capacity = new_capacity;
    map->size = 0;

    for (size_t i = 0; i < old_capacity; i++) {
        struct hm_entry *old_entry = &old_table[i];
        if (old_entry->state == OCCUPIED) {
            // re-insert the entry into the new table
            hm_insert(map, old_entry->key, old_entry->value);
            free(old_entry->key);
            free(old_entry->value);
        }
    }

    free(old_table);
}

void hm_insert(struct hash_map *map, const void *key, const void *value)
{
    if (!map || !key || !value) {
        return;
    }

    if (map->size >= map->capacity * 0.7) {
        hm_resize(map);
    }

    const size_t index = hm_simple_hash(key, map->capacity);

    for (size_t i = 0; i < map->capacity; i++) {
        const size_t probe_entry = (index + i) % map->capacity;
        struct hm_entry *entry = &map->table[probe_entry];

        if (entry->state == EMPTY || entry->state == DELETED) {
            entry->key = malloc(map->key_size);
            if (!entry->key) {
                return;
            }
            memcpy(entry->key, key, map->key_size);
            entry->value = malloc(map->value_size);
            if (!entry->value) {
                free(entry->key);
                entry->key = NULL;
                return;
            }
            memcpy(entry->value, value, map->value_size);
            entry->state = OCCUPIED;
            map->size++;
            return;
        }

        if (entry->state == OCCUPIED && map->cmp(entry->key, key) == 0) {
            memcpy(entry->value, value, map->value_size);
            return;
        }
    }
}

void hm_delete(struct hash_map *map, const void *key)
{
    const size_t index = hm_simple_hash(key, map->capacity);

    for (size_t i = 0; i < map->capacity; i++) {
        const size_t probe = (index + i) % map->capacity;
        struct hm_entry *entry = &map->table[probe];

        if (entry->state == EMPTY) {
            // Key not found
            return;
        }

        if (entry->state == OCCUPIED && map->cmp(entry->key, key) == 0) {
            // Key found, mark as deleted
            free(entry->key);
            entry->key = NULL;
            free(entry->value);
            entry->value = NULL;
            entry->state = DELETED;
            map->size--;
            return;
        }
    }
}

void hm_destroy(struct hash_map *map)
{
    if (!map) {
        return;
    }

    for (size_t i = 0; i < map->capacity; i++) {
        struct hm_entry *entry = &map->table[i];
        if (entry->state == OCCUPIED) {
            free(entry->key);
            entry->key = NULL;
            free(entry->value);
            entry->value = NULL;
        }
    }

    free(map->table);
    map->table = NULL;
    map->capacity = 0;
    map->cmp = NULL;
    map->size = 0;
}