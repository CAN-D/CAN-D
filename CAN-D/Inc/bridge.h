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

/* Application configuration */

/* Threads */
osThreadId GPSMonitorTaskHandle;

/* Queues */
osMessageQId UARTGprmcQueueHandle; /* Handles GPS GPRMC data */

/* Pools */

/* RTOS Tasks */
void APP_BRIDGE_GPSMonitorTask(void const* argument);

#ifdef __cplusplus
}
#endif
#endif /* BRIDGE_H_ */
