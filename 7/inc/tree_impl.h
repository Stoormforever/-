#ifndef TREE_IMPL_H
#define TREE_IMPL_H

#include "tree.h"
#include "tree_impl.h"
#include <stdio.h>

int create_tree(tree_node_t **root, FILE *f);

tree_node_t *create_node(char *word);

tree_node_t *tree_insert(tree_node_t *tree, tree_node_t *node);

void export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree);

tree_node_t *look_up(tree_node_t *tree, const char *word, int *count);

void free_tree_node(tree_node_t *node);

void tree_destroy(tree_node_t *tree);

tree_node_t *tree_delete(tree_node_t *tree, const char *word);

#endif