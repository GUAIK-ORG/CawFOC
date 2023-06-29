/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 22:58:39
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-29 12:48:51
 * @Description:
 */
#include "pid.h"

#define _constrain(amt, low, high) \
  ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

void PID_Init(PID_T *pid, float P, float I, float D, float ramp, float limit) {
  pid->p = P;
  pid->i = I;
  pid->d = D;
  pid->output_ramp = ramp;
  pid->limit = limit;
  pid->prev_error = 0.0f;
  pid->prev_output = 0.0f;
  pid->prev_integral = 0.0f;
  pid->prev_timestamp = HAL_GetTick();  // 获取毫秒时间
}

float PID_Calc(PID_T *pid, float error) {
  unsigned long timestamp_now = HAL_GetTick();
  float ts = (timestamp_now - pid->prev_timestamp) * 1e-3f;  // 转换成秒
  if (ts <= 0 || ts > 0.5f) ts = 1e-3f;

  // P环处理
  float proportional = pid->p * error;
  //  Tustin散点积分（I环）
  float integral =
      pid->prev_integral + pid->i * ts * 0.5f * (error + pid->prev_error);
  integral = _constrain(integral, -pid->limit, pid->limit);
  // D环 散点微分 （微分环）
  float derivative = pid->d * (error - pid->prev_error) / ts;

  // 将P，I，D值加起来
  float output = proportional + integral + derivative;
  output = _constrain(output, -pid->limit, pid->limit);

  if (pid->output_ramp > 0) {
    // 对PID变化率（加速度）进行限制
    float output_rate = (output - pid->prev_output) / ts;
    if (output_rate > pid->output_ramp)
      output = pid->prev_output + pid->output_ramp * ts;
    else if (output_rate < -pid->output_ramp)
      output = pid->prev_output - pid->output_ramp * ts;
  }

  pid->prev_integral = integral;
  pid->prev_output = output;
  pid->prev_error = error;
  pid->prev_timestamp = timestamp_now;
  return output;
}

void PID_Set(PID_T *pid, float P, float I, float D, float ramp) {
  pid->p = P;
  pid->i = I;
  pid->d = D;
  pid->output_ramp = ramp;
}