#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

typedef struct list_stack* list_stack_t;

bool list_stack_is_empty(const list_stack_t s);

int list_stack_push(list_stack_t s);

int list_stack_pop(list_stack_t s, void **elem);

void list_stack_make_empty(list_stack_t s);

void list_stack_print(const list_stack_t s);


void list_stack_destroy(list_stack_t s);

list_stack_t list_stack_create(void);


size_t list_stack_get_size(void);

size_t node_get_size(void);

#endif