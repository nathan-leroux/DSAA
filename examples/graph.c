#include "graph.h"

Graph* init_graph(bool directed) {
    Graph* g = malloc(sizeof(Graph));

    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for (int i=1; i<=MAXV; ++i) {
        g->degree[i] = 0;
    }

    for (int j=1; j<=MAXV; ++j) {
        g->edges[j] = NULL;
    }

    return g;
}


Search* init_search(void (*early)(int), void (*late)(int), void (*edge)(int, int)) {
    Search* s = malloc(sizeof(Search));

    memset(s->parent, 0 , sizeof(s->parent));
    memset(s->discovered, 0 , sizeof(s->discovered));
    memset(s->processed, 0 , sizeof(s->processed));
    memset(s->entry, 0 , sizeof(s->entry));
    memset(s->exit, 0 , sizeof(s->exit));

    s->process_early = early;
    s->process_late = late;
    s->process_edge = edge;

    return s;
}


void insert_edge(Graph* g, int x, int y, bool directed) {
    Edgenode* edge;

    edge = malloc(sizeof(Edgenode));

    
    edge->weight = 0;
    edge->y = y;

    edge->next = g->edges[x];
    g->edges[x] = edge;
    g->degree[x]++;

    // if undirected, add the same edge in the other direction
    if (!directed) {
        insert_edge(g, y, x, true);
    } else {
        g->nedges++;
    }
}


void print_graph(Graph* g) {
    Edgenode* edge;

    for (int i=1; i<=g->nvertices ; ++i) {
        printf("%d: ", i);
        edge = g->edges[i];

        while (edge != NULL) {
            printf(" %d", edge->y);
            edge = edge->next;
        }
        printf("\n");
    }
}

static void print_row(int col_space, int* array) {
    int digits;

    for (int i=1; i<MAXV; ++i) {
        if (array == NULL) {
            digits = printf("%d", i);
        }
        else {
            digits = printf("%d", array[i]);
        }
        for (int j=digits; j<col_space; ++j) {
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


void read_graph(char* filename, Graph* g, bool directed) {
    int edges_no;
    int x, y;
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

    for (int i=1; i<=edges_no; ++i) {
        ret = fscanf(fp, "%d %d", &x, &y);
        if (ret != 2) {
            printf("couldn't read edge %d\n", i);
            exit(EXIT_FAILURE);
        }

        insert_edge(g, x, y, false);
    }

    fclose(fp);
}


static void pass(int n) {
    
}


static void print_early(int n) {
    printf("%d: discovered\n", n);
}


static void print_edge(int x, int y) {
    printf("\tedge: %d %d\n", x, y);
}


void breadth_first_search(Graph* g, Search* s, int start) {
    int current_node;
    Queue* queue = queue_init();
    Edgenode* edge;

    s->discovered[start] = true;

    // using my queue implementation from before
    // implemented with char's
    // i guess as long as its not over 255 nodes this will work
    enqueue(queue, start);
    
    while (!queue_is_empty(queue)) {
        current_node = dequeue(queue);
        s->process_early(current_node);

        s->processed[current_node] = true;

        for (edge=g->edges[current_node]; edge != NULL; edge=edge->next) {
            if (!s->processed[edge->y] || g->directed) {
                s->process_edge(current_node, edge->y);
            }

            if (!s->discovered[edge->y]) {
                s->parent[edge->y] = current_node;
                s->discovered[edge->y] = true;
                enqueue(queue, edge->y);
            }
        }

        s->process_late(current_node);
    }
}


int depth_first_search(Graph* g, Search* s, int node, int time) {
    Edgenode* edge;

    ++time;
    s->entry[node] = time;

    s->discovered[node] = true;
    s->process_early(node);

    for (edge = g->edges[node]; edge != NULL; edge = edge->next) {
        if (s->discovered[edge->y]) {
            if ((!s->processed[edge->y] && (s->parent[node] != edge->y)) || g->directed) {
                s->process_edge(node, edge->y);
            }

            continue;
        }

        s->process_edge(node, edge->y);
        s->parent[edge->y] = node;
        time = depth_first_search(g, s, edge->y, time);
    }

    ++time;
    s->exit[node] = time;

    s->processed[node] = true;
    s->process_late(node);

    return time;
}


void example_graph(void) {

    Graph* g = init_graph(false);
    Search* s = init_search(&print_early, &pass, &print_edge);

    read_graph(GRAPH_FILE, g, false);

    print_graph(g);

    depth_first_search(g, s, 1, 0);

    print_search(s);
}
