//
// Created by Eli on 12/1/25.
//

#ifndef EM_DS_EM_ITERATOR_H
#define EM_DS_EM_ITERATOR_H

#include <stddef.h>
#include <stdint.h>

typedef struct Iterator {
    const void *data;
    size_t type_size;
    uint64_t pos;
    uint64_t length;
} Iterator;

Iterator iterator_make(const void *obj, size_t type_size, size_t length, uint64_t pos);

void *iterator_next(Iterator *it);

#endif //EM_DS_EM_ITERATOR_H
