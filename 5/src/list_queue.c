#include "list_queue.h"

struct node_t
{
    int query;
    struct node_t *next;
};

struct list_queue_t
{
    struct node_t *pout;
    struct node_t *pin;
};

list_queue_t list_queue_create(void)
{
    list_queue_t plist = malloc(sizeof(struct list_queue_t));

    if (plist)
    {
        plist->pin = NULL;
        plist->pout = NULL;
    }

    return plist;
}

bool list_queue_is_empty(list_queue_t queue)
{
    return queue->pout == NULL;
}

int list_queue_push(list_queue_t queue, int val)
{
    struct node_t *node = malloc(sizeof(struct node_t));
    if (!node)
        return ALLOCATION_ERROR;

    node->query = val;
    node->next = NULL;
    
    if (list_queue_is_empty(queue))
    {
        queue->pout = node;
        queue->pin = node;
    }
    else
    {
        struct node_t *tmp;
        tmp = queue->pin;
        tmp->next = node;
        queue->pin = node;
    }

    return ERR_OK;
}

int list_queue_pop(list_queue_t queue, void **pout)
{
    if (queue->pout == NULL)
        return EMPTY_QUEUE_ERROR;
    
    struct node_t *node = queue->pout;
    queue->pout = node->next;
    free(node);
    *pout = (void *)node;

    return ERR_OK;
}

void list_queue_destroy(list_queue_t queue)
{
    void* pout;

    while (queue->pout != NULL)
        list_queue_pop(queue, &pout);

    free(queue);
}

void list_queue_make_empty(list_queue_t queue)
{
    void *pout;

    while (queue->pout != NULL)
        list_queue_pop(queue, &pout);
}

void list_queue_print(const list_queue_t queue)
{
    if (list_queue_is_empty(queue))
        printf("Очередь пуста\n");
    else
    {
        printf("Лист-очередь:\n");
        struct node_t *node = queue->pout;
        while (node != NULL)
        {
            printf("PQ: %p elem: %d\n", (void*)node, node->query);
            node = node->next;
        }
    }
}

size_t list_queue_get_size(void)
{
    return sizeof(struct list_queue_t);
}

size_t node_get_size(void)
{
    return sizeof(struct node_t);
}