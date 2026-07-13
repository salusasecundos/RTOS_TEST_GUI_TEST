/*
 * usb_task.c
 *
 *  Created on: 6 апр. 2021 г.
 *      Author: Zver
 */
#include "usb_task.h"
#include "usbd_custom_hid_if.h"
//#include "bme280_defs.h"
#include "discovery_bme280.h"
#include "cmsis_os.h"


extern bme280_data comp_data;


osMailQId USB_Queue;
osMailQId USB_Out_Queue;

osThreadId UsbTaskHandle;
uint8_t ready = 0;
char string[32] ={0};
char string_USB[0x40] ={0};

void Usb_Task_Init(void)
{
	osThreadDef(usbtask, usb_task, osPriorityLow, 0, 512);
	UsbTaskHandle = osThreadCreate(osThread(usbtask), NULL);

	osMailQDef(usbinqueue, MAIL_SIZE, struct_usb);
	USB_Queue = osMailCreate(osMailQ(usbinqueue), NULL);

	osMailQDef(usboutqueue, MAIL_SIZE, struct_usb);
	USB_Out_Queue = osMailCreate(osMailQ(usboutqueue), NULL);

}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void usb_task(void const * argument)
{
	/* USER CODE BEGIN StartTask04 */
	MX_USB_DEVICE_Init();

	osEvent event;
	struct_usb *qstruct;
	struct_usb *o_qstruct;

	/* Infinite loop */
	for(;;)
	{
//		osDelay(200);
		BSP_LED_Toggle(LED3);//LED_GREEN
/*
		sprintf(string, "Temperatura : %li.%li", comp_data.temperature/100, comp_data.temperature%100);
		printf(string);
		printf("\n");
*/
		event = osMailGet(USB_Queue, NON_TIMEOUT);
		if (event.status == osEventMail)
		{
			qstruct = event.value.p;
			memcpy(string_USB, qstruct->string_USB, 64);
			ready = qstruct->usb_recieved;
			osMailFree(USB_Queue, qstruct);

//			sprintf(string, "%d", string_USB[2]);
//			printf(string);
//			printf("\n");
		}

		o_qstruct = osMailAlloc(USB_Out_Queue, 10);

		o_qstruct->string_USB[5] = (rt >> 24);
		o_qstruct->string_USB[6] = ((rt >> 16) & 0xFF);
		o_qstruct->string_USB[7] = ((rt >> 8) & 0xFF);
		o_qstruct->string_USB[8] = (rt & 0xFF);

		o_qstruct->string_USB[9] = (rp >> 24);
		o_qstruct->string_USB[10] = ((rp >> 16) & 0xFF);
		o_qstruct->string_USB[11] = ((rp >> 8) & 0xFF);
		o_qstruct->string_USB[12] = (rp & 0xFF);

		/*
		printf("%08X\n", o_qstruct->string_USB[5]);
		printf("%08X\n", o_qstruct->string_USB[6]);
		printf("%08X\n", o_qstruct->string_USB[7]);
		printf("%08X\n", o_qstruct->string_USB[8]);
*/

		o_qstruct->string_USB[13] = (rh >> 24);
		o_qstruct->string_USB[14] = ((rh >> 16) & 0xFF);
		o_qstruct->string_USB[15] = ((rh >> 8) & 0xFF);
		o_qstruct->string_USB[16] = (rh & 0xFF);


//		sprintf(string2, "Temperatura : %li.%li", rt/100, rt%100);

//		sprintf(string2, "Temperatura : %li.%li", rt/100, rt%100);
//		printf("Temperatura : %li.%li \r", rh/100, rh%100);
/*
		printf("%08X\n", o_qstruct->string_USB[13]);
		printf("%08X\n", o_qstruct->string_USB[14]);
		printf("%08X\n", o_qstruct->string_USB[15]);
		printf("%08X\n", o_qstruct->string_USB[16]);
		printf("\n");
*/

		if (o_qstruct != NULL)
		{
		    /* заполняешь o_qstruct */

		    osMailPut(USB_Out_Queue, o_qstruct);
		}



/*
		volatile uint32_t jopa = *(uint32_t *)0xDEADBEEF;
		int (*bad_instruction)(void) = (void *)0xE0000000;
		bad_instruction();
*/
	}
  /* USER CODE END StartTask04 */
}
