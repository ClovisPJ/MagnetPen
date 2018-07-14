#include <stdio.h>
#include "lsm303c/lsm303c.h"

int main () {
  lsm303c_begin();
  lsm303c_settings();
  printf("%f\n", lsm303c_mag_temp_sample());
}
