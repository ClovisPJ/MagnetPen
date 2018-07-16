#ifndef LSM303C_I2C_H
#define LSM303C_I2C_H

#include <stdint.h>

void lsm303c_begin(uint8_t *dev);
void lsm303c_close();

uint8_t lsm303c_read(uint8_t dev, uint8_t addr, uint8_t reg_addr);
void lsm303c_write(uint8_t dev, uint8_t addr, uint8_t reg_addr, uint8_t data);

#endif
