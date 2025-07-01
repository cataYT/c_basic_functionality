#pragma once

#include <stdlib.h>

/**
 * @typedef cmp_func
 * @brief   Custom comparison function.
 * 
 * @param[in] k1 Key to compare to.
 * @param[in] k2 Key to compare by.
 * 
 * @return 0 if equal, < 0 if smaller, > 0 if larger.
 */
typedef int (*cmp_func)(const void *, const void *);

/**
 * @enum  entry_state
 * @brief State for tracking entries.
 */
enum entry_state {
    /** If entry is empty. */
    EMPTY,
    /** If entry is occupied. */
    OCCUPIED,
    /** If entry is deleted. */
    DELETED
};

/**
 * @struct hm_entry
 * @brief  Entry for the hash map.
 */
struct hm_entry {
    /** Key of the value. */
    void *key;
    /** Value of the key. */
    void *value;
    /** State of the entry. */
    enum entry_state state;
};

/**
 * @struct hash_map
 * @brief  Hash map.
 */
struct hash_map {
    /** Key's size. */
    size_t key_size;
    /** Value's size. */
    size_t value_size;
    /** Table of hash entries. */
    struct hm_entry *table;
    /** Current size of the hash map. */
    size_t size;
    /** Capacity of the hash map. */
    size_t capacity;
    /** Custom comparasion function for comparing keys. */
    cmp_func cmp;
};

/**
 * @brief Initializes the hash map.
 * 
 * @param[in]  key_size   Key's size.
 * @param[in]  value_size Value's size.
 * @param[in]  capacity   Initial capacity of the hash map.
 * @param[in]  cmp        Custom comparision function used for comparing keys.
 * @param[out] map        Pointer to caller allocated hash_map struct.
 */
void hm_init(const size_t key_size, const size_t value_size, const size_t capacity, const cmp_func cmp, struct hash_map *map);
/**
 * @brief Gets value from its key.
 * 
 * @param[in] map Pointer to hash_map struct. 
 * @param[in] key Key to search.
 * 
 * @return Key's value if found and successful, NULL otherwise. 
 */
void *hm_get(const struct hash_map *map, const void *key);
/**
 * @brief Inserts a key into the hash map.
 * 
 * @param[in] map   Pointer to hash_map struct.
 * @param[in] key   Key to insert.
 * @param[in] value Value to insert.
 */
void hm_insert(struct hash_map *map, const void *key, const void *value);
/**
 * @brief Deletes an entry in the hash map.
 * 
 * @param[in] map Pointer to hash_map struct.
 * @param[in] key Key to delete.
 */
void hm_delete(struct hash_map *map, const void *key);
/**
 * @brief Destroys the hash map.
 * 
 * @param[in] map Pointer to hash_map struct. 
 */
void hm_destroy(struct hash_map *map);