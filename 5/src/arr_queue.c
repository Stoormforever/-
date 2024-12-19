#include "arr_queue.h"

#define MAX_ARR_LEN 1000

struct arr_queue_t
{
    int queries[MAX_ARR_LEN];
    int *pin;
    int *pout;
    size_t arr_len;
};

arr_queue_t arr_queue_create(void)
{
    arr_queue_t parr = malloc(sizeof(struct arr_queue_t));

    arr_queue_make_empty(parr);

    return parr;
}

void arr_queue_make_empty(arr_queue_t queue)
{
    queue->pin = queue->queries;
    queue->pout = queue->queries;
}

bool arr_queue_is_empty(arr_queue_t queue)
{
    return queue->pin == queue->pout;
}

int arr_queue_push(arr_queue_t queue, int val)
{
    if (queue->pout == queue->pin && queue->arr_len == MAX_ARR_LEN)
        return QUEUE_OVERFLOW;
    if (queue->pin == &(queue->queries[MAX_ARR_LEN]))
        queue->pin = queue->queries;
    *(queue->pin) = val;
    queue->pin++;
    queue->arr_len++;

    return ERR_OK;
}

int arr_queue_pop(arr_queue_t queue)
{
    if (queue->pout == queue->pin && queue->arr_len == 0)
        return EMPTY_QUEUE_ERROR;
    if (queue->pout == &(queue->queries[MAX_ARR_LEN]))
        queue->pout = queue->queries;
    
    queue->pout++;
    queue->arr_len--;

    return ERR_OK;
}

void arr_queue_destroy(arr_queue_t queue)
{
    free(queue);
}

void arr_queue_print(const arr_queue_t queue)
{
    printf("Mассив-очередь: \n");
    for (int *pq = queue->pout; pq != queue->pin; pq++)
        printf("PQ: %p, elem: %d\n", (void*)pq, *pq);
}

size_t arr_queue_get_size(void)
{
    return sizeof(struct arr_queue_t);
}