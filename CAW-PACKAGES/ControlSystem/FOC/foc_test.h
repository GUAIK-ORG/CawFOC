/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 13:27:35
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-29 01:44:34
 * @Description:
 */
#ifndef __FOC_TEST_H__
#define __FOC_TEST_H__
#include "foc.h"

void Foc_TestOpenloopVelocity(FOC_T *hfoc, float target_velocity);
void Foc_TestCloseloopVelocity(FOC_T *hfoc, float target_velocity);
void Foc_TestCloseloopAngle(FOC_T *hfoc, float angle);
#endif