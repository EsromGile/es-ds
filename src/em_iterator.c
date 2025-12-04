//
// Created by Eli on 12/1/25.
//

#include "em_iterator.h"

Iterator iterator_make(const void *obj, const size_t type_size, const size_t length, const uint64_t pos) {
    Iterator it;
    it.pos = !pos ? 0 : pos;
    it.length = !pos ? length : pos + length;
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
