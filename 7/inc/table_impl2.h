#ifndef ___CLOSED_HASH___
#define ___CLOSED_HASH___

#include "table.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

unsigned long hash_function(char *str, int size);

int restructurise_closed_ht(closed_ht_t **table, size_t new_len);

closed_ht_t *create_closed_ht(size_t len);

int read_table(closed_ht_t **table, FILE *f);

void destroy_closed_ht(closed_ht_t *table);

int add_element_closed_ht(closed_ht_t *table, char *val);

int find_elem_closed_ht_logcmp(closed_ht_t *table, char *val);

void print_closed_ht(closed_ht_t *table);

#endif