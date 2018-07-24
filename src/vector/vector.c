#include <stdio.h>
#include <math.h>

#include "vector.h"

void add (vector *vec, vector *vec1, vector *vec2) {
  vec->x = vec1->x + vec2->x;
  vec->y = vec1->y + vec2->y;
  vec->z = vec1->z + vec2->z;
}

void add4 (vector *vec, vector *vec1, vector *vec2, vector *vec3, vector *vec4) {
  vec->x = vec1->x + vec2->x + vec3->x + vec4->x;
  vec->y = vec1->y + vec2->y + vec3->y + vec4->y;
  vec->z = vec1->z + vec2->z + vec3->z + vec4->z;
}

void sub (vector *vec, vector *vec1, vector *vec2) {
  vec->x = vec1->x - vec2->x;
  vec->y = vec1->y - vec2->y;
  vec->z = vec1->z - vec2->z;
}

void scale (vector *vec1, float scale) {
  vec1->x = vec1->x * scale;
  vec1->y = vec1->y * scale;
  vec1->z = vec1->z * scale;
}

void power2 (vector *vec1) {
  vec1->x = vec1->x * vec1->x;
  vec1->y = vec1->y * vec1->y;
  vec1->z = vec1->z * vec1->z;
}

void root2 (vector *vec1) {
  vec1->x = sqrt(vec1->x);
  vec1->y = sqrt(vec1->y);
  vec1->z = sqrt(vec1->z);
}

void power3 (vector *vec1) {
  vec1->x = vec1->x * vec1->x * vec1->x;
  vec1->y = vec1->y * vec1->y * vec1->y;
  vec1->z = vec1->z * vec1->z * vec1->z;
}

void root3 (vector *vec1) {
  vec1->x = cbrt(vec1->x);
  vec1->y = cbrt(vec1->y);
  vec1->z = cbrt(vec1->z);
}

void print (vector *vec1) {
  printf("[%f.6, %f.6, %f.6]\n", vec1->x, vec1->y, vec1->z);
}
