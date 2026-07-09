/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f4xx_it.h"
#include "FreeRTOS.h"
#include "task.h"
//#include "usbd.h"
#include <stdio.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
//__attribute__(( naked ))
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

	__asm volatile
	(
		" movs r0,#4					\n"
		" movs r1, lr					\n"
		" tst r0, r1					\n"
		" beq _MSP						\n"
		" mrs r0, psp					\n"
		" b _HALT						\n"
		"_MSP:							\n"
		" mrs r0, msp					\n"
		"_HALT:							\n"
		" ldr r1,[r0,#20]				\n"
		" b GetRegistersFromStack		\n"
		" bkpt #0						\n"
	);


/*
	asm("MRS R0, PSP");			// FreeRTOS использует PSP
	  //top of stack is in R0. It is passed to C-function.
	  asm("BL (GetRegistersFromStack)");
*/



  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}



// Copy the register values from the stack to the C variables,
// dump it via printf() (if such function defined)
// and then stay in a infinite loop
__USED __NO_RETURN void GetRegistersFromStack(unsigned int * hardfault_args) {

	  volatile unsigned long stacked_r0 ;
	  volatile unsigned long stacked_r1 ;
	  volatile unsigned long stacked_r2 ;
	  volatile unsigned long stacked_r3 ;
	  volatile unsigned long stacked_r12 ;
	  volatile unsigned long stacked_lr ;
	  volatile unsigned long stacked_pc ;
	  volatile unsigned long stacked_psr ;
	  __UNUSED volatile unsigned long _CFSR ;
	  __UNUSED volatile unsigned long _HFSR ;
	  __UNUSED volatile unsigned long _DFSR ;
	  __UNUSED volatile unsigned long _AFSR ;
	  __UNUSED volatile unsigned long _BFAR ;
	  __UNUSED volatile unsigned long _MMAR ;

	  stacked_r0 = ((unsigned long)hardfault_args[0]) ;
	  stacked_r1 = ((unsigned long)hardfault_args[1]) ;
	  stacked_r2 = ((unsigned long)hardfault_args[2]) ;
	  stacked_r3 = ((unsigned long)hardfault_args[3]) ;
	  stacked_r12 = ((unsigned long)hardfault_args[4]) ;
	  stacked_lr = ((unsigned long)hardfault_args[5]) ;
	  stacked_pc = ((unsigned long)hardfault_args[6]) ;
	  stacked_psr = ((unsigned long)hardfault_args[7]) ;

	  // Configurable Fault Status Register
	  // Consists of MMSR, BFSR and UFSR
	  _CFSR = (*((volatile unsigned long *)(0xE000ED28))) ;

	  // Hard Fault Status Register
	  _HFSR = (*((volatile unsigned long *)(0xE000ED2C))) ;

	  // Debug Fault Status Register
	  _DFSR = (*((volatile unsigned long *)(0xE000ED30))) ;

	  // Auxiliary Fault Status Register
	  _AFSR = (*((volatile unsigned long *)(0xE000ED3C))) ;

	  // Read the Fault Address Registers. These may not contain valid values.
	  // Check BFARVALID/MMARVALID to see if they are valid values
	  // MemManage Fault Address Register
	  _MMAR = (*((volatile unsigned long *)(0xE000ED34))) ;
	  // Bus Fault Address Register
	  _BFAR = (*((volatile unsigned long *)(0xE000ED38))) ;

		printf("HardFault\r\n");
		printf("R0 = 0x%08lu\r\n", stacked_r0);
		printf("R1 = 0x%08lu\r\n", stacked_r1);
		printf("R2 = 0x%08lu\r\n", stacked_r2);
		printf("R3 = 0x%08lu\r\n", stacked_r3);
		printf("R12 = 0x%08lu (%lu)\r\n", stacked_r12, stacked_r12);
		printf("LR [R14] = 0x%08lu subroutine call return address\r\n", stacked_lr);
		printf("PC [R15] = 0x%08lu program counter\r\n", stacked_pc);
		printf("PSR = 0x%08lu program status register\r\n", stacked_psr);
		printf("BFAR = 0x%08lu\r\n", SCB->BFAR);
		printf("CFSR = 0x%08lu\r\n", SCB->CFSR);
		printf("HFSR = 0x%08lu\r\n", SCB->HFSR);
		printf("DFSR = 0x%08lu\r\n", SCB->DFSR);
		printf("AFSR = 0x%08lu\r\n", SCB->AFSR);
		printf("SCB_SHCSR = 0x%08lu\r\n", SCB->SHCSR);

	  __asm("BKPT #0\n") ; // Break into the debugger

	while(1)
	{

	}
}


/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	/* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */
	/* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
	HAL_TIM_IRQHandler(&htim14);
	/* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

	/* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}


/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
	HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  //tud_int_handler(0);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
