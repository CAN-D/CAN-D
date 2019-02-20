/**
  ******************************************************************************
  * File Name          : bridge.c
  * Description        : This file provides code for bridging peripheral
  *                      instances
  ******************************************************************************
  */

#include "bridge.h"
#include "can.h"
#include "usbd_cdc_if.h"
#include "stm32302c_custom.h"
#include "stm32f3xx_hal_gpio.h"

APP_ConfigType mAppConfiguration = {0};

void APP_CAN_Init(void)
{
  mAppConfiguration.SDStorage = APP_DISABLE;
  mAppConfiguration.USBStream = APP_DISABLE;
  mAppConfiguration.USBTransfer = APP_DISABLE;
}

/**
  * @brief  Function implementing the APP_BRIDGE_CANConfigTask thread.
  * @param  argument: Not used
  * @retval None
  */
void APP_BRIDGE_CANConfigTask(void const * argument)
{
  for(;;)
  {
    // Start/Stop the CAN module on button press
   if (BSP_PB_GetState(BUTTON_LOG) == GPIO_PIN_SET)
   {
     APP_CAN_StartStop();
   }

    osDelay(1);
  }
}

/**
  * @brief  Function implementing the APP_BRIDGE_USBStreamTask thread.
  * @param  argument: Not used
  * @retval None
  */
void APP_BRIDGE_USBStreamTask(void const * argument)
{
  osEvent event;

  for(;;)
  {
    // Pend on any CAN data we want to stream to the PC
    event = osMessageGet(USBStreamQueueHandle, 0);
    if (event.status == osEventMessage)
    {
      // Fill the USB TX buffer with the CAN data
      while (CDC_Transmit_FS((uint8_t*)event.value.p, (uint16_t)8) == 1)
      {
        // USB TX State is BUSY. Wait for it to be free.
      }
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
void APP_BRIDGE_GPSMonitorTask(void const * argument)
{
  osEvent event;

  for(;;)
  {
    if (mAppConfiguration.SDStorage == APP_ENABLE)
    {
      // Pend on GPS data sent via UART
      event = osMessageGet(UARTGprmcQueueHandle, 0);
      if (event.status == osEventMessage)
      {
        // Write data to SD card
      }

      event = osMessageGet(UARTGgaQueueHandle, 0);
      if (event.status == osEventMessage)
      {
        // Write data to SD card
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
