#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "timer.h"

#define ITERATIONS 100

int main(void)
{
    int max_sizes[5] = {10, 20, 30, 40, 50};
    tree_node_t *tree;
    size_t time_match_tree;
    size_t time_match_file;
    ull start, end;
    char fname[20];

    for (size_t k = 0; k < 5; k++)
    {
        sprintf(fname, "./exp/%d.txt", max_sizes[k]);
        FILE *f = fopen(fname, "r");

        time_match_tree = 0;
        time_match_file = 0;
        int count = 0;

        tree = NULL;
        create_tree(&tree, f);

        for (size_t i = 0; i < ITERATIONS; i++)
        {
            start = tick();
            tree_match(tree, 'b', &count);
            end = tick();
            time_match_tree += end - start;
            start = tick();
            file_match(f, 'b', &count);
            end = tick();
            time_match_file += end - start;
            rewind(f);
        }

        fclose(f);

        tree_destroy(tree);

        time_match_tree /= ITERATIONS;
        time_match_file /= ITERATIONS;

        printf("Времени (в тиках) портачено на %d элемент(а, ов)\n", max_sizes[k]);
        printf("Поиск по начальной букве в дереве: %lu\n", time_match_tree);
        printf("Поиск по начальной букве в файле: %lu\n", time_match_file);
    }

    return 0;
}