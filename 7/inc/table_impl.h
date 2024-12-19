#ifndef TABLE_IMPL_H
#define TABLE_IMPL_H

#include "table.h"
#include "table_impl.h"

void free_table(hash_table_t *table);

hash_table_t *create_table(int size);

int table_insert(hash_table_t *table, hash_item_t *item);

int fill_table(hash_table_t **table, FILE *f);

char *table_search(hash_table_t *table, char *key, int *count);

void print_table(hash_table_t* table);

#endif