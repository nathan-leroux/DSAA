#include "graph.h"

Graph* init_graph(bool directed) {
  Graph* g = malloc(sizeof(Graph));

  g->nvertices = 0;
  g->nedges = 0;
  g->directed = directed;

  for (int i = 1; i <= MAXV; ++i) {
    g->degree[i] = 0;
  }

  for (int j = 1; j <= MAXV; ++j) {
    g->edges[j] = NULL;
  }

  return g;
}

Search* init_search(void (*early)(int, Search*), void (*late)(int, Search*),
                    void (*edge)(int, int, Search*)) {
  Search* s = malloc(sizeof(Search));

  s->stack = stack_init();

  memset(s->parent, 0, sizeof(s->parent));
  memset(s->discovered, 0, sizeof(s->discovered));
  memset(s->processed, 0, sizeof(s->processed));
  memset(s->entry, 0, sizeof(s->entry));
  memset(s->exit, 0, sizeof(s->exit));

  s->process_early = early;
  s->process_late = late;
  s->process_edge = edge;

  return s;
}

void insert_edge(Graph* g, int x, int y, int weight, bool directed) {
  Edge* edge;

  edge = malloc(sizeof(Edge));

  edge->weight = weight;
  edge->x = x;
  edge->y = y;

  edge->next = g->edges[x];
  g->edges[x] = edge;
  g->degree[x]++;

  // if undirected, add the same edge in the other direction
  if (!directed) {
    insert_edge(g, y, x, weight, true);
  } else {
    g->nedges++;
  }
}

void print_graph(Graph* g) {
  Edge* edge;

  printf("Printing Graph\n");
  printf("vertex: connected_vertex(weight)\n");
  for (int i = 1; i <= g->nvertices; ++i) {
    printf("%d: ", i);
    edge = g->edges[i];

    while (edge != NULL) {
      printf(" %d(%d)", edge->y, edge->weight);
      edge = edge->next;
    }
    printf("\n");
  }
}

static void print_row(int col_space, int* array) {
  int digits;

  for (int i = 1; i < MAXV; ++i) {
    if (array == NULL) {
      digits = printf("%d", i);
    } else {
      digits = printf("%d", array[i]);
    }
    for (int j = digits; j < col_space; ++j) {
      printf(" ");
    }
  }
  printf("\n");
}

void print_search(Search* s) {
  int col_space = 3;

  printf("node\t");
  print_row(col_space, NULL);

  printf("parent\t");
  print_row(col_space, s->parent);

  printf("entry\t");
  print_row(col_space, s->entry);

  printf("exit\t");
  print_row(col_space, s->exit);
}

void read_graph(char* filename, Graph* g, bool weighted) {
  char* file_format;
  int file_args;
  int edges_no;
  int x, y;
  int weight = 1;
  int ret;

  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("couldn't open file %s\n", filename);
    exit(EXIT_FAILURE);
  }

  if (fscanf(fp, "vert=%d edge=%d", &(g->nvertices), &edges_no) != 2) {
    printf("couldn't read verts/edges\n");
    exit(EXIT_FAILURE);
  }

  if (weighted) {
    file_format = "%d %d %d";
    file_args = 3;
  } else {
    file_format = "%d %d";
    file_args = 2;
  }

  for (int i = 1; i <= edges_no; ++i) {
    ret = fscanf(fp, file_format, &x, &y, &weight);
    if (ret != file_args) {
      printf("couldn't read edge %d\n", i);
      exit(EXIT_FAILURE);
    }

    insert_edge(g, x, y, weight, g->directed);
  }

  fclose(fp);
}

enum Edge_t get_edge_type(int x, int y, Search* s) {
  if (s->parent[y] == x) {
    return TREE;
  }

  if (s->discovered[y] && !s->processed[y]) {
    return BACK;
  }

  if (s->processed[y] && (s->entry[y] > s->entry[x])) {
    return FORWARD;
  }

  if (s->processed[y] && (s->entry[y] < s->entry[x])) {
    return CROSS;
  }

  return -1;
}

EdgePQ* init_edge_pq(void) {
  EdgePQ* new_pq = malloc(sizeof(EdgePQ));

  for (int i = 0; i < MAXEDGE; ++i) {
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
  for (int i = pq->min_index; i < pq->nedges - 1; ++i) {
    pq->edges[i] = pq->edges[i + 1];
    pq->edges[i + 1] = NULL;
  }
  --pq->nedges;

  // reset the minimum edge
  pq->min_index = -1;
  for (int i = 0; i < pq->nedges; ++i) {
    if (pq->min_index == -1) {
      pq->min_index = i;
    }

    if (pq->edges[pq->min_index]->weight > pq->edges[i]->weight) {
      pq->min_index = i;
    }
  }

  return result;
}

static void pass(int n, Search* s) {}

static void topo_late(int x, Search* s) { push(s->stack, x); }

static void topo_edge(int x, int y, Search* s) {
  if (get_edge_type(x, y, s) == BACK) {
    printf("CYCLE FOUND, graph is not a DAG\n");
  }
}

void topo_sort(Graph* g, Search* s) {
  for (int i = 1; i <= g->nvertices; ++i) {
    if (!s->discovered[i]) {
      depth_first_search(g, s, i, 0);
    }
  }
}

static void print_early(int n, Search* s) {
  printf("%d: vertex discovered\n", n);
}

static void print_edge(int x, int y, Search* s) {
  printf("\t%d-%d: edge discovered\n", x, y);
}

void breadth_first_search(Graph* g, Search* s, int start) {
  int current_node;
  Queue* queue = queue_init();
  Edge* edge;

  s->discovered[start] = true;

  // using my queue implementation from before
  // implemented with char's
  // i guess as long as its not over 255 nodes this will work
  enqueue(queue, start);

  while (!queue_is_empty(queue)) {
    current_node = dequeue(queue);
    s->process_early(current_node, s);

    s->processed[current_node] = true;

    for (edge = g->edges[current_node]; edge != NULL; edge = edge->next) {
      if (!s->processed[edge->y] || g->directed) {
        s->process_edge(current_node, edge->y, s);
      }

      if (!s->discovered[edge->y]) {
        s->parent[edge->y] = current_node;
        s->discovered[edge->y] = true;
        enqueue(queue, edge->y);
      }
    }

    s->process_late(current_node, s);
  }
}

int depth_first_search(Graph* g, Search* s, int node, int time) {
  Edge* edge;

  ++time;
  s->entry[node] = time;

  s->discovered[node] = true;
  s->process_early(node, s);

  for (edge = g->edges[node]; edge != NULL; edge = edge->next) {
    if (s->discovered[edge->y]) {
      if ((!s->processed[edge->y] && (s->parent[node] != edge->y)) ||
          g->directed) {
        s->process_edge(node, edge->y, s);
      }

      continue;
    }

    s->process_edge(node, edge->y, s);
    s->parent[edge->y] = node;
    time = depth_first_search(g, s, edge->y, time);
  }

  ++time;
  s->exit[node] = time;

  s->processed[node] = true;
  s->process_late(node, s);

  return time;
}

void example_graph(void) {
  Graph* topo_g = init_graph(true);

  Search* topo_s = init_search(&pass, &topo_late, &topo_edge);

  printf("## Unweighted Graphs\n");
  printf("graph for BFS and DFS can be found pg214 in textbook\n");
  printf("directed graph for topo sort can be found pg231\n\n");

  printf("Breadth First Search\n");
  Graph* breadth_g = init_graph(false);
  Search* breadth_s = init_search(&print_early, &pass, &print_edge);
  read_graph(GRAPH_FILE, breadth_g, false);
  breadth_first_search(breadth_g, breadth_s, 1);

  printf("\n");
  printf("Depth First Search\n");
  Graph* depth_g = init_graph(false);
  Search* depth_s = init_search(&print_early, &pass, &print_edge);
  read_graph(GRAPH_FILE, depth_g, false);
  depth_first_search(depth_g, depth_s, 1, 0);

  printf("\n");
  printf("Topological Sort\n");
  read_graph(GRAPH_FILE, topo_g, false);
  topo_sort(topo_g, topo_s);
  stack_print(topo_s->stack);
}
