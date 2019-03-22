/**
  ******************************************************************************
  * File Name          : gps.c
  * Description        : This file provides code for dealing with gps data.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gps.h"
#include "fatfs.h"
#include "stm32302c_custom.h"
#include "stm32302c_custom_gps.h"
#include "stm32f3xx_hal_gpio.h"
#include "usbd_cdc_if.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct {
    char raw[128];
} GPSData;

/* Private define ------------------------------------------------------------*/
#define GPS_BUFFER_LENGTH 2

/* Private variables ---------------------------------------------------------*/
static char gpsLogIdentifier[] = GPS_LOG_FILENAME;
/* Threads */
static osThreadId GPSMonitorTaskHandle;
/* Queues */
static osMessageQId UARTGprmcQueueHandle; /* Handles GPS GPRMC data */
/* Data Pools */
osPoolDef(GPSDataPool, GPS_BUFFER_LENGTH, GPSData);
static osPoolId GPSDataPool;

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void APP_GPS_MonitorTask(void const* argument);

/* Exported functions --------------------------------------------------------*/
void APP_GPS_Init(void)
{
    BSP_GPS_Init();
}

void APP_GPS_InitTasks(void)
{
    osThreadDef(GPSMonitorTask, APP_GPS_MonitorTask, osPriorityNormal, 0, 256);
    GPSMonitorTaskHandle = osThreadCreate(osThread(GPSMonitorTask), NULL);

    osMessageQDef(UARTGprmcQueue, GPS_BUFFER_LENGTH, GPSData);
    UARTGprmcQueueHandle = osMessageCreate(osMessageQ(UARTGprmcQueue), NULL);
}

void APP_GPS_BufferGPSString(char* dataString, size_t dataLength)
{
    GPSData* data;
    data = osPoolAlloc(GPSDataPool);
    memcpy(data->raw, dataString, dataLength);
    osMessagePut(UARTGprmcQueueHandle, (uint32_t)data, 0);
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Function implementing the APP_GPS_MonitorTask thread.
  *         Monitors incoming GPS data.
  * @param  argument: Not used
  * @retval None
  */
void APP_GPS_MonitorTask(void const* argument)
{
    uint8_t usbTxCnt = 0;
    osEvent event;
    GPSData* data;

    for (;;) {
        // Pend on GPS data sent via UART
        event = osMessageGet(UARTGprmcQueueHandle, 0);
        if (event.status == osEventMessage) {
            data = event.value.p;
            // TODO: BO: Moving around configurations, fix this
            //if (mAppConfiguration.SDStorage == APP_ENABLE) {
            if (1) {
                // Write data to SD card
                APP_FATFS_LogSD((const uint8_t*)data->raw, 128, gpsLogIdentifier);
            }

            usbTxCnt = 0;
            while (APP_USB_Transmit((uint8_t*)data->raw, GPS_USB_DATA_SZ_BYTES) == 1) {
                // USB TX State is BUSY. Wait for it to be free.
                osDelay(1);
                if (++usbTxCnt >= GPS_USB_TX_MAX_TRY) {
                    break;
                }
            }
            osPoolFree(GPSDataPool, data);
        }
        osDelay(1);
    }
}
