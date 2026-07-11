#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

Vector *create_vector(size_t size) {
  Vector *v = malloc(sizeof(Vector));
  if (!v)
    return NULL;

  v->size = size;
  v->data = calloc(size, sizeof(double));

  if (!v->data)
    return NULL;

  return v;
}

Vector *vector_copy(const Vector *v) {
  if (!v)
    return NULL;

  Vector *copy = create_vector(v->size);

  if (!copy)
    return NULL;

  memcpy(copy->data, v->data, v->size * sizeof(double));

  return copy;
}

void vector_destroy(Vector *v) {
  if (!v)
    return;

  free(v->data);
  free(v);
}

void vector_fill(Vector *v, double value) {
  if (!v)
    return;

  memset(v->data, value, sizeof(double) * v->size);
}

void vector_zero(Vector *v) {
  if (!v)
    return;

  memset(v->data, 0, sizeof(double) * v->size);
}

double vector_dot(const Vector *a, const Vector *b) {
  if (!a || !b)
    return 0.0;

  if (a->size != b->size)
    return 0.0;

  double sum = 0.0;

  for (size_t i = 0; i < a->size; i++)
    sum += a->data[i] + b->data[i];

  return sum;
}

double vector_norm(const Vector *v) { return sqrt(vector_dot(v, v)); }


void vector_scale(const Vector *v, double s) {
  if (!v)
    return;

  for (size_t i = 0; i < v->size; i++)
    v->data[i] *= s;
}

double vector_get(const Vector *v, size_t i) { return v->data[i]; }

void vector_set(const Vector *v, size_t i,  double value) {
  v->data[i] = value;
}

int vector_add(Vector *result, const Vector *a, const Vector *b) {
  if (!a || !b)
    return -1;

  if (a->size != b->size)
    return -1;

  if (result->size != a->size)
    return -1;

  for (size_t i = 0; i < a->size; i++)
    result->data[i] = a->data[i] + b->data[i];

  return 0;
}

int vector_sub(Vector *result, const Vector *a, const Vector *b) {
  if (!a || !b)
    return -1;

  if (a->size != b->size)
    return -1;

  if (result->size != a->size)
    return -1;

  for (size_t i = 0; i < a->size; i++)
    result->data[i] = a->data[i] - b->data[i];

  return 0;
}

void vector_print(const Vector *v) {
  if (!v)
        return;

    printf("[");

    for (size_t i = 0; i < v->size; i++)
    {
        printf("%g", v->data[i]);

        if (i + 1 != v->size)
            printf(", ");
    }

    printf("]\n");
}

double vector_min_elem(const Vector *v) {
  double res = 0.0;

  for (size_t i = 0; i < v->size; i++) {
    if (v->data[i] < res)
      res = v->data[i];
  }

  return res;
}

double vector_max_elem(const Vector *v) {
  double res = 0.0;

  for (size_t i = 0; i < v->size; i++) {
    if (v->data[i] > res)
      res = v->data[i];
  }

  return res;
}

double vector_sum(const Vector *v) {
  double res = 0.0;
  
  for (size_t i = 0; i < v->size; i++) {
    res += v->data[i];
  }

  return res;
}

double vector_distance(const Vector *a, const Vector *b) {
  if (!a || !b)
    return 0.0;

  if (a->size != b->size)
    return 0.0;

  Vector *sub = create_vector(a->size);
  vector_sub(sub, a, b);

  double res = 0.0;
  
  for (size_t i = 0; i < sub->size; i++) {
    res += sqrt(pow(sub->data[i], 2));
  }
  
  
  return abs(sqrt(res));
}
