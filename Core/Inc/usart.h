/* ========= File: Core/Inc/usart.h ========= */
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* Initialize USART1 for GPS (9600 baud) */
void MX_USART1_UART_Init(void);
/* Initialize USART2 for debug (115200 baud) */
void MX_USART2_UART_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
