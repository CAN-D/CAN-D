/**
  ******************************************************************************
  * File Name          : RTC.h
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __rtc_H
#define __rtc_H
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

extern RTC_HandleTypeDef hrtc;

void APP_RTC_Init(void);

#ifdef __cplusplus
}
#endif
#endif /*__ rtc_H */
