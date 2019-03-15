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
static char gpsLogFilename[] = GPS_LOG_FILENAME;
static char* gpsUniqueLogFilename = GPS_LOG_FILENAME;
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

    // Create a unique log filename for each new new session
    gpsUniqueLogFilename = APP_FATFS_GetUniqueFilename(gpsLogFilename);
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
    osEvent event;
    GPSData* data;

    for (;;) {
       const uint8_t adata[] = "YELLOW";
       APP_FATFS_WriteSD(adata, 6, (const char*)gpsUniqueLogFilename);

        // Pend on GPS data sent via UART
        event = osMessageGet(UARTGprmcQueueHandle, 0);
        if (event.status == osEventMessage) {
            data = event.value.p;
            // TODO: BO: Moving around configurations, fix this
            //if (mAppConfiguration.SDStorage == APP_ENABLE) {
            if (1) {
                // Write data to SD card
                APP_FATFS_WriteSD((const uint8_t*)data->raw, 128, gpsUniqueLogFilename);
            }
            // TODO: BO: Moving around configurations, fix this
            //if (mAppConfiguration.USBStream == APP_ENABLE) {
            if (1) {
                // Fill the USB TX buffer with the GPS data
                while (CDC_Transmit_FS((uint8_t*)data->raw, (uint16_t)128) == 1) {
                    // USB TX State is BUSY. Wait for it to be free.
                }
            }
            osPoolFree(GPSDataPool, data);
        }
        osDelay(1);
    }
}
