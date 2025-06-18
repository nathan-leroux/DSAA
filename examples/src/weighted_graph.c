#include "weighted_graph.h"

SpanningTree* init_spantree(void) {
  return NULL;
}

// return min edge that hasn't been added yet
Edgenode* return_min_edge(SpanningTree* st) {
  return NULL;
}

// add a discovered edge to the datastructure for consideration
void add_possible_edge(SpanningTree* st, Edgenode* edge) {
}

Graph* prims(Graph* g, int current) {
  return NULL;
}

Graph* kruskals(Graph* g) {
  return NULL;
}

void example_weighted_graph(void) {
  Graph* g = init_graph(false);
  read_graph(W_GRAPH_FILE, g, true);

  Graph* spanning_tree = prims(g, 1);
  print_graph(spanning_tree);
}
