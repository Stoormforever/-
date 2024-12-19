#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "table.h"
#include "tree_impl.h"
#include "table_impl.h"
#include "table_impl2.h"
#include "avl_tree.h"
#include "timer.h"

#define COMPARES 5
#define ITERATIONS 100

int main(void)
{
    int max_sizes[5] = {1000, 2000, 3000, 4000, 5000};

    tree_node_t *tree = NULL;
    tree_node_t *avl_tree = NULL;
    hash_table_t *table = NULL;
    closed_ht_t *table2 = NULL;

    size_t time_find_tree;
    size_t time_find_avl;
    size_t time_find_table_1;
    size_t time_find_table_2;

    ull start, end;
    char fname[20];

    for (int k = 0; k < 5; k++)
    {
        sprintf(fname, "./exp/%d.txt", max_sizes[k]);
        FILE *f = fopen(fname, "r");
        table = create_table(max_sizes[k]);
        table2 = create_closed_ht(max_sizes[k]);

        time_find_tree = 0;
        time_find_avl = 0;
        time_find_table_1 = 0;
        time_find_table_2 = 0;
        int count_1 = 0;
        int count_2 = 0;
        int count_3 = 0;
        int count_4 = 0;

        tree = NULL;
        create_tree(&tree, f);
        rewind(f);
        fill_table(&table, f);
        rewind(f);
        read_table(&table2, f);
        

        for (size_t i = 0; i < ITERATIONS; i++)
        {
            start = tick();
            look_up(tree, "zuxxox", &count_4);
            end = tick();
            time_find_tree += end - start;
            avl_tree = tree_balance(tree);
            start = tick();
            look_up(avl_tree, "zuxxox", &count_3);
            end = tick();
            time_find_avl += end - start;
            start = tick();
            table_search(table, "zuxxox", &count_1);
            end = tick();
            time_find_table_1 += end - start;
            start = tick();
            count_2 = find_elem_closed_ht_logcmp(table2, "zuxxox");
            if (count_2 > COMPARES)
            {
                restructurise_closed_ht(&table2, table2->len + 100);
                start = tick();
            }
            end = tick();
            time_find_table_2 += end - start;

            rewind(f);
        }

        fclose(f);

        tree_destroy(tree);
        free_table(table);
        destroy_closed_ht(table2);

        time_find_tree /= ITERATIONS;
        time_find_avl /= ITERATIONS;
        time_find_table_1 /= ITERATIONS;

        printf("Времени (в тиках) портачено на %d элемент(а, ов)\n", max_sizes[k]);
        printf("Поиск в дереве:                 %lu\n", time_find_tree);
        printf("Поиск в сбалансированом дереве: %lu\n", time_find_avl);
        printf("Поиск в 1 таблице:                %lu| %d\n", time_find_table_1, count_1);
        printf("Поиск в 2 таблице:                %lu| %d\n", time_find_table_2, count_2);
    }

    return 0;
}