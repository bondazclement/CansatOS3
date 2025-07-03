#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C" {
#endif


// Déclarations des handles UART
extern UART_HandleTypeDef huart1; // Pour le GPS
extern UART_HandleTypeDef huart2; // Pour le Virtual COM Port (Debug)

// Prototypes des fonctions d'initialisation
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __USART_H */
