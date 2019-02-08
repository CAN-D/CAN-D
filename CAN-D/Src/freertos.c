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

osThreadId bridgeConfigTaskHandle;

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
  osThreadDef(bridgeConfigTask, APP_BRIDGE_ConfigTask, osPriorityNormal, 0, 128);
  bridgeConfigTaskHandle = osThreadCreate(osThread(bridgeConfigTask), NULL);

  /* add threads, ... */

  /* add queues, ... */
}
