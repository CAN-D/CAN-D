/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

RTC_HandleTypeDef hrtc;

/* RTC init function */
void APP_RTC_Init(void)
{
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    if (HAL_RTC_Init(&hrtc) != HAL_OK) {
        Error_Handler();
    }
}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

    if (rtcHandle->Instance == RTC) {
        /* RTC clock enable */
        __HAL_RCC_RTC_ENABLE();
    }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

    if (rtcHandle->Instance == RTC) {
        /* Peripheral clock disable */
        __HAL_RCC_RTC_DISABLE();
    }
}

uint8_t* APP_RTC_GetUTCTime(void)
{
    RTC_TimeTypeDef currentTime;
    RTC_DateTypeDef currentDate;
    static uint8_t time[UTC_TIME_STR_LEN];

    HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

    // Construct UTC Time string (hhmmss.sss)
    time[0] = currentTime.Hours;
    time[1] = currentTime.Minutes;
    time[2] = currentTime.Seconds;

    return time;
}
