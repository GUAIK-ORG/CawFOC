/*
 * @Author: Rick rick@guaik.io
 * @Date: 2022-12-09 14:15:44
 * @LastEditors: Rick rick@guaik.io
 * @LastEditTime: 2023-01-06 16:46:37
 * @FilePath: \MPU6050\CAW-PACKAGES\Utils\Log\log.c
 * @Description:
 * Copyright (c) 2022 by Rick email: rick@guaik.io, All Rights Reserved.
 */
#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

CAW_LOG_T G_CAW_LOG_Instance = {NULL, false};

int CAW_LOG_Init(UART_HandleTypeDef* huart, CAW_LOG_LEVEL level,
                 bool enable_color) {
  G_CAW_LOG_Instance.uart_ins = huart;
  G_CAW_LOG_Instance.enable_color = enable_color;
  G_CAW_LOG_Instance.level = level;
}

void CAW_LOG_Write(const char* fmt, CAW_LOG_LEVEL level, const char* file,
                   int line, const char* func, ...) {
  if (level < G_CAW_LOG_Instance.level) return;
  char tmp[128];
  char buf[128];
  memset(tmp, 0, sizeof(tmp));
  memset(buf, 0, sizeof(buf));
  va_list args;
  va_start(args, fmt);
  vsprintf(tmp, (char*)fmt, args);
  va_end(args);
  while (HAL_UART_GetState(G_CAW_LOG_Instance.uart_ins) != HAL_UART_STATE_READY)
    ;
  if (level == LEVEL_DEBUG) {
    if (G_CAW_LOG_Instance.enable_color)
      snprintf(buf, sizeof(buf),
               "\033[1;36mCAW-[DEBUG] <%s> | <%d> | <%s>: %s\033[m\r\n", file,
               line, func, tmp);
    else
      snprintf(buf, sizeof(buf), "CAW-[DEBUG] <%s> | <%d> | <%s>: %s\r\n", file,
               line, func, tmp);
  } else if (level == LEVEL_INFO) {
    if (G_CAW_LOG_Instance.enable_color)
      snprintf(buf, sizeof(buf),
               "\033[1;32mCAW-[INFO] <%s> | <%d> | <%s>: %s\033[m\r\n", file,
               line, func, tmp);
    else
      snprintf(buf, sizeof(buf), "CAW-[INFO] <%s> | <%d> | <%s>: %s\r\n", file,
               line, func, tmp);
  } else if (level == LEVEL_WARN) {
    if (G_CAW_LOG_Instance.enable_color)
      snprintf(buf, sizeof(buf),
               "\033[1;33mCAW-[WARN] <%s> | <%d> | <%s>: %s\033[m\r\n", file,
               line, func, tmp);
    else
      snprintf(buf, sizeof(buf), "CAW-[WARN] <%s> | <%d> | <%s>: %s\r\n", file,
               line, func, tmp);
  } else if (level == LEVEL_ERROR) {
    if (G_CAW_LOG_Instance.enable_color)
      snprintf(buf, sizeof(buf),
               "\033[1;31mCAW-[ERROR] <%s> | <%d> | <%s>: %s\033[m\r\n", file,
               line, func, tmp);
    else
      snprintf(buf, sizeof(buf), "CAW-[ERROR] <%s> | <%d> | <%s>: %s\r\n", file,
               line, func, tmp);
  } else {
    return;
  }

  HAL_UART_Transmit_IT(G_CAW_LOG_Instance.uart_ins, buf, strlen(buf) + 1);
  while (HAL_UART_GetState(G_CAW_LOG_Instance.uart_ins) ==
         HAL_UART_STATE_BUSY_TX)
    ;
}