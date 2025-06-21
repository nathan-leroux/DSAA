#ifndef PRIMS_H
#define PRIMS_H

#include "graph.h"


typedef struct {
  Edge* edges[MAXV+1];
  bool added[MAXV+1];
  int nvertices;
} PrimsSearch;

Graph* prims(Graph* g, int start);

#endif
