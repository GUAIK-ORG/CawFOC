/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 13:34:45
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-29 18:25:48
 * @Description:
 */
#include "foc_hal.h"

#include <i2c.h>

#include "../../Drivers/AS5600/as5600.h"

AS5600_T G_SENSOR_A;
AS5600_T G_SENSOR_B;

float Sensor_GetOnceAngleA() { return AS5600_GetOnceAngle(&G_SENSOR_A); }
float Sensor_GetAngleA() { return AS5600_GetAngle(&G_SENSOR_A); }
void Sensor_UpdateA() { AS5600_Update(&G_SENSOR_A); }
float Sensor_GetVelocityA() { return AS5600_GetVelocity(&G_SENSOR_A); }

float Sensor_GetOnceAngleB() { return AS5600_GetOnceAngle(&G_SENSOR_B); }
float Sensor_GetAngleB() { return AS5600_GetAngle(&G_SENSOR_B); }
void Sensor_UpdateB() { AS5600_Update(&G_SENSOR_B); }
float Sensor_GetVelocityB() { return AS5600_GetVelocity(&G_SENSOR_B); }

void FOC_HAL_InitA(FOC_T *hfoc, I2C_HandleTypeDef *h2ic) {
  AS5600_Init(&G_SENSOR_A, h2ic);
  FOC_Bind_SensorUpdate(hfoc, Sensor_UpdateA);
  FOC_Bind_SensorGetOnceAngle(hfoc, Sensor_GetOnceAngleA);
  FOC_Bind_SensorGetAngle(hfoc, Sensor_GetAngleA);
  FOC_Bind_SensorGetVelocity(hfoc, Sensor_GetVelocityA);
}

void FOC_HAL_InitB(FOC_T *hfoc, I2C_HandleTypeDef *h2ic) {
  AS5600_Init(&G_SENSOR_B, h2ic);
  FOC_Bind_SensorUpdate(hfoc, Sensor_UpdateB);
  FOC_Bind_SensorGetOnceAngle(hfoc, Sensor_GetOnceAngleB);
  FOC_Bind_SensorGetAngle(hfoc, Sensor_GetAngleB);
  FOC_Bind_SensorGetVelocity(hfoc, Sensor_GetVelocityB);
}
