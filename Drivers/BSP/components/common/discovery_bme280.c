/**
  ******************************************************************************
  * @file    stm32f429i_discovery_BMP180.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the
  *          MEMS BMP180 available on STM32F429I-Discovery Kit.
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
/* Includes ------------------------------------------------------------------*/
#include "discovery_bme280.h"
//#include "bme280_defs.h"
//#include "bmp280.h"
#include "main.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32F429I_DISCOVERY
  * @{
  */
/** @defgroup STM32F429I_DISCOVERY_BMP180 STM32F429I DISCOVERY BMP180
  * @{
  */
/** @defgroup STM32F429I_DISCOVERY_BMP180_Private_TypesDefinitions STM32F429I DISCOVERY BMP180 Private TypesDefinitions
  * @{
  */
/**
  * @}
  */
/** @defgroup STM32F429I_DISCOVERY_BMP180_Private_Defines STM32F429I DISCOVERY BMP180 Private Defines
  * @{
  */
/**
  * @}
  */
/** @defgroup STM32F429I_DISCOVERY_BMP180_Private_Macros STM32F429I DISCOVERY BMP180 Private Macros
  * @{
  */
/**
  * @}
  */ 
/** @defgroup STM32F429I_DISCOVERY_BMP180_Private_Variables STM32F429I DISCOVERY BMP180 Private Variables
  * @{
  */ 

/*!
 * @brief Calibration data
 */
struct bme280_calib_data;

/*!
 * @brief bme280 sensor structure which comprises of temperature, pressure and
 * humidity data
 */
#ifdef BME280_FLOAT_ENABLE
bme280_data *comp_data;
#else
bme280_data comp_data;
#endif /* BME280_USE_FLOATING_POINT */
/*!
 * @brief bme280 sensor structure which comprises of uncompensated temperature,
 * pressure and humidity data
 */
struct bme280_uncomp_data;
/*!
 * @brief bme280 sensor settings structure which comprises of mode,
 * oversampling and filter settings.
 */
struct bme280_settings;
/*!
 * @brief bme280 device structure
 */
extern bme280_DrvTypeDef bme280Drv;

extern bme280_dev dev;

bme280_DrvTypeDef *BME_280_driver;

/**
  * @}
  */

/** @defgroup STM32F429I_DISCOVERY_BMP180_Private_FunctionPrototypes STM32F429I DISCOVERY BMP180 Private FunctionPrototypes
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F429I_DISCOVERY_BMP180_Private_Functions STM32F429I DISCOVERY BMP180 Private Functions
  * @{
  */
  
/**
  * @brief  Set BMP180 Initialization.
  * @retval BMP_OK if no problem during initialization
  */
uint8_t BSP_BME_Init(bme280_dev *dev)//struct bme280_dev *dev
{  

	BME_280_driver = &bme280Drv;
	uint8_t ret = BME_ERROR;

  if (Bme_API_Read_ID(BME280_I2C_ADDR_PRIM) == BME280_CHIP_ID)
  {
	  dev->read = &BME_API_I2C_bus_read;
	  dev->write = &BME_API_I2C_bus_write;
	  dev->delay_ms = &BME_API_delay_msek;
	  dev->intf = BME280_I2C_INTF;
	  dev->dev_id = BME280_I2C_ADDR_PRIM;

	  BME_280_driver->Init(dev);		//struct bmp280_dev *dev
	  bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	  ret = BME_OK;
  }
  else
  {
    ret = BME_ERROR;
    printf("BME_ERROR");
  }
  return ret;
}


uint8_t BSP_BME_ReadData(void)
{
	__UNUSED int8_t rslt;
	uint8_t settings_sel;

	dev.settings.osr_h = BME280_OVERSAMPLING_1X;
	dev.settings.osr_p = BME280_OVERSAMPLING_16X;
	dev.settings.osr_t = BME280_OVERSAMPLING_2X;
    dev.settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    BME_280_driver->Set_sensor_settings(settings_sel, &dev);
    BME_280_driver->Set_sensor_mode(BME280_FORCED_MODE, &dev);
    BME_API_delay_msek(40);
	BME_280_driver->Get_sensor_data(BME280_ALL, &comp_data, &dev);
	return 0;
}

/**
  * @brief  Read temperature of BMP180 sensor.
  * @retval Compensated temperature
  */
int16_t BSP_BMP_ReadData()//struct bme280_dev *dev
{
	int8_t rslt;
	uint8_t settings_sel;
//	struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev.settings.osr_h = BME280_OVERSAMPLING_1X;
	dev.settings.osr_p = BME280_OVERSAMPLING_16X;
	dev.settings.osr_t = BME280_OVERSAMPLING_2X;
    dev.settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    rslt = bme280_set_sensor_settings(settings_sel, &dev);
    if (rslt != BME_OK)
    {
        return rslt;
    }

   	/* Continuously stream sensor data */
   	rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, &dev);
   	if (rslt != BME_OK)
   	{
   		return rslt;
   	}
   	/* Wait for the measurement to complete and print data @25Hz */
   	dev.delay_ms(40);
   	rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
   	if (rslt != BME_OK)
   	{
   		return rslt;
   	}
    return rslt;
}

/**
  * @brief  Read pressure of BMP180 sensor.
  * @retval Compensated pressure.
  */
int32_t BSP_BMP_ReadPressure(void)
{
  //int32_t pressure = 0x00;
  //pressure = PressureDrv->get_uncomp_pressure();
  //pressure = PressureDrv->Get_pressure(pressure);

//	int8_t (*Get_sensor_data)(uint8_t sensor_comp, struct bme280_data *comp_data, struct bme280_dev *dev);
//	void (*Parse_sensor_data)(const uint8_t *reg_data, struct bme280_uncomp_data *uncomp_data);
//	int8_t (*Compensate_data)(uint8_t sensor_comp, const struct bme280_uncomp_data *uncomp_data, struct bme280_data *comp_data, struct bme280_calib_data *calib_data);
  
  return 0;//pressure
}
/**
  * @brief  Read UNcompansated pressure of BMP180 sensor.
  * @retval UNcompensated pressure.
  */ 
uint32_t BSP_BMP_Read_U_pressure(void)
{
//	return PressureDrv->get_uncomp_pressure();
	return 0;
}
/**
  * @brief  Read UNcompansated temperature of BMP180 sensor.
  * @retval UNcompensated temperature.
  */
uint16_t BSP_BMP_Read_U_temperature(void)
{
	//return PressureDrv->get_uncomp_temperature();
	return 0;
}
/**
  * @}
  */ 
  
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/     
