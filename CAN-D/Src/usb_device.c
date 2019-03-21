/**
  ******************************************************************************
  * @file           : usb_device.c
  * @brief          : This file implements the USB Device
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usb_device.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#include "usbd_core.h"
#include "usbd_desc.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
USBD_HandleTypeDef hUsbDeviceFS;

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/* USB Device Core handle declaration. */
/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void APP_USB_DEVICE_Init(void)
{
    /* Init Device Library, add supported class and start the library. */
    USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);

    USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC);

    USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);

    USBD_Start(&hUsbDeviceFS);
}

/* Private functions ---------------------------------------------------------*/
