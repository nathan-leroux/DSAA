#include "dynamic_array.h"

#ifndef STACK_H
#define STACK_H

typedef struct {
    Dynarray* data;
} Stack;

Stack* stack_init(void);
void push(Stack*, char);
char pop(Stack*);
void example_stack(void);

#endif
