/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "can.h"
#include "cmsis_os.h"
#include "gps.h"
#include "main.h"
#include "task.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
extern osThreadId bridgeConfigTaskHandle;
extern osThreadId CANMonitorTaskHandle;
extern osThreadId GPSMonitorTaskHandle;

extern osMessageQId CANRxQueueHandle;
extern osMessageQId CANTxQueueHandle;
extern osMessageQId UARTGprmcQueueHandle;

/* Private function prototypes -----------------------------------------------*/
void APP_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void APP_FREERTOS_Init(void)
{
    APP_CAN_InitTasks();
    APP_GPS_InitTasks();
}

/* Private functions ---------------------------------------------------------*/
