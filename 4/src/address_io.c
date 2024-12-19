#include "address_io.h"

int read_address(void **address)
{
    printf("Введите адресс памяти: ");
    if (scanf("%p", address) != 1)
    {
        printf("Ошибка ввода\n");
        return READ_ERROR;
    }

    return ERR_OK;
}

int print_menu(int *choice)
{
    printf("Выберите пункт меню:\n\
            1) Добавить элемент в стэк\n\
            2) Удалить элемент стэка\n\
            3) Очистить стэк\n\
            4) Вывести стэк\n\
            5) Выход из программы\n");
    
    if (scanf("%d", choice) != 1 || *choice < 1 || *choice > 5)
    {
        printf("Ошибка меню\n");
        return MENU_ERROR;
    }

    return ERR_OK;
}
