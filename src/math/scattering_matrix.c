#include "scattering_matrix.h"
#include <math.h>

ScatteringMatrix *smatrix_create(size_t ports)
{
    ScatteringMatrix *sm = malloc(sizeof(*sm));

    if (!sm)
        return NULL;

    sm->S = matrix_create(ports, ports);

    if (!sm->S) {
        free(sm);
        return NULL;
    }

    return sm;
}

void smatrix_destroy(ScatteringMatrix *sm)
{
    if (!sm)
        return;

    matrix_destroy(sm->S);
    free(sm);
}

Vector *smatrix_propagate(
    const ScatteringMatrix *sm,
    const Vector *input)
{
    if (!sm || !input)
        return NULL;

    if (sm->S->cols != input->size)
        return NULL;

    Vector *out = create_vector(sm->S->rows);

    if (!out)
        return NULL;

    for (size_t i = 0; i < sm->S->rows; i++) {

        double sum = 0.0;

        for (size_t j = 0; j < sm->S->cols; j++)
            sum += matrix_get(sm->S, i, j) *
                   input->data[j];

        out->data[i] = sum;
    }

    return out;
}

ScatteringMatrix *smatrix_cascade(
    const ScatteringMatrix *a,
    const ScatteringMatrix *b)
{
    Matrix *m = matrix_mul(b->S, a->S);

    if (!m)
        return NULL;

    ScatteringMatrix *out = malloc(sizeof(*out));

    if (!out) {
        matrix_destroy(m);
        return NULL;
    }

    out->S = m;

    return out;
}

ScatteringMatrix *beam_splitter_create(double transmission)
{
    ScatteringMatrix *bs = smatrix_create(2);

    if (!bs)
        return NULL;

    double t = sqrt(transmission);
    double r = sqrt(1.0 - transmission);

    matrix_set(bs->S,0,0,t);
    matrix_set(bs->S,0,1,r);

    matrix_set(bs->S,1,0,r);
    matrix_set(bs->S,1,1,-t);

    return bs;
}
