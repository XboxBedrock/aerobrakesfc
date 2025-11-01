/*
 * servo_task.c
 *
 *  Created on: Oct 23, 2025
 *      Author: sushrut
 */


#include "common_porting.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "fatfs.h"
#include "spi.h"
#include "sd_task.h"
#include "main.h"
#include <string.h>
#include <stdio.h>


void StartSDTask(void * argument)
{
		QueueHandle_t xMyQueue;

		// Cast pvParameters to a pointer to QueueHandle_t and dereference it
		xMyQueue = *(QueueHandle_t *)argument;

	  FATFS FatFs; 	//Fatfs handle
	  FIL fil; 		//File handle
	  FRESULT fres; //Result after operations

	  //Open the file system
	  fres = f_mount(&FatFs, "", 1); //1=mount now
	  if (fres != FR_OK) {
		printf("f_mount error (%i)\r\n", fres);
		while(1);
	  }

	  DWORD free_clusters, free_sectors, total_sectors;

	  FATFS* getFreeFs;

	  fres = f_getfree("", &free_clusters, &getFreeFs);
	  if (fres != FR_OK) {
		printf("f_getfree error (%i)\r\n", fres);
		while(1);
	  }

	  //Formula comes from ChaN's documentation
	  total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	  free_sectors = free_clusters * getFreeFs->csize;

	  printf("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);

	  MyMessage_t xReceivedMessage;


	  fres = f_open(&fil, "log.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);

	  BYTE writeBuf[30];
	  strncpy((char*)writeBuf, "Loggy", 5);

	  UINT bytesWrote;
	  fres = f_write(&fil, writeBuf, 8, &bytesWrote);
	  f_printf(&fil, "Hello There\n");

	  f_close(&fil);

	  f_mount(NULL, "", 0);

	  while (1)
	  {
	    /* USER CODE END WHILE */

	    /* USER CODE BEGIN 3 */
		  if (xQueueReceive(xMyQueue, &xReceivedMessage, portMAX_DELAY) == pdPASS) {
			  fres = f_mount(&FatFs, "", 1); //1=mount now
			  if (fres != FR_OK) {
				printf("f_mount error (%i)\r\n", fres);
				while(1);
			  }
			  fres = f_open(&fil, "log.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);

			  f_printf(&fil, xReceivedMessage.message);

			  //BYTE writeBuf[xReceivedMessage.size+1];
			  //strncpy((char*)writeBuf, xReceivedMessage.message, xReceivedMessage.size);

			  //UINT bytesWrote;
			  //fres = f_write(&fil, writeBuf, xReceivedMessage.size+1, &bytesWrote);

			  f_close(&fil);
			  f_mount(NULL, "", 0);
		  }




	  }
}
