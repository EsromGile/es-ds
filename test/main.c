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

    Iterator *it2 = iterator_create(string, string_build_iterator);
    for (const char *value = iterator_next(it2); value != NULL; value = iterator_next(it2)) {
        printf("%c", *value);
    }

    // String *substring = string_substr(string, 2, 3);
    // string_debug_print(substring);
    // printf("\n");

    // int values[] = { 0, 1, 2, 3, 4, 5, 6 };
    // Slice *slice = slice_create(&values, sizeof(int), 2, 3);
    //
    // Iterator it;
    // iterator_init(&it, slice, slice_build_iterator);
    //
    // for (const int *value = iterator_next(&it); value != NULL; value = iterator_next(&it)) {
    //     printf("%d", *value);
    // }

    string_destroy(string);
    return 0;
}
