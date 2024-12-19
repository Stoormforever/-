#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include<stdlib.h>
#include<time.h>

typedef unsigned long long ull;

ull tick(void);

void fill_random_numbers(int *random_numbers, int max_size);

float rand_time(int min, int max);

#endif