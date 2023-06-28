/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 13:34:45
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-29 00:40:48
 * @Description:
 */
#include "foc_hal.h"

#include <i2c.h>

#include "../../Drivers/AS5600/as5600.h"

AS5600_T G_SENSOR_A;

float Sensor_GetOnceAngleA() { return AS5600_GetOnceAngle(&G_SENSOR_A); }
float Sensor_GetAngleA() { return AS5600_GetAngle(&G_SENSOR_A); }
void Sensor_UpdateA() { AS5600_Update(&G_SENSOR_A); }
float Sensor_GetVelocity() { return AS5600_GetVelocity(&G_SENSOR_A); }

void FOC_HAL_Init(FOC_T *hfoc, I2C_HandleTypeDef *h2ic) {
  AS5600_Init(&G_SENSOR_A, h2ic);
  FOC_Bind_SensorUpdate(hfoc, Sensor_UpdateA);
  FOC_Bind_SensorGetOnceAngle(hfoc, Sensor_GetOnceAngleA);
  FOC_Bind_SensorGetAngle(hfoc, Sensor_GetAngleA);
  FOC_Bind_SensorGetVelocity(hfoc, Sensor_GetVelocity);
}
