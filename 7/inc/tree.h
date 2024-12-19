#ifndef TREE_H
#define TREE_H

#include <stdio.h>

#define _GNU_SOURCE

typedef struct tree_node tree_node_t;

struct tree_node
{
    char *word;
    struct tree_node *left;
    struct tree_node *right;
};

#endif
