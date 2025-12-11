//
// Created by Eli on 12/10/25.
//

#ifndef EM_DS_EM_STRING_BUILDER_H
#define EM_DS_EM_STRING_BUILDER_H

typedef struct StringBuilder StringBuilder;

StringBuilder *string_builder_create();

void string_builder_destroy(StringBuilder *builder);

void string_builder_add(StringBuilder *self, const char *string);

const char *string_builder_build(StringBuilder *self);

#endif //EM_DS_EM_STRING_BUILDER_H