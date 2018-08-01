#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <bcm2835.h>
#include <vector.h>
#include "lsm303c/lsm303c.h"

#define ALPHA 0.025

float ***calib(void);

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

  float ***calib_data = calib();

  while (1) {

    for (int i = 0; dev[i] != '\0'; i++) {

      vec_raw[i] = lsm303c_mag_sample(dev[i]);
      //print(vec_raw[i]);

      vec_cal[i] = new();
      vec_smooth[i] = new();

      vec_raw[i]->x -= calib_data[i][0][0];
      vec_raw[i]->y -= calib_data[i][1][0];
      vec_raw[i]->z -= calib_data[i][2][0];
      vec_cal[i]->x = calib_data[i][0][1]*vec_raw[i]->x + calib_data[i][0][2]*vec_raw[i]->y + calib_data[i][0][3]*vec_raw[i]->z;
      vec_cal[i]->y = calib_data[i][1][1]*vec_raw[i]->x + calib_data[i][1][2]*vec_raw[i]->y + calib_data[i][1][3]*vec_raw[i]->z;
      vec_cal[i]->z = calib_data[i][2][1]*vec_raw[i]->x + calib_data[i][2][2]*vec_raw[i]->y + calib_data[i][2][3]*vec_raw[i]->z;
      float norm = sqrt(vec_cal[i]->x*vec_cal[i]->x + vec_cal[i]->y*vec_cal[i]->y + vec_cal[i]->z*vec_cal[i]->z);
      vec_cal[i]->x /= norm;
      vec_cal[i]->y /= norm;
      vec_cal[i]->z /= norm;
      vec_cal[i]->y *= -1;
      vec_cal[i]->z *= -1;

      vec_smooth[i]->x = vec_cal[i]->x * ALPHA + (vec_smooth[i]->x * (1 - ALPHA));
      vec_smooth[i]->y = vec_cal[i]->y * ALPHA + (vec_smooth[i]->y * (1 - ALPHA));
      vec_smooth[i]->z = vec_cal[i]->z * ALPHA + (vec_smooth[i]->z * (1 - ALPHA));

      print(vec_smooth[i]);
      printf("      ");

      free(vec_raw[i]);
      free(vec_cal[i]);
      free(vec_smooth[i]);
    }
    printf("\n");
  }
  free(dev);
}

float ***calib(void) {

  float ***calib_data;
  calib_data = malloc(4 * sizeof(*calib_data));
  for (int i = 0; i < 4; i++) {
    calib_data[i] = malloc(3 * sizeof(**calib_data));
    for (int j = 0; j < 3; j++) {
      calib_data[i][j] = malloc(4 * sizeof(***calib_data));
    }
  }
  calib_data[0][0][0] = -0.558741;
  calib_data[0][0][1] = 1.861665;
  calib_data[0][0][2] = 0.040568;
  calib_data[0][0][3] = 0.041919;
  calib_data[0][1][0] = 0.159977;
  calib_data[0][1][1] = 0.040568;
  calib_data[0][1][2] = 1.803733;
  calib_data[0][1][3] = 0.011467;
  calib_data[0][2][0] = 0.325079;
  calib_data[0][2][1] = 0.041919;
  calib_data[0][2][2] = 0.011467;
  calib_data[0][2][3] = 1.852330;

  calib_data[1][0][0] = -0.557650;
  calib_data[1][0][1] = 1.817609;
  calib_data[1][0][2] = 0.030680;
  calib_data[1][0][3] = 0.031854;
  calib_data[1][1][0] = 0.168439;
  calib_data[1][1][1] = 0.030680;
  calib_data[1][1][2] = 1.746731;
  calib_data[1][1][3] = 0.024925;
  calib_data[1][2][0] = 0.323114;
  calib_data[1][2][1] = 0.031854;
  calib_data[1][2][2] = 0.024925;
  calib_data[1][2][3] = 1.863000;

  calib_data[2][0][0] = -0.549185;
  calib_data[2][0][1] = 1.762639;
  calib_data[2][0][2] = 0.007462;
  calib_data[2][0][3] = -0.022670;
  calib_data[2][1][0] = 0.161929;
  calib_data[2][1][1] = 0.007462;
  calib_data[2][1][2] = 1.705247;
  calib_data[2][1][3] = -0.006544;
  calib_data[2][2][0] = 0.315190;
  calib_data[2][2][1] = -0.022670;
  calib_data[2][2][2] = -0.006544;
  calib_data[2][2][3] = 1.835400;

  calib_data[3][0][0] = 0.053485;
  calib_data[3][0][1] = 1.387425;
  calib_data[3][0][2] = 0.007230;
  calib_data[3][0][3] = 0.025192;
  calib_data[3][1][0] = 0.155217;
  calib_data[3][1][1] = 0.007230;
  calib_data[3][1][2] = 1.348098;
  calib_data[3][1][3] = 0.006040;
  calib_data[3][2][0] = 0.602069;
  calib_data[3][2][1] = 0.025192;
  calib_data[3][2][2] = 0.006040;
  calib_data[3][2][3] = 1.494375;
  return calib_data;
}
