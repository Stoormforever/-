#include "apartments.h"
#include <stdlib.h>
#define NO_FILE_ERROR 10
#define ARGC_ERROR 11
#define READ_FILE_ERROR 12

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Не верное кол-во аргументов");
        return ARGC_ERROR;
    }
    apartment_t apartments[ARR_LEN];
    size_t arr_len = 0;
    key_t keys[ARR_LEN];
    char menu[10];
    int main_sorted = 0;

    printf("\nВведите комманду:\n0) menu - показать меню\n1) read - прочитать файл\n2) print - вывести таблицу\n3) add - добавить квартиру\n4) delete - удалить квартиру по кол-ву комнат\n5) sort - отсортровать таблицу по ключам или по таблице\n6) search - найти квартиры по варианту\n7) exit - выйти из программы\n");
    scanf("%s", menu);
    while (strcmp(menu, "exit"))
    {
        if (!strcmp(menu, "read"))
        {
            FILE *f = fopen(argv[1], "r");
            if (f == NULL)
            {
                printf("Файл не найден");
                return NO_FILE_ERROR;
            }
            if (create_table(f, apartments, &arr_len, keys))
            {
                printf("Ошибка чтения файла");
                return READ_FILE_ERROR;
            }
            fclose(f);
        }
        else if (!strcmp(menu, "add"))
        {
            if (!add_apartment(&apartments[arr_len]))
                arr_len++;
        }
        else if (!strcmp(menu, "print"))
        {
            if (arr_len == 0)
                printf("Сначала прочитайте файл\n");
            else
                write_apartments(apartments, arr_len);

        }
        else if (!strcmp(menu, "delete"))
        {
            if (arr_len == 0)
                printf("Сначала прочитайте файл\n");
            else 
            {
                int rooms_num;
                printf("Введите кол-во комнат квартир которые хотите удалить: ");
                if (scanf("%d", &rooms_num) != 1 || rooms_num <= 0)
                    printf("Не верный ввод кол-ва квартир\n");
                else
                    delete_apartment(apartments, &arr_len, rooms_num);
            }
        }
        else if (!strcmp(menu, "search"))
        {
            if (arr_len == 0)
                printf("Сначала прочитайте файл\n");
            else 
            {
                int cost1, cost2;
                printf("Введите ценовой диапазон квартир которые хотите найти(min и max): ");
                if (scanf("%d", &cost1) != 1 || scanf("%d", &cost2) != 1)
                    printf("Не верный ввод цен\n");
                else if (cost1 <= 0 || cost2 <= 0 || cost2 < cost1)
                    printf("Не верный диапазон значения цен\n");
                else
                    match_apartments(apartments, arr_len, cost1, cost2);
            }
        }
        else if (!strcmp(menu, "sort"))
        {
             if (arr_len == 0)
                printf("Сначала прочитайте файл\n");
            else 
            {
                char sort_type[10];
                printf("Введите key чтобы отсортировать по ключам или main по таблице: ");
                if (scanf("%s", sort_type) != 1)
                {
                    printf("Не верный ввод сортировки\n");
                }
                else if (!strcmp(sort_type, "key"))
                {
                    char type;
                    printf("Введите q для ускоренного алгаритма и s для простого: ");
                    if (scanf("\n%c", &type) != 1)
                    {
                        printf("Не верный ввод типа\n");
                    }
                    else if (type == 's')
                    {
                        my_sort_keys(keys, arr_len);
                        if (main_sorted)
                            update_index(keys, arr_len);
                        write_apartments_by_keys(apartments, keys, arr_len);
                    }
                    else if (type == 'q')
                    {
                        qsort(keys, arr_len, sizeof(key_t), apartment_key_cmp);
                        if (main_sorted)
                            update_index(keys, arr_len);
                        write_apartments_by_keys(apartments, keys, arr_len);
                    }
                    else
                        printf("Не верное значение типа\n");
                }
                else if (!strcmp(sort_type, "main"))
                {
                    char type;
                    printf("Введите q для ускоренного алгаритма и s для простого: ");
                    if (scanf("\n%c", &type) != 1)
                    {
                        printf("Не верный ввод типа\n");
                    }
                    else if (type == 's')
                    {
                        my_sort(apartments, arr_len);
                        write_apartments(apartments, arr_len);
                        main_sorted = 1;
                    }
                    else if (type == 'q')
                    {
                        qsort(apartments, arr_len, sizeof(apartment_t), apartment_cmp);
                        write_apartments(apartments, arr_len);
                        main_sorted = 1;
                    }
                    else
                        printf("Не верное значение типа\n");
                }
                else
                    printf("Не верное значение типа сортировки\n");
            }
        }
        else
            printf("Комманда не найдена\n");
        scanf("%s", menu);
    }

    return 0;
}