//
// Created by eli on 11/22/25.
//

#ifndef EM_ALLOCATORS_MEM_PRINT_H
#define EM_ALLOCATORS_MEM_PRINT_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static inline void mem_print_bytes(const uint8_t *data, const size_t upper_bound, const uint8_t bytes_per_line) {
    if (!data) {
        printf("    NULL");
        return;
    }
    for (size_t row = 0; row < upper_bound; row += bytes_per_line) {
        printf("    %04zx: ", row);
        for (size_t col = 0; col < bytes_per_line; col++) {
            if (row + col < upper_bound) printf("%02x ", data[row + col]);
            else printf("   ");
        }
        printf(" |");
        for (size_t j = 0; j < bytes_per_line && row + j < upper_bound; j++) {
            const unsigned char character = data[row + j];
            if (character >= 0x20 && character <= 0x7E) printf("%c", character);
            else printf(".");
        }
        printf("|\n");
    }
}

#endif //EM_ALLOCATORS_MEM_PRINT_H
