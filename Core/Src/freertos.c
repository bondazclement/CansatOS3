#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gps.h"
#include <stdio.h>

#define ALTITUDE_DEPLOYMENT_M 100.0f
#define GPS_BUFFER_SIZE 128

osThreadId_t gpsServoTaskHandle;
const osThreadAttr_t gpsServoTask_attributes = {
  .name = "gpsServoTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};

void GpsServoTask(void *argument);

void MX_FREERTOS_Init(void) {
  gpsServoTaskHandle = osThreadNew(GpsServoTask, NULL, &gpsServoTask_attributes);
}

void GpsServoTask(void *argument)
{
  GPS_Data gps_data = {0};
  char gps_buffer[GPS_BUFFER_SIZE];
  uint8_t buffer_idx = 0;
  char uart_char;
  int gps_fix_found = 0;

  // Séquence de test au démarrage
  osDelay(30000); // Attente de 30 secondes

  // Vérification du fix GPS
  for (int i = 0; i < 30; i++) { // Tente de recevoir des données pendant 30s
      if (HAL_UART_Receive(&huart1, (uint8_t*)&uart_char, 1, 1000) == HAL_OK) {
          if (uart_char == '\n') {
              gps_buffer[buffer_idx] = '\0';
              if (GPS_Parse(gps_buffer, &gps_data) == 0 && gps_data.fix > 0) {
                  gps_fix_found = 1;
                  break;
              }
              buffer_idx = 0;
          } else if (buffer_idx < GPS_BUFFER_SIZE - 1) {
              gps_buffer[buffer_idx++] = uart_char;
          }
      }
  }


  if (gps_fix_found) {
    // Tour complet des servos
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500); // 0°
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 500);
    osDelay(1000);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2500); // 180°
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 2500);
    osDelay(1000);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500); // 0°
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 500);
  } else {
    // Mouvement avant/arrière
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1500); // 90° (position neutre)
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 1500);
    osDelay(1000);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2000); // +45°
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 2000);
    osDelay(1000);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000); // -45°
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 1000);
    osDelay(1000);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1500); // Retour à la position neutre
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 1500);
  }


  // Boucle principale
  for(;;)
  {
    if (HAL_UART_Receive(&huart1, (uint8_t*)&uart_char, 1, 100) == HAL_OK) {
        if (uart_char == '\n') {
            gps_buffer[buffer_idx] = '\0';
            if (GPS_Parse(gps_buffer, &gps_data) == 0) {
                 // Imprimer l'altitude pour le débogage
                char debug_msg[50];
                sprintf(debug_msg, "Altitude: %.2f m, Fix: %d\r\n", gps_data.altitude, gps_data.fix);
                HAL_UART_Transmit(&huart2, (uint8_t*)debug_msg, strlen(debug_msg), HAL_MAX_DELAY);

                if (gps_data.altitude > ALTITUDE_DEPLOYMENT_M) {
                    // Déploiement
                    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2500); // 180°
                    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 2500);
                } else {
                    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500); // 0°
                    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 500);
                }
            }
            buffer_idx = 0;
        } else if (buffer_idx < GPS_BUFFER_SIZE - 1) {
            gps_buffer[buffer_idx++] = uart_char;
        }
    }
  }
}
