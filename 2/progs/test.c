#include "apartments.h"
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

long long unsigned milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;
    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    apartment_t apartments[ARR_LEN];
    size_t arr_len = 0;
    key_t keys[ARR_LEN];
    long long unsigned beg, end;

    create_table(f, apartments, &arr_len, keys);
    fclose(f);

    if (!strcmp(argv[2], "key"))
    {
        if (!strcmp(argv[3], "s"))
        {
            beg = milliseconds_now();
            my_sort_keys(keys, arr_len);
            end = milliseconds_now();
            printf("%llu\n", end - beg);
        }
        if (!strcmp(argv[3], "q"))
        {
            beg = milliseconds_now();
            qsort(keys, arr_len, sizeof(key_t), apartment_key_cmp);
            end = milliseconds_now();
            printf("%llu\n", end - beg);
        }
    }
    if (!strcmp(argv[2], "main"))
    {
        if (!strcmp(argv[3], "s"))
        {
            beg = milliseconds_now();
            my_sort(apartments, arr_len);
            end = milliseconds_now();
            printf("%llu\n", end - beg);
        }
        if (!strcmp(argv[3], "q"))
        {
            beg = milliseconds_now();
            qsort(apartments, arr_len, sizeof(apartment_t), apartment_cmp);
            end = milliseconds_now();
            printf("%llu\n", end - beg);
        }
    }

    return 0;
}