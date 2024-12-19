#include "timer.h"

ull tick(void)
{
    ull ticks;
	__asm__ __volatile__ ("rdtsc" : "=A" (ticks) );

    return ticks;
}

void fill_random_adresses(void **random_adresses, int max_size)
{
    for (int i = 0; i < max_size; i++)
    {
        int tmp = rand() % 100;
        random_adresses[i] = (void *) &tmp;
    }
}
