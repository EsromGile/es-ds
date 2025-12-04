//
// Created by Eli on 11/30/25.
//

#ifndef EM_DS_EM_SLICE_H
#define EM_DS_EM_SLICE_H

#include <stddef.h>
#include <stdint.h>

typedef struct Slice {
    const void *data;
    size_t type_size;
    uint64_t start;
    uint64_t length;
} Slice;

Slice slice_make(const void *data, size_t type_size, size_t start, size_t length);

void *slice_get(const Slice *slice, uint64_t index);

#endif //EM_DS_EM_SLICE_H
