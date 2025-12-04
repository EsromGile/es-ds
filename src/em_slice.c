//
// Created by Eli on 11/30/25.
//

#include "em_slice.h"

Slice slice_make(const void *data, const size_t type_size, const size_t start, const size_t length) {
    Slice slice;
    slice.start = start;
    slice.length = length;
    slice.type_size = type_size;
    slice.data = data;
    return slice;
}

void *slice_get(const Slice *slice, const uint64_t index) {
    if (!slice || index >= slice->length) {
        return NULL;
    }
    return (uint8_t *) slice->data + (slice->start + index) * slice->type_size;
}
