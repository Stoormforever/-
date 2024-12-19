#include "arr_stack.h"

struct arr_stack
{
    void *arr[MAX_STACK_LEN];
    int top;
};

arr_stack_t arr_stack_create(void)
{
    arr_stack_t s = malloc(sizeof(struct arr_stack));

    if (s)
        arr_stack_make_empty(s);

    return s;
}

void arr_stack_make_empty(arr_stack_t s)
{
    s->top = -1;
}

void arr_stack_destroy(arr_stack_t s)
{
    free(s);
}

bool arr_stack_is_full(const arr_stack_t s)
{
    return s->top == MAX_STACK_LEN;
}

bool arr_stack_is_empty(const arr_stack_t s)
{
    return s->top == -1;
}

int arr_stack_push(arr_stack_t s, void *elem)
{
    s->top++;
    if (arr_stack_is_full(s))
        return STACK_OVERFLOW;
    s->arr[s->top] = elem;

    return ERR_OK;
}

int arr_stack_pop(arr_stack_t s)
{
    if (arr_stack_is_empty(s))
        return EMPTY_STACK_ERROR;
    
    s->top--;

    return ERR_OK;
}

void arr_stack_print(const arr_stack_t s)
{
    printf("Mассив-стек: \n");
    for (int i = s->top; i > -1; i--)
        printf("PS: %p, elem: %p\n", (void*)&s->arr[i], s->arr[i]);
}

size_t arr_stack_get_size(void)
{
    return sizeof(struct arr_stack);
}