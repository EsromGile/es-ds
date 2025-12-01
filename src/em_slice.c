//
// Created by Eli on 11/30/25.
//

#include "em_slice.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Slice {
    uint8_t *data;
    size_t start;
    size_t length;
    size_t type_size;
} Slice;

Slice *slice_create(void *data, const size_t type_size, const size_t start, const size_t length) {
    Slice *slice = malloc(sizeof(Slice));
    slice->start = start;
    slice->length = length;
    slice->type_size = type_size;
    slice->data = data;
    return slice;
}

// We aren't freeing object since we don't own the memory
void slice_destroy(Slice *slice) {
    if (!slice) return;
    slice->data = NULL;
    free(slice);
}

void slice_build_iterator(Iterator *it, void *obj) {
    const Slice *slice = obj;
    it->length = slice->length;
    it->data = slice->data + slice->start * slice->type_size;
    it->size = slice->type_size;
}


