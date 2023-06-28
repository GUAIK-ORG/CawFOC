/*
 * @Author: Rick rick@guaik.io
 * @Date: 2022-12-09 14:15:37
 * @LastEditors: Rick rick@guaik.io
 * @LastEditTime: 2023-01-06 16:47:26
 * @FilePath: \MPU6050\CAW-PACKAGES\Utils\Log\log.h
 * @Description:
 * Copyright (c) 2022 by Rick email: rick@guaik.io, All Rights Reserved.
 */
#ifndef __LOG_H__
#define __LOG_H__
#include <stdarg.h>
#include <stdbool.h>
#include <usart.h>

typedef enum {
  LEVEL_DEBUG = 0,
  LEVEL_INFO = 1,
  LEVEL_WARN = 2,
  LEVEL_ERROR = 3
} CAW_LOG_LEVEL;

typedef struct {
  UART_HandleTypeDef* uart_ins;
  bool enable_color;
  CAW_LOG_LEVEL level;
} CAW_LOG_T;

extern CAW_LOG_T G_CAW_LOG_Instance;

int CAW_LOG_Init(UART_HandleTypeDef* huart, CAW_LOG_LEVEL level,
                 bool enable_color);
void CAW_LOG_Write(const char* fmt, CAW_LOG_LEVEL level, const char* file,
                   int line, const char* func, ...);

#define CAW_LOG_DEBUG(fmt, ...)                                     \
  CAW_LOG_Write(fmt, LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, \
                ##__VA_ARGS__)
#define CAW_LOG_INFO(fmt, ...)                                     \
  CAW_LOG_Write(fmt, LEVEL_INFO, __FILE__, __LINE__, __FUNCTION__, \
                ##__VA_ARGS__)
#define CAW_LOG_WARN(fmt, ...)                                     \
  CAW_LOG_Write(fmt, LEVEL_WARN, __FILE__, __LINE__, __FUNCTION__, \
                ##__VA_ARGS__)
#define CAW_LOG_ERROR(fmt, ...)                                     \
  CAW_LOG_Write(fmt, LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, \
                ##__VA_ARGS__)

#endif