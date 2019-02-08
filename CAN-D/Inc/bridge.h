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

#include "main.h"
#include "cmsis_os.h"

/* Application configuration */
typedef struct
{
  uint8_t SDStorage;
  uint8_t USBTransfer;
} APP_ConfigType;

typedef enum
{
  APP_DISABLE = 0,
  APP_ENABLE = 1
} APP_ConfigurationState;

extern APP_ConfigType mAppConfiguration;

void APP_BRIDGE_ConfigTask(void const * argument);
void APP_CAN_SetConfiguration(APP_ConfigType newConfig);

#ifdef __cplusplus
}
#endif
#endif /* BRIDGE_H_ */
