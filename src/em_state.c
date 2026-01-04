//
// Created by eli on 1/4/26.
//

#include "em_state.h"

#include <errno.h>
#include <stdlib.h>

State state_make(StateFunction *init_fn, void *init_data) {
    State state;
    if (!init_fn) {
        errno = EINVAL;
        state.next = NULL;
        state.data = NULL;
    } else {
        state.next = init_fn;
        state.data = init_data;
    }
    return state;
}

void state_next(State *self) {
    if (!self) {
        errno = EFAULT;
    } else if (!self->next) {
        errno = EINVAL;
    } else self->next(self);
}