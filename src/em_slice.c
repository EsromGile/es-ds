//
// Created by Eli on 11/30/25.
//

#include "em_slice.h"

#include <errno.h>

Slice slice_make(const void *data, const size_t type_size, const size_t start, const size_t length) {
    Slice slice;
    slice.type_size = type_size;
    if (!data) {
        errno = EFAULT;
        slice.start = 0;
        slice.length = 0;
        slice.data = NULL;
    } else {
        slice.start = start;
        slice.length = length;
        slice.data = data;
    }
    return slice;
}

void *slice_get(const Slice *slice, const uint64_t index) {
    if (!slice) {
        errno = EFAULT;
        return NULL;
    }

    if (index >= slice->length) {
        errno = ERANGE;
        return NULL;
    }

    return (uint8_t *) slice->data + (slice->start + index) * slice->type_size;
}
