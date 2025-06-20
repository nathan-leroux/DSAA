#include "weighted_graph.h"

SpanSearch* init_spansearch(int nvertices) {
  SpanSearch* new_search = malloc(sizeof(SpanSearch));

  for (int i=1; i<=nvertices; ++i) {
    new_search->cost[i] = NULL;
    new_search->parent[i] = 0;
    new_search->added[i] = false;
  }

  new_search->nvertices = nvertices;

  return new_search;
}

// return min edge that hasn't been added yet
// ideally this would be a binary tree for lookup in lgn
// but with no generics in c im not making a binary tree again
// linear time it is
int min_cost_vertex(SpanSearch* st) {
  int min_vertex = 0;
  int min_weight = MAXWEIGHT;

  for (int i=1; i<=st->nvertices; ++i) {
    if (st->added[i] || st->cost[i] == NULL) {
      continue;
    }

    if (st->cost[i]->weight < min_weight) {
      min_weight = st->cost[i]->weight;
      min_vertex = i;
    }
  }

  // changed to allow kruskals to work with this func
  // st->added[min_vertex] = true;
  return min_vertex;
}

// add a discovered edge to the datastructure for consideration
void add_edge(SpanSearch* st, int parent, Edgenode* edge) {
  if (edge->y > st->nvertices) {
    printf("vertex %d added to search, thought only %d existed\n", edge->y, st->nvertices);
    exit(EXIT_FAILURE);
  }

  if (st->added[edge->y]) {
    printf("%d: already added\n", edge->y);
    return;
  }

  if (st->cost[edge->y] == NULL) {
    printf("%d: init cost %d\n", edge->y, edge->weight);
    st->cost[edge->y] = edge;
    st->parent[edge->y] = parent;
    return;
  }

  if (st->cost[edge->y]->weight > edge->weight) {
    printf("%d: new min %d from %d\n", edge->y, edge->weight, parent);
    st->cost[edge->y] = edge;
    st->parent[edge->y] = parent;
  }
}

Graph* prims(Graph* g, SpanSearch* st, int start) {
  Edgenode* i;
  Graph* span = init_graph(false);
  span->nvertices = g->nvertices;

  st->added[start] = true;

  // for all start edges, add
  for (i=g->edges[start]; i!=NULL; i=i->next) {
    add_edge(st, start, i);
  }

  // pick the cheapest vertex and add
  int cheapest = min_cost_vertex(st);
  st->added[cheapest] = true;
  printf("cheapest: %d\n", cheapest);

  while (cheapest != 0) {
    insert_edge(span, st->parent[cheapest], cheapest, st->cost[cheapest]->weight, false);

    // explore all the new edges from the cheapest vertex
    for (i=g->edges[cheapest]; i!=NULL; i=i->next) {
      add_edge(st, cheapest, i);
    }

    cheapest = min_cost_vertex(st);
    st->added[cheapest] = true;
    printf("cheapest: %d\n", cheapest);
  }
    
  return span;
}

Graph* kruskals(Graph* g, SpanSearch* st) {
  return NULL;
}

void example_weighted_graph(void) {
  Graph* g = init_graph(false);
  read_graph(W_GRAPH_FILE, g, true);

  SpanSearch* st = init_spansearch(g->nvertices);

  // Graph* spanning_tree = prims(g, st, 1);
  Graph* spanning_tree = kruskals(g, st);
  print_graph(spanning_tree);
}
