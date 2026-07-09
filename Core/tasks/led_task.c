/*
 * led_task.c
 *
 *  Created on: 7 апр. 2021 г.
 *      Author: Zver
 */



#include "cmsis_os.h"
#include "gpio.h"
#include "led_task.h"
#include "stdio.h"

osThreadId LedTaskHandle;

void Led_Task_Init(void)
{
	osThreadDef(ledtask, led_task, osPriorityLow, 0, 512);
	LedTaskHandle = osThreadCreate(osThread(ledtask), NULL);
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void led_task(void const *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
//	char *test = "hello world from HAL\n";
    osDelay(1000);
//    HAL_UART_Transmit(&huart3, (uint8_t *)test, strlen(test), 10);
    BSP_LED_Toggle(LED4); //LED_YELLOW
    printf("USART3\n");
  }
  /* USER CODE END StartTask03 */
}
