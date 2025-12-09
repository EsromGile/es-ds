//
// Created by Eli on 12/1/25.
//

#include "em_iterator.h"

#include <errno.h>

Iterator iterator_make(const void *obj, const size_t type_size, const size_t length, const uint64_t pos) {
    Iterator it;
    it.type_size = type_size;
    if (!obj) {
        errno = EFAULT;
        it.pos = 0;
        it.length = 0;
        it.data = NULL;
    } else {
        it.pos = pos;
        it.length = pos == 0 ? length : pos + length;
        it.data = obj;
    }
    return it;
}

void *iterator_next(Iterator *it) {
    if (!it || !it->data) {
        errno = EFAULT;
        return NULL;
    }

    if (it->pos < 0 || it->pos >= it->length) {
        errno = ERANGE;
        return NULL;
    }

    void *data = (uint8_t *) it->data + it->pos * it->type_size;
    it->pos++;
    return data;
}
