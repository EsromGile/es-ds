//
// Created by eli on 11/22/25.
//

#ifndef EM_ALLOCATORS_ARENA_H
#define EM_ALLOCATORS_ARENA_H
#include <stddef.h>

typedef struct Arena Arena;

Arena *arena_create(size_t initial_capacity);

void *arena_alloc(Arena *arena, size_t size);

void *arena_calloc(Arena *arena, size_t size);

char *arena_strdup(Arena *arena, const char *string);

void arena_reset(Arena *arena);

void arena_destroy(Arena *arena);

void arena_print(const Arena *arena);

#endif //EM_ALLOCATORS_ARENA_H
