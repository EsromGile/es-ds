//
// Created by Eli on 11/30/25.
//

#include "em_slice.h"
#include <stdio.h>

Slice slice_make(const void *obj, const slice_callback builder, const size_t start, const size_t length) {
    Slice slice;
    builder(&slice, obj);
    slice.length = length;
    slice.start = start;
    return slice;
}

Slice slice_generic_make(const void *data, const size_t type_size, const size_t start, const size_t length) {
    Slice slice;
    slice.start = start;
    slice.length = length;
    slice.type_size = type_size;
    slice.data = data;
    return slice;
}

void slice_build_iterator(Iterator *it, const void *obj) {
    const Slice *slice = obj;
    it->length = slice->length;
    it->data = slice->data + slice->start * slice->type_size;
    it->type_size = slice->type_size;
    it->pos = 0;
}
