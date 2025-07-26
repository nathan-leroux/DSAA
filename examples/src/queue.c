
#include "queue.h"

/*
 * Queue example
 *
 * Implemented with linked list
 * First In, First Out (FIFO)
 *
 * queue_init   - O(1)
 * enqueue      - O(1)
 * dequeue      - O(1)  (constant time as end node is cached)
 *
 */

void queue_print(Queue* queue) { list_print(queue->start); }

Queue* queue_init(void) {
  Queue* new_queue = malloc(sizeof(Queue));

  new_queue->start = list_init();
  new_queue->end = new_queue->start;

  return new_queue;
}

bool queue_is_empty(Queue* q) { return q->start == NULL; }

void enqueue(Queue* queue, char input) {
  list_append(&queue->start, input);

  // set the end marker if it hasn't been
  if (queue->end == NULL) {
    queue->end = queue->start;
  }
}

char dequeue(Queue* queue) {
  if (queue->start == NULL) {
    return 0;
  }

  struct linked_list* popped_node = queue->end;
  queue->end = popped_node->prev;

  return list_pop(&queue->start, popped_node);
}

void example_queue(void) {
  Queue* queue = queue_init();

  char* string = "abc";

  printf("## Queue\n\n");
  printf("Enqueue values\n");

  for (int i = 0; i < strlen(string); ++i) {
    printf("enqueue: %c\n", string[i]);
    enqueue(queue, string[i]);
  }

  printf("\n");
  printf("Dequeue values\n");

  for (int i = 0; i < strlen(string); ++i) {
    printf("dequeue: %c\n", dequeue(queue));
  }
}
