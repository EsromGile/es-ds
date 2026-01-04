//
// Created by eli on 1/4/26.
//

#ifndef EM_DS_EM_DS_UTILS_H
#define EM_DS_EM_DS_UTILS_H
#include <stdbool.h>
#include <stddef.h>

static bool is_power_of_two(const size_t num) {
    return num != 0 && !(num & (num - 1));
}

#endif //EM_DS_EM_DS_UTILS_H