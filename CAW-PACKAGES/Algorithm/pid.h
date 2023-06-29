/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 22:58:34
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-29 12:48:37
 * @Description:
 */
#ifndef __PID_H__
#define __PID_H__

typedef struct {
  float p;  // 比例增益
  float i;  // 积分增益
  float d;  // 微分增益
  float output_ramp;
  float limit;

  float prev_error;              // 最后跟踪误差
  float prev_output;             // 最后一个pid输出值
  float prev_integral;           // 最后一个积分分量
  unsigned long prev_timestamp;  // 上次执行的时间戳
} PID_T;

void PID_Init(PID_T *pid, float P, float I, float D, float ramp, float limit);
void PID_Set(PID_T *pid, float P, float I, float D, float ramp);
float PID_Calc(PID_T *pid, float error);

#endif