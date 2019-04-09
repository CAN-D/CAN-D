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

/**
  * @brief  RTC Init Function
  * @retval None
  */
void APP_RTC_Init(void)
{
    RTC_TimeTypeDef sTime = { 0 };
    RTC_DateTypeDef sDate = { 0 };

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

    sTime.Hours = 11;
    sTime.Minutes = 55;
    sTime.Seconds = 0;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
        Error_Handler();
    }
    sDate.WeekDay = RTC_WEEKDAY_THURSDAY;
    sDate.Month = RTC_MONTH_MARCH;
    sDate.Date = 14;
    sDate.Year = 0;

    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK) {
        Error_Handler();
    }
}

/**
  * @brief  Initialize the RTC MSP.
  * @param  hrtc RTC handle  
  * @retval None
  */
void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

    if (rtcHandle->Instance == RTC) {
        /* RTC clock enable */
        __HAL_RCC_RTC_ENABLE();
    }
}

/**
  * @brief  DeInitialize the RTC MSP.
  * @param  hrtc RTC handle 
  * @retval None
  */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

    if (rtcHandle->Instance == RTC) {
        /* Peripheral clock disable */
        __HAL_RCC_RTC_DISABLE();
    }
}

/**
  * @brief  Gets the current UTC Time via the RTC clk
  * @retval UTC Time array [Hours, Minutes, Seconds]
  */
uint8_t* APP_RTC_GetUTCTime(void)
{
    RTC_TimeTypeDef currentTime;
    static uint8_t time[UTC_TIME_STR_LEN];

    HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BCD);

    // Construct UTC Time string (hhmmss)
    time[0] = currentTime.Hours;
    time[1] = currentTime.Minutes;
    time[2] = currentTime.Seconds;

    return time;
}
