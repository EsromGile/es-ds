//
// Created by Eli on 12/1/25.
//

#include "em_iterator.h"

#include <stdint.h>
#include <stdlib.h>

Iterator iterator_create(void *obj, const iterator_callback builder) {
    Iterator it;
    builder(&it, obj);
    it.pos = 0;
    return it;
}

void *iterator_next(Iterator *it) {
    if (!it || it->pos < 0 || it->pos >= it->length) return NULL;
    void *data = (uint8_t *)it->data + it->pos * it->size;
    it->pos++;
    return data;
}