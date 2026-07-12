#include "cmatrix.h"
#include <stdlib.h>
#include "string.h"

CMatrix *cmatrix_create(size_t rows, size_t cols)
{
    CMatrix *m = malloc(sizeof(*m));

    if (!m)
        return NULL;

    m->rows = rows;
    m->cols = cols;

    m->data = calloc(
        rows * cols,
        sizeof(Complex));

    if (!m->data) {
        free(m);
        return NULL;
    }

    return m;
}

void cmatrix_destroy(CMatrix *m)
{
    if (!m)
        return;

    free(m->data);
    free(m);
}

CMatrix *cmatrix_identity(size_t n)
{
    CMatrix *m = cmatrix_create(n, n);

    if (!m)
        return NULL;

    for (size_t i = 0; i < n; i++)
        CMAT(m,i,i) = complex_new(1,0);

    return m;
}

CMatrix *cmatrix_copy(const CMatrix *m)
{
    CMatrix *copy =
        cmatrix_create(
            m->rows,
            m->cols);

    if (!copy)
        return NULL;

    memcpy(
        copy->data,
        m->data,
        sizeof(Complex) *
        m->rows *
        m->cols);

    return copy;
}

Complex cmatrix_get(
    const CMatrix *m,
    size_t r,
    size_t c)
{
    return CMAT(m,r,c);
}

void cmatrix_set(
    CMatrix *m,
    size_t r,
    size_t c,
    Complex value)
{
    CMAT(m,r,c) = value;
}

void cmatrix_fill(
    CMatrix *m,
    Complex value)
{
    size_t n =
        m->rows * m->cols;

    for(size_t i=0;i<n;i++)
        m->data[i]=value;
}

void cmatrix_zero(CMatrix *m) { cmatrix_fill(m, complex_new(0, 0)); }

CMatrix *cmatrix_add(
    const CMatrix *a,
    const CMatrix *b)
{
    if(a->rows!=b->rows ||
       a->cols!=b->cols)
        return NULL;

    CMatrix *c=
        cmatrix_create(
            a->rows,
            a->cols);

    if(!c)
        return NULL;

    size_t n=
        a->rows*a->cols;

    for(size_t i=0;i<n;i++)
        c->data[i]=
            complex_add(
                a->data[i],
                b->data[i]);

    return c;
}

CMatrix *cmatrix_sub(
    const CMatrix *a,
    const CMatrix *b)
{
    if(a->rows!=b->rows ||
       a->cols!=b->cols)
        return NULL;

    CMatrix *c=
        cmatrix_create(
            a->rows,
            a->cols);

    if(!c)
        return NULL;

    size_t n=
        a->rows*a->cols;

    for(size_t i=0;i<n;i++)
        c->data[i]=
            complex_sub(
                a->data[i],
                b->data[i]);

    return c;
}

CMatrix *cmatrix_scale(
    const CMatrix *m,
    Complex s)
{
    CMatrix *out=
        cmatrix_create(
            m->rows,
            m->cols);

    if(!out)
        return NULL;

    size_t n=
        m->rows*m->cols;

    for(size_t i=0;i<n;i++)
        out->data[i]=
            complex_mul(
                m->data[i],
                s);

    return out;
}

CMatrix *cmatrix_mul(
    const CMatrix *a,
    const CMatrix *b)
{
    if(a->cols!=b->rows)
        return NULL;

    CMatrix *c=
        cmatrix_create(
            a->rows,
            b->cols);

    if(!c)
        return NULL;

    for(size_t i=0;i<a->rows;i++)
    {
        for(size_t k=0;k<a->cols;k++)
        {
            Complex aik=
                CMAT(a,i,k);

            for(size_t j=0;j<b->cols;j++)
            {
                Complex prod=
                    complex_mul(
                        aik,
                        CMAT(b,k,j));

                CMAT(c,i,j)=
                    complex_add(
                        CMAT(c,i,j),
                        prod);
            }
        }
    }

    return c;
}

CMatrix *cmatrix_transpose(
    const CMatrix *m)
{
    CMatrix *t=
        cmatrix_create(
            m->cols,
            m->rows);

    if(!t)
        return NULL;

    for(size_t i=0;i<m->rows;i++)
        for(size_t j=0;j<m->cols;j++)
            CMAT(t,j,i)=CMAT(m,i,j);

    return t;
}

CMatrix *cmatrix_conjugate(
    const CMatrix *m)
{
    CMatrix *c=
        cmatrix_copy(m);

    if(!c)
        return NULL;

    size_t n=
        m->rows*m->cols;

    for(size_t i=0;i<n;i++)
        c->data[i]=
            complex_conj(
                c->data[i]);

    return c;
}

CMatrix *cmatrix_adjoint(
    const CMatrix *m)
{
    CMatrix *t=
        cmatrix_transpose(m);

    if(!t)
        return NULL;

    size_t n=
        t->rows*t->cols;

    for(size_t i=0;i<n;i++)
        t->data[i]=
            complex_conj(
                t->data[i]);

    return t;
}

Complex cmatrix_trace(
    const CMatrix *m)
{
    Complex tr=
        complex_new(0,0);

    if(m->rows!=m->cols)
        return tr;

    for(size_t i=0;i<m->rows;i++)
        tr=
            complex_add(
                tr,
                CMAT(m,i,i));

    return tr;
}

double cmatrix_norm(
    const CMatrix *m)
{
    double sum=0;

    size_t n=
        m->rows*m->cols;

    for(size_t i=0;i<n;i++)
        sum+=
            complex_abs2(
                m->data[i]);

    return sqrt(sum);
}


