//
// Created by Eli on 11/30/25.
//

#ifndef EM_DS_EM_SLICE_H
#define EM_DS_EM_SLICE_H

#include <stdint.h>

#include "em_iterator.h"

typedef struct Slice {
    uint8_t *data;
    size_t start;
    size_t length;
    size_t type_size;
} Slice;

Slice *slice_create(void *data, size_t type_size, size_t start, size_t length);

void slice_init(Slice *slice, void *data, size_t type_size, size_t start, size_t length);

// We aren't freeing object since we don't own the memory
void slice_destroy(Slice *slice);

void slice_build_iterator(Iterator *it, void *obj);

#endif //EM_DS_EM_SLICE_H