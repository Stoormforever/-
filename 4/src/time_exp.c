#include <stdio.h>
#include "arr_stack.h"
#include "list_stack.h"
#include "errors.h"
#include "timer.h"

#define ITERATIONS 100

int main(void)
{
    int max_sizes[5] = {10, 20, 30, 40, 50};
    size_t time_push_array, time_pop_array;
    size_t time_push_list, time_pop_list;
    ull start, end;
    void **random_numbers;

    for (size_t k = 0; k < 5; k++)
    {
        arr_stack_t arr_stack = arr_stack_create();
        list_stack_t list_stack = list_stack_create();
        if (!arr_stack || !list_stack)
            return ALLOCATION_ERROR;

        random_numbers = malloc(max_sizes[k] * sizeof(int *));
        if (!random_numbers)
            return ALLOCATION_ERROR;

        fill_random_adresses(random_numbers, max_sizes[k]);

        time_push_array = 0;
        time_pop_array = 0;
        time_push_list = 0;
        time_pop_list = 0;

        for (size_t i = 0; i < ITERATIONS; i++)
        {
            start = tick();
            for (int j = 0; j < max_sizes[k]; j++)
                arr_stack_push(arr_stack, random_numbers[j]);
            end = tick();
            time_push_array += end - start;
            start = tick();
            for (int j = 0; j < max_sizes[k]; j++)
                arr_stack_pop(arr_stack);
            end = tick();
            time_pop_array += end - start;

            start = tick();
            for (int j = 0; j < max_sizes[k]; j++)
                list_stack_push(list_stack);
            end = tick();
            time_push_list += end - start;
            start = tick();
            for (int j = 0; j < max_sizes[k]; j++)
                list_stack_pop(list_stack, &random_numbers[j]);
            end = tick();
            time_pop_list += end - start;
        }

        free(random_numbers);
        arr_stack_destroy(arr_stack);
        list_stack_destroy(list_stack);

        time_push_array /= ITERATIONS;
        time_push_list /= ITERATIONS;
        time_pop_array /= ITERATIONS;
        time_pop_list /= ITERATIONS;

        printf("Времени (в тиках) портачено на %d элемент(а, ов)\n", max_sizes[k]);
        printf("Добавление в стек на основе массива: %lu\n", time_push_array);
        printf("Добавление в стек на основе списка: %lu\n", time_push_list);
        printf("Удаление из стека на основе массива: %lu\n", time_pop_array);
        printf("Удаление из стека на основе списка: %lu\n", time_pop_list);

        printf("Количество занимаемой памяти (в байтах) для %d элемент(а, ов)\n", max_sizes[k]);
        printf("Стеком на основе массива: %lu\n", arr_stack_get_size() + max_sizes[k] * sizeof(void *));
        printf("Стеком на основе списка: %lu\n\n", list_stack_get_size() + max_sizes[k] * node_get_size());
    }

    return ERR_OK;
}