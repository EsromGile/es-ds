//
// Created by eli on 11/28/25.
//

#include "string.h"

int main(void) {
    String *string = string_create("Hello World");
    string_debug_print(string);

    String *substring = string_substr(string, 2, 3);
    string_debug_print(substring);

    string_destroy(string);
    return 0;
}
