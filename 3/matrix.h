#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

typedef enum BOOLEAN{false = 0, true} bool;

typedef struct node
{
    int start_column_ind;
    struct node *next_element;
} node_t;

typedef struct list
{
    struct node *ptr;
} list_t;

typedef struct
{
    int xsize, ysize;
    int size;
    int *AN;
    int *JA;
    list_t IA;
} matrix_t;

typedef struct 
{
    int xsize, ysize;
    int **matrix;
} std_matrix_t;

#endif
