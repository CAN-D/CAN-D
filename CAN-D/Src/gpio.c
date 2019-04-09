/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  *                      Configure GPIO pins as 
  *                         Analog 
  *                         Input 
  *                         Output
  *                         EVENT_OUT
  *                         EXTI
  *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  This function initializes all GPIIO clock sources
  * @retval None
  */
void APP_GPIO_Init(void)
{
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}

/* Private functions ---------------------------------------------------------*/