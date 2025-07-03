/* ========= File: Core/Src/usart.c ========= */
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : usart.c
  * Description        : Configuration of USART instances
  ******************************************************************************
  */
/* USER CODE END Header */

#include "usart.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/**
  * @brief USART1 Initialization Function (GPS)
  */
void MX_USART1_UART_Init(void)
{
  huart1.Instance               = USART1;
  huart1.Init.BaudRate          = 9600;
  huart1.Init.WordLength        = UART_WORDLENGTH_8B;
  huart1.Init.StopBits          = UART_STOPBITS_1;
  huart1.Init.Parity            = UART_PARITY_NONE;
  huart1.Init.Mode              = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl         = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling      = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling    = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function (Debug)
  */
void MX_USART2_UART_Init(void)
{
  huart2.Instance               = USART2;
  huart2.Init.BaudRate          = 115200;
  huart2.Init.WordLength        = UART_WORDLENGTH_8B;
  huart2.Init.StopBits          = UART_STOPBITS_1;
  huart2.Init.Parity            = UART_PARITY_NONE;
  huart2.Init.Mode              = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl         = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling      = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling    = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief UART MSP Initialization
  */
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
  GPIO_InitTypeDef           GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef   PeriphClkInit   = {0};

  if (uartHandle->Instance == USART1)
  {
    /* Peripheral clock config */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
      PA9  ---> USART1_TX
      PA10 ---> USART1_RX
    */
    GPIO_InitStruct.Pin       = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
  else if (uartHandle->Instance == USART2)
  {
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
      PA2  ---> USART2_TX (VCP_TX_Pin)
      PA15 ---> USART2_RX (VCP_RX_Pin)
    */
    GPIO_InitStruct.Pin       = VCP_TX_Pin;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(VCP_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = VCP_RX_Pin;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_USART2;
    HAL_GPIO_Init(VCP_RX_GPIO_Port, &GPIO_InitStruct);
  }
}

/**
  * @brief UART MSP De-Initialization
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  if (uartHandle->Instance == USART1)
  {
    __HAL_RCC_USART1_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
  }
  else if (uartHandle->Instance == USART2)
  {
    __HAL_RCC_USART2_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOA, VCP_TX_Pin | VCP_RX_Pin);
  }
}
