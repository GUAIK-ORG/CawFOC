#include "as5600.h"

#include "../../Utils/Log/log.h"

#define abs(x) ((x) > 0 ? (x) : -(x))
#define _2PI 6.283185307179586f
#define _PI 3.141592653589793f

HAL_StatusTypeDef _WriteData(I2C_HandleTypeDef *hi2c, uint16_t dev_addr,
                             uint8_t *data, uint16_t size) {
  HAL_StatusTypeDef sta = HAL_ERROR;
  sta = HAL_I2C_Master_Transmit(hi2c, dev_addr, data, size, -1);
  return sta;
}

HAL_StatusTypeDef _ReadData(I2C_HandleTypeDef *hi2c, uint16_t dev_addr,
                            uint8_t *data, uint16_t size) {
  HAL_StatusTypeDef sta = HAL_ERROR;
  sta = HAL_I2C_Master_Receive(hi2c, (dev_addr | 1), data, size, -1);
  return sta;
}

int AS5600_Init(AS5600_T *a, I2C_HandleTypeDef *hi2c) {
  a->i2c_ins = hi2c;
  a->rotation_offset = 0;
  a->prev_angle = AS5600_GetRawAngle(a);
  return 0;
}

uint16_t AS5600_GetRawAngle(AS5600_T *a) {
  uint16_t raw_angle;
  uint8_t buffer[2];
  uint8_t raw_angle_register = AS5600_RAW_ANGLE_REGISTER;

  _WriteData(a->i2c_ins, AS5600_ADDR, &raw_angle_register, 1);
  _ReadData(a->i2c_ins, AS5600_ADDR, buffer, 2);
  raw_angle = ((uint16_t)buffer[0] << 8) | (uint16_t)buffer[1];
  return raw_angle;
}

// 获得单圈弧度值
float AS5600_GetOnceAngle(AS5600_T *a) {
  return AS5600_GetRawAngle(a) * (360.0 / AS5600_RESOLUTION) * _PI / 180.0;
}

// 获得累计圈数
float AS5600_GetAngle(AS5600_T *a) {
  float angle_data = AS5600_GetRawAngle(a);
  float delta = angle_data - a->prev_angle;
  if (abs(delta) > (0.8 * AS5600_RESOLUTION)) {
    a->rotation_offset += (delta > 0 ? -_2PI : _2PI);
  }
  a->prev_angle = angle_data;
  return (a->rotation_offset + (angle_data / (float)AS5600_RESOLUTION) * _2PI);
}
