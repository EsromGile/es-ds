//
// Created by eli on 12/12/25.
//

#ifndef EM_DS_EM_HASH_H
#define EM_DS_EM_HASH_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define hash_key_t uint32_t

typedef struct HashTable HashTable;

HashTable *hash_table_create(hash_key_t capacity, size_t data_size);

void hash_table_destroy(HashTable *table);

bool hash_table_add(HashTable *self, void *value);

void *hash_table_get(const HashTable *self, hash_key_t key);

bool hash_table_contains_key(HashTable *self, hash_key_t key);

bool hash_table_contains_value(HashTable *self, void *value);

hash_key_t hash_table_hash(const HashTable *self, const void *value);

void hash_table_remove(HashTable *self, hash_key_t key);

void hash_table_clear(HashTable *self);

#endif //EM_DS_EM_HASH_H