#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

// Définitions des broches
#define LD3_Pin GPIO_PIN_3
#define LD3_GPIO_Port GPIOB
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA

extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void Error_Handler(void);
void MX_FREERTOS_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
