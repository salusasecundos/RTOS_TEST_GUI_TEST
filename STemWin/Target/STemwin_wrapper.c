#include "GUIDRV_FlexColor.h"
#include "STemwin_wrapper.h"


/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#define XSIZE_PHYS       320 
#define YSIZE_PHYS       240 
extern volatile GUI_TIMER_TIME OS_TimeMS;
/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif

/*********************************************************************
*
*       Defines, sfrs
*
**********************************************************************
*/
//
// COG interface register addr.
//

typedef struct
{
  __IO uint16_t REG;
  __IO uint16_t RAM;

}LCD_CONTROLLER_TypeDef;

//#define A16                 (0x00020000-2)
/* The Bank address need to be entred by the USER */

#define FMC_BANK_BASE  ((uint32_t) (0x60000000 | 0x0001FFFE))					//((uint32_t)       0x60000000  )
#define FMC_BANK       ((LCD_CONTROLLER_TypeDef *) FMC_BANK_BASE)

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

static void     FMC_BANK_WriteData(uint16_t Data);
static void     FMC_BANK_WriteReg(uint8_t Reg);
static uint16_t FMC_BANK_ReadData(void);

static void     LCDController_Init(void);
static void		gdisp_lld_init();
static void		Init_3_LCD();

/********************************************************************
*
*       LcdWriteReg
*
* Function description:
*   Sets display register
*/
static void LcdWriteReg(U16 Data) 
{
  FMC_BANK_WriteReg(Data);
}

/********************************************************************
*
*       LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
static void LcdWriteData(U16 Data) 
{
  FMC_BANK_WriteData(Data);
}

/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
static void LcdWriteDataMultiple(U16 * pData, int NumItems) 
{
  while (NumItems--) 
  {
    FMC_BANK_WriteData(*pData++);
  }
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
static void LcdReadDataMultiple(U16 * pData, int NumItems) 
{
  while (NumItems--) 
  {
    *pData++ = FMC_BANK_ReadData();
  }
}

/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) 
{
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};

  /* Set display driver and color conversion */
  pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_M565 , 0, 0);
 
  /* Display driver configuration, required for Lin-driver */
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);

  /* supported parameters: GUI_SWAP_XY, GUI_MIRROR_X, GUI_MIRROR_Y or any combination of these paramters */
  /* Orientation */
  Config.Orientation = GUI_SWAP_XY | GUI_MIRROR_Y;
  GUIDRV_FlexColor_Config(pDevice, &Config);
    
 #if (NUM_BUFFERS > 1)
      GUI_MULTIBUF_ConfigEx(0, NUM_BUFFERS);
  #endif

  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // Set controller and operation mode
  //
  PortAPI.pfWrite16_A0  = LcdWriteReg;
  PortAPI.pfWrite16_A1  = LcdWriteData;
  PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = LcdReadDataMultiple;

  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66702, GUIDRV_FLEXCOLOR_M16C0B16);

}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData)
{
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd)
  {
  case LCD_X_INITCONTROLLER:
  {
   
    /* Component Initialization */
//    LCDController_Init();
    gdisp_lld_init();
//    Init_3_LCD();
    
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/**
  * @brief  Writes register value.
  * @param  Data: 
  * @retval None
  */
static void FMC_BANK_WriteData(uint16_t Data) 
{
  /* Write 16-bit Reg */
  FMC_BANK->RAM = Data;
}

/**
  * @brief  Writes register address.
  * @param  Reg: 
  * @retval None
  */
static void FMC_BANK_WriteReg(uint8_t Reg) 
{
  /* Write 16-bit Index, then write register */
  FMC_BANK->REG = Reg;
}

/*
 * Write to LCD RAM.
 */
void Write_Command(uint16_t reg, uint16_t data)
{
	FMC_BANK->REG = reg;
	FMC_BANK->RAM = data;
}

/**
  * @brief  Reads register value.
  * @param  None
  * @retval Read value
  */
static uint16_t FMC_BANK_ReadData(void) 
{
  return FMC_BANK->RAM;
}

void GRAPHICS_IncTick(void)
{
  
    OS_TimeMS++;
} 
void GRAPHICS_HW_Init(void)
{ 
	  MX_GPIO_Init();
//	  MX_CRC_Init();
	  MX_FSMC_Init();
}

void GRAPHICS_Init(void)
{ 
 
  /* Initialize the GUI */
  GUI_Init();
   
  /* Activate the use of memory device feature */
     /* USER CODE BEGIN memory_device */

//       WM_SetCreateFlags(WM_CF_MEMDEV);

     /* USER CODE END memory_device */
}

/**
  * @brief  Initializes the LCD.
  * @param  None
  * @retval None
  */
static void __UNUSED LCDController_Init(void)
{ 
/* special hardware initialization may be needed before controller iniialization */

/* Initialize LCD controller */
    /* USER CODE BEGIN LCD_controller */

         //component_init();

	  /* Initialize ILI9325 low level bus layer ----------------------------------*/
//	  LCD_IO_Init();

	  /* Reset */
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_Delay(30);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(10);


	  /* Display ON Sequence (data sheet page 72) */

		Write_Command(0x07, 0x0021);
		Write_Command(0x00, 0x0001);
		Write_Command(0x07, 0x0023);
		Write_Command(0x10, 0x0000);  /* Exit Sleep Mode */  HAL_Delay(30);
		Write_Command(0x07, 0x0033);
	  /*
	   * Entry Mode R11h = 6018h
	   *
	   * DFM1 = 1, DFM0 = 1 => 65k Color Mode
	   * ID0 = 1, AM = 1    => the way of automatic incrementing
	   *                       of address counter in RAM
	   */
		Write_Command(0x11, 0x6018);
		Write_Command(0x02, 0x0600);  /* AC Settings *///600

	  /* Initialize other Registers */

	  /*
	   * Device Output Control R01h = 2B3Fh
	   *
	   * REV = 1            => character and graphics are reversed
	   * BGR = 1            => BGR color is assigned from S0
	   * TB  = 1            => sets gate output sequence (see datasheet page 29)
	   * MUX[8, 5:0]        => specify number of lines for the LCD driver
	   */
		Write_Command(0x0001, 0x2B3F);

}
  



static void __UNUSED Init_3_LCD(void)
{
	/* Reset */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_Delay(30);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_Delay(10);

//	unsigned short val = 0;
//	val = LCD->REG;
//	return val;

	Write_Command(0x0000, 0x0001); 	HAL_Delay(1);
	Write_Command(0x0003, 0xA8A4); 	HAL_Delay(1);
	Write_Command(0x000C, 0x0000); 	HAL_Delay(1);
	Write_Command(0x000D, 0x080C); 	HAL_Delay(1);
	Write_Command(0x000E, 0x2B00); 	HAL_Delay(1);
	Write_Command(0x001E, 0x00B7); 	HAL_Delay(1);
	Write_Command(0x0001, 0x2B3F); 	HAL_Delay(1);	//
	Write_Command(0x0002, 0x0600); 	HAL_Delay(1);
	Write_Command(0x0010, 0x0000); 	HAL_Delay(35);	//exit sleep mode

	Write_Command(0x0011, 0x6070); 	HAL_Delay(1);
	Write_Command(0x0005, 0x0000); 	HAL_Delay(1);
	Write_Command(0x0006, 0x0000); 	HAL_Delay(1);
	Write_Command(0x0016, 0xEF1C); 	HAL_Delay(1);
	Write_Command(0x0017, 0x0003); 	HAL_Delay(1);
	Write_Command(0x0007, 0x0233); 	HAL_Delay(1);
	Write_Command(0x000B, 0x0000); 	HAL_Delay(1);
	Write_Command(0x000F, 0x0000);	HAL_Delay(1);

	Write_Command(0x0041, 0x0000); 	HAL_Delay(1);
	Write_Command(0x0042, 0x0000); 	HAL_Delay(1);
	Write_Command(0x0048, 0x0000); 	HAL_Delay(1);
	Write_Command(0x0049, 0x013F); 	HAL_Delay(1);
	Write_Command(0x004A, 0x0000); 	HAL_Delay(1);
	Write_Command(0x004B, 0x0000); 	HAL_Delay(1);
	Write_Command(0x0044, 0xEF00); 	HAL_Delay(1);
	Write_Command(0x0045, 0x0000); 	HAL_Delay(1);
	Write_Command(0x0046, 0x013F); 	HAL_Delay(1);
// Adjust the Gamma Curve
	Write_Command(0x0030, 0x0707); 	HAL_Delay(1);
	Write_Command(0x0031, 0x0204); 	HAL_Delay(1);
	Write_Command(0x0032, 0x0204); 	HAL_Delay(1);
	Write_Command(0x0033, 0x0502); 	HAL_Delay(1);
	Write_Command(0x0034, 0x0507); 	HAL_Delay(1);
	Write_Command(0x0035, 0x0204); 	HAL_Delay(1);
	Write_Command(0x0036, 0x0204); 	HAL_Delay(1);
	Write_Command(0x0037, 0x0502); 	HAL_Delay(1);
	Write_Command(0x003A, 0x0302); 	HAL_Delay(1);
	Write_Command(0x003B, 0x0302); 	HAL_Delay(1);

	Write_Command(0x0023, 0x0000); 	HAL_Delay(1);
	Write_Command(0x0024, 0x0000); 	HAL_Delay(1);
	Write_Command(0x0025, 0x8000); 	HAL_Delay(1);
	Write_Command(0x004f, 0x0000);
	Write_Command(0x004e, 0x0000);
	Write_Command(0x0022, 0x0000);

}



static void __UNUSED gdisp_lld_init(void) {


	// Initialise the board interface

	// Hardware reset
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_Delay(30);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_Delay(10);

	Write_Command(0x00, 0x0001);		HAL_Delay(1);
	Write_Command(0x03, 0xA8A4);    	HAL_Delay(1);
	Write_Command(0x0C, 0x0000);    	HAL_Delay(1);
	Write_Command(0x0D, 0x080C);    	HAL_Delay(1);
    Write_Command(0x0E, 0x2B00);    	HAL_Delay(1);
    Write_Command(0x1E, 0x00B0);    	HAL_Delay(1);
	Write_Command(0x01, 0x2B3F);		HAL_Delay(1);
    Write_Command(0x02, 0x0600);    	HAL_Delay(1);
    Write_Command(0x10, 0x0000);    	HAL_Delay(1);
    Write_Command(0x11, 0x6070);    	HAL_Delay(1);
    Write_Command(0x05, 0x0000);    	HAL_Delay(1);
    Write_Command(0x06, 0x0000);    	HAL_Delay(1);
    Write_Command(0x16, 0xEF1C);    	HAL_Delay(1);
    Write_Command(0x17, 0x0003);    	HAL_Delay(1);
    Write_Command(0x07, 0x0133);    	HAL_Delay(1);
    Write_Command(0x0B, 0x0000);    	HAL_Delay(1);
    Write_Command(0x0F, 0x0000);    	HAL_Delay(1);
    Write_Command(0x41, 0x0000);    	HAL_Delay(1);
    Write_Command(0x42, 0x0000);    	HAL_Delay(1);
    Write_Command(0x48, 0x0000);    	HAL_Delay(1);
    Write_Command(0x49, 0x013F);    	HAL_Delay(1);
    Write_Command(0x4A, 0x0000);    	HAL_Delay(1);
    Write_Command(0x4B, 0x0000);    	HAL_Delay(1);
    Write_Command(0x44, 0xEF00);    	HAL_Delay(1);
    Write_Command(0x45, 0x0000);    	HAL_Delay(1);
    Write_Command(0x46, 0x013F);    	HAL_Delay(1);
    Write_Command(0x30, 0x0707);    	HAL_Delay(1);
    Write_Command(0x31, 0x0204);    	HAL_Delay(1);
    Write_Command(0x32, 0x0204);    	HAL_Delay(1);
    Write_Command(0x33, 0x0502);    	HAL_Delay(1);
    Write_Command(0x34, 0x0507);    	HAL_Delay(1);
    Write_Command(0x35, 0x0204);    	HAL_Delay(1);
    Write_Command(0x36, 0x0204);    	HAL_Delay(1);
    Write_Command(0x37, 0x0502);    	HAL_Delay(1);
    Write_Command(0x3A, 0x0302);    	HAL_Delay(1);
    Write_Command(0x3B, 0x0302);    	HAL_Delay(1);
    Write_Command(0x23, 0x0000);    	HAL_Delay(1);
    Write_Command(0x24, 0x0000);    	HAL_Delay(1);
    Write_Command(0x25, 0x8000);    	HAL_Delay(1);
    Write_Command(0x4f, 0x0000);		HAL_Delay(1);
    Write_Command(0x4e, 0x0000);		HAL_Delay(1);

	/* Turn on the back-light */
}


/*************************** End of file ****************************/

