/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "bridge.h"

extern osThreadId bridgeConfigTaskHandle;
extern osThreadId USBStreamTaskHandle;
extern osMessageQId USBStreamQueueHandle;

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */


/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
  /* add mutexes, ... */

  /* add semaphores, ... */

  /* start timers, add new ones, ... */

  /* Create the thread(s) */
  osThreadDef(bridgeConfigTask, APP_BRIDGE_CANConfigTask, osPriorityNormal, 0, 128);
  bridgeConfigTaskHandle = osThreadCreate(osThread(bridgeConfigTask), NULL);

  osThreadDef(USBStreamTask, APP_BRIDGE_USBStreamTask, osPriorityNormal, 0, 128);
  USBStreamTaskHandle = osThreadCreate(osThread(USBStreamTask), NULL);

  /* add threads, ... */

  /* add queues, ... */
  osMessageQDef(USBStreamQueue, 8, uint8_t);
  USBStreamQueueHandle = osMessageCreate(osMessageQ(USBStreamQueue), NULL);
}
