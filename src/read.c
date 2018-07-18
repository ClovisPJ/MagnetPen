#include <stdio.h>
#include <stdlib.h>

#include "lsm303c/lsm303c.h"
#include <bcm2835.h>

int main () {
  uint8_t *dev = malloc(1);
  dev[0] = RPI_BPLUS_GPIO_J8_11;
  dev[1] = '\0';
  lsm303c_settings(dev);
  while (1) {
    struct vector* vec = lsm303c_mag_sample(dev[0]);
    printf("[%f, %f, %f]\n", vec->x, vec->y, vec->z);
    free(vec);
    usleep(100000);
  }
}
