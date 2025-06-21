#include "kruskals.h"

static EdgePQ* init_edge_pq(void) {
  EdgePQ* new_pq = malloc(sizeof(EdgePQ));

  for (int i=0; i<MAXEDGE; ++i) {
    new_pq->edges[i] = NULL;
  }
  new_pq->nedges = 0;
  new_pq->min_index = -1;

  return new_pq;
}


void add_edge(EdgePQ* pq, Edge* edge) {
  int added_index = pq->nedges;

  if (pq->nedges >= MAXEDGE) {
    printf("Maximum edges reached! better adjust the constant\n");
    exit(EXIT_FAILURE);
  }

  pq->edges[added_index] = edge;
  ++pq->nedges;

  if (pq->min_index == -1 || pq->edges[pq->min_index]->weight > edge->weight) {
    pq->min_index = added_index;
  }
}

Edge* min_edge(EdgePQ* pq) {
  // return edge from min_index
  Edge* result = pq->edges[pq->min_index];

  // reshuffle from that index
  for (int i=pq->min_index; i<pq->nedges-1; ++i) {
    pq->edges[i] = pq->edges[i+1];
    pq->edges[i+1] = NULL;
  }
  --pq->nedges;

  // reset the minimum edge
  pq->min_index = -1;
  for (int i=0; i<pq->nedges; ++i) {
    if (pq->min_index == -1) {
      pq->min_index = i;
    }

    if (pq->edges[pq->min_index]->weight > pq->edges[i]->weight) {
      pq->min_index = i;
    }
  }

  return result;
}

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
