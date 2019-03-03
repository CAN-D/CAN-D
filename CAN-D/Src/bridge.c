/**
  ******************************************************************************
  * File Name          : bridge.c
  * Description        : This file provides code for bridging peripheral
  *                      instances
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bridge.h"
#include "can.h"
#include "fatfs.h"
#include "stm32302c_custom.h"
#include "stm32f3xx_hal_gpio.h"
#include "usbd_cdc_if.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
APP_ConfigType mAppConfiguration = { 0 };
extern osPoolId CANTxPool;

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void APP_CAN_Init(void)
{
    mAppConfiguration.SDStorage = APP_DISABLE;
    mAppConfiguration.USBStream = APP_DISABLE;
    mAppConfiguration.USBTransfer = APP_DISABLE;
    mAppConfiguration.CANTransmit = APP_DISABLE;
}

/**
  * @brief  Function implementing the APP_BRIDGE_CANConfigTask thread.
  * @param  argument: Not used
  * @retval None
  */
void APP_BRIDGE_CANConfigTask(void const* argument)
{
    for (;;) {
        // Start/Stop the CAN module on button press
        if (BSP_PB_GetState(BUTTON_LOG) == GPIO_PIN_SET) {
            APP_CAN_StartStop();
        }

        osDelay(1);
    }
}

/**
  * @brief  Function implementing the APP_BRIDGE_CANMonitorTask thread.
  *         Monitors incoming CAN data.
  * @retval None
  */
void APP_BRIDGE_CANMonitorTask(void const* argument)
{
    osEvent event;

    for (;;) {
        // Pend on any CAN Rx data
        event = osMessageGet(CANRxQueueHandle, 0);
        if (event.status == osEventMessage) {
            if (mAppConfiguration.SDStorage == APP_ENABLE) {
                // Write data to SD card
                APP_FATFS_WriteSD((const uint8_t*)event.value.p, 8, "CAN_data.log");
            }
            if (mAppConfiguration.USBStream == APP_ENABLE) {
                // Fill the USB TX buffer with the CAN data
                while (CDC_Transmit_FS((uint8_t*)event.value.p, (uint16_t)8) == 1) {
                    // USB TX State is BUSY. Wait for it to be free.
                }
            }
        }

        osDelay(1);
    }
}

/**
  * @brief  Function implementing the APP_BRIDGE_CANTransmitTask thread.
  *         Send outgoing CAN data.
  * @retval None
  */
void APP_BRIDGE_CANTransmitTask(void const* argument)
{
    osEvent event;
    CANTxMessage* msg;
    uint32_t mailbox;

    for (;;) {
        // Pend on any CAN Tx data
        event = osMessageGet(CANTxQueueHandle, 0);
        if (event.status == osEventMessage) {
            msg = event.value.p;
            if (mAppConfiguration.CANTransmit == APP_ENABLE) {
                if (HAL_CAN_GetTxMailboxesFreeLevel(msg->handle) > 0) {
                    /* Default to sending on MAILBOX0 */
                    mailbox = CAN_TX_MAILBOX0;
                    /* Check Tx Mailbox 1 status */
                    if ((msg->handle->Instance->TSR & CAN_TSR_TME1) != 0U) {
                        mailbox = CAN_TX_MAILBOX1;
                    }
                    /* Check Tx Mailbox 2 status */
                    else if ((msg->handle->Instance->TSR & CAN_TSR_TME2) != 0U) {
                        mailbox = CAN_TX_MAILBOX2;
                    }
                    HAL_CAN_AddTxMessage(msg->handle, msg->header, msg->data, (uint32_t*)mailbox);
                } else {
                    // Dropped a message!
                }
            }
            osPoolFree(CANTxPool, msg);
        }

        osDelay(1);
    }
}

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
            if (mAppConfiguration.SDStorage == APP_ENABLE) {
                // Write data to SD card
                APP_FATFS_WriteSD((const uint8_t*)event.value.p, 128, "GPS_data.log");
            }
            if (mAppConfiguration.USBStream == APP_ENABLE) {
                // Fill the USB TX buffer with the GPS data
                while (CDC_Transmit_FS((uint8_t*)event.value.p, (uint16_t)128) == 1) {
                    // USB TX State is BUSY. Wait for it to be free.
                }
            }
        }

        osDelay(1);
    }
}

/**
  * @brief  Sets the APP Configuration
  * @param  newConfig: the configuration to set
  * @retval None
  */
void APP_CAN_SetConfiguration(APP_ConfigType newConfig)
{
    mAppConfiguration = newConfig;
}

/* Private functions ---------------------------------------------------------*/