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
#include "can.h"

osThreadId canTaskHandle;
osMessageQId canDataQueueHandle;

void canBridgeTask(void const * argument);
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
  osThreadDef(canTask, canBridgeTask, osPriorityNormal, 0, 128);
  canTaskHandle = osThreadCreate(osThread(canTask), NULL);

  /* add threads, ... */

  /* add queues, ... */
  osMessageQDef(canDataQueue, 8, uint8_t);
  canDataQueueHandle = osMessageCreate(osMessageQ(canDataQueue), NULL);
}

/**
  * @brief  Function implementing the canBridgeTask thread.
  * @param  argument: Not used 
  * @retval None
  */
void canBridgeTask(void const * argument)
{
  for(;;)
  {
    // TODO: create BSP pkg for our PCB

    // Start/Stop the CAN module on button press
//    if (BSP_PB_GetState(BUTTON_KEY) == KEY_PRESSED)
//    {
//      if (hcan.State == HAL_CAN_STATE_LISTENING)
//      {
//        HAL_CAN_Stop(&hcan);
//        HAL_CAN_DeactivateNotification(&hcan, CAN_IT_START);
//      }
//      else if (hcan.State == HAL_CAN_STATE_READY)
//      {
//        // Changes the hcan.State to HAL_CAN_STATE_LISTENING
//        HAL_CAN_Start(&hcan);
//        HAL_CAN_ActivateNotification(&hcan, CAN_IT_START);
//      }
//    }

    // Monitor CAN RX data
    if (hcan.State == HAL_CAN_STATE_LISTENING)
    {
      osEvent event;
      uint8_t rxData;

      event = osMessageGet(canDataQueueHandle, CAN_RXQ_TIMEOUT_MS);
      if (event.status == osEventMessage)
      {
        rxData = (uint8_t)event.value.v;
        // TODO: pass along CAN RX data
      }
    }

	  osDelay(1);
  }
}
