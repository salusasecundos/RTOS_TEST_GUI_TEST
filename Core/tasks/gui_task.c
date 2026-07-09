/*
 * GUI_TASK.c
 *
 *  Created on: 6 апр. 2021 г.
 *      Author: Zver
 */



#include "gui_task.h"
#include "usbd_custom_hid_if.h"
//#include "bme280_defs.h"
#include "discovery_bme280.h"
#include "cmsis_os.h"
#include "usb_task.h"

osThreadId GuiTaskHandle;

char string2[32] ={0};

extern bme280_dev dev;

extern char string_USB[0x40];

int32_t rt,rp,rh;

void Gui_Task_Init(void)
{
	osThreadDef(guitask, gui_task, osPriorityLow, 0, 512);
	GuiTaskHandle = osThreadCreate(osThread(guitask), NULL);
}

/* USER CODE BEGIN Header_StartTask01 */
/**
  * @brief  Function implementing the myTask01 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask01 */
void gui_task(void const *argument)
{
	/* USER CODE BEGIN StartTask01 */
	uint8_t i = 0;

    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font20_1);

    sprintf(string2, "Chip ID : 0X%02X", dev.chip_id);
    GUI_DispStringAt(string2, 10, 85);

    /* Infinite loop */
    for(;;)
    {
    	while (i<=9)
    	{
    		osDelay(200);
    		sprintf(string2, "%d", i);
    		GUI_DispStringAt(string2, 10, 5);
    		i++;
    		/*
			colour += 0xFF;
			if (colour == GUI_WHITE)
			{
				colour = 0xFF0000FF;
			}
			GUI_SetBkColor(colour);
			printf("\nColour is 0x%08X", (unsigned int)colour);
    		 */

    		rt = comp_data.temperature;
			rp = comp_data.pressure;
			rh = comp_data.humidity;


    		BSP_BME_ReadData();
    		sprintf(string2, "Temperatura : %li.%li", rt/100, rt%100);
    		GUI_DispStringAt(string2, 10, 25);
    		sprintf(string2, "Davlenie        : %li.%li", rp / 10000, rp % 10000);
    		GUI_DispStringAt(string2, 10, 45);
    		sprintf(string2, "Vlazhnost      : %li.%li", rh / 1000, rh % 1000);
    		GUI_DispStringAt(string2, 10, 65);
			sprintf(string2, "USB_RECIEVED : %d", string_USB[2]);
			GUI_DispStringAt(string2, 10, 105);
			sprintf(string2, "USB_RECIEVED : %d", string_USB[3]);
			GUI_DispStringAt(string2, 10, 125);
			sprintf(string2, "USB_RECIEVED : %d", string_USB[1]);
			GUI_DispStringAt(string2, 10, 145);
		}
		i=0;
	}
  /* USER CODE END StartTask01 */
}
