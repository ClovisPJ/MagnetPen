#include <stdio.h>
#include <stdlib.h>

#include <bcm2835.h>
#include <vector.h>
#include "lsm303c/lsm303c.h"

#define ALPHA 0.025

int main () {
  uint8_t *dev = malloc(5);
  dev[0] = RPI_BPLUS_GPIO_J8_11;
  dev[1] = RPI_BPLUS_GPIO_J8_13;
  dev[2] = RPI_BPLUS_GPIO_J8_15;
  dev[3] = RPI_BPLUS_GPIO_J8_16;
  dev[4] = '\0';
  lsm303c_settings(dev);

  vector** vec_raw = malloc(4 * sizeof(vector*));
  vector** vec_cal = malloc(4 * sizeof(vector*));
  vector** vec_smooth = malloc(4 * sizeof(vector*));

  while (1) {

    for (int i = 0; dev[i] != '\0'; i++) {
      // DATA COLLECTION
      vec_raw[i] = lsm303c_mag_sample(dev[i]);

      // CALIBRATE
      vec_cal[i] = new();
      vec_smooth[i] = new();

      vec_raw[i]->x =* 100000/1100;  vec_raw[i]->x =- 617.106577;
      vec_raw[i]->y =* 100000/1100;  vec_raw[i]->y =- 3724.617984;
      vec_raw[i]->z =* 100000/980;   vec_raw[i]->z =- 16432.772031;
      vec_cal[i]->x = 0.982945*vec_raw[i]->x + 0.012083*vec_raw[i]->y + 0.014055*vec_raw[i]->z;
      vec_cal[i]->y = 0.012083*vec_raw[i]->x + 0.964757*vec_raw[i]->y + 0.001436*vec_raw[i]->z;
      vec_cal[i]->z = 0.014055*vec_raw[i]->x + 0.001436*vec_raw[i]->y + 0.952889*vec_raw[i]->z;
      float norm = sqrt(vec_cal[i]->x*vec_cal[i]->x + vec_cal[i]->y*vec_cal[i]->y + vec_cal[i]->z*vec_cal[i]->z);
      vec_cal[i]->x /= norm;
      vec_cal[i]->y /= norm;
      vec_cal[i]->z /= norm;
      vec_cal[i]->y *= -1;
      vec_cal[i]->z *= -1;

      vec_smooth[i]->x = vec_cal[i]->x * ALPHA + (vec_smooth[i]->x * (1 - ALPHA));
      vec_smooth[i]->y = vec_cal[i]->y * ALPHA + (vec_smooth[i]->y * (1 - ALPHA));
      vec_smooth[i]->z = vec_cal[i]->z * ALPHA + (vec_smooth[i]->z * (1 - ALPHA));

      // PRINT
      print(vec_smooth[i]);

      // FREE
      free(vec_raw[i]);
      free(vec_cal[i]);
      free(vec_smooth[i]);
    }

  }
  free(dev);
}
