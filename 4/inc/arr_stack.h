#ifndef ARR_STACK_H
#define ARR_STACK_H

#include <stdbool.h>
#include <stdio.h>
#include "stdlib.h"
#include "errors.h"

#define MAX_STACK_LEN 50

typedef struct arr_stack* arr_stack_t;

void arr_stack_make_empty(arr_stack_t s);

bool arr_stack_is_empty(const arr_stack_t s);

bool arr_stack_is_full(const arr_stack_t s);

int arr_stack_push(arr_stack_t s, void *elem);

int arr_stack_pop(arr_stack_t s);

void arr_stack_print(const arr_stack_t s);


arr_stack_t arr_stack_create(void);

void arr_stack_destroy(arr_stack_t s);


size_t arr_stack_get_size(void);

#endif