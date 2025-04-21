#include "binary_tree.h"


#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct {
    struct tree* data;
}Pqueue;

Pqueue* pq_init(void);
void pq_insert(Pqueue*, int);
int pq_get_minimum(Pqueue*);
void example_priority_queue(void);

#endif
