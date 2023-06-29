/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 22:57:48
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-29 14:39:32
 * @Description:
 */
#include "lowpass_filter.h"

void LOWPASS_FILTER_Init(LOWPASS_FILTER_T *f, float time_const) {
  f->tf = time_const;
  f->prev_y = 0.0f;
  f->prev_timestamp = HAL_GetTick();
}

float LOWPASS_FILTER_Calc(LOWPASS_FILTER_T *f, float x) {
  unsigned long timestamp = HAL_GetTick();
  float delta = (timestamp - f->prev_timestamp) * 1e-3f;
  if (delta < 0.0f)
    delta = 1e-3f;
  else if (delta > 0.3f) {
    f->prev_y = x;
    f->prev_timestamp = timestamp;
    return x;
  }

  float alpha = f->tf / (f->tf + delta);
  float y = alpha * f->prev_y + (1.0f - alpha) * x;
  f->prev_y = y;
  f->prev_timestamp = timestamp;
  return y;
}