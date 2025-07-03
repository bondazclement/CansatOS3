#ifndef __MAIN_H
#define __MAIN_H

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"
#include "stm32l4xx_hal_uart.h"
#include "stm32l4xx_hal_gpio.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"

/* Extern declarations */
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;

/* Prototype fonctions utiles */
uint32_t Servo_CalcPulse(uint32_t angle);

#endif /* __MAIN_H */
