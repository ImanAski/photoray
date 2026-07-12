#ifndef PHORAY_CMATRIX_H
#define PHORAY_CMATRIX_H

#include <stddef.h>
#include "complex.h"

#define CMAT(m,r,c) ((m)->data[(r)*(m)->cols + (c)])

typedef struct {
    size_t rows;
    size_t cols;
    Complex *data;
} CMatrix;

/* ---------- Construction ---------- */

CMatrix *cmatrix_create(size_t rows, size_t cols);
CMatrix *cmatrix_identity(size_t n);
CMatrix *cmatrix_copy(const CMatrix *m);

void cmatrix_destroy(CMatrix *m);

/* ---------- Element access ---------- */

Complex cmatrix_get(
    const CMatrix *m,
    size_t row,
    size_t col);

void cmatrix_set(
    CMatrix *m,
    size_t row,
    size_t col,
    Complex value);

/* ---------- Filling ---------- */

void cmatrix_fill(
    CMatrix *m,
    Complex value);

void cmatrix_zero(CMatrix *m);

/* ---------- Arithmetic ---------- */

CMatrix *cmatrix_add(
    const CMatrix *a,
    const CMatrix *b);

CMatrix *cmatrix_sub(
    const CMatrix *a,
    const CMatrix *b);

CMatrix *cmatrix_scale(
    const CMatrix *m,
    Complex s);

CMatrix *cmatrix_mul(
    const CMatrix *a,
    const CMatrix *b);

/* ---------- Linear algebra ---------- */

CMatrix *cmatrix_transpose(
    const CMatrix *m);

CMatrix *cmatrix_conjugate(
    const CMatrix *m);

CMatrix *cmatrix_adjoint(
    const CMatrix *m);

Complex cmatrix_trace(
    const CMatrix *m);

double cmatrix_norm(
    const CMatrix *m);

CMatrix *cmatrix_inverse(
    const CMatrix *m);

/* ---------- Quantum / Photonics ---------- */

CMatrix *cmatrix_tensor(
    const CMatrix *a,
    const CMatrix *b);

CMatrix *cmatrix_commutator(
    const CMatrix *a,
    const CMatrix *b);

CMatrix *cmatrix_anticommutator(
    const CMatrix *a,
    const CMatrix *b);

CMatrix *cmatrix_power(
    const CMatrix *m,
    unsigned int n);

CMatrix *cmatrix_exponential(
    const CMatrix *m);

/* ---------- Utilities ---------- */

void cmatrix_print(
    const CMatrix *m);

#endif
