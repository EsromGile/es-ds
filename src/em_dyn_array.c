//
// Created by eli on 1/4/26.
//

#include "em_dyn_array.h"
#include "private/em_ds_utils.h"

#include <errno.h>
#include <string.h>
#include <stdint.h>

typedef struct DynArray {
    size_t capacity;
    size_t used;
    size_t next;
    size_t data_size;
    void *data;
} DynArray;

void dyn_array_realloc(DynArray *self) {
    self->capacity *= 2;
    if (self->capacity > UINT_LEAST32_MAX) self->capacity = UINT_LEAST32_MAX;
    void *data = realloc(self->data, self->capacity * self->data_size);
    if (!data) {
        errno = ENOMEM;
        return;
    }
    self->data = data;
}

DynArray *dyn_array_create(const size_t initial_capacity, const size_t data_size) {
    if (data_size < 1 || !is_power_of_two(data_size)) {
        errno = EINVAL;
        return NULL;
    }

    DynArray *self = malloc(sizeof(DynArray));
    if (!self) {
        errno = ENOMEM;
        return NULL;
    }

    self->capacity = initial_capacity;
    self->used = 0;
    self->next = 0;
    self->data_size = data_size;

    self->data = malloc(data_size * initial_capacity);
    if (!self->data) {
        errno = ENOMEM;
        free(self);
        return NULL;
    }

    return self;
}

void dyn_array_destroy(DynArray *self) {
    if (!self) {
        errno = EFAULT;
        return;
    }
    if (self->data) free(self->data);
    free(self);
}

void dyn_array_insert(DynArray *self, void *item, const size_t index) {
    if (!self || !item) {
        errno = EFAULT;
        return;
    }

    if (index >= UINT_LEAST32_MAX) {
        errno = EINVAL;
        return;
    }

    if (index >= self->capacity) {
        while (self->capacity < UINT_LEAST32_MAX && index > self->capacity) self->capacity *= 2;
        dyn_array_realloc(self);
        if (errno) return;
    }

    memcpy(self->data + index * self->data_size, item, self->data_size);

    self->used++;
    if (index > self->next) self->next = index;
    else if (index == self->next) self->next++;
}

void dyn_array_remove(DynArray *self, const size_t index) {
    if (!self) {
        errno = EFAULT;
        return;
    }

    if (self->used == 0 || index >= self->capacity || index < 1) {
        errno = EINVAL;
        return;
    }

    self->used--;
    memset(self->data + index * self->data_size, 0, self->data_size);
    if (index == self->next - 1) self->next--;
}

void dyn_array_remove_into(DynArray *self, const size_t index, void *dest) {
    if (!self || !dest) {
        errno = EFAULT;
        return;
    }

    void *data = dyn_array_get(self, index);
    if (!data) return;

    memcpy(dest, data, self->data_size);
    dyn_array_pop(self);
}

void dyn_array_push(DynArray *self, void *item) {
    if (!self || !item) {
        errno = EFAULT;
        return;
    }

    self->used++;
    if (self->used == self->capacity) {
        dyn_array_realloc(self);
        if (errno) return;
    }

    memcpy(self->data + self->next * self->data_size, item, self->data_size);
    self->next++;
}

void dyn_array_pop(DynArray *self) {
    if (!self) {
        errno = EFAULT;
        return;
    }

    if (self->next == 0 || self->used == 0) {
        errno = EINVAL;
        return;
    }

    self->used--;
    self->next--;
    memset(self->data + self->next * self->data_size, 0, self->data_size);
}

void dyn_array_pop_into(DynArray *self, void *dest) {
    if (!self || !dest) {
        errno = EFAULT;
        return;
    }

    void *data = dyn_array_get(self, self->next - 1);
    if (!data) return;

    memcpy(dest, data, self->data_size);
    dyn_array_pop(self);
}

void dyn_array_clear(DynArray *self) {
    if (!self) {
        errno = EFAULT;
        return;
    }

    self->used = 0;
    self->next = 0;

    if (!self->data) {
        self->data = malloc(self->capacity * self->data_size);
        if (!self->data) errno = ENOMEM;
    } else memset(self->data, 0, self->data_size * self->capacity);
}

void *dyn_array_get(const DynArray *self, const size_t index) {
    if (!self) {
        errno = EFAULT;
        return NULL;
    }

    if (index >= self->capacity) {
        errno = ERANGE;
        return NULL;
    }

    return self->data + index * self->data_size;
}

void *dyn_array_get_last(const DynArray *self) {
    if (!self) {
        errno = EFAULT;
        return NULL;
    }

    return dyn_array_get(self, self->next - 1);
}