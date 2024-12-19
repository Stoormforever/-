#ifndef QUEUE_IMPL_H
#define QUEUE_IMPL_H

#include "queue.h"

node_t* create_node(int data);
queue_t* push_back(queue_t *queue, node_t *node);
queue_t* pop_front(queue_t *queue);

void init_queue(queue_t *queue);
void free_queue(queue_t *queue);
void print_queue(queue_t queue);

#endif