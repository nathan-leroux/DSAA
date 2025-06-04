#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "linked_list.h"


#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    struct linked_list* start;
    struct linked_list* end;
} Queue;

void queue_print(Queue*);
Queue* queue_init(void);
bool queue_is_empty(Queue*);
void enqueue(Queue*, char);
char dequeue(Queue*);
void example_queue(void);

#endif
