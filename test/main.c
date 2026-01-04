//
// Created by eli on 11/28/25.
//

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "em_dyn_array.h"
#include "em_hash.h"
#include "em_iterator.h"
#include "em_slice.h"
#include "em_state.h"
#include "em_string.h"
#include "em_string_builder.h"

StateFunction start, end;
void start(State *state) {
    printf("start\n");
    state->next = end;
}
void end(State *state) {
    printf("end\n");
    state->next = start;
}

int main(void) {
    // String *string = string_create("Hello World");
    // string_debug_print(string);
    //
    // printf("INSERT");
    // string_insert(string, 5, "-elloello");
    // string_debug_print(string);
    //
    // printf("CONCAT");
    // string_concat(string, "#EIEIO");
    // string_debug_print(string);
    //
    // String *substr = string_substr(string, 6, 10);
    // string_debug_print(substr);
    // string_destroy(substr);

    // StringBuilder *builder = string_builder_create();
    // string_builder_multi_add(builder, 16, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15");
    // String *str = string_own_create(string_builder_build(builder));
    // printf("%s\n", string_cstr(str));
    // string_destroy(str);
    // string_builder_destroy(builder);

    // HashTable *hash_table = hash_table_create(0, sizeof(uint32_t));
    // uint32_t value = 32;
    // hash_table_add(hash_table, &value);
    // bool x = hash_table_contains_value(hash_table, &value);
    // printf("Contains: %d\n", x);

    DynArray *array = dyn_array_create(16, sizeof (int));
    for (int i = 0; i < 100; i++) {
        dyn_array_push(array, &i);
    }

    for (int i = 0; i < 100; i++) {
        int dest;
        dyn_array_pop_into(array, &dest);
        int *data = dyn_array_get_last(array);
        printf("STATE:\n");
        printf("  > Dest | Pointer: %p, Value: %d\n", &dest, dest);
        if (data) printf("  > Last | Pointer: %p, Value: %d\n", data, *data);
        else printf("  > Last | Pointer: NULL, Value: NULL");
    }


    // State state = state_make(start, NULL);
    // state_next(&state);
    // state_next(&state);

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

    // string_destroy(string);
    return 0;
}
