/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "gps.h"
#include "can.h"
#include "cmsis_os.h"
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
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
    APP_CAN_InitTasks();
    /* add mutexes, ... */

    /* add semaphores, ... */

    /* start timers, add new ones, ... */

    /* Create the thread(s) */

    osThreadDef(GPSMonitorTask, APP_BRIDGE_GPSMonitorTask, osPriorityNormal, 0, 128);
    GPSMonitorTaskHandle = osThreadCreate(osThread(GPSMonitorTask), NULL);

    osMessageQDef(UARTGprmcQueue, 128, char);
    UARTGprmcQueueHandle = osMessageCreate(osMessageQ(UARTGprmcQueue), NULL);

    /* add threads, ... */

    /* add queues, ... */
}

/* Private functions ---------------------------------------------------------*/
