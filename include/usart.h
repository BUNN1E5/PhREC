/* Modified to work with Arduino */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include <Arduino.h>

extern UART_HandleTypeDef huart1;


void MX_USART1_UART_Init(void);
void UART_RxCpltCallback(UART_HandleTypeDef *huart);
