#include "menu.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

void print_menu(void)
{
    printf("----------------------------------------------\n");
    printf("|                 Меню                       |\n");
    printf("----------------------------------------------\n");
    printf("| 0. Выход из программы.                     |\n");
    printf("| 1. Считать слова из файла.                 |\n");
    printf("| 2. Добавить слово.                         |\n");
    printf("| 3. Удалить слово.                          |\n");
    printf("| 4. Поиск слова.                            |\n");
    printf("| 5. Сбалансировать дерево.                  |\n");
    printf("| 6. Нарисовать дерево.                      |\n");
    printf("----------------------------------------------\n");
}

int read_choice(int *choice)
{
    printf("Введите пункт меню: ");
    if (scanf("%d", choice) != 1 || *choice < 0 || *choice > 6)
    {
        printf("Пункт меню не найден\n");
        return READ_ERROR;
    }

    return ERR_OK;
}

int read_table_size(int *size)
{
    printf("Введите размер таблицы: ");
    if (scanf("%d", size) != 1 || *size <= 0)
    {
        printf("Не верный размер таблицы\n");
        return READ_ERROR;
    }

    return ERR_OK;
}

int read_word(char **word)
{
    printf("Введите слово: ");
    *word = malloc(sizeof(char) * MAX_WORD_LEN);

    if (*word == NULL)
        return ALLOCATION_ERROR;
        
    if (scanf("%s", *word) != 1)
    {
        printf("Ошибка ввода");
        return READ_ERROR;
    }
    
    return ERR_OK;
}
