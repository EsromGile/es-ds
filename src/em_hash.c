//
// Created by eli on 12/12/25.
//

#include "em_hash.h"
#include "private/em_hash_utils.h"

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define HashValue uint8_t *
#define SEED 0x00000000
#define HASH_TABLE_INIT_CAPACITY 1024

typedef struct HashNode {
    HashValue *values;
    uint32_t capacity;
} HashNode;

typedef struct HashTable {
    hash_key_t capacity;
    size_t data_size;
    uint32_t seed;
    HashValue entries[];
} HashTable;

// where num > 0
bool is_power_of_two(const uint32_t num) {
    const int x = (int) log2(num);
    return pow(2, x) == num;
}

HashTable *hash_table_create(hash_key_t capacity, const size_t data_size) {
    if (capacity == 0) capacity = HASH_TABLE_INIT_CAPACITY;
    else if (!is_power_of_two(capacity)) {
        errno = EINVAL;
        return NULL;
    }

    HashTable *hash_table = malloc(sizeof(HashTable) + capacity * sizeof(HashValue));
    if (!hash_table) {
        errno = ENOMEM;
        return NULL;
    }
    memset(hash_table->entries, 0, capacity * sizeof(HashValue));

    hash_table->seed = SEED;
    hash_table->capacity = capacity;
    hash_table->data_size = data_size;

    return hash_table;
}

void hash_table_destroy(HashTable *table);

bool hash_table_add(HashTable *self, void *value) {
    const hash_key_t key = hash_table_hash(self, value);
    if (self->entries[key] != NULL) { // TODO: handle collision
        errno = EINVAL;
        return false;
    } else {
        HashValue node_value = malloc(self->data_size);
        if (!node_value) {
            errno = ENOMEM;
            return false;
        }
        memcpy(node_value, value, self->data_size);
        self->entries[key] = node_value;
    }
    return true;
}

void *hash_table_get(const HashTable *self, const hash_key_t key) {
    return self->entries[key];
}

bool hash_table_contains_key(HashTable *self, hash_key_t key);

bool hash_table_contains_value(HashTable *self, void *value) {
    const hash_key_t key = hash_table_hash(self, value);
    const HashValue node_value = self->entries[key] ;
    const int result = memcmp(node_value, value, self->data_size);
    return result == 0;
}

hash_key_t hash_table_hash(const HashTable *self, const void *value) {
    return murmur3_32(value, self->data_size, SEED) & self->capacity - 1;
}

void hash_table_remove(HashTable *self, hash_key_t key);

void hash_table_clear(HashTable *self);


