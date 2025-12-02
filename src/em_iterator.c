//
// Created by Eli on 12/1/25.
//

#include "em_iterator.h"

#include <stdint.h>
#include <stdlib.h>

Iterator iterator_make(const void *obj, const iterator_callback builder) {
    Iterator it;
    builder(&it, obj);
    it.pos = 0;
    return it;
}

Iterator iterator_generic_make(const void *obj, const size_t type_size, const size_t length) {
    Iterator it;
    it.pos = 0;
    it.length = length;
    it.type_size = type_size;
    it.data = obj;
    return it;
}


void *iterator_next(Iterator *it) {
    if (!it || it->pos < 0 || it->pos >= it->length) return NULL;
    void *data = (uint8_t *) it->data + it->pos * it->type_size;
    it->pos++;
    return data;
}
