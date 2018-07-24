#include <stdio.h>
#include <stdlib.h>

#include <bcm2835.h>
#include <vector.h>
#include "lsm303c/lsm303c.h"

int main () {
  uint8_t *dev = malloc(5);
  dev[0] = RPI_BPLUS_GPIO_J8_11;
  dev[1] = RPI_BPLUS_GPIO_J8_13;
  dev[2] = RPI_BPLUS_GPIO_J8_15;
  dev[3] = RPI_BPLUS_GPIO_J8_16;
  dev[4] = '\0';
  lsm303c_settings(dev);

  float smoothing = 0.025;

  vector* avg;
  vector* pos_vec;

  vector** vec_raw = malloc(4 * sizeof(vector*));
  vector** vec_temp = malloc(4 * sizeof(vector*));
  vector** vec_smooth = malloc(4 * sizeof(vector*));

  while (1) {

    // DATA COLLECTION

    vec_raw[0] = lsm303c_mag_sample(dev[0]);
    vec_raw[1] = lsm303c_mag_sample(dev[1]);
    vec_raw[2] = lsm303c_mag_sample(dev[2]);
    vec_raw[3] = lsm303c_mag_sample(dev[3]);
    
    // LOW PASS FILTER

    if (vec_smooth[0] == NULL) {
      vec_smooth[0] = copy(vec_raw[0]);
      vec_smooth[1] = copy(vec_raw[1]);
      vec_smooth[2] = copy(vec_raw[2]);
      vec_smooth[3] = copy(vec_raw[3]);
    }

    vec_temp[0] = scale ( sub(vec_smooth[0], vec_raw[0]), smoothing);
    vec_temp[1] = scale ( sub(vec_smooth[1], vec_raw[1]), smoothing);
    vec_temp[2] = scale ( sub(vec_smooth[2], vec_raw[2]), smoothing);
    vec_temp[3] = scale ( sub(vec_smooth[3], vec_raw[3]), smoothing);
    vec_smooth[0] = sub(vec_smooth[0], vec_temp[0]);
    vec_smooth[1] = sub(vec_smooth[1], vec_temp[1]);
    vec_smooth[2] = sub(vec_smooth[2], vec_temp[2]);
    vec_smooth[3] = sub(vec_smooth[3], vec_temp[3]);
    free(vec_raw[0]);
    free(vec_raw[1]);
    free(vec_raw[2]);
    free(vec_raw[3]);
    free(vec_temp[0]);
    free(vec_temp[1]);
    free(vec_temp[2]);
    free(vec_temp[3]);
    vec_temp[0] = copy(vec_smooth[0]);
    vec_temp[1] = copy(vec_smooth[1]);
    vec_temp[2] = copy(vec_smooth[2]);
    vec_temp[3] = copy(vec_smooth[3]);

    /* LOW PASS FILTERED DATA
    print(vec_smooth[0]);
    print(vec_smooth[1]);
    print(vec_smooth[2]);
    print(vec_smooth[3]);
    */

    // POSITION CALCULATION

    avg = scale( root3( add(4, power3(vec_temp[0]), power3(vec_temp[1]), power3(vec_temp[2]), power3(vec_temp[3]))) , 0.25f);
    vector **vec_diff = malloc(4 * sizeof(vector*));
    // NB vec_temp's have been cubed
    vec_diff[0] = sub(vec_temp[0], avg);
    vec_diff[1] = sub(vec_temp[1], avg);
    vec_diff[2] = sub(vec_temp[2], avg);
    vec_diff[3] = sub(vec_temp[3], avg);
    free(avg);
    pos_vec = add(4, vec_diff[0], vec_diff[1], vec_diff[2], vec_diff[3]);
    free(vec_diff[0]);
    free(vec_diff[1]);
    free(vec_diff[2]);
    free(vec_diff[3]);

    print(pos_vec);
    
    free(pos_vec);

  }
  free(vec_smooth[0]);
  free(vec_smooth[1]);
  free(vec_smooth[2]);
  free(vec_smooth[3]);
  free(dev);
}
