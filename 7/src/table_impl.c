#include "table.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned long hash_function(char *str, int size)
{
    unsigned long index = 0;
    for (size_t j = 0; str[j]; j++)
        index += str[j];
    return index % size;
}

hash_item_t *create_item(char *key, char* value)
{
    hash_item_t *item = malloc(sizeof(struct hash_item));

    if (item)
    {
        char *ptmp1 = strdup(key);
        if (ptmp1)
            item->key = ptmp1;
        else
        {
            free(item);
            return NULL;
        }

        char *ptmp2 = strdup(value);
        if (ptmp2)
            item->value = ptmp2;
        else
        {
            free(item->key);
            free(item);
            return NULL;
        }
    }

    return item;
}

int list_add_end(node_t **head, hash_item_t *item)
{
    node_t *list = malloc(sizeof(struct node));

    if (!list)
        return ALLOCATION_ERROR;

    list->item = item;
    list->next = NULL;

    if (*head != NULL)
    {
        node_t *cur = *head;

        for (; cur->next; cur = cur->next);

        cur->next = list;
    }
    else
        *head = list;

    return ERR_OK;
}

void list_destroy(node_t *head)
{
    node_t *node;

    for (; head; head = node)
    {
        node = head->next;
        free(head->item->key);
        free(head->item->value);
        free(head->item);
        free(head);
    }
}

void free_item(hash_item_t *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void free_table_items(hash_table_t *table)
{
    for (int i = 0; i < table->size; i++)
        if (table->items[i])
            free_item(table->items[i]);

    free(table->items);
}

void free_table_lists(hash_table_t *table)
{
    for (int i = 0; i < table->size; i++)
        list_destroy(table->overflow_lists[i]);

    free(table->overflow_lists);
}

void free_table(hash_table_t *table)
{
    if (table)
    {
        free_table_items(table);
        free_table_lists(table);
    }

    free(table);
}

hash_table_t *create_table(int size)
{
    hash_table_t *table = malloc(sizeof(struct hash_table));

    if (table)
    {
        table->size = size;
        table->cur_size = 0;

        table->items = malloc(table->size * sizeof(struct hash_item*));

        if (!table->items)
        {
            free(table);
            return NULL;
        }

        for (int i = 0; i < size; i++)
            table->items[i] = NULL;

        table->overflow_lists = malloc(table->size * sizeof(node_t*));

        if (!table->overflow_lists)
        {
            free(table->items);
            free(table);
            return NULL;
        }

        for (int i = 0; i < table->size; i++)
            table->overflow_lists[i] = NULL;
    }

    return table;
}

void handle_collision(hash_table_t *table, unsigned long index, hash_item_t *item)
{
    node_t* head = table->overflow_lists[index];

    if (list_add_end(&head, item))
        return;

    table->overflow_lists[index] = head;
}

int table_insert(hash_table_t *table, hash_item_t *item)
{
    unsigned long index = hash_function(item->key, table->size);

    if (!table->items[index])
    {
        if (table->cur_size == table->size)
        {
            free_table(table);
            return OVERFLOW_ERROR;
        }
        table->items[index] = item;
        table->cur_size++;
    }
    else
    {
        handle_collision(table, index, item);
    }

    return ERR_OK;
}

int fill_table(hash_table_t **table, FILE *f)
{
    hash_item_t *item;
    char *word = NULL;
    size_t buff = 0;
    int word_len;

    while((word_len = getline(&word, &buff, f)) != -1)
    {
        if (word[word_len - 1] == '\n')
        {
            word[word_len - 1] = '\0';
            word_len--;
        }
        else if (word_len == 0)
        {
            free(word);
            printf("Ошибка чтения файла");
            return READ_ERROR;
        }
        else
        {
            free(word);
            printf("Ошибка чтения файла");
            return READ_ERROR;
        }

        item = create_item(word, word);
        if (!item)
        {
            free(word);
            printf("Ошибка выделения памяти");
            return ALLOCATION_ERROR;
        }
        if (table_insert(*table, item))
        {
            return OVERFLOW_ERROR;
            printf("Таблица переполнена");
        }

        free(word);
        word = NULL;
        buff = 0;
    }

    free(word);

    return ERR_OK;
}

char *table_search(hash_table_t *table, char *key, int *count)
{
    unsigned long index = hash_function(key, table->size);
    hash_item_t *item = table->items[index];
    node_t *head = table->overflow_lists[index];

    while (item != NULL)
    {
        if (!strcmp(item->key, key))
            return item->value;

        if (!head)
            return NULL;

        item = head->item;
        head = head->next;
        (*count)++;
    }

    return NULL;
}

void print_table(hash_table_t* table)
{
    printf("\n-------------------\n");
    for (int i=0; i < table->size; i++)
    {
        if (table->items[i])
        {
            printf("Индекс:%d, Значение:%s", i, table->items[i]->value);
            if (table->overflow_lists[i])
            {
                printf(" => Список коллизий => ");
                node_t *head = table->overflow_lists[i];
                while (head)
                {
                    printf("Значение:%s ", head->item->value);
                    head = head->next;
                }
            }
            printf("\n");
        }
    }
    printf("-------------------\n");
}
