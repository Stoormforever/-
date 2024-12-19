#ifndef APARTMENTS_H
#define APARTMENTS_H

#include <stdio.h>
#include <string.h>
#define ARR_LEN 2000
#define ADDRESS_LEN 20
#define BUILD_TIME_LEN 20

typedef struct
{
    char build_time[BUILD_TIME_LEN + 2];
    int last_residents_num;
    int animals;
}
second_t;

typedef union
{
    int facing;
    second_t second;
}
kind_t;

typedef struct
{
    char address[ADDRESS_LEN];
    int total_area;
    int rooms_num;
    int cost;
    int choice;
    kind_t kind;
}
apartment_t;

typedef struct 
{
    size_t src_ind;
    char key[ADDRESS_LEN];
}key_t;


int create_table(FILE *f, apartment_t *apartments, size_t *arr_len, key_t *keys);
int add_apartment(apartment_t *apartment);
void delete_apartment(apartment_t *apartments, size_t *arr_len, int rooms_num);
void match_apartments(const apartment_t *apartments, size_t arr_len, int cost1, int cost2);
int apartment_key_cmp(const void *arg1, const void *arg2);
int apartment_cmp(const void *arg1, const void *arg2);
void my_sort_keys(key_t *keys, size_t arr_len);
void my_sort(apartment_t *apartments, size_t arr_len);
void update_index(key_t *keys, size_t arr_len);
void write_apartments(const apartment_t *apartments, size_t arr_len);
void write_apartments_by_keys(const apartment_t *apartments, key_t *keys, size_t arr_len);

#endif