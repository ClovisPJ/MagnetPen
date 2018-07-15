#include <stdio.h>
#include <stdlib.h>
#include "lsm303c/lsm303c.h"

int main () {
  lsm303c_settings();
  printf("%f\n", lsm303c_mag_temp_sample());
  struct vector* vec = lsm303c_accel_sample();
  printf("[%d, %d, %d]", vec->x, vec->y, vec->z);
  free(vec);
}
