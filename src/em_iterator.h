//
// Created by Eli on 12/1/25.
//

#ifndef EM_DS_EM_ITERATOR_H
#define EM_DS_EM_ITERATOR_H
#include <stdio.h>

typedef struct Iterator {
    const void *data;
    size_t type_size;
    size_t pos;
    size_t length;
} Iterator;

typedef void (*iterator_callback)(Iterator *it, const void *data);

Iterator iterator_make(const void *obj, iterator_callback builder);

Iterator iterator_generic_make(const void *obj, size_t type_size, size_t length);

void *iterator_next(Iterator *it);

#endif //EM_DS_EM_ITERATOR_H
