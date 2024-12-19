#ifndef ARR_QUEUE_H
#define ARR_QUEUE_H

#include <stdlib.h>
#include "errors.h"
#include "stdbool.h"
#include <stdio.h>

typedef struct arr_queue_t *arr_queue_t;


bool arr_queue_is_empty(arr_queue_t queue);

void arr_queue_make_empty(arr_queue_t queue);

int arr_queue_push(arr_queue_t queue, int val);

int arr_queue_pop(arr_queue_t queue);

void arr_queue_print(const arr_queue_t queue);


arr_queue_t arr_queue_create(void);

void arr_queue_destroy(arr_queue_t queue);


size_t arr_queue_get_size(void);

#endif