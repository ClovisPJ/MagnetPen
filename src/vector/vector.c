#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include "vector.h"

vector *new () {
  return malloc(sizeof(vector));
}
/*
vector *add (vector *vec1, vector *vec2) {
  vector *vec = new();
  vec->x = vec1->x + vec2->x;
  vec->y = vec1->y + vec2->y;
  vec->z = vec1->z + vec2->z;
}*/

vector* add (int count, ...) {
  va_list args;
  va_start(args, count);
  vector *sum = new();
  vector *arg_vec;
  for (int i = 0; i < count; i++) {
    arg_vec = va_arg(args, vector*);
    sum->x += arg_vec->x;
    sum->y += arg_vec->y;
    sum->z += arg_vec->z;
  }
  va_end(args);
  return sum;
}

vector *sub (vector *vec1, vector *vec2) {
  vector *vec = new();
  vec->x = vec1->x - vec2->x;
  vec->y = vec1->y - vec2->y;
  vec->z = vec1->z - vec2->z;
}

vector *scale (vector *vec1, float scale) {
  vec1->x = vec1->x * scale;
  vec1->y = vec1->y * scale;
  vec1->z = vec1->z * scale;
  return vec1;
}

vector *power2 (vector *vec1) {
  vec1->x = vec1->x * vec1->x;
  vec1->y = vec1->y * vec1->y;
  vec1->z = vec1->z * vec1->z;
  return vec1;
}

vector *root2 (vector *vec1) {
  vec1->x = sqrt(vec1->x);
  vec1->y = sqrt(vec1->y);
  vec1->z = sqrt(vec1->z);
  return vec1;
}

vector *power3 (vector *vec1) {
  vec1->x = vec1->x * vec1->x * vec1->x;
  vec1->y = vec1->y * vec1->y * vec1->y;
  vec1->z = vec1->z * vec1->z * vec1->z;
  return vec1;
}

vector *root3 (vector *vec1) {
  vec1->x = cbrt(vec1->x);
  vec1->y = cbrt(vec1->y);
  vec1->z = cbrt(vec1->z);
  return vec1;
}

vector *copy(vector *vec1) {
  vector *vec = new();
  vec->x = vec1->x;
  vec->y = vec1->y;
  vec->z = vec1->z;
  return vec;
}

void print (vector *vec1) {
  printf("[%.3f, %.3f, %.3f]\n", vec1->x, vec1->y, vec1->z);
}
