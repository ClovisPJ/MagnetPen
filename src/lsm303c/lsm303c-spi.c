#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <bcm2835.h>
#include "lsm303c-spi.h"

void lsm303c_begin(uint8_t *dev) {
  if (!bcm2835_init()) {
    printf("bcm2835_init failed. Are you running as root??\n");
    return;
  }
  if (!bcm2835_spi_begin()) {
    printf("bcm2835_spi_begin failed. Are you running as root??\n");
    return;
  }
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);                   // The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
  //bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
  //bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
  for (int i = 0; dev[i] != '\0'; i++) {
    bcm2835_gpio_fsel(*dev, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(*dev, HIGH);
  }
}

void lsm303c_close() {
  bcm2835_spi_end();
  bcm2835_close();
}

uint8_t lsm303c_read(uint8_t dev, uint8_t addr, uint8_t reg_addr) {
  char *buf = malloc(2);
  *buf = reg_addr | 0b10000000;
  *(buf+1) = 0xFF;
  bcm2835_gpio_write(dev, LOW);
  bcm2835_spi_transfern(buf, 2);
  bcm2835_gpio_write(dev, HIGH);
  uint8_t val = *(buf+1);
  free(buf);
  return val;
}

void lsm303c_write(uint8_t dev, uint8_t addr, uint8_t reg_addr, uint8_t data) {
  char *buf = malloc(2);
  *buf = reg_addr & 0b01111111;
  *(buf+1) = data;
  bcm2835_gpio_write(dev, LOW);
  bcm2835_spi_writenb(buf, 2);
  bcm2835_gpio_write(dev, HIGH);
  free(buf);
}
