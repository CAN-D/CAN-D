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

extern CAN_HandleTypeDef hcan;

void MX_CAN_Init(void);

#ifdef __cplusplus
}
#endif
#endif /*__ can_H */
