#include "list_queue.h"
#include "arr_queue.h"
#include "errors.h"
#include "model.h"
#include "menu.h"

int get_random_num(void)
{
    return rand() % 100;
}

int main(void)
{
    srand(time(NULL));
    int rc = 0;

    arr_queue_t arr_queue = arr_queue_create();
    if (!arr_queue)
    {   
        printf("Ошибка выделения памти\n");
        return ALLOCATION_ERROR;
    }
    list_queue_t list_queue = list_queue_create();
    if (!list_queue)
    {
        printf("Ошибка выделения памти\n");
        arr_queue_destroy(arr_queue);
        return ALLOCATION_ERROR;
    }

    int choice;
    if ((rc = print_menu(&choice)))
    {
        arr_queue_destroy(arr_queue);
        list_queue_destroy(list_queue);
        return rc;
    }

    while (choice != 6)
    {
        if (choice == 1)
        {
            if ((rc = arr_queue_push(arr_queue, get_random_num())))
            {
                printf("Переполнение очереди\n");
                arr_queue_destroy(arr_queue);
                list_queue_destroy(list_queue);
                return rc;
            }
            if ((rc = list_queue_push(list_queue, get_random_num())))
            {
                printf("Ошибка выделения памти\n");
                arr_queue_destroy(arr_queue);
                list_queue_destroy(list_queue);
                return rc;
            }
        }
        else if (choice == 2)
        {
            void *address;

            if ((rc = arr_queue_pop(arr_queue)))
            {
                printf("Очередь уже пуста\n");
                arr_queue_destroy(arr_queue);
                list_queue_destroy(list_queue);
                return rc;
            }
            if ((rc = list_queue_pop(list_queue, &address)))
            {
                printf("Очередь уже пуста\n");
                arr_queue_destroy(arr_queue);
                list_queue_destroy(list_queue);
                return rc;
            }
        }
        else if (choice == 3)
        {
            arr_queue_make_empty(arr_queue);
            list_queue_make_empty(list_queue);
            printf("Очередь очищена\n");
        }
        else if (choice == 4)
        {
            arr_queue_print(arr_queue);
            list_queue_print(list_queue);
        }
        else if (choice == 5)
        {
            if (arr_model())
                printf("Ошибка выделения памти\n");
            if (list_model())
                printf("Ошибка выделения памти\n");
        }

        if ((rc = print_menu(&choice)))
        {
            arr_queue_destroy(arr_queue);
            list_queue_destroy(list_queue);
            return rc;
        }
    }
    arr_queue_destroy(arr_queue);
    list_queue_destroy(list_queue);

    return ERR_OK;
}