#include "tree.h"
#include "tree_impl.h"
#include "avl_tree.h"
#include "table.h"
#include "table_impl.h"
#include "menu.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int rc;

    if (argc < 2)
    {
        printf("Ошибка кол-ва аргументов\n");
        return ARGS_ERROR;
    }

    tree_node_t * tree = NULL;
    hash_table_t *table = NULL;
    
    print_menu();

    int choice;
    int size;

    if ((rc = read_choice(&choice)))
        return rc;

    while (choice != 0)
    {
        if (choice == 1)
        {
            FILE *f_in = fopen(argv[1], "r");

            if (f_in == NULL)
            {
                printf("Файл не найден\n");
                return NO_FILE_ERROR;
            }

            if ((rc = read_table_size(&size)))
            {
                fclose(f_in);
                return rc;
            }

            table = create_table(size);

            if (!table)
            {
                printf("Ошибка выделения памяти\n");
                fclose(f_in);
                return rc;
            }

            if (fill_table(&table, f_in))
            {
                fclose(f_in);
                return rc;
            }

            rewind(f_in);

            if ((rc = create_tree(&tree, f_in)))
            {
                tree_destroy(tree);
                fclose(f_in);
                return rc;
            }

            fclose(f_in);

            printf("Файл прочитан\n");
        }
        else if (choice == 2)
        {
            char *word;

            if ((rc = read_word(&word)))
            {
                tree_destroy(tree);
                return rc;
            }

            tree_node_t *node = create_node(word);
            if (!node)
            {
                printf("Ошибка выделения памяти\n");
                free_tree_node(node);
                tree_destroy(tree);
                return ALLOCATION_ERROR;
            }
            free(word);
            tree = tree_insert(tree, node);
        }
        else if (choice == 3)
        {
            char *word;

            if ((rc = read_word(&word)))
            {
                tree_destroy(tree);
                return rc;
            }

            tree_node_t *node = tree_delete(tree, word);
            free(word);
            if (node)
                tree = node;
        }
        else if (choice == 4)
        {
            char *word;

            if ((rc = read_word(&word)))
            {
                tree_destroy(tree);
                return rc;
            }
            int count = 0;
            int count1 = 0;
            tree_node_t *node = look_up(tree, word, &count1);
            char *found = table_search(table, word, &count);

            if (found == NULL)
                printf("Слово в таблице не найдено\n");
            else
                printf("Поиск в таблице: %s, Кол-во сравнений:%d\n", found, count);
        
            free(word);
            
            if (!node)
                printf("Слово в дереве не найдено\n");
            else
                printf("Поиск в дереве: %s, Кол-во сравнений:%d\n", node->word, count1);
        }
        else if (choice == 5)
        {
            tree_node_t *tmp = tree_balance(tree);

            if (!tmp)
                printf("Пустое дерево\n");
            else
                tree = tmp;
        }
        else if (choice == 6)
        {
            FILE *f_out = fopen("output.dot", "w");

            print_table(table);

            export_to_dot(f_out, "tree", tree);

            fclose(f_out);

            system("dot -Tpng output.dot > output.png");
        }

        read_choice(&choice);
    }

    tree_destroy(tree);
    free_table(table);

    return ERR_OK;
}