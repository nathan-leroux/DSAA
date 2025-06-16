#include "weighted_graph.h"

Graph* prims(Graph* g, int start) {
  Graph* spanning_tree = init_graph(false);
  Edgenode* min_node;
  int distance[MAXV+1];
  bool added[MAXV+1];

  // TODO keep track of smallest edge to add

  // find all available edges from this point
  for (Edgenode* i=g->edges[start]; i!=NULL; i=i->next) {
    distance[i->y] = i->weight;
    if (i->weight < ) {
      min = i->weight;
    }
  }



  // pick smallest and add
  // update available edges from the new vertex added
  // repeat
  return spanning_tree;
}

void example_weighted_graph(void) {
  Graph* g = init_graph(false);
  read_graph(W_GRAPH_FILE, g, true);

  print_graph(g);

  Graph* spanning_tree = prims(g, 1);
  print_graph(spanning_tree);
}
