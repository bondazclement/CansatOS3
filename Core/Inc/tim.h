#ifndef __TIM_H
#define __TIM_H

#include "stm32l4xx_hal.h"

extern TIM_HandleTypeDef htim1;

void MX_TIM1_Init(void);
uint32_t Servo_CalcPulse(uint8_t angle);

#endif /* __TIM_H */
