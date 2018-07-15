#ifndef LSM303C_H
#define LSM303C_H

#include <stdint.h>

void lsm303c_begin();
void lsm303c_close();
uint8_t bcm2835_i2c_read(uint8_t addr, uint8_t subaddr);
void bcm2835_i2c_write(uint8_t addr, uint8_t subaddr, uint8_t data);

#endif
