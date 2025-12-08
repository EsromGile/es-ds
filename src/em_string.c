//
// Created by eli on 11/28/25.
//

#include "em_string.h"
#include "em_mem_print.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
    size_t length;
    size_t capacity;
    char *data;
} String;

/* ===== TODOS =====
 * - add error logging
 * - add smart memory capacity scaling
 */

static size_t string_alloc_round(const size_t min_capacity) {
    return (min_capacity / 16 + 1) * 16;
}

static String *string_buffer_create(const size_t min_capacity) {
    String *s = malloc(sizeof(String));
    if (!s) return NULL;

    const size_t alloc_size = string_alloc_round(min_capacity);
    s->data = malloc(alloc_size);
    if (!s->data) {
        free(s);
        return NULL;
    }

    s->capacity = alloc_size - 1;
    s->length = 0;
    s->data[0] = '\0';
    return s;
}

static void string_buffer_populate(String *self, const char *string, const size_t length) {
    memcpy(self->data, string, length);
    self->data[length - 1] = '\0';
    self->length = length - 1;
}

static bool string_resize_memory(String *self, const size_t min_capacity) {
    if (self->capacity >= min_capacity) return true;

    size_t alloc_size = self->capacity;
    while (alloc_size < min_capacity) {
        alloc_size = string_alloc_round((size_t) ((double) alloc_size * 1.5));
    }

    char *new_data = realloc(self->data, alloc_size);
    if (!new_data) return false;
    self->data = new_data;
    self->capacity = alloc_size - 1;
    return true;
}

// --- Constructors / Destructors ---
String *string_create(const char *string) {
    const size_t length = strlen(string) + 1;
    String *s = string_buffer_create(length);
    if (!s) return NULL;

    string_buffer_populate(s, string, length);
    return s;
}

String *string_empty() {
    String *s = string_buffer_create(16);
    if (!s) return NULL;

    s->data[0] = '\0';
    return s;
}

String *string_copy(const String *self) {
    const size_t length = self->length + 1;
    String *s = string_buffer_create(length);
    if (!s) return NULL;

    string_buffer_populate(s, self->data, length);
    return s;
}

void string_destroy(String *self) {
    if (!self) return;
    free(self->data);
    free(self);
}

// --- Basic Operations ---
size_t string_length(const String *self) {
    return self ? self->length : 0;
}

const char *string_cstr(const String *self) {
    if (!self) return NULL;
    return self->data;
}

// --- Modification ---
void string_concat(String *self, const char *suffix) {
    if (!suffix) return;
    const size_t suffix_len = strlen(suffix);
    const size_t new_length = self->length + suffix_len;
    if (!string_resize_memory(self, new_length)) return;
    memcpy(self->data + self->length, suffix, suffix_len);
    self->data[new_length] = '\0';
    self->length = new_length;
}

void string_insert(String *self, const size_t pos, const char *substring) {
    if (!substring) return;
    if (pos == self->length) return string_concat(self, substring);
    if (pos > self->length) return;
    const size_t new_length = self->length + strlen(substring);
    const size_t substring_length = strlen(substring);
    if (!string_resize_memory(self, new_length)) return;
    memmove(self->data + pos + substring_length, self->data + pos, self->length - pos + 1);
    memcpy(self->data + pos, substring, substring_length);
    self->data[new_length] = '\0';
    self->length = new_length;
}

// --- Comparison ---
int string_compare(const String *a, const String *b) {
    if (!a && !b) return 0;
    if (!a) return -1;
    if (!b) return 1;
    return strcmp(a->data, b->data);
}

bool string_equals(const String *a, const String *b) {
    return string_compare(a, b) == 0;
}

// --- Utility ---
String *string_substr(const String *self, const size_t start, const size_t length) {
    if (!self || start + length > self->length) return NULL;
    String *s = string_buffer_create(length + 1);
    if (!s) return NULL;

    memcpy(s->data, self->data + start, length);
    s->data[length] = '\0';
    s->length = length;
    return s;
}

void string_clear(String *self) {
    if (!self) return;
    memset(self->data, 0, self->capacity + 1);
    self->data[0] = '\0';
    self->length = 0;
}

void string_debug_print(const String *self) {
    printf("\n===== STRING =====\n");
    printf("Capacity: %zu\n", self->capacity);
    printf("Length: %zu\n", self->length);
    printf("Contents: {\n");
    mem_print_bytes((uint8_t *)self->data, self->capacity + 1, 16);
    printf("}\n");
    printf("==================\n");
}
