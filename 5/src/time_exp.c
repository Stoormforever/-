#include <stdio.h>
#include "arr_queue.h"
#include "list_queue.h"
#include "errors.h"
#include "timer.h"

#define ITERATIONS 100

int main(void)
{
    int max_sizes[5] = {100, 200, 300, 400, 500};
    size_t time_push_array, time_pop_array;
    size_t time_push_list, time_pop_list;
    ull start, end;
    int *random_numbers;

    for (size_t k = 0; k < 5; k++)
    {
        arr_queue_t arr_queue = arr_queue_create();
        list_queue_t list_queue = list_queue_create();
        if (!arr_queue || !list_queue)
            return ALLOCATION_ERROR;

        random_numbers = malloc(max_sizes[k] * sizeof(int *));
        if (!random_numbers)
            return ALLOCATION_ERROR;

        fill_random_numbers(random_numbers, max_sizes[k]);

        time_push_array = 0;
        time_pop_array = 0;
        time_push_list = 0;
        time_pop_list = 0;

        for (size_t i = 0; i < ITERATIONS; i++)
        {
            start = tick();
            for (int j = 0; j < max_sizes[k]; j++)
                arr_queue_push(arr_queue, random_numbers[j]);
            end = tick();
            time_push_array += end - start;
            start = tick();
            for (int j = 0; j < max_sizes[k]; j++)
                arr_queue_pop(arr_queue);
            end = tick();
            time_pop_array += end - start;

            start = tick();
            for (int j = 0; j < max_sizes[k]; j++)
                list_queue_push(list_queue, random_numbers[j]);
            end = tick();
            time_push_list += end - start;
            start = tick();
            for (int j = 0; j < max_sizes[k]; j++)
                list_queue_pop(list_queue);
            end = tick();
            time_pop_list += end - start;
        }

        free(random_numbers);
        arr_queue_destroy(arr_queue);
        list_queue_destroy(list_queue);

        time_push_array /= ITERATIONS;
        time_push_list /= ITERATIONS;
        time_pop_array /= ITERATIONS;
        time_pop_list /= ITERATIONS;

        printf("Времени (в тиках) портачено на %d элемент(а, ов)\n", max_sizes[k]);
        printf("Добавление в очередь на основе массива: %lu\n", time_push_array);
        printf("Добавление в очередь на основе списка: %lu\n", time_push_list);
        printf("Удаление из очереди на основе массива: %lu\n", time_pop_array);
        printf("Удаление из очереди на основе списка: %lu\n", time_pop_list);

        printf("Количество занимаемой памяти (в байтах) для %d элемент(а, ов)\n", max_sizes[k]);
        printf("очередью на основе массива: %lu\n", arr_queue_get_size() + max_sizes[k] * sizeof(void *));
        printf("очередью на основе списка: %lu\n\n", list_queue_get_size() + max_sizes[k] * node_get_size());
    }

    return ERR_OK;
}