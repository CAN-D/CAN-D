/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fatfs.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
uint8_t retUSER;  /* Return value for USER */
char USERPath[4]; /* USER logical drive path */
FATFS USERFatFS;  /* File system object for USER logical drive */
FIL USERFile;     /* File object for USER */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void MX_FATFS_Init(void)
{
  /*## FatFS: Link the SD driver ###########################*/
  retUSER = FATFS_LinkDriver(&SD_Driver, USERPath);
}
/* Private functions ---------------------------------------------------------*/
