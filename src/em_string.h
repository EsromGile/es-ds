//
// Created by eli on 11/28/25.
//

#ifndef EM_DS_STRING_H
#define EM_DS_STRING_H

#include <stdbool.h>
#include <stddef.h>

typedef struct String String;

// --- Constructors / Destructors ---
String *string_create(const char *string);

String *string_empty();

String *string_copy(const String *self);

void string_destroy(String *self);

// --- Basic Operations ---
size_t string_length(const String *self);

const char *string_cstr(const String *self);

// --- Modification ---

void string_concat(String *self, const char *suffix);

void string_insert(String *self, size_t pos, const char *substring);

// --- Comparison ---
int string_compare(const String *a, const String *b);

bool string_equals(const String *a, const String *b);

// --- Utility ---
String *string_substr(const String *self, size_t start, size_t length);

void string_clear(String *self);

void string_debug_print(const String *self);

#endif //EM_DS_STRING_H
