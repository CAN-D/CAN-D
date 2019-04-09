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
static char gpsLogIdentifier[] = GPS_LOG_IDENTIFIER;
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

/**
  * @brief  GPS Init Function
  * @retval None
  */
void APP_GPS_Init(void)
{
    BSP_GPS_Init();
}

/**
  * @brief  Initializes RTOS tasks and queues used by the GPS Module
  * @retval None
  */
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

/**
  * @brief Rx Transfer completed callback.
  * @param huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    char rxData[128] = "0";
    uint8_t rx_idx = 0;

    // Read the data from the register
    rxData[rx_idx] = huart->Instance->RDR;

    // The GPS RX data will be held between '$' and '\n' characters
    if (rxData[rx_idx] == '$') {
        if (strncmp("$GPRMC", rxData, sizeof("$GPRMC") - 1) == 0)
            APP_GPS_BufferGPSString(rxData, GPS_DATA_LENGTH);

        memset(rxData, 0, sizeof(rxData));
    }
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
    size_t usbMaxMsgLen = GPS_DATA_SZ_BYTES + PROTO_BUFFER_OVERHEAD; // Max length of the serialized data
    size_t usbTxNumBytes = 0; // Number of bytes in serialized data
    uint8_t usbTxMsg[usbMaxMsgLen]; // Serialized (packaged) protobuf data
    FromEmbedded fromEmbeddedMsg = FromEmbedded_init_zero;

    for (;;) {
        // Pend on GPS data sent via UART
        event = osMessageGet(UARTGprmcQueueHandle, 0);
        if (event.status == osEventMessage) {
            gpsRxMsg = event.value.p;

            // Write data to SD card
            APP_FATFS_LogSD((const uint8_t*)gpsRxMsg->raw, GPS_DATA_SZ_BYTES, gpsLogIdentifier);

            // Pack the protobuf message for USB transfer
            fromEmbeddedMsg.contents.gpsDataChunk.size = GPS_DATA_SZ_BYTES;
            fromEmbeddedMsg.which_contents = FromEmbedded_gpsDataChunk_tag;
            memcpy(fromEmbeddedMsg.contents.gpsDataChunk.bytes, gpsRxMsg->raw, GPS_DATA_SZ_BYTES);
            usbTxNumBytes = APP_PROTO_HANDLE_bufferFromEmbeddedMsg(&fromEmbeddedMsg, (uint8_t*)usbTxMsg, usbMaxMsgLen);

            // Write serialized data to USB
            usbTxCnt = 0;
            while (APP_USB_Transmit((uint8_t*)usbTxMsg, usbTxNumBytes) == USBD_BUSY) {
                // USB TX State is BUSY. Wait for it to be free.
                osDelay(1);
                if (++usbTxCnt >= GPS_USB_TX_MAX_TRY) {
                    usbTxCnt = 0;
                    break;
                }
            }
            osPoolFree(GPSDataPool, gpsRxMsg);
        }
        osDelay(1);
    }
}
