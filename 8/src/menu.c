#include "errors.h"
#include <stdio.h>

void print_menu(void)
{
    printf("\
    Меню:\n\
    1 - Ввести матрицу смежности\n\
    2 - Вывести матрицу смежности\n\
    3 - Вывести граф\n\
    4 - Определить тип графа\n\
    0 - Завершить программу\n\n");
}


int get_cmd(int *cmd)
{
    printf("%s", "\nВведите пункт меню: ");
    if (scanf("%d", cmd) != 1)
    {
        printf("Не верный пункт меню\n");
        return READ_ERROR;
    }

    return ERR_OK;
}