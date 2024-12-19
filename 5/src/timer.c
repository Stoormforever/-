#include "timer.h"

ull tick(void)
{
    ull ticks;
	__asm__ __volatile__ ("rdtsc" : "=A" (ticks) );

    return ticks;
}

void fill_random_numbers(int *random_numbers, int max_size)
{
    for (int i = 0; i < max_size; i++)
        random_numbers[i] = rand() % 100;
}

float rand_time(int min, int max)
{
    return (max - min) * (float)(rand()) / (float)RAND_MAX + min;
}