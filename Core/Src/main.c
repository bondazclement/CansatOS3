/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h" // Pour osKernelStart()

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init(); // GPS
  MX_USART2_UART_Init(); // Debug
  MX_TIM1_Init();

  /* Start PWM channels */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

  /* Init scheduler */
  osKernelInitialize();  // Initialisation du noyau
  MX_FREERTOS_Init();    // Création des tâches
  osKernelStart();       // Démarrage du planificateur

  /* We should never get here as control is now taken by the scheduler */
  while (1)
  {
  }
}

// ... (Le reste du fichier main.c, y compris SystemClock_Config, ne change pas)
// Assurez-vous que le reste du fichier est identique à ce que je vous ai fourni précédemment.
