/**
  ******************************************************************************
  * File Name          : CAN.h
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __can_H
#define __can_H
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define CAN_RX_FIFO_0 ((uint32_t)0)
#define CAN_RX_FIFO_1 ((uint32_t)1)
#define CAN_RXQ_TIMEOUT_MS ((uint32_t)250) /* Timeout when waiting on the can RX queue*/
#define CAN_IT_START CAN_IT_RX_FIFO0_FULL | CAN_IT_RX_FIFO1_FULL | CAN_IT_ERROR /* Interrupts to be enabled on CAN start */

typedef struct {
    CAN_HandleTypeDef* handle;
    CAN_TxHeaderTypeDef* header;
    uint8_t* data;
} CANTxMessage;

typedef struct {
    CAN_HandleTypeDef* handle;
    CAN_RxHeaderTypeDef* header;
    uint8_t* data;
} CANRxMessage;

typedef struct
{
    APP_ConfigurationState SDStorage; /* Store CAN Data on SD Card */
    APP_ConfigurationState USBStream; /* Transfer all SD Card data to PC via USB */
    APP_ConfigurationState USBTransfer; /* Transfer CAN Data directly to USB Device */
    APP_ConfigurationState CANTransmit; /* Transmit data over the CAN bus */
} APP_ConfigType;

extern CAN_HandleTypeDef hcan;

void MX_CAN_Init(void);
void APP_CAN_InitTasks(void);
void APP_CAN_StartStop(void);
void APP_CAN_SetConfiguration(APP_ConfigType newConfig);

#ifdef __cplusplus
}
#endif
#endif /*__ can_H */
