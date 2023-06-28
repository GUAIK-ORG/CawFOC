/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 13:27:39
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-29 00:49:33
 * @Description:
 */
#include "foc_test.h"

#define _PI 3.141592653589793f

// 测试开环速度控制
void Foc_TestOpenloopVelocity(FOC_T *hfoc, float target_velocity) {
  unsigned long now_ms = HAL_GetTick();
  // 计算每个Loop的运行时间间隔
  float Ts = (now_ms - hfoc->open_loop_timestamp) * 1e-3;
  hfoc->shaft_angle = _normalizeAngle(hfoc->shaft_angle + target_velocity * Ts);
  float Uq = hfoc->voltage_limit;
  FOC_SetTorque(hfoc, Uq, _openloop_electricalAngle(hfoc->shaft_angle, 7));
  hfoc->open_loop_timestamp = now_ms;
}

// 测试闭环位置控制和力矩控制
void Foc_TestCloseloopAngle(FOC_T *hfoc, float angle) {
  float SensorAngle = hfoc->Sensor_GetAngle();
  float Kp = 0.133;
  // 位置控制
  //   FOC_SetTorque(hfoc, Kp * (angle - hfoc->dir * SensorAngle) * 180 / _PI,
  //                 FOC_CloseloopElectricalAngle(hfoc));
  // 力矩控制
  FOC_SetTorque(hfoc, 0.5, FOC_CloseloopElectricalAngle(hfoc));
}