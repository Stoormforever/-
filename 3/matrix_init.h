#ifndef __PROCESSING_H__
#define __PROCESSING_H__

#include "matrix.h"

void init_sizes(matrix_t *const vector, const int xsize);

int init_sparce_matrix(matrix_t *const sparce_matrix, int *const A, int *const IA, list_t *list);

int init_std_matrix(std_matrix_t *const matrix, const int xsize, const int ysize);

int filling_matrix(std_matrix_t *std_matrix, matrix_t *sparce_matrix,
    const bool enter_type, const bool mv_type);

void copy_matrix(std_matrix_t std_matrix, matrix_t *sparce_matrix);

int new_matrix(std_matrix_t *const matrix);

void free_memory(std_matrix_t *const matrix);

void free_std_matrix(std_matrix_t *matrix, std_matrix_t *vector, std_matrix_t *result);

void free_all_memory(list_t *list_matrix, list_t *list_vector, list_t *list_result,
    std_matrix_t *std_matrix, std_matrix_t *std_vector, std_matrix_t *std_result);

#endif