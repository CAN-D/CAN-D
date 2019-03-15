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

extern FRESULT resSD; /* Return value for SD */
extern char SDPath[4]; /* USER logical drive path */
extern FATFS SDFatFS; /* File system object for SD logical drive */
extern FIL SDFile; /* File object for SD card */

void APP_FATFS_Init(void);
char* APP_FATFS_GetUniqueFilename(char* filename);
void APP_FATFS_Deinit(void);
uint8_t APP_FATFS_WriteSD(const uint8_t* writeData, uint32_t bytes, const char* fileName);

#ifdef __cplusplus
}
#endif
#endif /*__fatfs_H */
