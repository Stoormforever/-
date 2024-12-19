#include "table.h"
#include "table_impl.h"
#include "table_impl2.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "errors.h"

int restructurise_closed_ht(closed_ht_t **table, size_t size)
{
    int rc = 0;
    closed_ht_t *old = *table;
    closed_ht_t *res = create_closed_ht(size);
    for (size_t i = 0; i < old->len; ++i)
    {
        if (old->arr[i])
        {
            int temp = add_element_closed_ht(res, old->arr[i]);
            rc = (rc > temp) ? rc : temp;
        }
    }
    destroy_closed_ht(old);
    *table = res;
    return rc;
}

closed_ht_t *create_closed_ht(size_t len)
{
    closed_ht_t *res = malloc(sizeof(closed_ht_t));
    if (res)
    {
        res->arr = calloc(len, sizeof(char *));
        res->len = len;
    }
    return res;
}

void destroy_closed_ht(closed_ht_t *table)
{
    if (!table)
    {
        return;
    }
    for (size_t i = 0; i < table->len; ++i)
    {
        free(table->arr[i]);
    }

    free(table->arr);
    free(table);
}

int add_element_closed_ht(closed_ht_t *table, char *val)
{
    size_t probing = 0;
    size_t elem_index = hash_function(val, table->len);
    while (table->arr[elem_index] != NULL)
    {
        ++probing;
        elem_index = (elem_index + 1) % table->len;
        if (probing > table->len)
        {
            return -1;
        }
    }
    char *ptmp = strdup(val);
    if (ptmp)
        table->arr[elem_index] = ptmp;
    return probing;
}

int read_table(closed_ht_t **table, FILE *f)
{
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

        add_element_closed_ht(*table, word);

        free(word);
        word = NULL;
        buff = 0;
    }

    free(word);

    return ERR_OK;
}

int find_elem_closed_ht_logcmp(closed_ht_t *table, char *val)
{
    int comprasions = 0;
    size_t elem_index = hash_function(val, table->len);
    void *head = table->arr[elem_index];
    while (head)
    {
        ++comprasions;
        if (!strcmp(head, val))
        {
            return comprasions;
        }
        head = table->arr[elem_index++ % table->len];
        if ((size_t)comprasions > table->len)
        {
            break;
        }
    }
    return -1;
}

void print_closed_ht(closed_ht_t *table)
{
    for (size_t i = 0; i < 100; ++i)
    {
        if (table->arr[i])
        {
            printf("[%-3lu] [hash: %-3ld]: %s\n", i, hash_function(table->arr[i], table->len), (char *)table->arr[i]);
        }
        else
        {
            printf("[%-3lu]\n", i);
        }
    }
}
