#include "complex.h"

#include <math.h>

Complex complex_new(double real, double imag)
{
    Complex z;
    z.real = real;
    z.imag = imag;
    return z;
}

Complex complex_add(Complex a, Complex b)
{
    return complex_new(
        a.real + b.real,
        a.imag + b.imag);
}

Complex complex_sub(Complex a, Complex b)
{
    return complex_new(
        a.real - b.real,
        a.imag - b.imag);
}

Complex complex_scale(Complex z, double s)
{
    return complex_new(
        z.real * s,
        z.imag * s);
}

Complex complex_mul(Complex a, Complex b)
{
    return complex_new(
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real);
}

Complex complex_div(Complex a, Complex b)
{
    double denom =
        b.real * b.real +
        b.imag * b.imag;

    return complex_new(
        (a.real * b.real + a.imag * b.imag) / denom,
        (a.imag * b.real - a.real * b.imag) / denom);
}

Complex complex_conj(Complex z)
{
    return complex_new(
        z.real,
        -z.imag);
}

double complex_abs2(Complex z)
{
    return
        z.real * z.real +
        z.imag * z.imag;
}

double complex_abs(Complex z)
{
    return sqrt(complex_abs2(z));
}

Complex complex_exp(Complex z)
{
    /*
        e^(a+ib)
        =
        e^a(cos(b)+isin(b))
    */

    double e = exp(z.real);

    return complex_new(
        e * cos(z.imag),
        e * sin(z.imag));
}
