#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector {
  float x;
  float y;
  float z;
} vector;

vector *new ();
vector *add (int count, ...);
vector *sub (vector *vec1, vector *vec2);
vector *scale (vector *vec1, float scale);
vector *power2 (vector *vec1);
vector *root2 (vector *vec1);
vector *power3 (vector *vec1);
vector *root3 (vector *vec1);
vector *copy(vector *vec1);
void print (vector *vec1);

#endif
