/*
 * @Author: Rick rick@guaik.io
 * @Date: 2023-06-28 13:34:37
 * @LastEditors: Rick
 * @LastEditTime: 2023-06-28 15:32:07
 * @Description:
 */
#ifndef __FOC_HAL_H__
#define __FOC_HAL_H__

#include "foc.h"

void FOC_HAL_Init(FOC_T *hfoc, I2C_HandleTypeDef *h2ic);

#endif