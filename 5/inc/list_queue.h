#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include <stdlib.h>
#include "errors.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct list_queue_t *list_queue_t;

typedef struct node_t *node_t;

bool list_queue_is_empty(list_queue_t queue);

int list_queue_push(list_queue_t queue, int val);

int list_queue_pop(list_queue_t queue, void **pout);

void list_queue_make_empty(list_queue_t queue);

void list_queue_print(const list_queue_t queue);


list_queue_t list_queue_create(void);

void list_queue_destroy(list_queue_t queue);


size_t list_queue_get_size(void);

size_t node_get_size(void);

#endif