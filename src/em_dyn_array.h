//
// Created by eli on 1/4/26.
//

#ifndef EM_DS_EM_DYN_ARRAY_H
#define EM_DS_EM_DYN_ARRAY_H

#include <stdlib.h>

typedef struct DynArray DynArray;

DynArray *dyn_array_create(size_t initial_capacity, size_t data_size);

void dyn_array_destroy(DynArray *self);

void dyn_array_insert(DynArray *self, void *item, size_t index);

void dyn_array_remove(DynArray *self, size_t index);

void dyn_array_remove_into(DynArray *self, size_t index, void *dest);

void dyn_array_push(DynArray *self, void *item);

void dyn_array_pop(DynArray *self);

void dyn_array_pop_into(DynArray *self, void *dest);

void dyn_array_clear(DynArray *self);

void *dyn_array_get(const DynArray *self, size_t index);

void *dyn_array_get_last(const DynArray *self);

#endif //EM_DS_EM_DYN_ARRAY_H