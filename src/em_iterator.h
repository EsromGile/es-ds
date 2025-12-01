//
// Created by Eli on 12/1/25.
//

#ifndef EM_DS_EM_ITERATOR_H
#define EM_DS_EM_ITERATOR_H
#include <stdio.h>

typedef struct Iterator {
    void *data;
    size_t size;
    size_t pos;
    size_t length;
} Iterator;

typedef void (*iterator_func)(Iterator *, void *);

Iterator *iterator_create(void *obj, iterator_func);

void iterator_init(Iterator *it, void *obj, iterator_func);

void *iterator_next(Iterator *it);

#endif //EM_DS_EM_ITERATOR_H