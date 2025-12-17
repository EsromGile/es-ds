//
// Created by eli on 12/17/25.
//

#ifndef EM_DS_EM_HASH_UTILS_H
#define EM_DS_EM_HASH_UTILS_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

static inline uint32_t murmur_32_scramble(uint32_t k) {
    k *= 0xcc9e2d51;
    k = k << 15 | k >> 17;
    k *= 0x1b873593;
    return k;
}

static inline uint32_t murmur3_32(const uint8_t *key, const size_t length, const uint32_t seed) {
    uint32_t hash = seed;
    uint32_t hash_key;

    /* Read in groups of 4. */
    for (size_t i = length >> 2; i; i--) {
        memcpy(&hash_key, key, sizeof(uint32_t));
        key += sizeof(uint32_t);
        hash ^= murmur_32_scramble(hash_key);
        hash = hash << 13 | hash >> 19;
        hash = hash * 5 + 0xe6546b64;
    }

    /* Read the rest. */
    hash_key = 0;
    for (size_t i = length & 3; i; i--) {
        hash_key <<= 8;
        hash_key |= key[i - 1];
    }
    hash ^= murmur_32_scramble(hash_key);

    /* Finalize. */
    hash ^= length;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;
    return hash;
}

#endif //EM_DS_EM_HASH_UTILS_H