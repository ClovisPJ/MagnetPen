#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "lsm303c-i2c.h"
#include "lsm303c.h"

void lsm303c_accel_set(uint8_t addr, uint8_t bits, uint8_t val) {
  uint8_t reg = lsm303c_accel_read(addr);
  reg = (reg & (~bits)) | (val & bits);
  lsm303c_accel_write(addr, reg);
}

void lsm303c_mag_set(uint8_t addr, uint8_t bits, uint8_t val) {
  uint8_t reg = lsm303c_mag_read(addr);
  reg = (reg & (~bits)) | (val & bits);
  lsm303c_mag_write(addr, reg);
}

uint8_t lsm303c_accel_get(uint8_t addr, uint8_t bits) {
  return lsm303c_accel_read(addr) & bits;
}

uint8_t lsm303c_mag_get(uint8_t addr, uint8_t bits) {
  return lsm303c_mag_read(addr) & bits;
}

void lsm303c_settings() {
  lsm303c_begin();

//  lsm303c_accel_set(ACC_CTRL_REG4, ACC_CTRL_REG4_SPI, ACC_CTRL_REG4_SPI_RW);
//  lsm303c_accel_set(ACC_CTRL_REG4, ACC_CTRL_REG4_I2C, ACC_CTRL_REG4_I2C_OFF);

  lsm303c_accel_set(ACC_CTRL_REG1, ACC_CTRL_REG1_RES, ACC_CTRL_REG1_RES_LOWRES);
  lsm303c_accel_set(ACC_CTRL_REG1, ACC_CTRL_REG1_ODR, ACC_CTRL_REG1_ODR_100HZ);
  lsm303c_accel_set(ACC_CTRL_REG1, ACC_CTRL_REG1_ZEN, ACC_CTRL_REG1_ZEN_ON);
  lsm303c_accel_set(ACC_CTRL_REG1, ACC_CTRL_REG1_YEN, ACC_CTRL_REG1_YEN_ON);
  lsm303c_accel_set(ACC_CTRL_REG1, ACC_CTRL_REG1_XEN, ACC_CTRL_REG1_XEN_ON);
  lsm303c_accel_set(ACC_CTRL_REG4, ACC_CTRL_REG4_FS, ACC_CTRL_REG4_FS_2G);


//  lsm303c_mag_set(MAG_CTRL_REG3, MAG_CTRL_REG3_I2C, MAG_CTRL_REG3_I2C_ON);
//  lsm303c_mag_set(MAG_CTRL_REG3, MAG_CTRL_REG3_SPI, MAG_CTRL_REG3_SPI_RW);

  lsm303c_mag_set(MAG_CTRL_REG1, MAG_CTRL_REG1_XYOM, MAG_CTRL_REG1_XYOM_HIGH);
  lsm303c_mag_set(MAG_CTRL_REG1, MAG_CTRL_REG1_TEMP, MAG_CTRL_REG1_TEMP_ON);
  lsm303c_mag_set(MAG_CTRL_REG2, MAG_CTRL_REG2_FS, MAG_CTRL_REG2_FS_16G);
  lsm303c_mag_set(MAG_CTRL_REG3, MAG_CTRL_REG3_MODE, MAG_CTRL_REG3_MODE_CONT);
  lsm303c_mag_set(MAG_CTRL_REG4, MAG_CTRL_REG4_ZOM, MAG_CTRL_REG4_ZOM_HIGH);
}

struct vector* lsm303c_accel_sample() {
  struct vector* accel = malloc(sizeof(struct vector));

  while ( lsm303c_accel_get(ACC_STATUS, ACC_STATUS_ZDA) == 0 ||
          lsm303c_accel_get(ACC_STATUS, ACC_STATUS_YDA) == 0 ||
          lsm303c_accel_get(ACC_STATUS, ACC_STATUS_XDA) == 0    ) {; }

  accel->x = (uint16_t)( (lsm303c_accel_read(ACC_OUT_X_H) << 8) | lsm303c_accel_read(ACC_OUT_X_L) ) * SENSITIVITY_ACC;
  accel->y = (uint16_t)( (lsm303c_accel_read(ACC_OUT_Y_H) << 8) | lsm303c_accel_read(ACC_OUT_Y_L) ) * SENSITIVITY_ACC;
  accel->z = (uint16_t)( (lsm303c_accel_read(ACC_OUT_Z_H) << 8) | lsm303c_accel_read(ACC_OUT_Z_L) ) * SENSITIVITY_ACC;
  return accel;
}

struct vector* lsm303c_mag_sample() {
  struct vector* mag = malloc(sizeof(struct vector));

  while ( lsm303c_mag_get(MAG_STATUS, MAG_STATUS_ZDA) == 0 ||
          lsm303c_mag_get(MAG_STATUS, MAG_STATUS_YDA) == 0 ||
          lsm303c_mag_get(MAG_STATUS, MAG_STATUS_XDA) == 0    ) {; }

  mag->x = (uint16_t)( (lsm303c_mag_read(MAG_OUT_X_H) << 8) | lsm303c_mag_read(MAG_OUT_X_L) ) * SENSITIVITY_MAG;
  mag->y = (uint16_t)( (lsm303c_mag_read(MAG_OUT_Y_H) << 8) | lsm303c_mag_read(MAG_OUT_Y_L) ) * SENSITIVITY_MAG;
  mag->z = (uint16_t)( (lsm303c_mag_read(MAG_OUT_Z_H) << 8) | lsm303c_mag_read(MAG_OUT_Z_L) ) * SENSITIVITY_MAG;
  return mag;
}

float lsm303c_mag_temp_sample() {
  float temp = (float)( (lsm303c_mag_read(MAG_TEMP_H) << 8) | lsm303c_mag_read(MAG_TEMP_L) );
  temp /= 8;
  temp += 25;
  return temp;
}
