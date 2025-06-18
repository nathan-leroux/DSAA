#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include "graph.h"

#define W_GRAPH_FILE "weighted.txt"

void example_weighted_graph(void);

typedef struct {
  Graph* g;
  Edgenode* edges[MAXV+1];
  bool added[MAXV+1];
} SpanningTree;

// typedef struct {
// } UnionSet;

SpanningTree* init_spantree(void);
Graph* prims(Graph* g, int current);
Graph* kruskals(Graph* g);
Graph* dijkstras(Graph* g, int start, int end);

#endif
