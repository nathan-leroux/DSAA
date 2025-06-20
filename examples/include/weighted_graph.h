#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include "graph.h"
#include "union_find.h"

#define W_GRAPH_FILE "weighted.txt"


typedef struct {
  Edgenode* cost[MAXV+1];
  int parent[MAXV+1];
  bool added[MAXV+1];
  int nvertices;
} SpanSearch;

// typedef struct {
// } UnionSet;

SpanSearch* init_spansearch(int nvertices);
int min_cost_vertex(SpanSearch* st);
void add_edge(SpanSearch* st, int parent, Edgenode* edge);

Graph* prims(Graph* g, SpanSearch* st, int start);
Graph* kruskals(Graph* g, SpanSearch* st);
Graph* dijkstras(Graph* g, int start, int end);

void example_weighted_graph(void);

#endif
