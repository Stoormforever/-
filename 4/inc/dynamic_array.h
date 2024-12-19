#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "errors.h"
#include <stdio.h>
#include "stdlib.h"

typedef struct dyn_array_t* address_arr_t;

address_arr_t init_da_array(void);

int da_append(address_arr_t parr, int *elem);

void da_make_empty(address_arr_t parr);

void da_destroy(address_arr_t parr);

void da_print(const address_arr_t parr);

#endif