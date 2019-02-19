/**
  ******************************************************************************
  * @file    stm32302c_custom_sd.c
  * @author  Mark Griffith
  * @brief   This file provides a set of functions needed to manage the UART 
  *          FGPMMOPA6H GPS component mounted on the CAN-D custom board.
  *          It implements a high level communication layer for initializing
  *          communicaiton with the GPS peripheral over UART.
  *          The needed STM32F30x hardware resources (UART and 
  *          GPIO) are defined in stm32303c_custom.h file, and the initialization is 
  *          performed in UARTx_Init() function declared in stm32303c_custom.c 
  *          file.
  ******************************************************************************
  */

#include "stm32303c_custom_gps.h"

/**
  * @brief  Initializes the GPS communication.
  * @retval None
  */
void BSP_SD_Init(void)
{ 
  // Configure IO functionalities for UART TX & RX pins
  GPS_IO_Init();

  // Configure GPS to use 1s position echo time
  GPS_IO_WriteString(PMTK_API_SET_FIX_CTL_1HZ);

  // Configure GPS to use 1s update time
  GPS_IO_WriteString(PMTK_SET_NMEA_UPDATE_1HZ);

  // Configure GPS to only output GPRMC and GGA data messages
  USART1_Send(PMTK_SET_NMEA_OUTPUT_RMCGGA);				
}