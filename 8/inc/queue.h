#ifndef QUEUE_H
#define QUEUE_H

typedef struct node node_t;

typedef struct queue queue_t;

struct node
{
    int data;
    struct node *next;
};

struct queue
{
    node_t *head;
    node_t *tail;
};


#endif