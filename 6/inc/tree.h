#ifndef TREE_H
#define TREE_H

#include <stdio.h>

#define _GNU_SOURCE

#define MAX_WORD_LEN 20

struct tree_node
{
    char *word;
    struct tree_node *left;
    struct tree_node *right;
};

typedef struct tree_node tree_node_t;

int create_tree(tree_node_t **root, FILE *f);

tree_node_t *create_node(char *word);

tree_node_t *tree_insert(tree_node_t *tree, tree_node_t *node);

void export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree, char letter);

tree_node_t *look_up(tree_node_t *tree, const char *word);

void tree_match(tree_node_t *tree, char letter, int *count);

void file_match(FILE *f, char letter, int *count);

tree_node_t *tree_delete(tree_node_t *tree, const char *word);

void free_tree_node(tree_node_t *node);

void tree_destroy(tree_node_t *tree);

#endif