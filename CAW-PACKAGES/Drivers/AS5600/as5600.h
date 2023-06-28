#ifndef __AS5600_H__
#define __AS5600_H__

#include <stdbool.h>
#include <stdint.h>

#include "i2c.h"

#define AS5600_RAW_ADDR 0x36
#define AS5600_ADDR (AS5600_RAW_ADDR << 1)
#define AS5600_WRITE_ADDR (AS5600_RAW_ADDR << 1)
#define AS5600_READ_ADDR ((AS5600_RAW_ADDR << 1) | 1)
#define AS5600_RAW_ANGLE_REGISTER 0x0C

#define AS5600_RESOLUTION 4096  // 12bit Resolution

typedef struct {
  I2C_HandleTypeDef *i2c_ins;
  float prev_angle;
  unsigned long prev_angle_ts;
  float rotation_offset;

  float vel_rotation_offset;        // 计算速度使用的圈数累加
  float vel_prev_angle;             // 计算速度使用的角度
  unsigned long vel_prev_angle_ts;  // 计算速度使用的时间记录

} AS5600_T;

int AS5600_Init(AS5600_T *a, I2C_HandleTypeDef *hi2c);

uint16_t AS5600_GetRawAngle(AS5600_T *a);
float AS5600_GetOnceAngle(AS5600_T *a);
float AS5600_GetAngle(AS5600_T *a);
void AS5600_Update(AS5600_T *a);
float AS5600_GetVelocity();

#endif