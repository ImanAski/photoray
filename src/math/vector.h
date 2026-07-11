#ifndef PHORAY_VECTOR_H
#define PHORAY_VECTOR_H

#include <stddef.h>

typedef struct {
  double *data;
  size_t size;
} Vector;

/**
 * creates an empty vector
 *
 * Returns Vector
 */
Vector *create_vector(size_t size);

/**
 * copies the vector into new position
 *
 * Return Vector
 */
Vector *vector_copy(const Vector *v);

/**
 *
 * Deletes a vector completely
 *
 * Returns void
 */
void vector_destroy(Vector *v);

/**
 * fill all the elements in a vector with a given value
 *
 * Returns void
 */
void vector_fill(Vector *v, double value);

/**
 * Makes all the elements in the given vector zero
 *
 * Returns void
 */
void vector_zero(Vector *v);

double vector_norm(const Vector *v);
double vector_dot(const Vector *a, const Vector *b);

void vector_set(const Vector *v, size_t i, double value);
double vector_get(const Vector *v, size_t i);

int vector_add(Vector *result, const Vector *a, const Vector *b);
int vector_sub(Vector *result, const Vector *a, const Vector *b);

double vector_min_elem(const Vector *v);
double vector_max_elem(const Vector *v);

double vector_sum(const Vector *v);
double vector_distance(const Vector *a, const Vector *b);

void vector_print(const Vector *v);

#endif
