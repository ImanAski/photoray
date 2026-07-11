#ifndef PHORAY_VECTOR_H
#define PHORAY_VECTOR_H

#include <stddef.h>

typedef struct {
  double *data;
  size_t size;
} Vector;

Vector *create_vector(size_t size);
Vector *vector_copy(const Vector *v);
void vector_destroy(Vector *v);

void vector_fill(Vector *v, double value);
void vector_zero(Vector *v);

double vector_norm(const Vector *v);
double vector_dot(const Vector *a, const Vector *b);

void vector_set(const Vector *v, size_t i, double value);
double vector_get(const Vector *v, size_t i);

int vector_add(Vector *result, const Vector *a, const Vector *b);
int vector_sub(Vector *result, const Vector *a, const Vector *b);

void vector_print(const Vector *v);

#endif
