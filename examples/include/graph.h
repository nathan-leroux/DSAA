#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

#define MAXV 10
#define MAXEDGE 30
#define MAXWEIGHT 1000
#define GRAPH_FILE "dag.txt"
#define W_GRAPH_FILE "weighted.txt"

enum Edge_t {
  TREE,
  BACK,
  FORWARD,
  CROSS,
};

typedef struct Edge {
  int x;
  int y;
  int weight;
  struct Edge* next;
} Edge;

typedef struct {
  Edge* edges[MAXEDGE];
  int nedges;
  int min_index;
} EdgePQ;

typedef struct {
  Edge* edges[MAXV + 1];
  int degree[MAXV + 1];
  int nvertices;
  int nedges;
  int directed;
} Graph;

typedef struct Search {
  bool discovered[MAXV + 1];
  bool processed[MAXV + 1];
  int parent[MAXV + 1];
  int entry[MAXV + 1];
  int exit[MAXV + 1];
  Stack* stack;
  void (*process_early)(int, struct Search*);
  void (*process_late)(int, struct Search*);
  void (*process_edge)(int, int, struct Search*);
} Search;

Search* init_search(void(int, Search*), void(int, Search*),
                    void(int, int, Search*));
Graph* init_graph(bool directed);
void insert_edge(Graph*, int, int, int, bool);
void read_graph(char*, Graph*, bool);
void print_graph(Graph* g);

EdgePQ* init_edge_pq(void);
void add_edge(EdgePQ* pq, Edge* edge);
Edge* min_edge(EdgePQ* pq);

void breadth_first_search(Graph*, Search*, int);
int depth_first_search(Graph*, Search*, int, int);

void example_graph(void);

#endif
