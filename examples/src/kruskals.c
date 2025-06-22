#include "kruskals.h"


Graph* kruskals(Graph* g) {
  UnionFind* uf = init_union_find(g->nvertices);
  EdgePQ* pq = init_edge_pq();
  Graph* span = init_graph(false);
  span->nvertices = g->nvertices;


  // load up the edges
  for (int i=1; i<=g->nvertices; ++i) {
    for (Edge* edge=g->edges[i]; edge!=NULL; edge=edge->next) {
      add_edge(pq, edge);
    }
  }

  // pick smallest edge
  Edge* smallest = min_edge(pq);

  int count = 1;
  while (count < g->nvertices) {
    // if not connected already, connect components
    if (find_uf(uf, smallest->y) != find_uf(uf,smallest->x)) {
      printf("%d, %d  connected, weight %d\n", smallest->x, smallest->y, smallest->weight);

      merge_uf(uf, smallest->y, smallest->x);
      insert_edge(span, smallest->x, smallest->y, smallest->weight, false);
      ++count;
    }
    else {
      printf("\t%d, %d  ignored, already connected\n", smallest->x, smallest->y);
    }

    smallest = min_edge(pq);
  }

  return span;
}
