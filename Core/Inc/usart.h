/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
//#include "typedefs.h"
#include "stdio.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

#define MAIL_SIZE (uint32_t)	1
#define QUEUE_SIZE (uint32_t)	10
#define RXBUFFERSIZE			25

//osThreadId TaskStringOutHandle, TaskParseUSARTHandle;
//osMailQId strout_Queue;
//osMessageQId USART_Queue;

typedef struct struct_out_t {
  uint32_t tick_count;
  uint16_t y_pos;
  char str[60];
} struct_out;

//char str1[60];
//char buf1[1];
//uint8_t aRxBuffer[RXBUFFERSIZE];

typedef enum  {
	STATUS_IDLE = 0x00,
	STATUS_RUN = 0x01,
	STATUS_WAIT = 0x02,
	STATUS_ON_3 = 0x04,

	STATUS_OFF_1 = 0x08,
	STATUS_OFF_2 = 0x10,
	STATUS_OFF_3 = 0x20,

	STATUS_READ = 0x27,
	STATUS_READ_CNV = 0x28,
	STATUS_OFF_RD = 0x29,
	STATUS_ON_RD = 0x2A,
	STATUS_READ_RD = 0x2B,
	STATUS_READ_CNV_RD = 0x2C,
	STATUS_DONE = 0x2D,

	STATUS_STOP = 0x3D

} COMMANDSTATUS;

/*
typedef enum  {
	STATUS_PLC_ON_1 = 0x01,
	STATUS_PLC_ON_2 = 0x02,
	STATUS_PLC_ON_3 = 0x04,
	STATUS_DONE = 0x0D
} REDBACK_STATUS;
*/
/*
struct unit
{
	unit1;
	unit2;
};

*/
//#define DBG_USART                  USART3

//#define printf(...)                USART_printf(DBG_USART, __VA_ARGS__)




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void UART_Task_Init(void);


/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
