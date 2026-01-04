//
// Created by eli on 1/4/26.
//

#ifndef EM_DS_EM_STATE_H
#define EM_DS_EM_STATE_H

struct State;
typedef void StateFunction(struct State *state);

typedef struct State {
    StateFunction *next;
    void *data;
} State;

State state_make(StateFunction *init_fn, void *init_data);

void state_next(State *self);

#endif //EM_DS_EM_STATE_H