#include "tree.h"
#include "menu.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int rc;

    if (argc < 2)
    {
        printf("Ошибка кол-ва аргументов");
        return ARGS_ERROR;
    }

    tree_node_t * tree = NULL;
    
    print_menu();

    int choice;
    char letter = 0;

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

            if ((rc = create_tree(&tree, f_in)))
            {
                tree_destroy(tree);
                return rc;
            }

            fclose(f_in);
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

            tree_node_t *node = look_up(tree, word);
            free(word);
            if (!node)
                printf("Слово не найдено\n");
            else
                printf("Слово было найдено\n");
        }
        else if (choice == 5)
        {
            int count = 0;

            if ((rc = read_letter(&letter)))
            {
                tree_destroy(tree);
                return rc;
            }

            tree_match(tree, letter, &count);

            printf("Кол-во найденных слов на данную букву: %d\n", count);
        }
        else if (choice == 6)
        {
            printf ("Слова которые начинаются на ранее заданую букву будут выделены\n");

            FILE *f_out = fopen("output.dot", "w");

            export_to_dot(f_out, "tree", tree, letter);

            fclose(f_out);

            system("dot -Tpng output.dot > output.png");
        }

        read_choice(&choice);
    }

    tree_destroy(tree);

    return ERR_OK;
}