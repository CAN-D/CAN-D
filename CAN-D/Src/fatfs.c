/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  */

#include "fatfs.h"

uint8_t retUSER;    /* Return value for USER */
char USERPath[4];   /* USER logical drive path */
FATFS USERFatFS;    /* File system object for USER logical drive */
FIL USERFile;       /* File object for USER */

void MX_FATFS_Init(void) 
{
  /*## FatFS: Link the SD driver ###########################*/
  retUSER = FATFS_LinkDriver(&SD_Driver, USERPath);
}
