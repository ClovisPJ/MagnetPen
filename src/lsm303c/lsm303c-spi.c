#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <bcm2835.h>
#include "lsm303c-spi.h"

void lsm303c_begin() {
  if (!bcm2835_init()) {
    printf("bcm2835_init failed. Are you running as root??\n");
    return;
  }
  if (!bcm2835_spi_begin()) {
    printf("bcm2835_spi_begin failed. Are you running as root??\n");
  }
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);      // the default

  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  // CS0 is ACC
  // CS1 is MAG
}

void lsm303c_close() {
  bcm2835_spi_end();
  bcm2835_close();
}

uint8_t lsm303c_read(uint8_t addr) {
  char *buf = malloc(2);
  *buf = addr | 0b10000000;
  *(buf+1) = 0xFF;
  bcm2835_spi_transfern(buf, 2);
  uint8_t val = *(buf+1);
  free(buf);
  return val;
}

void lsm303c_write(uint8_t addr, uint8_t val) {
  char *buf = malloc(2);
  *buf = addr & 0b01111111;
  *(buf+1) = val;
  bcm2835_spi_writenb(buf, 2);
  free(buf);
}

void lsm303c_accel_write(uint8_t addr, uint8_t val) {
  bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
  lsm303c_write(addr, val);
}

uint8_t lsm303c_accel_read(uint8_t addr) {
  bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
  return lsm303c_read(addr);
}

void lsm303c_mag_write(uint8_t addr, uint8_t val) {
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  lsm303c_write(addr, val);
}

uint8_t lsm303c_mag_read(uint8_t addr) {
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  return lsm303c_read(addr);
}
