//
// Created by eli on 11/28/25.
//

#include <stdio.h>

#include "em_iterator.h"
#include "em_slice.h"
#include "em_string.h"

int main(void) {
    String *string = string_create("Hello World");
    string_debug_print(string);

    string_insert(string, 5, "-elloello");
    string_debug_print(string);

    string_concat(string, "#EIEIO");
    string_debug_print(string);

    String *substr = string_substr(string, 6, 10);
    string_debug_print(substr);
    string_destroy(substr);

    // const Slice slice1 = slice_make(string_cstr(string), sizeof(char), 2, 3);
    // const char *s = slice_get(&slice1, 0);
    // printf("%c\n", *s);

    // Iterator it3 = iterator_make(slice1.data, sizeof(char), slice1.length, slice1.start);
    // printf(">>> SLICE:{\n");
    // for (const char *value = iterator_next(&it3); value != NULL; value = iterator_next(&it3)) {
    //     printf("%c", *value);
    // }
    // printf("\n}\n");
    //
    // Iterator it2 = iterator_make(string_cstr(string), sizeof(char), string_length(string), 0);
    // printf(">>> ITERATOR:{\n");
    // for (const char *value = iterator_next(&it2); value != NULL; value = iterator_next(&it2)) {
    //     printf("%c", *value);
    // }
    // printf("\n}\n");

    // String *substring = string_substr(string, 2, 3);
    // string_debug_print(substring);
    // printf("\n");

    // const int values[] = {0, 1, 2, 3, 4, 5, 6};
    // const Slice slice = slice_make(&values, sizeof(int), 2, 3);
    // Iterator it4 = iterator_make(slice.data, sizeof(int), slice.length, 0);
    // for (const int *value = iterator_next(&it4); value != NULL; value = iterator_next(&it4)) {
    //     printf("%d", *value);
    // }
    //
    // Iterator it = iterator_make(values, sizeof(int), sizeof(values) / sizeof(int), 0);
    // for (const int *value = iterator_next(&it); value != NULL; value = iterator_next(&it)) {
    //     printf("%d", *value);
    // }

    string_destroy(string);
    return 0;
}
