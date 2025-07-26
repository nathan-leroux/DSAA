#include "weighted_graph.h"

// return min edge that hasn't been added yet
// ideally this would be a binary tree for lookup in lgn
// but with no generics in c im not making a binary tree again
// linear time it is
// add a discovered edge to the datastructure for consideration

void example_weighted_graph(void) {
  Graph* g = init_graph(false);
  read_graph(W_GRAPH_FILE, g, true);

  printf("## Weighted Graphs\n");
  printf("weighted graph for examples can be found pg248 in textbook\n\n");

  printf("Prims algorithm for minimum spanning tree\n");
  Graph* prims_tree = prims(g, 1);
  print_graph(prims_tree);

  printf("\n");
  printf("Kruskals algorithm for minimum spanning tree\n");
  Graph* kruskals_tree = kruskals(g);
  print_graph(kruskals_tree);

  printf("\n");
  printf("Dijkstras algorithm for shortest path\n");
  Graph* dijkstras_path = dijkstras(g, 7, 2);
  print_graph(dijkstras_path);
}
