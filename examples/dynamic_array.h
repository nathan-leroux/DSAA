#include <stdio.h>

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

typedef struct Dynarray {
    size_t length;
    size_t data_end;
    char* data;
} Dynarray;

void dynarray_print(Dynarray*);
void dynarray_append(Dynarray*, char);
Dynarray* dynarray_init(size_t len);
char dynarray_pop(Dynarray*, size_t);

#endif
