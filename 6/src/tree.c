#include "tree.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

tree_node_t *create_node(char *word)
{
    tree_node_t *node = malloc(sizeof(struct tree_node));

    if (node)
    {
        char *ptmp = strdup(word);
        if (ptmp)
            node->word = ptmp;
        else
            return NULL;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

int create_tree(tree_node_t **root, FILE *f)
{
    tree_node_t *node;
    char *word = NULL;
    size_t buff = 0;
    int word_len;

    while((word_len = getline(&word, &buff, f)) != -1)
    {
        if (word[word_len - 1] == '\n')
        {
            word[word_len - 1] = '\0';
            word_len--;
        }
        else if (word_len == 0)
        {
            free(word);
            printf("Ошибка чтения файла");
            return READ_ERROR;
        }
        else
        {
            free(word);
            printf("Ошибка чтения файла");
            return READ_ERROR;
        }

        node = create_node(word);
        if (!node)
        {
            free(word);
            printf("Ошибка выделения памяти");
            return ALLOCATION_ERROR;
        }
        *root = tree_insert(*root, node);

        free(word);
        word = NULL;
        buff = 0;
    }

    free(word);

    printf("Файл прочитан\n");

    return ERR_OK;
}

tree_node_t *tree_insert(tree_node_t *tree, tree_node_t *node)
{
    int cmp;
    
    if (tree == NULL)
        return node;

    cmp = strcmp(node->word, tree->word);

    if (cmp < 0)
        tree->left = tree_insert(tree->left, node);
    else if (cmp > 0)
        tree->right = tree_insert(tree->right, node);
    
    return tree;
}

void apply_pre(struct tree_node *tree, void (*f)(tree_node_t*, void*, char), void *arg, char letter)
{
    if (tree == NULL)
        return;
    
    f(tree, arg, letter);

    apply_pre(tree->left, f, arg, letter);

    apply_pre(tree->right, f, arg, letter);
}


void to_dot(struct tree_node *tree, void *param, char letter)
{
    FILE *f = param;

    if (letter && tree->word[0] == letter)
        fprintf(f, "%s [color=\"red\"];\n", tree->word);

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->word, tree->left->word);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->word, tree->right->word);
}

void export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree, char letter)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply_pre(tree, to_dot, f, letter);

    fprintf(f, "}\n");
}

void tree_match(tree_node_t *tree, char letter, int *count)
{
    if (tree == NULL)
        return;

    if (tree->word[0] == letter)
        (*count)++;
    
    tree_match(tree->left, letter, count);

    tree_match(tree->right, letter, count);
}

void file_match(FILE *f, char letter, int *count)
{
    char *word = NULL;
    size_t buff = 0;
    while (getline(&word, &buff, f) != -1)
    {
        if (word[0] == letter)
            (*count)++;
        
        free(word);
        word = NULL;
        buff = 0;
    }

    free(word);
}

tree_node_t *look_up(tree_node_t *tree, const char *word)
{
    int cmp;

    if (tree == NULL)
        return NULL;

    cmp = strcmp(word, tree->word);

    if (cmp == 0)
        return tree;
    else if (cmp < 0)
        return look_up(tree->left, word);
    else
        return look_up(tree->right, word);
}

void free_tree_node(tree_node_t *node)
{
    free(node->word);
    free(node);
}

void tree_destroy(tree_node_t *tree)
{
    if (tree == NULL)
        return;
    
    tree_destroy(tree->right);
    tree_destroy(tree->left);
    free_tree_node(tree);
}

int word_copy(tree_node_t *src, tree_node_t *dst)
{
    char *ptmp = strdup(src->word);
    if (ptmp)
    {
        free(dst->word);
        dst->word = ptmp;
        return ERR_OK;
    }

    return ALLOCATION_ERROR;
}

tree_node_t *tree_delete(tree_node_t *tree, const char *word)
{
    if (tree == NULL)
    {
        printf("Пустое дерево\n");
        return NULL;
    }

    tree_node_t *del_node = tree;
    int cmp = strcmp(word, tree->word);
    tree_node_t *parent = tree;
        
    while (cmp)
    {
        if (cmp < 0)
        {
            parent = del_node;
            del_node = del_node->left;
        }
        else if (cmp > 0)
        {
            parent = del_node;
            del_node = del_node->right;
        }
        
        if (del_node == NULL)
        {
            printf("Слово не найдено\n");
            return NULL;
        }
        
        cmp = strcmp(word, del_node->word);
    }

    if (!del_node->left && !del_node->right)
    {
        if (parent->left == del_node)
            parent->left = NULL;
        else
            parent->right = NULL;
        
        free_tree_node(del_node);
    }
    
    else if (!del_node->left || !del_node->right)
    {
        tree_node_t *node;

        if (del_node->left != NULL)
            node = del_node->left;
        else
            node = del_node->right;

        if (parent->left == del_node)
            parent->left = node;
        else
            parent->right = node;

        if (del_node == tree)
            tree = node;

        free_tree_node(del_node);  
    }

    else if (del_node->left && del_node->right)
    {
        tree_node_t *parent_min = del_node;
        tree_node_t *min = del_node->right;

        while (min->left != NULL)
        {
            parent_min = min;
            min = min->left;
        }

        if (word_copy(min, del_node))
        {
            printf("Ошибка копирования памяти");
            return NULL;
        }
        del_node = min;

        if (parent_min->left == min)
            parent_min->left = min->right;
        else
            parent_min->right = min->right;
    
        free(del_node->word);
        free(del_node);
    }

    return tree;
}