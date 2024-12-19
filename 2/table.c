#include <stdio.h>
#define ARR_LEN 5

int main (int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    int sizes[ARR_LEN] = {100, 200, 500, 1000, 2000};
    double avg_main[ARR_LEN], avg_key[ARR_LEN];

    for (size_t i = 0; i < ARR_LEN; i++)
        fscanf(f, "%lf\n", &avg_main[i]);
    for (size_t i = 0; i < ARR_LEN; i++)
        fscanf(f, "%lf\n", &avg_key[i]);
    fclose(f);

    printf("----------------------------------------------\n");
    printf("|кол-во|по таблице (мс)|по ключам (мс)|оценка|\n");
    printf("----------------------------------------------\n");
    for (size_t i = 0; i < ARR_LEN; i++)
    {
        double res = (avg_main[i] - avg_key[i]) / avg_key[i] * 100;
        printf("|%6d|%15.3lf|%14.3lf|%6.0lf|\n", sizes[i], avg_main[i], avg_key[i], res);
    }
    printf("----------------------------------------------\n");

    return 0;
}