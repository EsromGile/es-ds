//
// Created by eli on 11/28/25.
//

#include "em_string.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
    size_t length;
    size_t capacity;
    char data[];
} String;

static String *string_buffer_create(const size_t buffer_size) {
    String *s = malloc(sizeof(String) + buffer_size);
    if (!s) return NULL;

    s->capacity = buffer_size - 1;
    s->length = 0;
    return s;
}

static void string_buffer_populate(String *src, const char *dest, const size_t length) {
    memcpy(src->data, dest, length);
    src->data[length - 1] = '\0';
    src->length = length - 1;
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

String *string_copy(const String *string) {
    const size_t length = string->length + 1;
    String *s = string_buffer_create(length);
    if (!s) return NULL;

    string_buffer_populate(s, string->data, length);
    return s;
}

void string_destroy(String *string) {
    if (!string) return;
    free(string);
}

// --- Basic Operations ---
size_t string_length(const String *string) {
    return string ? string->length : 0;
}

const char *string_cstr(const String *string) {
    if (!string) return NULL;
    return string->data;
}

// --- Modification ---
void string_concat(String *dest, const String *src);

void string_insert(String *string, size_t pos, const char *substring);

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
String *string_substr(const String *string, const size_t start, const size_t len) {
    const size_t substr_len = len + 1; // Accounting for missing \0 character
    if (!string || start + len > string->length) return NULL;
    String *s = string_buffer_create(substr_len);
    if (!s) return NULL;

    string_buffer_populate(s, string->data + start, substr_len);
    return s;
}

void string_clear(String *string) {
    if (!string) return;
    memset(string->data, 0, string->capacity + 1);
    string->data[0] = '\0';
    string->length = 0;
}

void string_print(const String *string) {
    printf("%s", string->data);
}

void string_debug_print(const String *string) {
    for (size_t j = 0; j < 16 && j <= string->capacity; j++) {
        const unsigned char character = string->data[j];
        if (character >= 0x20 && character <= 0x7E) printf("%c", character);
        else if (character == '\0') printf("\\0");
        else printf(".");
    }
}
