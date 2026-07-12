#include "matrix.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>


Matrix *matrix_create(size_t rows, size_t cols)
{
    Matrix *m = malloc(sizeof(Matrix));
    if (!m)
        return NULL;

    m->rows = rows;
    m->cols = cols;
    m->data = calloc(rows * cols, sizeof(double));

    if (!m->data) {
        free(m);
        return NULL;
    }

    return m;
}

Matrix *matrix_identity(size_t n)
{
    Matrix *m = matrix_create(n, n);

    if (!m)
        return NULL;

    for (size_t i = 0; i < n; i++)
        MAT(m, i, i) = 1.0;

    return m;
}

Matrix *matrix_copy(const Matrix *m)
{
    Matrix *copy = matrix_create(m->rows, m->cols);

    if (!copy)
        return NULL;

    memcpy(copy->data,
           m->data,
           sizeof(double) * m->rows * m->cols);

    return copy;
}

void matrix_destroy(Matrix *m)
{
    if (!m)
        return;

    free(m->data);
    free(m);
}

double matrix_get(const Matrix *m, size_t r, size_t c)
{
    return MAT(m, r, c);
}

void matrix_set(const Matrix *m, size_t r, size_t c, double value)
{
    MAT(m, r, c) = value;
}

Matrix *matrix_add(const Matrix *a, const Matrix *b)
{
    if (a->rows != b->rows ||
        a->cols != b->cols)
        return NULL;

    Matrix *c = matrix_create(a->rows, a->cols);

    if (!c)
        return NULL;

    size_t n = a->rows * a->cols;

    for (size_t i = 0; i < n; i++)
        c->data[i] = a->data[i] + b->data[i];

    return c;
}

Matrix *matrix_sub(const Matrix *a, const Matrix *b)
{
    if (a->rows != b->rows ||
        a->cols != b->cols)
        return NULL;

    Matrix *c = matrix_create(a->rows, a->cols);

    if (!c)
        return NULL;

    size_t n = a->rows * a->cols;

    for (size_t i = 0; i < n; i++)
        c->data[i] = a->data[i] - b->data[i];

    return c;
}

Matrix *matrix_mul(const Matrix *a, const Matrix *b)
{
    if (a->cols != b->rows)
        return NULL;

    Matrix *c = matrix_create(a->rows, b->cols);

    if (!c)
        return NULL;

    for (size_t i = 0; i < a->rows; i++)
        for (size_t k = 0; k < a->cols; k++) {

            double aik = MAT(a, i, k);

            for (size_t j = 0; j < b->cols; j++)
                MAT(c, i, j) += aik * MAT(b, k, j);
        }

    return c;
}

Matrix *matrix_scale(const Matrix *m, double s)
{
    Matrix *out = matrix_copy(m);

    if (!out)
        return NULL;

    size_t n = m->rows * m->cols;

    for (size_t i = 0; i < n; i++)
        out->data[i] *= s;

    return out;
}

Matrix *matrix_transpose(const Matrix *m)
{
    Matrix *t = matrix_create(m->cols, m->rows);

    if (!t)
        return NULL;

    for (size_t i = 0; i < m->rows; i++)
        for (size_t j = 0; j < m->cols; j++)
            MAT(t, j, i) = MAT(m, i, j);

    return t;
}

double matrix_trace(const Matrix *m)
{
    if (m->rows != m->cols)
        return 0.0;

    double tr = 0;

    for (size_t i = 0; i < m->rows; i++)
        tr += MAT(m, i, i);

    return tr;
}

double matrix_norm(const Matrix *m)
{
    double sum = 0;

    size_t n = m->rows * m->cols;

    for (size_t i = 0; i < n; i++)
        sum += m->data[i] * m->data[i];

    return sqrt(sum);
}
