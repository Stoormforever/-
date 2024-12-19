#include "menu.h"

int print_menu(int *choice)
{
    printf("Выберите пункт меню:\n\
            1) Добавить элемент в очередь\n\
            2) Удалить элемент из очереди\n\
            3) Очистить очередь\n\
            4) Вывести очередь\n\
            5) Смоделировать ОА\n\
            6) Выход из программы\n");
    
    if (scanf("%d", choice) != 1 || *choice < 1 || *choice > 6)
    {
        printf("Ошибка меню\n");
        return MENU_ERROR;
    }

    return ERR_OK;
}
