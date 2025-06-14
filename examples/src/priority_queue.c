#include "priority_queue.h"

#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

/*
 * Priority Queue
 *
 * not much to implement, essentially a wrapper of a binary tree
 *
 * pq_insert()      - O(logn)
 * pq_get_minimum() - O(logn)
 *
 */

Pqueue* pq_init(void) {
  Pqueue* new_pqueue = malloc(sizeof(Pqueue));

  new_pqueue->data = NULL;

  return new_pqueue;
}

void pq_insert(Pqueue* queue, int input) {
  tree_insert(&queue->data, NULL, input);
}

int pq_get_minimum(Pqueue* queue) {
  int result;

  struct tree* result_node = tree_minimum(queue->data);
  result = result_node->value;

  tree_delete(&queue->data, result_node);
  return result;
}

void example_priority_queue(void) {
  printf("## Priority Queue example\n");
  printf("##\n");
  printf("## inserting values into queue\n");
  printf("##\n");
  Pqueue* queue = pq_init();

  printf("insert: %d\n", 5);
  pq_insert(queue, 5);
  printf("insert: %d\n", 2);
  pq_insert(queue, 2);
  printf("insert: %d\n", 4);
  pq_insert(queue, 4);
  printf("insert: %d\n", 1);
  pq_insert(queue, 1);
  printf("insert: %d\n", 3);
  pq_insert(queue, 3);

  tree_print(queue->data);

  printf("##\n");
  printf("## Retrieving in order\n");
  printf("##\n");

  printf("got: %d\n", pq_get_minimum(queue));
  printf("got: %d\n", pq_get_minimum(queue));
  printf("got: %d\n", pq_get_minimum(queue));
  printf("got: %d\n", pq_get_minimum(queue));
  printf("got: %d\n", pq_get_minimum(queue));
}
