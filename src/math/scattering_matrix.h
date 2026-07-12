#ifndef PHORAY_SMATRIX_H
#define PHORAY_SMATRIX_H

#include <stdlib.h>
#include "matrix.h"
#include "vector.h"

typedef struct {
  Matrix *S;
} ScatteringMatrix;

ScatteringMatrix *smmatrix_create(size_t ports);
void smatrix_destroy(ScatteringMatrix *sm);

Vector *smatrix_propagate(const ScatteringMatrix *sm, const Vector *input);
ScatteringMatrix *smatrix_cascade(const ScatteringMatrix *a,
                                  const ScatteringMatrix *b);

ScatteringMatrix *beam_splitter_create(double t);
#endif
