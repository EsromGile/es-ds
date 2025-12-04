//
// Created by eli on 11/28/25.
//

#ifndef EM_DS_STRING_H
#define EM_DS_STRING_H
#include <stdbool.h>
#include <stddef.h>

#include "em_iterator.h"
#include "em_slice.h"

typedef struct String {
    size_t length;
    size_t capacity;
    char data[];
} String;

// --- Constructors / Destructors ---
String *string_create(const char *string);

String *string_empty();

String *string_copy(const String *string);

void string_destroy(String *string);

// --- Basic Operations ---
size_t string_length(const String *string);

const char *string_cstr(const String *string);

// --- Modification ---
int string_append(String *string, const char *suffix);

int string_concat(String *dest, const String *src);

int string_insert(String *string, size_t pos, const char *substring);

int string_resize(String *string, size_t new_capacity);

// --- Comparison ---
int string_compare(const String *a, const String *b);

bool string_equals(const String *a, const String *b);

// --- Utility ---
String *string_substr(const String *string, size_t start, size_t len);

void string_clear(String *string);

void string_print(const String *string);

void string_debug_print(const String *string);

#endif //EM_DS_STRING_H
