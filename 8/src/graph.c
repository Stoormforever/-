#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "queue.h"
#include "queue_impl.h"

#define MAX_LEN 10000

#define min(x, y) ( (x) < (y) ? (x) : (y) )
#define max(x, y) ( (x) > (y) ? (x) : (y) )

int** allocate_matrix(size_t n, size_t m)
{
    int **data = malloc(n * sizeof(int*) + n * m * sizeof(int));
    
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
    {
        data[i] = (int*)((char*) data + n * sizeof(int*) + i * m * sizeof(int));
        for (size_t j = 0; j < m; ++j)
            data[i][j] = 0;
    }
    
    return data;
}

void free_graph(graph_t *graph)
{
    if (graph->matrix)
    {
        free(graph->matrix);
        graph->matrix = NULL;
    }
    if (graph->transpos_matrix)
    {
        free(graph->transpos_matrix);
        graph->transpos_matrix = NULL;
    }
}

void init_graph(graph_t *graph)
{
    graph->matrix = NULL;
    graph->transpos_matrix = NULL;
    graph->size = 0;
}

int create_graph(graph_t *graph)
{
    printf("Введите количество вершин в графе: ");

    if (scanf("%d", &(graph->size)) != 1 || graph->size < 1)
    {
        printf("\nНеверный ввод\n\n");
        fflush(stdin);
        return READ_ERROR;
    }
    fflush(stdin);
    
    graph->matrix = allocate_matrix(graph->size, graph->size);
    graph->transpos_matrix = allocate_matrix(graph->size, graph->size);

    if (!graph->matrix || !graph->transpos_matrix)
    {
        free_graph(graph);
        return ALLOCATION_ERROR;
    }
    
    int path;
    
    for (int i = 0; i < graph->size; i++)
    {
        printf("\n - Вершина %d -\n", i);
        for (int j = 0; j < graph->size; ++j)
        {
            printf("\tПуть в вершину %d: ", j);
            if (scanf("%d", &path) != 1 || path < 0)
            {
                fflush(stdin);
                printf("Неверный ввод.\n");
                j--;
            }
            fflush(stdin);
            (graph->matrix)[i][j] = path;
            (graph->transpos_matrix)[j][i] = path;
        }
    }
    fflush(stdin);
    
    return ERR_OK;
}

void print_graph_matrix(graph_t graph)
{
    for (int i = 0; i < graph.size; i++)
    {
        for (int j = 0; j < graph.size; j++)
            printf("%d ", graph.matrix[i][j]);
        printf("\n");
    }
}

void print_graph(graph_t *graph)
{
    FILE *f = fopen("graph.gv", "w");

    fprintf(f, "digraph graph_pic {\n");

    for (int i = 0; i < graph->size; ++i)
        for (int j = 0; j < graph->size; ++j)
            if (graph->matrix[i][j] != 0)
                fprintf(f, "%d -> %d [label=\"%.1d\"];\n", i, j, graph->matrix[i][j]);
    
    fprintf(f, "}\n");
    
    fclose(f);
}
    
    
int dfs(graph_t *graph, int **matrix)
{
    int *visited = calloc(graph->size ,sizeof(int));

    if (!visited)
        return ALLOCATION_ERROR;

    queue_t points;
    init_queue(&points);
    node_t* point = create_node(0);
    points = *push_back(&points, point);
    
    int index = points.head->data;
    visited[index] = 1;
    
    while (points.head)
    {
        for (int i = 0; i < graph->size; ++i)
        {
            if (i != index && matrix[index][i] && matrix[i][index] && !visited[i])
            {
                visited[i] = 1;
                point = create_node(i);
                points = *push_back(&points, point);

            }
            if (i != index && matrix[index][i] && !visited[i])
            {
                visited[i] = 1;
                point = create_node(i);
                points = *push_back(&points, point);
            }
        }
        points = *pop_front(&points);
        
        if (points.head)
            index = points.head->data;
    }
    
    if (points.head)
        free_queue(&points);
    
    int type = 0;
    
    for (int i = 0; i < graph->size; ++i)
        if (visited[i] == 0)
            type = 1;
    free(visited);
    
    return type;
}

int is_connected(graph_t *graph)
{
    int connected = dfs(graph, graph->transpos_matrix);
    
    if (!connected)
        printf("\nГраф является связным.\n\n");
    else if (connected == ALLOCATION_ERROR)
        printf("\nОшибка выделения памяти.\n");
    else
        printf("\nГраф не является связным.\n\n");
    
    return connected;
}