/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"

#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "foc.h"
#include "foc_hal.h"
#include "foc_test.h"
#include "i2c.h"
#include "log.h"
#include "lowpass_filter.h"
#include "pid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for FOCATask */
osThreadId_t FOCATaskHandle;
const osThreadAttr_t FOCATask_attributes = {
    .name = "FOCATask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartFOCATask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of FOCATask */
  FOCATaskHandle = osThreadNew(StartFOCATask, NULL, &FOCATask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartFOCATask */
/**
 * @brief  Function implementing the FOCATask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFOCATask */
void StartFOCATask(void *argument) {
  /* USER CODE BEGIN StartFOCATask */
  FOC_T foc1;
  PID_T velPID1;
  PID_T anglePID1;
  LOWPASS_FILTER_T velFilter1;
  FOC_Closeloop_Init(&foc1, &htim1, PWM_PERIOD, 12.6, 1, 7);
  FOC_SetVoltageLimit(&foc1, 10.0);
  FOC_HAL_Init(&foc1, &hi2c1);

  PID_Init(&velPID1, 2, 0, 0, 100000, foc1.voltage_power_supply / 2);
  PID_Init(&anglePID1, 2, 0, 0, 100000, 100);
  LOWPASS_FILTER_Init(&velFilter1, 0.01);

  FOC_AlignmentSensor(&foc1);
  /* Infinite loop */
  for (;;) {
    // 闭环位置控制
    // Foc_TestCloseloopAngle(&foc1, &anglePID1, 3.141592654);

    // 闭环速度控制
    Foc_TestCloseloopVelocity(&foc1, &velFilter1, &velPID1, 10);
    FOC_SensorUpdate();
    osDelay(1);
  }
  /* USER CODE END StartFOCATask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
