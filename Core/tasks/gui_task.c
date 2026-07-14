/*
 * GUI_TASK.c
 *
 *  Created on: 6 апр. 2021 г.
 *      Author: Zver
 */

#include "gui_task.h"
#include "usbd_custom_hid_if.h"
#include "bme280_task.h"
#include "discovery_bme280.h"
#include "cmsis_os.h"

extern osMailQId Sensor_to_gui_Queue;
extern char string_data[0x40];
extern bme280_dev dev;

osThreadId GuiTaskHandle;
osMailQId USB_Queue;

//int32_t rt, rp, rh;
//int32_t colour;

void Gui_Task_Init(void)
{
	osThreadDef(guitask, gui_task, osPriorityLow, 0, 512);
	GuiTaskHandle = osThreadCreate(osThread(guitask), NULL);

	osMailQDef(usbinqueue, MAIL_SIZE, struct_usb);
	USB_Queue = osMailCreate(osMailQ(usbinqueue), NULL);
}


void gui_task(void const *argument)
{
	uint8_t i = 0;
    osEvent event;
    struct_data *message;
    uint8_t buffer[0x40];
	uint8_t usb_data_in[0x40];
    bme280_data buffer1;	//sensor_data_in
	bme280_data sensor_data_in;
    int32_t irt, irp, irh;
	struct_usb *qstruct;
	uint8_t ready = 0;

	char string_USB[0x40];
	char string2[32] ={0};

    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font20_1);

    sprintf(string2, "Chip ID : 0X%02X", dev.chip_id);
    GUI_DispStringAt(string2, 10, 85);

    /* Infinite loop */
    for(;;)
    {
    	while (i <= 9)
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

            event = osMailGet(Sensor_to_gui_Queue, 5);
            if (event.status == osEventMail)
            {
                message = event.value.p;
        		memcpy(buffer, message->string_data, 64);
//				memcpy(usb_data_in, message->string_data, 64);
        		buffer1 = message->sensor_data;	//sensor_data_in
				sensor_data_in = message->sensor_data;
                osMailFree(Sensor_to_gui_Queue, message);
            }

    		event = osMailGet(USB_Queue, NON_TIMEOUT);
    		if (event.status == osEventMail)
    		{
    			qstruct = event.value.p;
    			memcpy(string_USB, qstruct->string_USB, 64);
    			ready = qstruct->usb_recieved;
    			osMailFree(USB_Queue, qstruct);
    		}

    		irt = buffer1.temperature;
			irp = buffer1.pressure;
			irh = buffer1.humidity;
/*
    		sprintf(string2, "Temperatura : %li.%li", sensor_data_in.temperature/100, sensor_data_in.temperature%100);
    		GUI_DispStringAt(string2, 10, 25);
    		sprintf(string2, "Davlenie        : %li.%li", sensor_data_in.pressure / 10000, sensor_data_in.pressure % 10000);
    		GUI_DispStringAt(string2, 10, 45);
    		sprintf(string2, "Vlazhnost      : %li.%li", sensor_data_in.humidity / 1000, sensor_data_in.humidity % 1000);
    		GUI_DispStringAt(string2, 10, 65);
*/
    		sprintf(string2, "Temperatura : %li.%li", irt/100, irt%100);
    		GUI_DispStringAt(string2, 10, 25);
    		sprintf(string2, "Davlenie        : %li.%li", irp / 10000, irp % 10000);
    		GUI_DispStringAt(string2, 10, 45);
    		sprintf(string2, "Vlazhnost      : %li.%li", irh / 1000, irh % 1000);
    		GUI_DispStringAt(string2, 10, 65);
			//-----------------------------------------------------------
			sprintf(string2, "USB_RECIEVED : %d", string_USB[1]);
			GUI_DispStringAt(string2, 10, 105);
			sprintf(string2, "USB_RECIEVED : %d", string_USB[2]);
			GUI_DispStringAt(string2, 10, 125);
			sprintf(string2, "USB_RECIEVED : %d", string_USB[3]);
			GUI_DispStringAt(string2, 10, 145);
			//-----------------------------------------------------------
			sprintf(string2, "USB_STATUS : %d", buffer[1]);
			GUI_DispStringAt(string2, 10, 165);
			//-----------------------------------------------------------
			sprintf(string2, "LAN_STATUS : ");
			GUI_DispStringAt(string2, 10, 185);
		}
		i=0;
	}
}
