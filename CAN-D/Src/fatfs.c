/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fatfs.h"
#include "cmsis_os.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
FRESULT resSD; /* Return value for SD */
char SDPath[4]; /* SD logical drive path */
FATFS SDFatFS; /* File system object for SD logical drive */
FIL SDFile; /* File object for SD */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void APP_FATFS_Init(void)
{
    // Link the SD driver
    resSD = FATFS_LinkDriver(&SD_Driver, SDPath);
}

/**
  * @brief  Writes a buffer to the SD Card
  * @param  writeData: buffer containing the data to write
  * @param  bytes: Number of bytes in writeData buffer
  * @param  fileName: Name of the file to write to 
  * @retval writtenBytes: The number of bytes written to the SD card
  */
uint8_t APP_FATFS_WriteSD(const uint8_t* writeData, uint32_t bytes, const char* fileName)
{
    uint32_t writtenBytes = 0;

    // If already mounted, this should return FR_OK
    if (f_mount(&SDFatFS, (TCHAR const*)SDPath, FATFS_FORCED_MOUNTING) == FR_OK) {
        // Open the file for writing. Create new file if it doesn't exist
        // osThreadResumeAll();
        if ((f_open(&SDFile, fileName, FA_WRITE | FA_OPEN_ALWAYS)) == FR_OK) {
            // Move the write pointer to the end of the file (append)
            if (f_lseek(&SDFile, f_size(&SDFile)) == FR_OK) {
                f_write(&SDFile, writeData, bytes, (void*)&writtenBytes);
                f_close(&SDFile);
            }
        }
    }

    return writtenBytes;
}

/* Private functions ---------------------------------------------------------*/
