/**
  ******************************************************************************
  * @file    stm32302c_custom.h
  * @author  Mark Griffith
  * @brief   This file contains definitions for STM32302c_CUSTOM's Leds, push-buttons
  *          and COM port hardware resources.
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32302C_CUSTOM_H
#define __STM32302C_CUSTOM_H

#ifdef __cplusplus
 extern "C" {
#endif
  
#include "stm32f3xx_hal.h"

extern UART_HandleTypeDef huart;

/**
 * @brief LED Types Definition
 */
typedef enum
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  /* Color led aliases */
  LED_GREEN  = LED1,    
  LED_BLUE   = LED2,
  LED_RED    = LED3
}Led_TypeDef;

/**
 * @brief BUTTON Types Definition
 */
typedef enum
{
  BUTTON_LOG  = 0,
  BUTTON_MARK = 1,
  BUTTON_RST  = 2
}Button_TypeDef;

typedef enum
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef;

/**
 * @brief LEDs Config
 */
#define LEDn                             3

#define LED1_PIN                         GPIO_PIN_8 // PA.08
#define LED1_GPIO_PORT                   GPIOA
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()
  
#define LED2_PIN                         GPIO_PIN_9 // PA.09
#define LED2_GPIO_PORT                   GPIOA
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()
  
#define LED3_PIN                         GPIO_PIN_15 // PB.15
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

#define LEDx_GPIO_CLK_ENABLE(__LED__)    do { if ((__LED__) == LED1) LED1_GPIO_CLK_ENABLE(); else\
                                              if ((__LED__) == LED2) LED2_GPIO_CLK_ENABLE(); else\
                                              if ((__LED__) == LED3) LED3_GPIO_CLK_ENABLE();} while(0)

#define LEDx_GPIO_CLK_DISABLE(__LED__)   (((__LED__) == LED1) ? LED1_GPIO_CLK_DISABLE() :\
                                          ((__LED__) == LED2) ? LED2_GPIO_CLK_DISABLE() :\
                                          ((__LED__) == LED3) ? LED3_GPIO_CLK_DISABLE() : 0 )

/**
 * @brief Push Buttons Config
 * Note: the push buttons all share the same interrupt line.
 *       This external line interrupt is also used for the
 *       SD Detect pin
 */
#define BUTTONn                          3

#define LOG_BUTTON_PIN                   GPIO_PIN_14 // PB.14
#define LOG_BUTTON_GPIO_PORT             GPIOB
#define LOG_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define LOG_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define LOG_BUTTON_EXTI_IRQn             EXTI9_5_IRQn

#define MARK_BUTTON_PIN                   GPIO_PIN_13 // PB.13
#define MARK_BUTTON_GPIO_PORT             GPIOB
#define MARK_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define MARK_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define MARK_BUTTON_EXTI_IRQn             EXTI9_5_IRQn

#define RST_BUTTON_PIN                   GPIO_PIN_12 // PB.12
#define RST_BUTTON_GPIO_PORT             GPIOB
#define RST_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define RST_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define RST_BUTTON_EXTI_IRQn             EXTI9_5_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__BUTTON__)     do { if ((__BUTTON__) == BUTTON_LOG) LOG_BUTTON_GPIO_CLK_ENABLE(); else\
                                                     if ((__BUTTON__) == BUTTON_MARK) MARK_BUTTON_GPIO_CLK_ENABLE(); else\
                                                     if ((__BUTTON__) == BUTTON_RST) RST_BUTTON_GPIO_CLK_ENABLE();} while(0)

#define BUTTONx_GPIO_CLK_DISABLE(__BUTTON__)    (((__BUTTON__) == BUTTON_LOG) ? LOG_BUTTON_GPIO_CLK_DISABLE() :\
                                                 ((__BUTTON__) == BUTTON_MARK) ? MARK_BUTTON_GPIO_CLK_DISABLE() :\
                                                 ((__BUTTON__) == BUTTON_RST) ? RST_BUTTON_GPIO_CLK_DISABLE() : 0 )

#if defined(HAL_UART_MODULE_ENABLED)

/**
 * @brief Definition for GPS COM port, connected to USART2
 */ 
#define GPS_UARTx                        USART2
#define GPS_UARTx_CLK_ENABLE()           __HAL_RCC_USART2_CLK_ENABLE()
#define GPS_UARTx_CLK_DISABLE()          __HAL_RCC_USART2_CLK_DISABLE()

#define GPS_UARTx_TX_PIN                GPIO_PIN_2 // PA.02
#define GPS_UARTx_TX_GPIO_PORT          GPIOA
#define GPS_UARTx_TX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define GPS_UARTx_TX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
#define GPS_UARTx_TX_AF                 GPIO_AF7_USART2

#define GPS_UARTx_RX_PIN                GPIO_PIN_3 // PA.03
#define GPS_UARTx_RX_GPIO_PORT          GPIOA
#define GPS_UARTx_RX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define GPS_UARTx_RX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
#define GPS_UARTx_RX_AF                 GPIO_AF7_USART2

#define GPS_UARTx_BAUD                  9600
   
#define GPS_UARTx_IRQn                  USART2_IRQn

#endif /* HAL_UART_MODULE_ENABLED */

#if defined(HAL_SPI_MODULE_ENABLED)
/**
  * @brief  Definition for SPI Interface pins (SPI1 used)
  */
#define CUSTOM_SPIx                               SPI1
#define CUSTOM_SPIx_CLK_ENABLE()                  __HAL_RCC_SPI1_CLK_ENABLE()
#define CUSTOM_SPIx_CLK_DISABLE()                 __HAL_RCC_SPI1_CLK_DISABLE()
#define CUSTOM_SPIx_FORCE_RESET()                 __HAL_RCC_SPI1_FORCE_RESET()
#define CUSTOM_SPIx_RELEASE_RESET()               __HAL_RCC_SPI1_RELEASE_RESET()

#define CUSTOM_SPIx_SCK_AF                        GPIO_AF5_SPI1
#define CUSTOM_SPIx_SCK_GPIO_PORT                 GPIOA
#define CUSTOM_SPIx_SCK_PIN                       GPIO_PIN_5
#define CUSTOM_SPIx_SCK_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
#define CUSTOM_SPIx_SCK_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOA_CLK_DISABLE()

#define CUSTOM_SPIx_MISO_MOSI_AF                  GPIO_AF5_SPI1
#define CUSTOM_SPIx_MISO_MOSI_GPIO_PORT           GPIOA
#define CUSTOM_SPIx_MISO_MOSI_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define CUSTOM_SPIx_MISO_MOSI_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOA_CLK_DISABLE()
#define CUSTOM_SPIx_MISO_PIN                      GPIO_PIN_6
#define CUSTOM_SPIx_MOSI_PIN                      GPIO_PIN_7

/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define CUSTOM_SPIx_TIMEOUT_MAX                   1000

#endif /* HAL_SPI_MODULE_ENABLED */

/*##################### SD ###################################*/
/* Chip Select macro definition */
#define SD_CS_LOW()  HAL_GPIO_WritePin(SD_CS_GPIO_PORT, SD_CS_PIN, GPIO_PIN_RESET)
#define SD_CS_HIGH() HAL_GPIO_WritePin(SD_CS_GPIO_PORT, SD_CS_PIN, GPIO_PIN_SET)

/**
  * @brief SD card Control pins
  */
#define SD_CS_PIN                         GPIO_PIN_0 // PB.00
#define SD_CS_GPIO_PORT                   GPIOB
#define SD_CS_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define SD_CS_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()

/**
  * @brief  SD Detect Interface pins
  */
#define SD_DETECT_PIN                     GPIO_PIN_1 // PB.01
#define SD_DETECT_GPIO_PORT               GPIOB
#define SD_DETECT_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define SD_DETECT_GPIO_CLK_DISABLE()      __HAL_RCC_GPIOB_CLK_DISABLE()
#define SD_DETECT_EXTI_IRQn               EXTI9_5_IRQn

void     BSP_LED_Init(Led_TypeDef Led);
void     BSP_LED_On(Led_TypeDef Led);
void     BSP_LED_Off(Led_TypeDef Led);
void     BSP_LED_Toggle(Led_TypeDef Led);
void     BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t BSP_PB_GetState(Button_TypeDef Button);

#ifdef __cplusplus
}
#endif

#endif /* __H */
