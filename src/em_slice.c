//
// Created by Eli on 11/30/25.
//

#include "em_slice.h"
#include <stdio.h>
#include <stdlib.h>


Slice *slice_create(void *data, const size_t type_size, const size_t start, const size_t length) {
    Slice *slice = malloc(sizeof(Slice));
    if (!slice) return NULL;
    slice_init(slice, data, type_size, start, length);
    return slice;
}

void slice_init(Slice *slice, void *data, const size_t type_size, const size_t start, const size_t length) {
    if (!slice || !data) return;
    slice->start = start;
    slice->length = length;
    slice->type_size = type_size;
    slice->data = data;
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


