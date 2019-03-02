/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "bridge.h"
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
    /* add mutexes, ... */

    /* add semaphores, ... */

    /* start timers, add new ones, ... */

    /* Create the thread(s) */
    osThreadDef(bridgeConfigTask, APP_BRIDGE_CANConfigTask, osPriorityNormal, 0, 128);
    bridgeConfigTaskHandle = osThreadCreate(osThread(bridgeConfigTask), NULL);

    osThreadDef(CANMonitorTask, APP_BRIDGE_CANMonitorTask, osPriorityNormal, 0, 128);
    CANMonitorTaskHandle = osThreadCreate(osThread(CANMonitorTask), NULL);

    osThreadDef(CANTransmitTask, APP_BRIDGE_CANTransmitTask, osPriorityNormal, 0, 128);
    CANMonitorTaskHandle = osThreadCreate(osThread(CANTransmitTask), NULL);

    osThreadDef(GPSMonitorTask, APP_BRIDGE_GPSMonitorTask, osPriorityNormal, 0, 128);
    GPSMonitorTaskHandle = osThreadCreate(osThread(GPSMonitorTask), NULL);

    /* add threads, ... */

    /* add queues, ... */
    osMessageQDef(CANRxQueue, 8, uint8_t);
    CANRxQueueHandle = osMessageCreate(osMessageQ(CANRxQueue), NULL);

    osMessageQDef(CANTxQueue, 16, CANTxMessage);
    CANTxQueueHandle = osMessageCreate(osMessageQ(CANTxQueue), NULL);

    osMessageQDef(UARTGprmcQueue, 128, char);
    UARTGprmcQueueHandle = osMessageCreate(osMessageQ(UARTGprmcQueue), NULL);
}

/* Private functions ---------------------------------------------------------*/
