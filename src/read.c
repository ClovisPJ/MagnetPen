#include <stdio.h>
#include "lsm303c/lsm303c-i2c.h"

int main () {
  lsm303c_begin();
  //lsm303c_settings();
  //printf("%f\n", lsm303c_mag_temp_sample());
  bcm2835_i2c_write(0b00111010, 0x20, 0);
}
