#include "prims.h"

PrimsSearch* init_primssearch(int nvertices) {
  PrimsSearch* new_search = malloc(sizeof(PrimsSearch));

  for (int i=1; i<=nvertices; ++i) {
    new_search->edges[i] = NULL;
    new_search->added[i] = false;
  }

  new_search->nvertices = nvertices;

  return new_search;
}

static int min_cost_vertex(PrimsSearch* st) {
  int min_vertex = 0;
  int min_weight = MAXWEIGHT;

  for (int i=1; i<=st->nvertices; ++i) {
    if (st->added[i] || st->edges[i] == NULL) {
      continue;
    }

    if (st->edges[i]->weight < min_weight) {
      min_weight = st->edges[i]->weight;
      min_vertex = i;
    }
  }

  // changed to allow kruskals to work with this func
  // st->added[min_vertex] = true;
  return min_vertex;
}

static void add_span_edge(PrimsSearch* st, Edge* edge) {
  if (edge->y > st->nvertices) {
    printf("vertex %d added to search, thought only %d existed\n", edge->y, st->nvertices);
    exit(EXIT_FAILURE);
  }

  if (st->added[edge->y]) {
    printf("%d: already added\n", edge->y);
    return;
  }

  if (st->edges[edge->y] == NULL) {
    printf("%d: init cost %d\n", edge->y, edge->weight);
    st->edges[edge->y] = edge;
    return;
  }

  if (st->edges[edge->y]->weight > edge->weight) {
    printf("%d: new min %d from %d\n", edge->y, edge->weight, edge->x);
    st->edges[edge->y] = edge;
  }
}

Graph* prims(Graph* g, int start) {
  PrimsSearch* st = init_primssearch(g->nvertices);

  Edge* i;
  Graph* span = init_graph(false);
  span->nvertices = g->nvertices;

  st->added[start] = true;

  // for all start edges, add
  for (i=g->edges[start]; i!=NULL; i=i->next) {
    add_span_edge(st, i);
  }

  // pick the cheapest vertex and add
  int cheapest = min_cost_vertex(st);
  st->added[cheapest] = true;
  printf("cheapest: %d\n", cheapest);

  while (cheapest != 0) {
    insert_edge(span, st->edges[cheapest]->x, cheapest, st->edges[cheapest]->weight, false);

    // explore all the new edges from the cheapest vertex
    for (i=g->edges[cheapest]; i!=NULL; i=i->next) {
      add_span_edge(st, i);
    }

    cheapest = min_cost_vertex(st);
    st->added[cheapest] = true;
    printf("cheapest: %d\n", cheapest);
  }
    
  return span;
}
