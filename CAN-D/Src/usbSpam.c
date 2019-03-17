/**
  ******************************************************************************
  * File Name          : usbSpam.c
  * Description        : This file spam the USB interface with data.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbSpam.h"
#include "cmsis_os.h"
#include "usbd_cdc_if.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Threads */
static osThreadId USBSpamTaskHandle;

/* Private macro -------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void APP_USBSpam_SpamTask(void const* argument);

/* Exported functions --------------------------------------------------------*/
void APP_USBSpam_InitTasks(void)
{
    osThreadDef(USBSpamTask, APP_USBSpam_SpamTask, osPriorityNormal, 0, 128);
    USBSpamTaskHandle = osThreadCreate(osThread(USBSpamTask), NULL);
}

/* Private functions ---------------------------------------------------------*/
void APP_USBSpam_SpamTask(void const* argument)
{
    for (;;) {
        uint8_t adata[] = "TEST\r\n";
        while (CDC_Transmit_FS(adata, (uint16_t)7) == 1) {
            osDelay(1);
        }
        osDelay(1000);
    }
}
