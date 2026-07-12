#ifndef PHORAY_MATRIX_H
#define PHORAY_MATRIX_H

#include <stdlib.h>

#define MAT(m, r, c) ((m)->data[(r) * (m)->cols + (c)])

typedef struct Matrix {
  size_t rows;
  size_t cols;
  double *data;
} Matrix;

Matrix *matrix_create(size_t rows, size_t cols);
Matrix *matrix_identity(size_t n);
Matrix *matrix_copy(const Matrix *m);

void matrix_destroy(Matrix *m);

double matrix_get(const Matrix *m, size_t r, size_t c);
void matrix_set(const Matrix *m, size_t r, size_t c, double value);

Matrix *matrix_add(const Matrix *a, const Matrix *b);
Matrix *matrix_sub(const Matrix *a, const Matrix *b);
Matrix *matrix_scale(const Matrix *m, double s);
Matrix *matrix_mul(const Matrix *a, const Matrix *b);

Matrix *matrix_transpose(const Matrix *);
double matrix_determinant(const Matrix *);
Matrix *matrix_inverse(const Matrix *);
double matrix_trace(const Matrix *);
double matrix_norm(const Matrix *);

void matrix_print(const Matrix *);

#endif
