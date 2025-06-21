#include "graph.h"
#include "union_find.h"

#ifndef KRUSKALS_H
#define KRUSKALS_H

typedef struct {
  Edge* edges[MAXEDGE];
  int nedges;
  int min_index;
} EdgePQ;

Graph* kruskals(Graph* g);

#endif
