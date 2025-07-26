#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Linked List example
 *
 * list_print   - helper function
 * list_create  - O(1)
 * list_pop     - O(1)
 * list_append  - O(1)  (appends at the head of the list)
 * list_tail    - O(n)  (traverses list)
 *
 */

void list_print(struct linked_list* list) {
  printf("[");

  while (list != NULL) {
    printf("%c", list->value);

    if (list->next != NULL) {
      printf(", ");
    }

    list = list->next;
  }

  printf("]\n");
}

struct linked_list* list_init(void) { return NULL; }

struct linked_list* list_create(void) {
  struct linked_list* new_list = malloc(sizeof(struct linked_list));

  new_list->prev = NULL;
  new_list->value = 0;
  new_list->next = NULL;

  return new_list;
}

char list_pop(struct linked_list** head, struct linked_list* node) {
  if (node->prev != NULL) {
    node->prev->next = node->next;
  }
  if (node->next != NULL) {
    node->next->prev = node->prev;
  }

  char popped_value = node->value;

  // avoiding chopping the lists head off and getting seggies
  if (node->prev == NULL && node->next == NULL) {
    *head = NULL;
  } else if (node->prev == NULL) {
    *head = node->next;
  }

  free(node);

  return popped_value;
}

// appends at the head
void list_append(struct linked_list** list_p, char value) {
  struct linked_list* new_list = list_create();
  struct linked_list* old_list = *list_p;

  new_list->value = value;
  new_list->next = old_list;

  if (old_list != NULL) {
    old_list->prev = new_list;
  }

  *list_p = new_list;
}

struct linked_list* list_tail(struct linked_list* list) {
  while (list->next != NULL) {
    list = list->next;
  }

  return list;
}

void example_linked_list(void) {
  // ensure i would be able to make a stack and a queue with this
  struct linked_list* list = list_init();
  char* string = "linked list";

  printf("## Linked List\n\n");
  printf("Appending to array  (added to head so input is reversed)\n");

  for (int i = 0; i < strlen(string); ++i) {
    list_append(&list, string[i]);
    list_print(list);
  }
  printf("\n");
  printf("Popping from head\n");

  list_pop(&list, list);
  list_print(list);

  printf("\n");
  printf("Popping from tail\n");

  list_pop(&list, list_tail(list));
  list_print(list);
}
