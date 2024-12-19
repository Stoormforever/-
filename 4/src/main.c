#include "arr_stack.h"
#include "list_stack.h"
#include "address_io.h"
#include "dynamic_array.h"

int main(void)
{
    int rc = 0;

    arr_stack_t arr_stack = arr_stack_create();
    if (!arr_stack)
    {   
        printf("Ошибка выделения памти\n");
        return ALLOCATION_ERROR;
    }
    list_stack_t list_stack = list_stack_create();
    if (!list_stack)
    {
        printf("Ошибка выделения памти\n");
        arr_stack_destroy(arr_stack);
        return ALLOCATION_ERROR;
    }
    address_arr_t freed_addresses = init_da_array();
    if (!freed_addresses)
    {
        printf("Ошибка выделения памти\n");
        arr_stack_destroy(arr_stack);
        list_stack_destroy(list_stack);
        return ALLOCATION_ERROR;
    }

    int choice;
    if ((rc = print_menu(&choice)))
    {
        arr_stack_destroy(arr_stack);
        list_stack_destroy(list_stack);
        da_destroy(freed_addresses);
        return rc;
    }

    while (choice != 5)
    {
        if (choice == 1)
        {
            void *address;
            if ((rc = read_address(&address)))
            {
                arr_stack_destroy(arr_stack);
                list_stack_destroy(list_stack);
                da_destroy(freed_addresses);
                return rc;
            }
            if ((rc = arr_stack_push(arr_stack, address)))
            {
                printf("Переполнение стэка\n");
                arr_stack_destroy(arr_stack);
                list_stack_destroy(list_stack);
                da_destroy(freed_addresses);
                return rc;
            }
            if ((rc = list_stack_push(list_stack)))
            {
                printf("Ошибка выделения памти\n");
                arr_stack_destroy(arr_stack);
                list_stack_destroy(list_stack);
                da_destroy(freed_addresses);
                return rc;
            }
        }
        else if (choice == 2)
        {
            void *elem;
            if ((rc = arr_stack_pop(arr_stack)))
            {
                printf("Стэк уже пуст\n");
                arr_stack_destroy(arr_stack);
                list_stack_destroy(list_stack);
                da_destroy(freed_addresses);
                return rc;
            }
            if ((rc = list_stack_pop(list_stack, &elem)))
            {
                printf("Стэк уже пуст\n");
                arr_stack_destroy(arr_stack);
                list_stack_destroy(list_stack);
                da_destroy(freed_addresses);
                return rc;
            }
            da_append(freed_addresses, elem);
        }
        else if (choice == 3)
        {
            arr_stack_make_empty(arr_stack);
            list_stack_make_empty(list_stack);
            da_make_empty(freed_addresses);
            printf("Стэк очищен\n");
        }
        else if (choice == 4)
        {
            arr_stack_print(arr_stack);
            list_stack_print(list_stack);
            da_print(freed_addresses);
        }

        if ((rc = print_menu(&choice)))
        {
            arr_stack_destroy(arr_stack);
            list_stack_destroy(list_stack);
            da_destroy(freed_addresses);
            return rc;
        }
    }
    arr_stack_destroy(arr_stack);
    list_stack_destroy(list_stack);
    da_destroy(freed_addresses);

    return ERR_OK;
}