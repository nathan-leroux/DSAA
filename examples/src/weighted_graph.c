#include "weighted_graph.h"

// return min edge that hasn't been added yet
// ideally this would be a binary tree for lookup in lgn
// but with no generics in c im not making a binary tree again
// linear time it is
// add a discovered edge to the datastructure for consideration



void example_weighted_graph(void) {
  Graph* g = init_graph(false);
  read_graph(W_GRAPH_FILE, g, true);

  Graph* prims_tree = prims(g, 1);

  printf("\n## PRIMS\n");
  print_graph(prims_tree);

  Graph* kruskals_tree = kruskals(g);

  printf("\n## KRUSKALS\n");
  print_graph(kruskals_tree);
}
