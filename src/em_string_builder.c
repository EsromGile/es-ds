//
// Created by Eli on 12/10/25.
//
#include "em_string_builder.h"

#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "em_arena.h"

#define MAX_STRING_BUILDER_SIZE 1024;

typedef struct StringBuilder {
    size_t count;
    size_t capacity;
    uint64_t length;
    Arena *arena;
    char **ptrs;
} StringBuilder;

static inline const char* string_builder_populate(const StringBuilder *self) {
    char *string = malloc(sizeof(char) * self->length + 1);
    uint64_t cumulative_length = 0;
    for (uint64_t i = 0; i < self->count; i++) {
        const uint64_t len = strlen(self->ptrs[i]);
        memmove(string + cumulative_length, self->ptrs[i], len);
        cumulative_length += len;
    }
    string[self->length] = '\0';
    return string;
}

static inline void string_builder_reset(StringBuilder *self) {
    arena_reset(self->arena);
    memset(self->ptrs, 0, self->capacity * sizeof(char *));

    self->count = 0;
    self->length = 0;
}

StringBuilder *string_builder_create() {
    StringBuilder *builder = malloc(sizeof(StringBuilder));
    builder->capacity = 16;
    if (!builder) {
        errno = ENOMEM;
        return NULL;
    }

    builder->ptrs = malloc(sizeof(char *) * builder->capacity);
    if (!builder->ptrs) {
        free(builder);
        return NULL;
    }

    builder->arena = arena_create(0);
    if (!builder->arena) {
        errno = ENOMEM;
        free(builder->ptrs);
        free(builder);
        return NULL;
    }

    builder->length = 0;
    builder->count = 0;
    return builder;
}

void string_builder_destroy(StringBuilder *builder) {
    free(builder->ptrs);
    arena_destroy(builder->arena);
    free(builder);
}

void string_builder_add(StringBuilder *self, const char *string) {
    if (!self || !string) {
        errno = EFAULT;
        return;
    }

    // TODO: scale up ptrs if too small

    char *cpy = arena_strdup(self->arena, string);
    self->ptrs[self->count++] = cpy;
    self->length += strlen(cpy);
}

const char *string_builder_build(StringBuilder *self) {
    if (!self) {
        errno = EFAULT;
        return NULL;
    }

    if (self->count == 0) {
        errno = EINVAL;
        return NULL;
    }

    const char *string = string_builder_populate(self);
    string_builder_reset(self);


    return string;
}