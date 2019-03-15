/**
  ******************************************************************************
  * File Name          : gps.h
  * Description        : This file provides code for dealing with GPS data.
  ******************************************************************************
  */

#ifndef GPS_H_
#define GPS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define GPS_DATA_LENGTH 128
#define GPS_LOG_FILENAME "GPS_Data"

void APP_GPS_Init(void);
void APP_GPS_InitTasks(void);
void APP_GPS_BufferGPSString(char* dataString, size_t dataLength);

#ifdef __cplusplus
}
#endif
#endif /* GPS_H_ */
