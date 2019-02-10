/**
  ******************************************************************************
  * @file    stm32302c_custom.h
  * @author  Mark Griffith
  * @brief   This file contains definitions for STM32303C_CUSTOM's Leds, push-buttons
  *          and COM port hardware resources.
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32303C_CUSTOM_H
#define __STM32303C_CUSTOM_H

#ifdef __cplusplus
 extern "C" {
#endif
  
#include "stm32f3xx_hal.h"

/**
 * @brief LED Types Definition
 */
typedef enum
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,
  /* Color led aliases */
  LED_GREEN  = LED1,    
  LED_ORANGE = LED2,
  LED_RED    = LED3,
  LED_BLUE   = LED4
}Led_TypeDef;

/**
 * @brief BUTTON Types Definition
 */
typedef enum 
{
  BUTTON_KEY   = 0,
  BUTTON_SEL   = 1,
  BUTTON_LEFT  = 2,
  BUTTON_RIGHT = 3,
  BUTTON_DOWN  = 4,
  BUTTON_UP    = 5
}Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef;

/**
 * @brief COM Types Definition
 */
typedef enum 
{
  COM1 = 0
}COM_TypeDef;


#define LEDn                             4

#define LED1_PIN                         GPIO_PIN_8 // PA.08
#define LED1_GPIO_PORT                   GPIOA
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()
  
#define LED2_PIN                         GPIO_PIN_9 // PA.09
#define LED2_GPIO_PORT                   GPIOA
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()
  
#define LED3_PIN                         GPIO_PIN_10 // PA.10
#define LED3_GPIO_PORT                   GPIOA
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()
  
#define LED4_PIN                         GPIO_PIN_15 // PB.15
#define LED4_GPIO_PORT                   GPIOB
#define LED4_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED4_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()

#define LEDx_GPIO_CLK_ENABLE(__LED__)    do { if ((__LED__) == LED1) LED1_GPIO_CLK_ENABLE(); else\
                                              if ((__LED__) == LED2) LED2_GPIO_CLK_ENABLE(); else\
                                              if ((__LED__) == LED3) LED3_GPIO_CLK_ENABLE(); else\
                                              if ((__LED__) == LED4) LED4_GPIO_CLK_ENABLE();} while(0)

#define LEDx_GPIO_CLK_DISABLE(__LED__)   (((__LED__) == LED1) ? LED1_GPIO_CLK_DISABLE() :\
                                          ((__LED__) == LED2) ? LED2_GPIO_CLK_DISABLE() :\
                                          ((__LED__) == LED3) ? LED3_GPIO_CLK_DISABLE() :\
                                          ((__LED__) == LED4) ? LED4_GPIO_CLK_DISABLE() : 0 )

#define BUTTONn                          1

/**
 * @brief Key push-button
 */
#define KEY_BUTTON_PIN                   GPIO_PIN_0 // PB.00
#define KEY_BUTTON_GPIO_PORT             GPIOB
#define KEY_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define KEY_BUTTON_EXTI_IRQn             EXTI9_5_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__BUTTON__)     do { if ((__BUTTON__) == BUTTON_KEY) KEY_BUTTON_GPIO_CLK_ENABLE();} while(0)

#define BUTTONx_GPIO_CLK_DISABLE(__BUTTON__)    (((__BUTTON__) == BUTTON_KEY) ? KEY_BUTTON_GPIO_CLK_DISABLE() : 0 )

#if defined(HAL_UART_MODULE_ENABLED)

#define COMn                                    1

/**
 * @brief Definition for COM port1, connected to USART2
 */ 
#define CUSTOM_COM1                               USART2
#define CUSTOM_COM1_CLK_ENABLE()                  __HAL_RCC_USART2_CLK_ENABLE()
#define CUSTOM_COM1_CLK_DISABLE()                 __HAL_RCC_USART2_CLK_DISABLE()

#define CUSTOM_COM1_TX_PIN                        GPIO_PIN_2 // PA.02
#define CUSTOM_COM1_TX_GPIO_PORT                  GPIOA
#define CUSTOM_COM1_TX_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define CUSTOM_COM1_TX_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()
#define CUSTOM_COM1_TX_AF                         GPIO_AF7_USART2

#define CUSTOM_COM1_RX_PIN                        GPIO_PIN_3 // PA.03
#define CUSTOM_COM1_RX_GPIO_PORT                  GPIOA
#define CUSTOM_COM1_RX_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define CUSTOM_COM1_RX_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()
#define CUSTOM_COM1_RX_AF                         GPIO_AF7_USART2
   
#define CUSTOM_COM1_IRQn                          USART2_IRQn

#define COMx_CLK_ENABLE(__INDEX__)                do { if ((__INDEX__) == COM1) CUSTOM_COM1_CLK_ENABLE();} while(0)
#define COMx_CLK_DISABLE(__INDEX__)               (((__INDEX__) == COM1) ? CUSTOM_COM1_CLK_DISABLE() : 0)

#define COMx_TX_GPIO_CLK_ENABLE(__INDEX__)        do { if ((__INDEX__) == COM1) CUSTOM_COM1_TX_GPIO_CLK_ENABLE();} while(0)
#define COMx_TX_GPIO_CLK_DISABLE(__INDEX__)       (((__INDEX__) == COM1) ? CUSTOM_COM1_TX_GPIO_CLK_DISABLE() : 0)

#define COMx_RX_GPIO_CLK_ENABLE(__INDEX__)        do { if ((__INDEX__) == COM1) CUSTOM_COM1_RX_GPIO_CLK_ENABLE();} while(0)
#define COMx_RX_GPIO_CLK_DISABLE(__INDEX__)       (((__INDEX__) == COM1) ? CUSTOM_COM1_RX_GPIO_CLK_DISABLE() : 0)

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
#define SD_CS_LOW()                       HAL_GPIO_WritePin(SD_CS_GPIO_PORT, SD_CS_PIN, GPIO_PIN_RESET)
#define SD_CS_HIGH()                      HAL_GPIO_WritePin(SD_CS_GPIO_PORT, SD_CS_PIN, GPIO_PIN_SET)

/**
  * @brief SD card Control pins
  */
#define SD_CS_PIN                         GPIO_PIN_7 // PB.07
#define SD_CS_GPIO_PORT                   GPIOB
#define SD_CS_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define SD_CS_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()

/**
  * @brief  SD Detect Interface pins
  */
#define SD_DETECT_PIN                     GPIO_PIN_6 // PB.06
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
#if defined(HAL_UART_MODULE_ENABLED)
void     BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef* huart);
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* __H */