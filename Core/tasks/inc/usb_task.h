/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for
  *                      the gpio
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usb_task_H
#define __usb_task_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "stdlib.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */

#define NON_TIMEOUT 0

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

//USBD_HandleTypeDef hUsbDeviceFS;
extern int32_t rt,rp,rh;

#define MAIL_SIZE (uint32_t)	1
/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */
 void usb_task(void const * argument);
 void Usb_Task_Init(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
