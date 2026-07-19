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

osThreadId GuiTaskHandle;
extern bme280_dev dev;

extern osMailQId Sensor_to_gui_Queue;
osMailQId Usb_To_gui_Queue;

//int32_t colour;

void Gui_Task_Init(void)
{
	osThreadDef(guitask, gui_task, osPriorityLow, 0, 512);
	GuiTaskHandle = osThreadCreate(osThread(guitask), NULL);

	osMailQDef(usbinqueue, MAIL_SIZE, struct_usb);
	Usb_To_gui_Queue = osMailCreate(osMailQ(usbinqueue), NULL);
}

void gui_task(void const *argument)
{
	uint8_t i = 0;
	uint32_t counter = 0;
	uint8_t ready = 0;
    uint8_t control_data[0x40] = {0};
    uint8_t usb_data_in[0x40] = {0};
	char display_str[32] = {0};

	bme280_data sensor_data_in;

	struct_usb *qstruct;
    struct_data *message;

    osEvent event;

//    GUI_SetBkColor(GUI_LIGHTBLUE);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font20_1);

    sprintf(display_str, "Chip ID : 0X%02X", dev.chip_id);
    GUI_DispStringAt(display_str, 10, 25);

    /* Infinite loop */
    for(;;)
    {

    	if (counter == 10){ i++ ; counter = 0; if (i == 10){i = 0;}}
    	else { counter++; }

		sprintf(display_str, "%d  ", i);
		GUI_DispStringAt(display_str, 10, 5);

/*
		colour += 0xFF;
		if (colour == GUI_WHITE)
		{
			colour = 0xFF0000FF;
		}
		GUI_SetBkColor(colour);
		printf("\nColour is 0x%08X", (unsigned int)colour);
*/
		//-----------------------------------------------------------------------------------------------
        event = osMailGet(Sensor_to_gui_Queue, 5);
        if (event.status == osEventMail)
        {
            message = event.value.p;
    		memcpy(control_data, message->string_data, 64);
    		sensor_data_in = message->sensor_data;
            osMailFree(Sensor_to_gui_Queue, message);
        }
        //-----------------------------------------------------------------------------------------------
        event = osMailGet(Usb_To_gui_Queue, NON_TIMEOUT);
        if (event.status == osEventMail)
        {
        	qstruct = event.value.p;
        	memcpy(usb_data_in, qstruct->string_USB, 64);
        	ready = qstruct->usb_recieved;
        	osMailFree(Usb_To_gui_Queue, qstruct);
  		}
        //-----------------------------------------------------------------------------------------------
		sprintf(display_str, "Temperatura : %li.%li  ", sensor_data_in.temperature/100, sensor_data_in.temperature%100);
		GUI_DispStringAt(display_str, 10, 45);
		sprintf(display_str, "Davlenie        : %li.%li  ", sensor_data_in.pressure / 10000, sensor_data_in.pressure % 10000);
		GUI_DispStringAt(display_str, 10, 65);
		sprintf(display_str, "Vlazhnost      : %li.%li  ", sensor_data_in.humidity / 1000, sensor_data_in.humidity % 1000);
		GUI_DispStringAt(display_str, 10, 85);
		sprintf(display_str, "USB_STATUS : %d  ", control_data[39]);
		GUI_DispStringAt(display_str, 10, 105);
		//-----------------------------------------------------------------------------------------------
		sprintf(display_str, "USB_RECIEVED : %d  ", usb_data_in[1]);
		GUI_DispStringAt(display_str, 10, 125);
		sprintf(display_str, "USB_RECIEVED : %d  ", usb_data_in[2]);
		GUI_DispStringAt(display_str, 10, 145);
		sprintf(display_str, "USB_RECIEVED : %d  ", usb_data_in[3]);
		GUI_DispStringAt(display_str, 10, 165);
		//-----------------------------------------------------------------------------------------------
		sprintf(display_str, "LAN_STATUS :  ");
		GUI_DispStringAt(display_str, 10, 185);
	}
}
