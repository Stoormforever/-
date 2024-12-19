#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "matrix.h"

void std_multiplication(std_matrix_t *matrix, std_matrix_t *vector, std_matrix_t *result);

void transpose(std_matrix_t *matrix);

void sparce_multiplication(matrix_t *matrix, std_matrix_t *vector, matrix_t *result);

#endif