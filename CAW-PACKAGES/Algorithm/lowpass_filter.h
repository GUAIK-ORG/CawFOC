/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 22:57:43
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-29 12:58:46
 * @Description:
 */
#ifndef __LOWPASS_FILTER_H__
#define __LOWPASS_FILTER_H__

typedef struct {
  float tf;
  float prev_y;
  unsigned long prev_timestamp;
} LOWPASS_FILTER_T;

void LOWPASS_FILTER_Init(LOWPASS_FILTER_T *f, float time_const);
float LOWPASS_FILTER_Calc(LOWPASS_FILTER_T *f, float x);

#endif