#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"


/*
 * Stack example
 *
 * Implemented with dynamic array
 * First In, First Out (FIFO)
 *
 * stack_init   - O(1)
 * push         - O(1)
 * pop          - O(1)
 *
*/


Stack* stack_init(void) {
    Stack* new_stack = malloc(sizeof(Stack));
    new_stack->data = dynarray_init(2);

    return new_stack;
}


void push(Stack* stack, char input) {
    dynarray_append(stack->data, input);
}


char pop(Stack* stack) {
    Dynarray* array = stack->data;

    return dynarray_pop(array, array->data_end-1);
}


void example_stack(void) {
    Stack* stack = stack_init();
    char* string = "abc";

    printf("## Stack example\n");
    printf("##\n");
    printf("## push to stack\n");
    printf("##\n");

    for (int i=0; i<strlen(string); ++i) {
        printf("push: %c\n", string[i]);
        push(stack, string[i]);
    }

    printf("##\n");
    printf("## pop from stack\n");
    printf("##\n");

    printf("pop: %c\n", pop(stack));
    printf("pop: %c\n", pop(stack));
    printf("pop: %c\n", pop(stack));
}
