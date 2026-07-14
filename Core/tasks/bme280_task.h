/*
 * bme280_task.c
 *
 *  Created on: 6 апр. 2021 г.
 *      Author: Zver
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __bme280_task_H
#define __bme280_task_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "stdlib.h"
#include "bme280_task.h"
#include "bme280_defs.h"
//#include "discovery_bme280.h"

/* USER CODE BEGIN Includes */

 typedef struct
{
 	char string_USB[0x40];
 	char usb_recieved;
} struct_usb;

 typedef struct
{
    bme280_data sensor_data;
    char string_data[0x40];
    char data_recieved;
} struct_data;
/* USER CODE END Includes */

#define MAIL_SIZE (uint32_t)	1
#define NON_TIMEOUT 0

/* USER CODE BEGIN Private defines */
// osThreadId GuiTaskHandle;

//extern bme280_data comp_data;

// int32_t rt,rp,rh;
/* USER CODE END Private defines */
 void sensor_task(void const * argument);
 void Sensor_Task_Init(void);

/* USER CODE BEGIN Prototypes */
 //void gui_task(void const *argument);
 //void Gui_Task_Init(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__bme280_task_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

