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

extern CAN_HandleTypeDef hcan;

void MX_CAN_Init(void);
void APP_CAN_StartStop(void);

#ifdef __cplusplus
}
#endif
#endif /*__ can_H */
