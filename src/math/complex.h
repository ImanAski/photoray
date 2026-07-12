#ifndef PHORAY_COMPLEX_H
#define PHORAY_COMPLEX_H

#include <math.h>

typedef struct {
    double real;
    double imag;
} Complex;

Complex complex_new(double real, double imag);

Complex complex_add(Complex a, Complex b);
Complex complex_sub(Complex a, Complex b);
Complex complex_mul(Complex a, Complex b);
Complex complex_div(Complex a, Complex b);

Complex complex_conj(Complex z);

double complex_abs(Complex z);
double complex_abs2(Complex z);

Complex complex_exp(Complex z);

Complex complex_scale(Complex z, double s);

#endif
