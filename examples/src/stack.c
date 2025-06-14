#include "stack.h"

/*
 * Stack example
 *
 * Implemented with dynamic array
 * Last In, First Out (LIFO)
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

bool stack_is_empty(Stack* s) { return s->data->data_end == 0; }

void stack_print(Stack* s) {
  printf("[");
  if (!stack_is_empty(s)) {
    printf("%d", pop(s));
  }

  while (!stack_is_empty(s)) {
    printf(", %d", pop(s));
  }
  printf("]\n");
}

void push(Stack* stack, char input) { dynarray_append(stack->data, input); }

char pop(Stack* stack) {
  Dynarray* array = stack->data;

  return dynarray_pop(array, array->data_end - 1);
}

void example_stack(void) {
  Stack* stack = stack_init();
  char* string = "abc";

  printf("## Stack example\n");
  printf("##\n");
  printf("## push to stack\n");
  printf("##\n");

  for (int i = 0; i < strlen(string); ++i) {
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
