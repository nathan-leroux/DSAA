#include "dijkstras.h"

Graph* dijkstras(Graph* g, int start, int end) {
  Graph* shortest_path = init_graph(false);
  shortest_path->nvertices = g->nvertices;
  Queue* q = queue_init();
  Edge* e;
  int current;
  int dist[MAXV];
  Edge* prev[MAXV];

  for (int i = 1; i <= g->nvertices; ++i) {
    dist[i] = MAXINT;
    prev[i] = NULL;
  }

  dist[start] = 0;
  enqueue(q, start);

  while (!queue_is_empty(q)) {
    current = dequeue(q);

    for (Edge* e = g->edges[current]; e != NULL; e = e->next) {
      if (dist[e->y] == MAXINT) {
        enqueue(q, e->y);
      }

      if (dist[e->y] > dist[current] + e->weight) {
        dist[e->y] = dist[current] + e->weight;
        prev[e->y] = e;
      }
    }
  }

  current = end;
  for (e = prev[current]; e != NULL; e = prev[e->x]) {
    insert_edge(shortest_path, e->x, e->y, e->weight, false);
  }

  return shortest_path;
}
