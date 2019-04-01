/**
  ******************************************************************************
  * @file   fatfs.h
  * @brief  Header for fatfs applications
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __fatfs_H
#define __fatfs_H
#ifdef __cplusplus
extern "C" {
#endif

#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h" /* defines SD_Driver as external */

#define FATFS_NO_FORCED_MOUNTING 0
#define FATFS_FORCED_MOUNTING 1

/* FATFS_Peripher_Identifiers */
#define CAN_LOG_IDENTIFIER "CAN_Data"
#define GPS_LOG_IDENTIFIER "GPS_Data"
#define MARK_LOG_IDENTIFIER "MARK_Data"

#define CAN_LOG_FILENAME "CAN_Data.log"
#define GPS_LOG_FILENAME "GPS_Data.log"
#define MARK_LOG_FILENAME "MARK_Data.log"

extern FRESULT resSD; /* Return value for SD */
extern char SDPath[4]; /* USER logical drive path */
extern FATFS SDFatFS; /* File system object for SD logical drive */
extern FIL SDFile; /* File object for SD card */

void APP_FATFS_Init(void);
void APP_FATFS_Deinit(void);
void APP_FATFS_StartSession(void);
void APP_FATFS_StopSession(void);
uint32_t APP_FATFS_GetLineCount(void);
uint8_t APP_FATFS_LogSD(const uint8_t* writeData, uint32_t bytes, char* periphIdentifier);
uint8_t APP_FATFS_WriteSD(const uint8_t* writeData, uint32_t bytes, const char* fileName);

#ifdef __cplusplus
}
#endif
#endif /*__fatfs_H */
