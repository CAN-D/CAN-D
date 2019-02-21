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
uint8_t retSD; /* Return value for SD */
char SDPath[4]; /* SD logical drive path */
FATFS SDFatFS; /* File system object for SD logical drive */
FIL SDFile; /* File object for SD */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void MX_FATFS_Init(void)
{
    /*## FatFS: Link the SD driver ###########################*/
    retUSER = FATFS_LinkDriver(&SD_Driver, USERPath);
}
/* Private functions ---------------------------------------------------------*/
