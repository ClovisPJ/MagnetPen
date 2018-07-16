#ifndef LSM303C_H
#define LSM303C_H

#include <stdint.h>

#define SENSITIVITY_ACC 0.06103515625   // LSB/mg
#define SENSITIVITY_MAG 0.00048828125   // LSB/Ga

struct vector {
  float x;
  float y;
  float z;
};

#define ACC                                  0x1d

#define ACC_CTRL_REG1                        0x20
  #define ACC_CTRL_REG1_RES                  0b10000000
    #define ACC_CTRL_REG1_RES_HIGHRES        0b00000000
    #define ACC_CTRL_REG1_RES_LOWRES         0b10000000
  #define ACC_CTRL_REG1_ODR                  0b01110000
    #define ACC_CTRL_REG1_ODR_OFF            0b00000000
    #define ACC_CTRL_REG1_ODR_10HZ           0b00010000
    #define ACC_CTRL_REG1_ODR_50HZ           0b00100000
    #define ACC_CTRL_REG1_ODR_100HZ          0b00110000
    #define ACC_CTRL_REG1_ODR_200HZ          0b01000000
    #define ACC_CTRL_REG1_ODR_400HZ          0b01010000
    #define ACC_CTRL_REG1_ODR_800HZ          0b01100000
  #define ACC_CTRL_REG1_BDU                  0b00001000
    #define ACC_CTRL_REG1_BDU_CONT           0
    #define ACC_CTRL_REG1_BDU_DISC           0b00001000
  #define ACC_CTRL_REG1_ZEN                  0b00000100
    #define ACC_CTRL_REG1_ZEN_ON             0b00000100
    #define ACC_CTRL_REG1_ZEN_OFF            0
  #define ACC_CTRL_REG1_YEN                  0b00000010
    #define ACC_CTRL_REG1_YEN_ON             0b00000010
    #define ACC_CTRL_REG1_YEN_OFF            0
  #define ACC_CTRL_REG1_XEN                  0b00000001
    #define ACC_CTRL_REG1_XEN_ON             0b00000001
    #define ACC_CTRL_REG1_XEN_OFF            0
#define ACC_CTRL_REG4                        0x23
  #define ACC_CTRL_REG4_FS                   0b00110000
    #define ACC_CTRL_REG4_FS_2G              0b00000000
    #define ACC_CTRL_REG4_FS_4G              0b00100000
    #define ACC_CTRL_REG4_FS_8G              0b00110000
  #define ACC_CTRL_REG4_I2C                  0b00000010
    #define ACC_CTRL_REG4_I2C_ON             0
    #define ACC_CTRL_REG4_I2C_OFF            0b00000010
  #define ACC_CTRL_REG4_SPI                  0b00000001
    #define ACC_CTRL_REG4_SPI_W              0b00000000
    #define ACC_CTRL_REG4_SPI_RW             0b00000001

#define ACC_OUT_X_L                          0x28
#define ACC_OUT_X_H                          0x29
#define ACC_OUT_Y_L                          0x2A
#define ACC_OUT_Y_H                          0x2B
#define ACC_OUT_Z_L                          0x2C
#define ACC_OUT_Z_H                          0x2D
#define ACC_STATUS                           0x27
  #define ACC_STATUS_ZDA                     0b00000100
  #define ACC_STATUS_YDA                     0b00000010
  #define ACC_STATUS_XDA                     0b00000001


#define MAG                                  0x1e

#define MAG_CTRL_REG1                        0x20
  #define MAG_CTRL_REG1_XYOM                 0b01100000
    #define MAG_CTRL_REG1_XYOM_LOW           0b00000000
    #define MAG_CTRL_REG1_XYOM_MED           0b00100000
    #define MAG_CTRL_REG1_XYOM_HIGH          0b01000000
    #define MAG_CTRL_REG1_XYOM_ULTRA         0b01100000
  #define MAG_CTRL_REG1_TEMP                 0b10000000
    #define MAG_CTRL_REG1_TEMP_ON            0b00000000
    #define MAG_CTRL_REG1_TEMP_OFF           0b10000000
#define MAG_CTRL_REG2                        0x21
  #define MAG_CTRL_REG2_FS                   0b01100000
    #define MAG_CTRL_REG2_FS_16G             0b01100000
#define MAG_CTRL_REG3                        0x22
  #define MAG_CTRL_REG3_I2C                  0b10000000
    #define MAG_CTRL_REG3_I2C_ON             0
    #define MAG_CTRL_REG3_I2C_OFF            0b10000000
  #define MAG_CTRL_REG3_SPI                  0b00000100
    #define MAG_CTRL_REG3_SPI_W              0b00000000
    #define MAG_CTRL_REG3_SPI_RW             0b00000100
  #define MAG_CTRL_REG3_MODE                 0b00000011
    #define MAG_CTRL_REG3_MODE_CONT          0b00000000
    #define MAG_CTRL_REG3_MODE_SING          0b00000001
    #define MAG_CTRL_REG3_MODE_OFF           0b00000010
    #define MAG_CTRL_REG3_MODE_OFF_ALT       0b00000011
#define MAG_CTRL_REG4                        0x23
  #define MAG_CTRL_REG4_ZOM                  0b00001100
    #define MAG_CTRL_REG4_ZOM_LOW            0b00000000
    #define MAG_CTRL_REG4_ZOM_MED            0b00000100
    #define MAG_CTRL_REG4_ZOM_HIGH           0b00001000
    #define MAG_CTRL_REG4_ZOM_ULTRA          0b00001100

#define MAG_OUT_X_L                          0x28
#define MAG_OUT_X_H                          0x29
#define MAG_OUT_Y_L                          0x2A
#define MAG_OUT_Y_H                          0x2B
#define MAG_OUT_Z_L                          0x2C
#define MAG_OUT_Z_H                          0x2D
#define MAG_TEMP_L                           0x2E
#define MAG_TEMP_H                           0x2F
#define MAG_STATUS                           0x27
  #define MAG_STATUS_ZDA                     0b00000100
  #define MAG_STATUS_YDA                     0b00000010
  #define MAG_STATUS_XDA                     0b00000001

void lsm303c_set(uint8_t dev, uint8_t addr, uint8_t reg_addr, uint8_t bits, uint8_t val);
uint8_t lsm303c_get(uint8_t dev, uint8_t addr, uint8_t reg_addr, uint8_t bits);

void lsm303c_settings(uint8_t *dev);
struct vector* lsm303c_accel_sample(uint8_t dev);
struct vector* lsm303c_mag_sample(uint8_t dev);
float lsm303c_mag_temp_sample(uint8_t dev);

#endif
