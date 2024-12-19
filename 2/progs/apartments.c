#include "apartments.h"
#define READ_ERROR 1
#define VALUE_ERROR 2
#define DATA_OVERFLOW 3
#define INPUT_ERROR 4

int read_apartment(FILE *f, apartment_t *apartment)
{
    char address[ADDRESS_LEN + 2];
    int total_area;
    int rooms_num;
    int cost;
    int choice;

    char build_time[BUILD_TIME_LEN + 2];
    int last_residents_num;
    int animals;
    int facing;
    
    if (fscanf(f, "%s\n%d\n%d\n%d\n%d\n", address, &total_area, &rooms_num, &cost, &choice) != 5)
        return READ_ERROR;
    if (total_area <= 0 || rooms_num <= 0 || cost <= 0)
        return VALUE_ERROR;
    if (choice == 1)
    {
        if (!fscanf(f, "%d\n", &facing))
            return READ_ERROR;
        if (facing != 0 && facing != 1)
            return VALUE_ERROR;
    }
    else if (choice == 2)
    {
        if (!fscanf(f, "%s\n", build_time))
            return READ_ERROR;
        if (!fscanf(f, "%d\n", &last_residents_num))
            return READ_ERROR;
        if (last_residents_num < 0)
            return VALUE_ERROR;
        if (!fscanf(f, "%d\n", &animals))
            return READ_ERROR;
        if (animals != 0 && animals != 1)
            return VALUE_ERROR;
    }
    else
        return VALUE_ERROR;
    
    strcpy(apartment->address, address);
    apartment->total_area = total_area;
    apartment->rooms_num = rooms_num;
    apartment->cost = cost;
    apartment->choice = choice;
    if (choice == 1)
        apartment->kind.facing = facing;
    else
    {
        strcpy(apartment->kind.second.build_time, build_time);
        apartment->kind.second.last_residents_num = last_residents_num;
        apartment->kind.second.animals = animals;
    }

    return 0;
}

int create_table(FILE *f, apartment_t *apartments, size_t *arr_len, key_t *keys)
{
    apartment_t apartment;
    int rc = 0;
    *arr_len = 0;

    while(!rc)
    {
        rc = read_apartment(f, &apartment);
        if (!rc)
        {
            if (*arr_len < ARR_LEN)
            {
                apartments[*arr_len] = apartment;
                keys[*arr_len].src_ind = *arr_len;
                strcpy(keys[*arr_len].key, apartments[*arr_len].address);
                (*arr_len)++;
            }
            else
            {
                return DATA_OVERFLOW;
            }
        }
    }

    if (*arr_len && feof(f))
        rc = 0;

    return rc;
}

int add_apartment(apartment_t *apartment)
{
    char address[ADDRESS_LEN + 2];
    int total_area;
    int rooms_num;
    int cost;
    int choice;

    char build_time[BUILD_TIME_LEN + 2];
    int last_residents_num;
    int animals;
    int facing;

    printf("Введите адрес квартры (если содержит пробел введите _): \n");
    if (scanf("%s", address) != 1)
    {
        printf("Не верный ввод\n");
        return INPUT_ERROR;
    }
    printf("Введите общую площадь(м^2): \n");
    if (scanf("%d", &total_area) != 1)
    {
        printf("Не верный ввод\n");
        return INPUT_ERROR;
    }
    printf("Введите кол-во комнат: \n");
    if (scanf("%d", &rooms_num) != 1)
    {
        printf("Не верный ввод\n");
        return INPUT_ERROR;
    }
    printf("Введите цену за квадратный метр: \n");
    if (scanf("%d", &cost) != 1)
    {
        printf("Не верный ввод\n");
        return INPUT_ERROR;
    }
    printf("Укажите тип жилья первичное или вторичное,\n\
    (необходимо ввести 1 или 2 соответсвенно): \n");
    if (scanf("%d", &choice) != 1)
    {
        printf("Не верный тип\n");
        return INPUT_ERROR;
    }
    if (choice != 1 && choice != 2)
    {
        printf("Введенено не корректное число\n");
        return VALUE_ERROR;
    }
    else if (choice == 1)
    {
        printf("Есть ли отделка у жилья ?\n\
        (необходимо ввести 0 или 1 соответсвенно):\n");
        if(scanf("%d", &facing) != 1)
        {
            printf("Не верный ввод\n");
            return INPUT_ERROR;
        }
        if (facing != 0 && facing != 1)
        {
            printf("Введенено не корректное число\n");
            return VALUE_ERROR;
        }
    }
    else if (choice == 2)
    {
        printf("Введите время постройки (если содержит пробел введите _):\n");
        if (scanf("%s", build_time) != 1)
        {
            printf("Не верный ввод\n");
            return INPUT_ERROR;
        }
        printf("Введите кол-во бывших резидентов:\n");
        if (scanf("%d", &last_residents_num) != 1)
        {
            printf("Не верный ввод\n");
            return INPUT_ERROR;
        }
        if (last_residents_num < 0)
        {
            printf("Не верное значение кол-ва\n");
            return VALUE_ERROR;
        }
        printf("Были ли животны ?,\n\
        (необходимо ввести 0 или 1 соответсвенно): \n");
        if(scanf("%d", &animals) != 1)
        {
            printf("Не верный ввод\n");
            return INPUT_ERROR;
        }
        if (animals != 0 && animals != 1)
        {
            printf("Введенено не корректное число\n");
            return VALUE_ERROR;
        }
    }

    strcpy(apartment->address, address);
    apartment->total_area = total_area;
    apartment->rooms_num = rooms_num;
    apartment->cost = cost;
    apartment->choice = choice;
    if (choice == 1)
        apartment->kind.facing = facing;
    else
    {
        strcpy(apartment->kind.second.build_time, build_time);
        apartment->kind.second.last_residents_num = last_residents_num;
        apartment->kind.second.animals = animals;
    }

    return 0;
}

void delete_apartment(apartment_t *apartments, size_t *arr_len, int rooms_num)
{
    size_t i = 0;
    while (i < *arr_len)
    {
        if (apartments[i].rooms_num == rooms_num)
        {
            for (size_t j = i; j < *arr_len - 1; j++)
                apartments[j] = apartments[j + 1];
            (*arr_len)--;
        }
        else
            i++;
    }
}

void write_apartment(const apartment_t *apartment)
{
    printf("|%20s|%10d|%10d|%10d", apartment->address, apartment->total_area,\
    apartment->rooms_num, apartment->cost);
    if (apartment->choice == 1)
        printf("|%3d|          -         |     -    | - |\n", apartment->kind.facing);
    else
        printf("| - |%20s|%10d|%3d|\n", apartment->kind.second.build_time,\
        apartment->kind.second.last_residents_num, apartment->kind.second.animals);
}

void match_apartments(const apartment_t *apartments, size_t arr_len, int cost1, int cost2)
{
    for (int i = 0; i < arr_len; i++)
		if (apartments[i].choice == 2 && apartments[i].kind.second.animals == 0 &&\
        apartments[i].rooms_num == 2 && cost1 < apartments[i].cost && apartments[i].cost < cost2)
				write_apartment(&apartments[i]);
}

void update_index(key_t *keys, size_t arr_len)
{
	for (size_t i = 0; i < arr_len; i++)
		keys[i].src_ind = i;		
}

int apartment_cmp(const void *arg1, const void *arg2)
{
	apartment_t *temp1 = (apartment_t *)arg1;
	apartment_t *temp2 = (apartment_t *)arg2;
	return strcmp(temp1->address, temp2->address);
}

int apartment_key_cmp(const void *arg1, const void *arg2)
{
	key_t *temp1 = (key_t *)arg1;
	key_t *temp2 = (key_t *)arg2;
	return strcmp(temp1->key, temp2->key);
}

void my_sort_keys(key_t *keys, size_t arr_len)
{
    for (size_t i = 0; i < arr_len - 1; i++)
    {
        for (size_t j = 0; j < arr_len - i - 1; j++)
        {
            if (strcmp(keys[j].key, keys[j + 1].key) > 0)
            {
                key_t tmp = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = tmp;
            }
        }
    }
}

void my_sort(apartment_t *apartments, size_t arr_len)
{
    for (size_t i = 0; i < arr_len - 1; i++)
    {
        for (size_t j = 0; j < arr_len - i - 1; j++)
        {
            if (strcmp(apartments[j].address, apartments[j + 1].address) > 0)
            {
                apartment_t tmp = apartments[j];
                apartments[j] = apartments[j + 1];
                apartments[j + 1] = tmp;
            }
        }
    }
}

void write_apartments(const apartment_t *apartments, size_t arr_len)
{
    printf("-----------------------------------------------------------------------------------------------\n");
    for (size_t i = 0; i < arr_len; i++)
    {
        write_apartment(&apartments[i]);
    }
    printf("-----------------------------------------------------------------------------------------------\n");
}

void write_apartments_by_keys(const apartment_t *apartments, key_t *keys, size_t arr_len)
{
    printf("-----------------------------------------------------------------------------------------------\n");
    for (size_t i = 0; i < arr_len; i++)
    {
        write_apartment(&apartments[keys[i].src_ind]);
    }
    printf("-----------------------------------------------------------------------------------------------\n");
}