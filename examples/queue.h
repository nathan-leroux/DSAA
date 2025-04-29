#include "linked_list.h"


#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    struct linked_list* start;
    struct linked_list* end;
} Queue;

void queue_print(Queue*);
Queue* queue_init(void);
void enqueue(Queue*, char);
char dequeue(Queue*);
void example_queue(void);

#endif
