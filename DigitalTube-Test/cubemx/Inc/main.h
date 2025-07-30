/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern UART_HandleTypeDef huart1;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART1_UART_Init(void);
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TM1629A_A_STB_Pin GPIO_PIN_8
#define TM1629A_A_STB_GPIO_Port GPIOC
#define TM1629A_A_CLK_Pin GPIO_PIN_9
#define TM1629A_A_CLK_GPIO_Port GPIOC
#define TM1629A_A_DIO_Pin GPIO_PIN_11
#define TM1629A_A_DIO_GPIO_Port GPIOA
#define LED_COMPETITION_Pin GPIO_PIN_11
#define LED_COMPETITION_GPIO_Port GPIOC
#define LED_TRAIN_Pin GPIO_PIN_12
#define LED_TRAIN_GPIO_Port GPIOC
#define LED_ASSESS_Pin GPIO_PIN_2
#define LED_ASSESS_GPIO_Port GPIOD
#define BCD_3_Pin GPIO_PIN_3
#define BCD_3_GPIO_Port GPIOB
#define BCD_2_Pin GPIO_PIN_4
#define BCD_2_GPIO_Port GPIOB
#define BCD_1_Pin GPIO_PIN_5
#define BCD_1_GPIO_Port GPIOB
#define BCD_0_Pin GPIO_PIN_6
#define BCD_0_GPIO_Port GPIOB
#define LED_START_RESET_Pin GPIO_PIN_7
#define LED_START_RESET_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
