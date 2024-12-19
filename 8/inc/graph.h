#ifndef GRAPH__H
#define GRAPH__H

#include "matrix.h"

int create_graph(graph_t *graph);

void init_graph(graph_t *graph);
void free_graph(graph_t *graph);

void print_graph_matrix(graph_t graph);
void print_graph(graph_t *graph);
int is_connected(graph_t *graph);

#endif