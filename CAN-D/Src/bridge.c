/**
  ******************************************************************************
  * File Name          : bridge.c
  * Description        : This file provides code for bridging peripheral
  *                      instances
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bridge.h"
#include "fatfs.h"
#include "stm32302c_custom.h"
#include "stm32f3xx_hal_gpio.h"
#include "usbd_cdc_if.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Function implementing the APP_BRIDGE_GPSMonitorTask thread.
  *         Monitors incoming GPS data.
  * @param  argument: Not used
  * @retval None
  */
void APP_BRIDGE_GPSMonitorTask(void const* argument)
{
    osEvent event;

    for (;;) {
        // Pend on GPS data sent via UART
        event = osMessageGet(UARTGprmcQueueHandle, 0);
        if (event.status == osEventMessage) {
            // TODO: BO: Moving around configurations, fix this
            //if (mAppConfiguration.SDStorage == APP_ENABLE) {
            if (1) {
                // Write data to SD card
                APP_FATFS_WriteSD((const uint8_t*)event.value.p, 128, "GPS_data.log");
            }
            // TODO: BO: Moving around configurations, fix this
            //if (mAppConfiguration.USBStream == APP_ENABLE) {
            if (1) {
                // Fill the USB TX buffer with the GPS data
                while (CDC_Transmit_FS((uint8_t*)event.value.p, (uint16_t)128) == 1) {
                    // USB TX State is BUSY. Wait for it to be free.
                }
            }
        }

        osDelay(1);
    }
}

/* Private functions ---------------------------------------------------------*/