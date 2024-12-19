#include "list_stack.h"

struct node
{
    void *address;
    struct node *next;
};

struct list_stack
{
    struct node *top;
};

list_stack_t list_stack_create(void)
{
    list_stack_t s = malloc(sizeof(struct list_stack));

    if (s)
        s->top = NULL;
    
    return s;
}

bool list_stack_is_empty(const list_stack_t s)
{
    return s->top == NULL;
}

int list_stack_push(list_stack_t s)
{
    struct node *node = malloc(sizeof(struct node));

    if (!node)
        return ALLOCATION_ERROR;
    
    node->next = s->top;
    node->address = node;
    s->top = node;

    return ERR_OK;
}

int list_stack_pop(list_stack_t s, void **elem)
{
    struct node *node;

    if (list_stack_is_empty(s))
        return EMPTY_STACK_ERROR;

    node = s->top;    
    *elem = node->address;
    s->top = node->next;  
    free(node);

    return ERR_OK;
}

void list_stack_make_empty(list_stack_t s)
{
    void *elem;

    while (!list_stack_is_empty(s))
        (void) list_stack_pop(s, &elem);
}

void list_stack_destroy(list_stack_t s)
{
    list_stack_make_empty(s);
    
    free(s);
}

void list_stack_print(const list_stack_t s)
{
    printf("Лист-стэк:\n");
    struct node *node = s->top;
    while (node != NULL)
    {
        printf("PS: %p elem: %p\n", (void*)node, node->address);
        node = node->next;
    }
}

size_t list_stack_get_size(void)
{
    return sizeof(struct list_stack);
}

size_t node_get_size(void)
{
    return sizeof(struct node);
}