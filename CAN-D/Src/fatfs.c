/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fatfs.h"
#include "cmsis_os.h"
#include "stm32302c_custom_sd.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
FRESULT resSD; /* Return value for SD */
char SDPath[4]; /* SD logical drive path */
FATFS SDFatFS; /* File system object for SD logical drive */
FIL SDFile; /* File object for SD */
static uint8_t SDInitialized = 0; /* Keeps track of if the SD card is initialized or not */
static uint16_t sessionCount = 0; /* 0 if no session started */
static uint16_t prevSessionCount = 0;
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void APP_FATFS_Init(void)
{
    // Link the SD driver
    resSD = FATFS_LinkDriver(&SD_Driver, SDPath);
    SDInitialized = 1;
}

void APP_FATFS_Deinit(void)
{
    f_mount(NULL, 0, 0); // Unmount
    FATFS_UnLinkDriver(SDPath); // Unlink the SD Driver
    SDInitialized = 0;
}

void APP_FATFS_StartSession(void)
{
    FILINFO fno;
    char toAppend[4]; // Temp buf
    char filename[] = "CAN_Data";
    uint16_t appendCount = prevSessionCount;

    if (sessionCount == 0) {
        // Only generate a unique filename if SD Card is present
        if (BSP_SD_IsDetected() == SD_PRESENT) {
            strcat(filename, "_");
            while (appendCount < 9999) {
                appendCount++;
                sprintf(toAppend, "%d", appendCount);
                strcat(filename, toAppend);
                strcat(filename, ".log");
                if (f_stat(filename, &fno) != FR_OK) {
                    // File already exists.
                    filename[strlen(filename) - 5] = '\0'; // Remove "appendCount.log"
                } else {
                    // Filename is unique. Found our new session count.
                    sessionCount = appendCount;
                    break;
                }
            }
        } else { // SD not detected
            sessionCount = 0;
        }
    }
}

void APP_FATFS_StopSession(void)
{
    prevSessionCount = sessionCount;
    sessionCount = 0;
}

uint8_t APP_FATFS_LogSD(const uint8_t* writeData, uint32_t bytes, char* periphIdentifier)
{
    char uniqueID[4];

    // Check that we have started a session
    if (sessionCount == 0) {
        return 0;
    }

    sprintf(uniqueID, "%d", sessionCount);
    strcat(periphIdentifier, uniqueID);
    strcat(periphIdentifier, ".log");

    return APP_FATFS_WriteSD(writeData, bytes, (const char*)periphIdentifier);
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

    if (BSP_SD_IsDetected() == SD_PRESENT) {
        // If the SD card was ejected but is now detected
        if (SDInitialized == 0) {
            APP_FATFS_Init();
        }
        if (f_mount(&SDFatFS, (TCHAR const*)SDPath, FATFS_FORCED_MOUNTING) == FR_OK) {
            // Open the file for writing. Create new file if it doesn't exist
            if ((f_open(&SDFile, fileName, FA_WRITE | FA_OPEN_ALWAYS)) == FR_OK) {
                // Move the write pointer to the end of the file (append)
                if (f_lseek(&SDFile, f_size(&SDFile)) == FR_OK) {
                    f_write(&SDFile, writeData, bytes, (void*)&writtenBytes);
                    f_close(&SDFile);
                }
            }
        }
        f_mount(NULL, 0, 0);
    } else if (SDInitialized == 1) {
        APP_FATFS_Deinit();
    }

    return writtenBytes;
}

/* Private functions ---------------------------------------------------------*/
