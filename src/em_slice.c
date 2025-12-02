//
// Created by Eli on 11/30/25.
//

#include "em_slice.h"
#include <stdio.h>
#include <stdlib.h>


Slice slice_create(const void *data, const size_t type_size, const size_t start, const size_t length) {
    Slice slice;
    slice.start = start;
    slice.length = length;
    slice.type_size = type_size;
    slice.data = data;
    return slice;
}

// We aren't freeing object since we don't own the memory
void slice_destroy(Slice *slice) {
    if (!slice) return;
    slice->data = NULL;
    free(slice);
}

void slice_build_iterator(Iterator *it, const void *obj) {
    const Slice *slice = obj;
    it->length = slice->length;
    it->data = slice->data + slice->start * slice->type_size;
    it->size = slice->type_size;
}


