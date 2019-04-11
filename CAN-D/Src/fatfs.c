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

#define FINAL_DEMO

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define SD_PATH_LEN 4

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
FRESULT resSD; /* Return value for SD */
char SDPath[SD_PATH_LEN]; /* SD logical drive path */
FATFS SDFatFS; /* File system object for SD logical drive */
FIL SDFile; /* File object for SD */
static uint8_t SDInitialized = 0; /* Keeps track of if the SD card is initialized or not */
static uint16_t sessionCount = 0; /* 0 if no session started */
static uint16_t prevSessionCount = 0;
static uint32_t lineNumber = 0; /* Number of messages written to the SD card */
/* Private function prototypes -----------------------------------------------*/
static FRESULT APP_FATFS_RemoveFile(const char* file, size_t size);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Removes all of the log files in the root directory
  *         of the SD card.
  */
static FRESULT APP_FATFS_RemoveFile(const char* file, size_t size)
{
    FRESULT ret = FR_OK;
#if !defined(FINAL_DEMO)
    char path[SD_PATH_LEN + size];

    // get the path to our SD drive
    path[0] = SDPath[0];
    path[1] = SDPath[1];
    path[2] = SDPath[2];
    path[3] = SDPath[3];

    ret = f_mount(&SDFatFS, (TCHAR const*)SDPath, FATFS_FORCED_MOUNTING);
    if (ret == FR_OK) {
        // Remove file if it exists
        strcat(path, file);
        ret = f_unlink((const TCHAR*)path);
    }
    f_mount(NULL, 0, 0);
#endif // FINAL_DEMO

    return ret;
}

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  FatFS Init Function
  * @retval None
  */
void APP_FATFS_Init(void)
{
    // Link the SD driver
    resSD = FATFS_LinkDriver(&SD_Driver, SDPath);

#if defined(FATFS_FORMAT_SD)
    if (f_mount(&SDFatFS, (TCHAR const*)SDPath, FATFS_FORCED_MOUNTING) == FR_OK) {
        // Create a FAT file system on the SD card (format the card)
        // This deletes all content on the device
        if (f_mkfs((TCHAR const*)SDPath, 0, 0) != FR_OK) {
            /* FatFs Format Error */
            Error_Handler();
        }
    }
#endif // FATFS_FORMAT_SD

    // Remove all log files
    APP_FATFS_RemoveFile(CAN_LOG_FILENAME, sizeof(CAN_LOG_FILENAME));
    APP_FATFS_RemoveFile(GPS_LOG_FILENAME, sizeof(GPS_LOG_FILENAME));
    APP_FATFS_RemoveFile(MARK_LOG_FILENAME, sizeof(MARK_LOG_FILENAME));

    SDInitialized = 1;
}

/**
  * @brief  FatFS DeInit Function
  * @retval None
  */
void APP_FATFS_Deinit(void)
{
    f_mount(NULL, 0, 0); // Unmount
    FATFS_UnLinkDriver(SDPath); // Unlink the SD Driver
    SDInitialized = 0;
}

/**
  * @brief  Toggles the Log Session
  * @retval None
  */
void APP_FATFS_ToggleSession(void)
{
    if (sessionCount == 0)
        APP_FATFS_StartSession();
    else
        APP_FATFS_StopSession();
}

/**
  * @brief  Starts the Log Session
  * @retval None
  */
void APP_FATFS_StartSession(void)
{
    sessionCount = 1;
    BSP_LED_On(LED2);
}

/**
  * @brief  Stops the Log Session. 
  *         Calls to APP_FATFS_LogSD() will do nothing.
  * @retval None
  */
void APP_FATFS_StopSession(void)
{
    prevSessionCount = sessionCount;
    sessionCount = 0;
    BSP_LED_Off(LED2);
}

/**
  * @brief  Gets the number of log entries for the
  *         current logging session
  * @retval lineNumber: number of entries in logs
  */
uint32_t APP_FATFS_GetLineCount(void)
{
    return lineNumber;
}

/**
  * @brief  Writes a buffer to the SD Card based on a Peripheral Idfentifier String
  * @param  writeData: buffer containing the data to write
  * @param  bytes: Number of bytes in writeData buffer
  * @param  periphIdentifier: Peripheral Idfentifier String
  *         Can be one of @defgroup FATFS_Peripher_Identifiers
  * @retval writtenBytes: The number of bytes written to the SD card
  */
uint8_t APP_FATFS_LogSD(const uint8_t* writeData, uint32_t bytes, char* periphIdentifier)
{
    uint8_t writtenBytes = 0;

    // Check that we have started a session
    if (sessionCount == 0) {
        return 0;
    }

    if (strcmp(periphIdentifier, CAN_LOG_IDENTIFIER) == 0) {
        writtenBytes = APP_FATFS_WriteSD(writeData, bytes, (const char*)CAN_LOG_FILENAME);
        if (writtenBytes == bytes) {
            // Successful write. Increment the number of messages written
            // to the SD Card.
            lineNumber++;
        }
    } else if (strcmp(periphIdentifier, GPS_LOG_IDENTIFIER) == 0) {
        writtenBytes = APP_FATFS_WriteSD(writeData, bytes, (const char*)GPS_LOG_FILENAME);
    } else if (strcmp(periphIdentifier, MARK_LOG_IDENTIFIER) == 0) {
        writtenBytes = APP_FATFS_WriteSD(writeData, bytes, (const char*)MARK_LOG_FILENAME);
    }

    return writtenBytes;
}

/**
  * @brief  Writes a buffer to the SD Card
  * @param  writeData: buffer containing the data to write
  * @param  bytes: Number of bytes in writeData buffer
  * @param  filename: Name of the file to write to 
  * @retval writtenBytes: The number of bytes written to the SD card
  */
uint8_t APP_FATFS_WriteSD(const uint8_t* writeData, uint32_t bytes, const char* filename)
{
    uint32_t writtenBytes = 0;

#if !defined(FINAL_DEMO)
    if (BSP_SD_IsDetected() == SD_PRESENT) {
        // If the SD card was ejected but is now detected
        if (SDInitialized == 0) {
            APP_FATFS_Init();
        }
        if (f_mount(&SDFatFS, (TCHAR const*)SDPath, FATFS_FORCED_MOUNTING) == FR_OK) {
            // Open the file for writing. Create new file if it doesn't exist
            if ((f_open(&SDFile, filename, FA_WRITE | FA_OPEN_ALWAYS)) == FR_OK) {
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
#endif // FINAL_DEMO

    return writtenBytes;
}
