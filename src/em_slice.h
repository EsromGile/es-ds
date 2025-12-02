//
// Created by Eli on 11/30/25.
//

#ifndef EM_DS_EM_SLICE_H
#define EM_DS_EM_SLICE_H

#include "em_iterator.h"

typedef struct Slice {
    const void *data;
    size_t start;
    size_t length;
    size_t type_size;
} Slice;

typedef void (*slice_callback)(Slice *slice, const void *data);

Slice slice_generic_make(const void *data, size_t type_size, size_t start, size_t length);

Slice slice_make(const void *obj, slice_callback builder, size_t start, size_t length);

void slice_build_iterator(Iterator *it, const void *obj);

#endif //EM_DS_EM_SLICE_H
