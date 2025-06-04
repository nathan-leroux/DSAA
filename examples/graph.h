#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

#define MAXV 10
#define GRAPH_FILE "graph.txt"


typedef struct Edgenode {
    int y;
    int weight;
    struct Edgenode* next;
} Edgenode;


typedef struct {
    Edgenode* edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    int directed;
} Graph;


typedef struct {
    bool discovered[MAXV+1];
    bool processed[MAXV+1];
    int parent[MAXV+1];
    int entry[MAXV+1];
    int exit[MAXV+1];
    void (*process_early)(int);
    void (*process_late)(int);
    void (*process_edge)(int, int);
} Search;


Search* init_search(void (int), void (int), void (int, int));
Graph* init_graph(bool);
void example_graph(void);

#endif
