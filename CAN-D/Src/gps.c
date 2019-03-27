/**
  ******************************************************************************
  * File Name          : gps.c
  * Description        : This file provides code for dealing with gps data.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gps.h"
#include "fatfs.h"
#include "proto_handler.h"
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
    GPSData gpsRx = { 0 };
    volatile uint8_t usbTxCnt = 0;
    osEvent event;
    GPSData* gpsRxMsg = &gpsRx;
    size_t usbMaxMsgLen = GPS_USB_DATA_SZ_BYTES + 10; // Max length of the serialized data
    uint8_t usbTxMsg[usbMaxMsgLen]; // Serialized (packaged) protobuf data
    FromEmbedded fromEmbeddedMsg = FromEmbedded_init_zero;

    for (;;) {
        fromEmbeddedMsg.contents.gpsDataChunk.size = 128;
        fromEmbeddedMsg.which_contents = 2;
        memcpy(fromEmbeddedMsg.contents.gpsDataChunk.bytes, gpsRxMsg->raw, GPS_USB_DATA_SZ_BYTES);
        APP_PROTO_HANDLE_bufferFromEmbeddedMsg(&fromEmbeddedMsg, (uint8_t*)usbTxMsg, usbMaxMsgLen);

        usbTxCnt = 0;
        while (APP_USB_Transmit((uint8_t*)usbTxMsg, GPS_USB_DATA_SZ_BYTES) == 1) {
            // USB TX State is BUSY. Wait for it to be free.
            osDelay(1);
            if (++usbTxCnt >= GPS_USB_TX_MAX_TRY) {
                usbTxCnt = 0;
                break;
            }
        }
        // Pend on GPS data sent via UART
        event = osMessageGet(UARTGprmcQueueHandle, 0);
        if (event.status == osEventMessage) {
            gpsRxMsg = event.value.p;
            // TODO: BO: Moving around configurations, fix this
            //if (mAppConfiguration.SDStorage == APP_ENABLE) {
            if (1) {
                // Write data to SD card
                APP_FATFS_LogSD((const uint8_t*)gpsRxMsg->raw, GPS_SD_DATA_SZ_BYTES, gpsLogIdentifier);
            }

            // Construct FromEmbedded protobuf message
            fromEmbeddedMsg.contents.canDataChunk.size = 128;
            fromEmbeddedMsg.which_contents = 2;
            memcpy(fromEmbeddedMsg.contents.gpsDataChunk.bytes, (uint8_t*)gpsRxMsg->raw, GPS_USB_DATA_SZ_BYTES);
            APP_PROTO_HANDLE_bufferFromEmbeddedMsg(&fromEmbeddedMsg, (uint8_t*)usbTxMsg, usbMaxMsgLen);

            usbTxCnt = 0;
            while (APP_USB_Transmit((uint8_t*)usbTxMsg, GPS_USB_DATA_SZ_BYTES) == 1) {
                // USB TX State is BUSY. Wait for it to be free.
                osDelay(1);
                if (++usbTxCnt >= GPS_USB_TX_MAX_TRY) {
                    break;
                }
            }
            osPoolFree(GPSDataPool, gpsRxMsg);
        }
        osDelay(1);
    }
}
