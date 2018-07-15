#include <stdio.h>
#include <stdint.h>

#include <bcm2835.h>

#include "lsm303c-i2c.h"

void lsm303c_begin() {
  if (!bcm2835_init()) {
    printf("bcm2835_init failed. Are you running as root??\n");
    return;
  }
  if (!bcm2835_i2c_begin()) {
    printf("bcm2835_i2c_begin failed. Are you running as root??\n");
    return;
  }
  bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_2500);
}

void lsm303c_close() {
  bcm2835_i2c_end();
  bcm2835_close();
}

uint8_t bcm2835_i2c_read(uint8_t addr, uint8_t subaddr) {
  bcm2835_i2c_setSlaveAddress(addr);
  bcm2835_i2c_write(&subaddr, 1);
  return;
}

void bcm2835_i2c_write(uint8_t addr, uint8_t subaddr, uint8_t data) {
  bcm2835_i2c_setSlaveAddress(addr);
  bcm2835_i2c_write(&subaddr, 1);
  bcm2835_i2c_write(&data, 1);
}
