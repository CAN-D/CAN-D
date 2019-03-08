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
#include "stm32f3xx_hal_gpio.h"
#include "usbd_cdc_if.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct {
    char raw[128];
} GPSData;

/* Private define ------------------------------------------------------------*/
#define GPS_BUFFER_LENGTH 2

/* Private variables ---------------------------------------------------------*/
uint8_t UartRxCplt = 0;
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
void APP_GPS_InitTasks(void)
{
    osThreadDef(GPSMonitorTask, APP_GPS_MonitorTask, osPriorityNormal, 0, 128);
    if ((GPSMonitorTaskHandle = osThreadCreate(osThread(GPSMonitorTask), NULL)) == NULL)
        Error_Handler();

    osMessageQDef(UARTGprmcQueue, GPS_BUFFER_LENGTH, GPSData);
    if ((UARTGprmcQueueHandle = osMessageCreate(osMessageQ(UARTGprmcQueue), NULL)) == NULL)
        Error_Handler();
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
    // osEvent event;
    // GPSData* dataGPS;
    uint8_t rxBuffer[10];

    for (;;) {
        // Pend on GPS data sent via UART
        // event = osMessageGet(UARTGprmcQueueHandle, 0);
        // if (event.status == osEventMessage) {
        //     dataGPS = event.value.p;
        //     // TODO: BO: Moving around configurations, fix this
        //     //if (mAppConfiguration.SDStorage == APP_ENABLE) {
        //     if (1) {
        //         // Write data to SD card
        //         // APP_FATFS_WriteSD((const uint8_t*)dataGPS->raw, 128, "GPSData.log");
        //     }
        //     // TODO: BO: Moving around configurations, fix this
        //     //if (mAppConfiguration.USBStream == APP_ENABLE) {
        //     if (1) {
        //         // Fill the USB TX buffer with the GPS data
        //         while (CDC_Transmit_FS((uint8_t*)dataGPS->raw, (uint16_t)128) == 1) {
        //             // USB TX State is BUSY. Wait for it to be free.
        //         }
        //     }
        //     osPoolFree(GPSDataPool, dataGPS);
        // }

        if (UartRxCplt == 1) {
            while (CDC_Transmit_FS(huart.pRxBuffPtr, (uint16_t)10) == 1) {
                // USB TX State is BUSY. Wait for it to be free.
            }
            UartRxCplt = 0;
        } else {
            // Put UART peripheral in reception process
            HAL_UART_Receive_IT(&huart, (uint8_t*)rxBuffer, 10);
        }

        osDelay(1);
    }
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* UartHandle)
{
    // char rxData[128] = "0";
    // uint8_t rx_idx = 0;

    // // Read the data from the register
    // rxData[rx_idx] = *huart.pRxBuffPtr;

    // The GPS RX data will be held between '$' and '\n' characters
    // TODO: BO: This is demo specific code
    // if (rxData[rx_idx] == '$') {
    // if (1) {
    // TODO: BO: This is demo specific code
    // if (strncmp("$GPRMC", rxData, sizeof("$GPRMC") - 1) == 0)
    //     APP_GPS_BufferGPSString(rxData, GPS_DATA_LENGTH);
    // APP_GPS_BufferGPSString((char*)huart.pRxBuffPtr, GPS_DATA_LENGTH);

    // memset(rxData, 0, sizeof(rxData));
    // }
    UartRxCplt = 1;
}
