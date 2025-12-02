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
    printf("\n");

    Slice slice1 = slice_make(string, string_build_slice, 2, 3);
    Iterator it3 = iterator_make(&slice1, slice_build_iterator);
    printf(">>> SLICE:{\n");
    for (const char *value = iterator_next(&it3); value != NULL; value = iterator_next(&it3)) {
        printf("%c", *value);
    }
    printf("\n}\n");

    Iterator it2 = iterator_make(string, string_build_iterator);
    printf(">>> ITERATOR:{\n");
    for (const char *value = iterator_next(&it2); value != NULL; value = iterator_next(&it2)) {
        printf("%c", *value);
    }
    printf("\n}\n");

    // String *substring = string_substr(string, 2, 3);
    // string_debug_print(substring);
    // printf("\n");

    const int values[] = {0, 1, 2, 3, 4, 5, 6};
    Slice slice = slice_generic_make(&values, sizeof(int), 2, 3);
    Iterator it4 = iterator_make(&slice, slice_build_iterator);
    for (const int *value = iterator_next(&it4); value != NULL; value = iterator_next(&it4)) {
        printf("%d", *value);
    }

    Iterator it = iterator_generic_make(values, sizeof(int), sizeof(values) / sizeof(int));
    for (const int *value = iterator_next(&it); value != NULL; value = iterator_next(&it)) {
        printf("%d", *value);
    }

    string_destroy(string);
    return 0;
}
