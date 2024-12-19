#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <time.h>
#include <stdlib.h>

typedef unsigned long long ull;

void fill_random_adresses(void **random_adresses, int max_size);

ull tick(void);

#endif