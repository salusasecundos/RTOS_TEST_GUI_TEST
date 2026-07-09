/**
  ******************************************************************************
  * @file    stm32f429i_discovery_BMPscope.h
  * @author  MCD Application Team
  * @brief   This file contains definitions for stm32f429i_discovery_BMPscope.c 
  *          firmware driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F429I_DISCOVERY_BMP180_H
#define __STM32F429I_DISCOVERY_BMP180_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "stm32f429i_discovery.h"
/* Include BMPscope component driver */
//#include "../Components/Bmp180/bmp180.h"
#include "bme280.h"
//#include "bme280_defs.h"
// Drivers/BSP/components/BMP180/


/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */ 

/** @addtogroup STM32F429I_DISCOVERY_BMPSCOPE
  * @{
  */
  
/** @defgroup STM32F429I_DISCOVERY_BMPSCOPE_Exported_Types STM32F429I DISCOVERY BMPSCOPE Exported Types
  * @{
  */
typedef enum 
{
  BME_OK = 0,
  BME_ERROR = 1,
  BME_TIMEOUT = 2
}BMP_StatusTypeDef;
/**
  * @}
  */
typedef enum
{
  I2C_OK       = 0x00U,
  I2C_ERROR    = 0x01U,
} BMP_I2C_StatusTypeDef;
/** @defgroup STM32F429I_DISCOVERY_BMPSCOPE_Exported_Constants STM32F429I DISCOVERY BMPSCOPE Exported Constants
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F429I_DISCOVERY_BMPSCOPE_Exported_Macros STM32F429I DISCOVERY BMPSCOPE Exported Macros
  * @{
  */
/**
  * @}
  */
 
/** @defgroup STM32F429I_DISCOVERY_BMPSCOPE_Exported_Functions STM32F429I DISCOVERY BMPSCOPE Exported Functions
  * @{
  */
/* BMPscope Functions */ 

uint8_t BSP_BME_Init(bme280_dev *dev);//struct bme280_dev *dev
int16_t BSP_BME_ReadTemp(void);
int32_t BSP_BME_ReadPressure(void);
uint32_t BSP_BME_Read_U_pressure(void);
uint16_t BSP_BME_Read_U_temperature(void);
uint8_t BSP_BME_ReadData(void);
int16_t BSP_BMP_ReadData();//struct bme280_dev *dev
/**
  * @}
  */

/**
  * @}
  */ 
int8_t BME_API_I2C_bus_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t cnt);
int8_t BME_API_I2C_bus_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t cnt);
uint8_t Bme_API_Read_ID(uint8_t addr);
void BME_API_delay_msek(uint32_t msek);






/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32F429I_DISCOVERY_BMPSCOPE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
