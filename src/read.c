#include <stdio.h>
#include <stdlib.h>

#include <bcm2835.h>
#include <vector.h>
#include "lsm303c/lsm303c.h"

int main () {
  uint8_t *dev = malloc(1);
  dev[0] = RPI_BPLUS_GPIO_J8_11;
  dev[1] = RPI_BPLUS_GPIO_J8_13;
  dev[2] = RPI_BPLUS_GPIO_J8_15;
  dev[3] = RPI_BPLUS_GPIO_J8_16;
  dev[4] = '\0';
  lsm303c_settings(dev);

  while (1) {
    vector* vec1 = lsm303c_mag_sample(dev[0]);
    vector* vec2 = lsm303c_mag_sample(dev[1]);
    vector* vec3 = lsm303c_mag_sample(dev[2]);
    vector* vec4 = lsm303c_mag_sample(dev[3]);

    vector* avg = malloc(sizeof(vector));
    vector* vec1_diff = malloc(sizeof(vector));
    vector* vec2_diff = malloc(sizeof(vector));
    vector* vec3_diff = malloc(sizeof(vector));
    vector* vec4_diff = malloc(sizeof(vector));
    vector* pos_vec = malloc(sizeof(vector));
    power3(vec1);
    power3(vec2);
    power3(vec3);
    power3(vec4);
    add4(avg, vec1, vec2, vec3, vec4);
    root3(avg);
    scale(avg, 0.25f);
    sub(vec1_diff, vec1, avg);
    sub(vec2_diff, vec2, avg);
    sub(vec3_diff, vec3, avg);
    sub(vec4_diff, vec4, avg);
    add4(pos_vec, vec1_diff, vec2_diff, vec3_diff, vec4_diff);

    print(pos_vec);

    free(vec1);
    free(vec2);
    free(vec3);
    free(vec4);
    free(avg)
    free(vec1_diff)
    free(vec2_diff)
    free(vec3_diff)
    free(vec4_diff)
    free(pos_vec)
  }
}
