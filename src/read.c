#include <stdio.h>
#include <stdlib.h>
#include "lsm303c/lsm303c.h"

int main () {
  lsm303c_settings();
  while (1) {
    struct vector* vec1 = lsm303c_accel_sample();
    struct vector* vec2 = lsm303c_mag_sample();
    printf("[%d, %d, %d]      ", vec1->x, vec1->y, vec1->z);
    printf("[%d, %d, %d]\n", vec2->x, vec2->y, vec2->z);
    free(vec1);
    free(vec2);
    usleep(1000);
  }
}

