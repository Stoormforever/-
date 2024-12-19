#include "timer.h"

ull tick(void)
{
    ull ticks;
	__asm__ __volatile__ ("rdtsc" : "=A" (ticks) );

    return ticks;
}