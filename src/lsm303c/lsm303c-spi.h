#ifndef LSM303C_SPI_H
#define LSM303C_SPI_H

#include <stdint.h>

void lsm303c_begin();
void lsm303c_close();

uint8_t lsm303c_read(uint8_t addr);
void lsm303c_write(uint8_t addr, uint8_t val);

void lsm303c_accel_write(uint8_t addr, uint8_t val);
uint8_t lsm303c_accel_read(uint8_t addr);
void lsm303c_mag_write(uint8_t addr, uint8_t val);
uint8_t lsm303c_mag_read(uint8_t addr);

#endif
