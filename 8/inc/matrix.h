#ifndef MATRIX_H
#define MATRIX_H

typedef struct graph graph_t;

struct graph
{
    int size;

    int** matrix;
    int** transpos_matrix;
};

#endif