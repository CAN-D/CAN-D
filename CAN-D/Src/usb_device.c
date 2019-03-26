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

/**
  * Makes the USB device forget any previous connections such that
  * calling APP_USB_DEVICE_Init() will re-do the enumeration procedure.
  * @retval None
  */
void APP_USB_ForceEnumeration(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_USB;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
    HAL_Delay(500);
}

/* Private functions ---------------------------------------------------------*/
