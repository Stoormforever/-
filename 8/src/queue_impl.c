#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

node_t *create_node(int data) 
{
    node_t *node = malloc(sizeof(node_t));
    
    if (node)
    {
        node->data = data;
        node->next = NULL;
    }
    
    return node;
}

queue_t* push_back(queue_t *queue, node_t *node)
{
    if (!queue->head)
    {
        queue->head = node;
        queue->tail = node;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = queue->tail->next;
    }

    return queue;
}

queue_t* pop_front(queue_t *queue)
{
    node_t *temp = queue->head->next;

    free(queue->head);
    queue->head = temp;

    return queue;
}

void init_queue(queue_t *queue)
{
    queue->tail = NULL;
    queue->head = NULL;
}

void free_queue(queue_t *queue)
{
    while (queue->head)
    {
        node_t *temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }
}

void print_queue(queue_t queue)
{
    while (queue.head)
    {
        printf("%d ", queue.head->data);
        queue.head = queue.head->next;
    }
}