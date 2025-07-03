#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"

// Inclure les en-têtes des périphériques
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "freertos.h"


// Définitions des broches pour la LED
#define LD3_Pin GPIO_PIN_3
#define LD3_GPIO_Port GPIOB

void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
