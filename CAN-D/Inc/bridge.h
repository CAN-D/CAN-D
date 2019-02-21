/**
  ******************************************************************************
  * File Name          : bridge.h
  * Description        : This file provides code for bridging peripheral
  *                      instances
  ******************************************************************************
  */

#ifndef BRIDGE_H_
#define BRIDGE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "cmsis_os.h"
#include "main.h"

typedef enum {
    APP_DISABLE = 0,
    APP_ENABLE = 1
} APP_ConfigurationState;

/* Application configuration */
typedef struct
{
    APP_ConfigurationState SDStorage; /* Store CAN Data on SD Card */
    APP_ConfigurationState USBStream; /* Transfer all SD Card data to PC via USB */
    APP_ConfigurationState USBTransfer; /* Transfer CAN Data directly to USB Device */
} APP_ConfigType;

APP_ConfigType mAppConfiguration;

/* Threads */
osThreadId bridgeConfigTaskHandle;
osThreadId USBStreamTaskHandle;
osThreadId GPSMonitorTaskHandle;

/* Queues */
osMessageQId USBStreamQueueHandle;
osMessageQId UARTGprmcQueueHandle; /* Handles GPS GPRMC data */

/* RTOS Tasks */
void APP_BRIDGE_CANConfigTask(void const* argument);
void APP_BRIDGE_USBStreamTask(void const* argument);
void APP_BRIDGE_GPSMonitorTask(void const* argument);

void APP_CAN_SetConfiguration(APP_ConfigType newConfig);

#ifdef __cplusplus
}
#endif
#endif /* BRIDGE_H_ */
