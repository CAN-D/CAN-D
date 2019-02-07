/**
  ******************************************************************************
  * File Name          : bridge.c
  * Description        : This file provides code for bridging peripheral
  *                      instances
  ******************************************************************************
  */

#include "bridge.h"
#include "can.h"

APP_ConfigType mAppConfiguration = {0};

void APP_CAN_Init(void)
{
  mAppConfiguration.SDStorage = APP_DISABLE;
  mAppConfiguration.USBTransfer = APP_DISABLE;
}

/**
  * @brief  Function implementing the APP_BRIDGE_ConfigTask thread.
  * @param  argument: Not used
  * @retval None
  */
void APP_BRIDGE_ConfigTask(void const * argument)
{
  for(;;)
  {
    // TODO: create BSP pkg for our PCB
    // Start/Stop the CAN module on button press
//    if (BSP_PB_GetState(BUTTON_KEY) == KEY_PRESSED)
//    {
//      APP_CAN_StartStop();
//    }

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
