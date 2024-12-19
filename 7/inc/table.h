#ifndef ASSOSIATIVE_ARRAY_H
#define ASSOSIATIVE_ARRAY_H

#define _GNU_SOURCE

#include <stdio.h>

typedef struct hash_item hash_item_t;

typedef struct hash_table hash_table_t;

typedef struct node node_t;

struct node
{
    hash_item_t* item;
    node_t* next;
};

struct hash_item
{
    char *key;
    char *value;
};

struct hash_table
{
    hash_item_t **items;
    node_t **overflow_lists;
    int size;
    int cur_size;
};

typedef struct closed_ht_type closed_ht_t;

struct closed_ht_type
{
    char **arr; 
    size_t len;
};

#endif
