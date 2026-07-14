/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "GUI.h"
//#include "HW_Init.h"


#include "cmsis_os.h"
#include "gpio.h"
#include "usart.h"
#include "i2c.h"
#include "usb_device.h"
#include "discovery_bme280.h"
#include "functions.h"
#include "fonts.h"
//#include "stdio.h"

#include "usb_device.h"
#include "usbd_def.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_customhid.h"
#include "usbd_custom_hid_if.h"
#include "usb_device.h"

USBD_HandleTypeDef hUsbDeviceFS;

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

extern bme280_DrvTypeDef bme280Drv;

bme280_dev dev;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);

extern void GRAPHICS_HW_Init(void);
extern void GRAPHICS_Init(void);


//extern void GRAPHICS_MainTask(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*
static void taskInit(void* pvParameters)
{
    (void)pvParameters;
    gfxInit();
}
*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
//  MX_GPIO_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

  MX_I2C1_Init();

  /* Initialise the graphical hardware */
  GRAPHICS_HW_Init();

    /* Initialise the graphical stack engine */
  GRAPHICS_Init();

  MX_USART3_UART_Init();
  MX_USB_DEVICE_Init();

  printf("Start\n");
  printf("USART3\n");
  if (BSP_BME_Init(&dev) == BME_ERROR)
  {
	  printf("SENSOR ERROR");
	  while(1);
  }
  /* USER CODE END 2 */

  /* Init scheduler */
  MX_FREERTOS_Init(); 

  /* Start scheduler */
  osKernelStart();
 
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM14 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM14) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


// HardFault handler
// note: attribute 'naked' tells the compiler that the function is an embedded assembly function
// note: this function calls a GetRegistersFromStack() function
//__attribute__((naked))
/*
void HardFault_Handler(void)
{

	__asm__ volatile (
			"TST LR, #4                               \n"
			"ITE EQ                                   \n"
			"MRSEQ R0, MSP                            \n"
			"MRSNE R0, PSP                            \n"
			"LDR R1, [R0, #24]                        \n"
			"LDR R2, haddr_const                      \n"
			"BX R2                                    \n"
			"haddr_const: .word GetRegistersFromStack \n"
		);
}

// Copy the register values from the stack to the C variables,
// dump it via printf() (if such function defined)
// and then stay in a infinite loop
__USED __NO_RETURN void GetRegistersFromStack(unsigned int * hardfault_args) {
	unsigned int stacked_r0;
	unsigned int stacked_r1;
	unsigned int stacked_r2;
	unsigned int stacked_r3;
	unsigned int stacked_r12;
	unsigned int stacked_lr;
	unsigned int stacked_pc;
	unsigned int stacked_psr;

	stacked_r0 = ((unsigned long)hardfault_args[0]);
	stacked_r1 = ((unsigned long)hardfault_args[1]);
	stacked_r2 = ((unsigned long)hardfault_args[2]);
	stacked_r3 = ((unsigned long)hardfault_args[3]);

	stacked_r12 = ((unsigned long)hardfault_args[4]);
	stacked_lr  = ((unsigned long)hardfault_args[5]);
	stacked_pc  = ((unsigned long)hardfault_args[6]);
	stacked_psr = ((unsigned long)hardfault_args[7]);

	printf("HardFault\r\n");
	printf("R0 = 0x%08X\r\n", stacked_r0);
	printf("R1 = 0x%08X\r\n", stacked_r1);
	printf("R2 = 0x%08X\r\n", stacked_r2);
	printf("R3 = 0x%08X\r\n", stacked_r3);
	printf("R12 = 0x%08X (%u)\r\n", stacked_r12, stacked_r12);
	printf("LR [R14] = 0x%08X subroutine call return address\r\n", stacked_lr);
	printf("PC [R15] = 0x%08X program counter\r\n", stacked_pc);
	printf("PSR = 0x%08X program status register\r\n", stacked_psr);
	printf("BFAR = 0x%08X\r\n", SCB->BFAR);
	printf("CFSR = 0x%08X\r\n", SCB->CFSR);
	printf("HFSR = 0x%08X\r\n", SCB->HFSR);
	printf("DFSR = 0x%08X\r\n", SCB->DFSR);
	printf("AFSR = 0x%08X\r\n", SCB->AFSR);
	printf("SCB_SHCSR = 0x%08x\r\n", SCB->SHCSR);

	while(1);
}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
