#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <bcm2835.h>
#include "lsm303c-i2c.h"

void lsm303c_begin(uint8_t *dev) {
  if (!bcm2835_init()) {
    printf("bcm2835_init failed. Are you running as root??\n");
    return;
  }
  if (!bcm2835_i2c_begin()) {
    printf("bcm2835_i2c_begin failed. Are you running as root??\n");
    return;
  }
  bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_2500);
  for (int i = 0; dev[i] != '\0'; i++) {
    bcm2835_gpio_fsel(*dev, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(*dev, LOW);
  }
}

void lsm303c_close() {
  bcm2835_i2c_end();
  bcm2835_close();
}

uint8_t lsm303c_read(uint8_t dev, uint8_t addr, uint8_t reg_addr) {
  bcm2835_i2c_setSlaveAddress(addr);
  uint8_t *buffer = malloc(1);
  bcm2835_gpio_write(dev, HIGH);
  bcm2835_i2c_read_register_rs(&reg_addr, buffer, 1);
  bcm2835_gpio_write(dev, LOW);
  uint8_t val = *buffer;
  free(buffer);
  return val;
}

void lsm303c_write(uint8_t dev, uint8_t addr, uint8_t reg_addr, uint8_t data) {
  bcm2835_i2c_setSlaveAddress(addr);
  uint8_t *buffer = malloc(2);
  *buffer = reg_addr;
  *(buffer+1) = data;
  bcm2835_gpio_write(dev, HIGH);
  bcm2835_i2c_write(buffer, 2);
  bcm2835_gpio_write(dev, LOW);
  free(buffer);
}
