#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"

#ifndef STACK_H
#define STACK_H

typedef struct {
  Dynarray* data;
} Stack;

Stack* stack_init(void);
bool stack_is_empty(Stack*);
void stack_print(Stack*);
void push(Stack*, char);
char pop(Stack*);
void example_stack(void);

#endif
