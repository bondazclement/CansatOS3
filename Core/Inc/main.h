#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
// C'est le fichier le plus important, il doit être inclus en premier.
#include "stm32l4xx_hal.h"

/* Private defines -----------------------------------------------------------*/
// Toutes les définitions de broches sont centralisées ici.
#define LD3_Pin GPIO_PIN_3
#define LD3_GPIO_Port GPIOB
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Exported types ------------------------------------------------------------*/
// Les handles des périphériques sont déclarés ici pour être accessibles partout.
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

// Prototypes des fonctions d'initialisation pour être visibles globalement
void MX_GPIO_Init(void);
void MX_TIM1_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_FREERTOS_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
