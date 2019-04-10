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

/* Define this to format the SD Card as FatFS Filesystem */
// #define FATFS_FORMAT_SD

#define FATFS_NO_FORCED_MOUNTING 0
#define FATFS_FORCED_MOUNTING 1

/* @defgroup FATFS_Peripher_Identifiers */
#define CAN_LOG_IDENTIFIER "CANData"
#define GPS_LOG_IDENTIFIER "GPSData"
#define MARK_LOG_IDENTIFIER "MARKData"

#define CAN_LOG_FILENAME "CANData.log"
#define GPS_LOG_FILENAME "GPSData.log"
#define MARK_LOG_FILENAME "MARKData.log"

extern FRESULT resSD; /* Return value for SD */
extern char SDPath[4]; /* USER logical drive path */
extern FATFS SDFatFS; /* File system object for SD logical drive */
extern FIL SDFile; /* File object for SD card */

void APP_FATFS_Init(void);
void APP_FATFS_Deinit(void);
void APP_FATFS_ToggleSession(void);
void APP_FATFS_StartSession(void);
void APP_FATFS_StopSession(void);
uint32_t APP_FATFS_GetLineCount(void);
uint8_t APP_FATFS_LogSD(const uint8_t* writeData, uint32_t bytes, char* periphIdentifier);
uint8_t APP_FATFS_WriteSD(const uint8_t* writeData, uint32_t bytes, const char* fileName);

#ifdef __cplusplus
}
#endif
#endif /*__fatfs_H */
