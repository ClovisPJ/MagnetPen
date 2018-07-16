#include <stdio.h>
#include <stdlib.h>

#include "lsm303c/lsm303c.h"
#include <bcm2835.h>

int main () {
  uint8_t *dev = malloc(4);
  dev[0] = RPI_BPLUS_GPIO_J8_11;
  dev[1] = RPI_BPLUS_GPIO_J8_13;
  dev[2] = RPI_BPLUS_GPIO_J8_15;
  dev[3] = RPI_BPLUS_GPIO_J8_16;
  dev[4] = '\0';
  lsm303c_settings(dev);
  while (1) {
    struct vector* vec1 = lsm303c_accel_sample(dev[0]);
    struct vector* vec2 = lsm303c_mag_sample(dev[0]);
    printf("[%f, %f, %f]\n", vec1->x, vec1->y, vec1->z);
    printf("                                 [%f, %f, %f]\n", vec2->x, vec2->y, vec2->z);
    free(vec1);
    free(vec2);
    usleep(100000);
  }
}

