#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "matrix.h"
#include "menu.h"

int main(void)
{
    int rc = 0;   
    int cmd = 1;
    int graph_created = 0;
    
    graph_t graph;
    init_graph(&graph);
    
    while (cmd)
    {
        print_menu();
        if ((rc = get_cmd(&cmd)))
            return rc;
        switch(cmd)
        {
            case(0):
                if (graph_created)
                    free_graph(&graph);
                printf("\nПрограмма завершена.\n");
                break;
            case(1):
                if (graph_created)
                    free_graph(&graph);
                if ((rc = create_graph(&graph)))
                    printf("\nНе удалось считать матрицу смежностей.\n");
                else
                {
                    graph_created = 1;
                    printf("\nМатрица успешно смежностей считана.\n");
                }
                break;
            case(2):
                if (!graph_created)
                    printf("\nМатрица смежностей не создана.\n");
                else
                    print_graph_matrix(graph);
                break;
            case(3):
                if (!graph_created)
                    printf("\nМатрица смежностей не создана.\n");
                else
                {
                    print_graph(&graph);
                    system("dot -Tpng graph.gv > graph.png");
                }
                break;
            case(4):
                if (!graph_created)
                    printf("\nМатрица смежностей не создана.\n");
                else
                    is_connected(&graph);
                break;
            default:
                printf("\nНекорректный номер команды.\n\n");
        }
    }
    return rc;
}