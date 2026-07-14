/*
 * bme280_task.c
 *
 *  Created on: 6 апр. 2021 г.
 *      Author: Zver
 */

#include "usb_task.h"
#include "usbd_custom_hid_if.h"
#include "bme280_task.h"
//#include "discovery_bme280.h"
#include "cmsis_os.h"


extern bme280_data comp_data;

osMailQId Sensor_to_usb_Queue;
osMailQId Sensor_to_gui_Queue;

osThreadId SensorTaskHandle;
//uint8_t ready = 0;
//char string[32] ={0};
//char string_USB[0x40] ={0};

void Sensor_Task_Init(void)
{
	osThreadDef(sensortask, sensor_task, osPriorityLow, 0, 512);
	SensorTaskHandle = osThreadCreate(osThread(sensortask), NULL);

	osMailQDef(sensor_to_usb_queue, MAIL_SIZE, struct_usb);
	Sensor_to_usb_Queue = osMailCreate(osMailQ(sensor_to_usb_queue), NULL);

	osMailQDef(sensor_to_gui_queue, MAIL_SIZE, struct_usb);
	Sensor_to_gui_Queue = osMailCreate(osMailQ(sensor_to_gui_queue), NULL);
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void sensor_task(void const * argument)
{

//	struct_data *qstruct;
	struct_data *qstruct;
	uint8_t i = 0;

	for(;;)
	{

		if (i == 10)
		{
			i = 0;
		}
        i++;
		qstruct = osMailAlloc(Sensor_to_gui_Queue, 5);

		if (qstruct != NULL)
		{
			//memory clean but not so neccesary
//            memset(o_qstruct, 0, sizeof(*o_qstruct));
			qstruct->string_data[1] = i;

            if (osMailPut(Sensor_to_gui_Queue, qstruct) != osOK)
            {
                //В очередь положить не удалось. Возвращаем блок обратно в пул.
                osMailFree(Sensor_to_gui_Queue, qstruct);
            }
            osDelay(100);
		}

		osDelay(500);

	}
}

