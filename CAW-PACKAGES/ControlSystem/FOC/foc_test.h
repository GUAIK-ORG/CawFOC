/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 13:27:35
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-29 15:59:38
 * @Description:
 */
#ifndef __FOC_TEST_H__
#define __FOC_TEST_H__
#include "../../Algorithm/lowpass_filter.h"
#include "../../Algorithm/pid.h"
#include "foc.h"

void Foc_TestOpenloopVelocity(FOC_T *hfoc, float target_velocity);
void Foc_TestCloseloopVelocity(FOC_T *hfoc, LOWPASS_FILTER_T *filter,
                               PID_T *pid, float target_velocity);
void Foc_TestCloseloopAngle(FOC_T *hfoc,PID_T *pid, float angle);
#endif