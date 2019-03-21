/**
  ******************************************************************************
  * @file           : usb_device.h
  * @brief          : Header for usb_device.c file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DEVICE__H__
#define __USB_DEVICE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f3xx.h"
#include "stm32f3xx_hal.h"
#include "usbd_def.h"

/** USB Device initialization function. */
void APP_USB_DEVICE_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEVICE__H__ */
